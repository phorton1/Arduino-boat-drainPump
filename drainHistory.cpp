//-----------------------------------------------------------------------
// drainHistory.cpp
//-----------------------------------------------------------------------
// The drain pump supports two kinds of chart_history.
//		- a chart_history of runs, presented as a simple html text page
//		  This chart_history is small, as the pump only runs 3-5 times a day
//		  so, 50 is enough for about a week.
//		- a chart_history of sensor values and pump on/off for charting
//		  This chart_history is event driven when the levels change by a
//		  certain amount (scaled by 10) and the pump is turned on/off.
//        This chart_history is currently memory based and large enough to
//		  keep approximately 24 hours worth of data for analysis.
//
// HTML Text Entry points:  endRun() and onCustomLink() -> getHTML()
// Chart Entry points: addDrainHistory() and onCustomLink -> methods

#include "drainPump.h"
#include <myIOTLog.h>
#include <myIOTWebServer.h>
#include <myIOTDataLog.h>

#define MAX_HTML_HISTORY		50	// 400 bytes of chart_history;
	// Should be sufficiean for about a week.
	// Note that the head slot is never used
#define NUM_CHART_RECS	4000		// * six bytes per record = 24K
	// The drain pump changes levels rapidly at first and
	// then infrequently.  If scaled by 10 the values should
	// always fit in a byte, and, in fact, we will keep the
	// pump 'on' state in the high order bit of the high_sensor
	// byte (thus limiting it to 0..1270) very reasonable
	// with current values.


//------------------------------------------------------------------------
// HTML History Page
//------------------------------------------------------------------------

#define HIST_FLAG_FORCE			0x8000
	// stuffed into the chart_history error if the run was a force
	// so that we can display it later


typedef struct {
	time_t 		start;		// starting time
	uint16_t 	dur;		// duration cannot be larger than 65534 (like 18 hours)
	uint16_t	err;		// uint32_t error_code enum compressed into a word
}	htmlHistory_t;				// 8 bytes


static uint32_t num_runs;			// 4.4 billion; may be an issue at wrap
static int html_head;
static int html_tail;
static htmlHistory_t html_history[MAX_HTML_HISTORY];


void drainPump::endRun(time_t time_now)
{
	time_t elapsed = time_now - m_run_start;
	LOGD("endRun elapsed(%u)",elapsed);
	setTime(ID_TIME_LAST_RUN,m_run_start);
	setInt(ID_SINCE_LAST_RUN,m_run_start+elapsed);
    setInt(ID_DUR_LAST_RUN,elapsed);

	// add to circular html_history buffer;
	// if head collides with tail, bump the tail by one
	// note that the 'head' slot itself is never valid.
	
	int head = html_head++;
	if (html_head >= MAX_HTML_HISTORY)
		html_head = 0;
	if (html_tail == html_head)
	{
		html_tail++;
		if (html_tail >= MAX_HTML_HISTORY)
			html_tail = 0;
	}
	
	// debugging

	num_runs++;
	uint32_t num_used = html_head - html_tail;
	if (html_tail > html_head)
		num_used = MAX_HTML_HISTORY - html_tail + html_head;
		// == MAX_HTML_HISTORY-1

	LOGD("adding html_history(%u) slot(%u) head(%u) tail(%d) num_used(%u/%u)",
		 num_runs,head,html_head,html_tail,num_used,MAX_HTML_HISTORY);

	htmlHistory_t *hist = &html_history[head];
	hist->start = m_run_start;
	hist->dur   = (uint16_t) elapsed;

	// use the special flag if it was FORCE
	hist->err   = _drain_mode == DRAIN_MODE_FORCE ?
		HIST_FLAG_FORCE : (uint16_t) m_error_code;
		
	m_run_start = 0;
}



static String durString(uint32_t since)
{
	char buf[128] = "&nbsp;";
	int days = since / (24 * 60 * 60);
	int hours = ((since % (24 * 60 * 60)) / (60 * 60)) % 24;
	int minutes = ((since % (24 * 60 * 60 * 60)) / 60) % 60;
	int secs = since % 60;
	if (days)
	{
		sprintf(buf,"%d days  %02d:%02d:%02d",days, hours, minutes, secs);
	}
	else
	{
		sprintf(buf,"%02d:%02d:%02d",hours, minutes, secs);
	}
	return String(buf);
}



static bool sendRecordHTML(int num,time_t time_now,const htmlHistory_t *rec, const htmlHistory_t *prev_rec)
	// Note that the "ago" is since the run ENDED, to be consistent
	// with the interval between runs, which is from when the previous ENDED
	// till the current one STARTED
{
	String text = "";
	String dur = "";

	text += "<tr><td>";
	text += String(num);
	text += "</td><td>";
	text += timeToString(rec->start);
	text += "</td><td align='center'>";
	text += String(rec->dur);
	text += "</td><td>";
	text += durString(time_now - rec->start - rec->dur);	// since it ENDED
	text += "</td><td>";
	if (prev_rec)
	{
		uint32_t since = rec->start - prev_rec->start - prev_rec->dur;
		text += durString(since);
	}
	else
	{
		text += "&nbsp;";
	}
	text += "</td><td align='center'>";
	text += rec->err == HIST_FLAG_FORCE ? "FORCE" : errorCodes[rec->err];
		// write "FORCE" if special flag, otherwise use the error code mapping
	text += "</td></tr>";
	if (!myiot_web_server->writeBinaryData(text.c_str(),text.length()))
		return false;
	return true;
}



static String buildHTML()
	// Only called with at least one valid entry.
	// Head can only be zero if we have wrapped (i.e. whole buffer is full)
	// 	so, if the head happens to be zero, then we start at the end of the array.
	// Start at the one before the head.
	// We pull off the head/tail values in case a run is going on and ends
	// 	while this is called.
	// We are done when we've completed the tail entry.
{
	bool done = false;
	int tail = html_tail;
	int head = html_head;

	uint32_t num_used = head - tail;
	if (tail > head)
		num_used = MAX_HTML_HISTORY - 1;
    LOGD("buildHTML() num_runs(%u) head(%u) tail(%d) num_used(%u/%u)",
		 num_runs,head,tail,num_used,MAX_HTML_HISTORY);

    if (!myiot_web_server->startBinaryResponse("text/html", CONTENT_LENGTH_UNKNOWN))
        return "";

    String text = "<head>\n";
    text += "<title>";
    text += drain_pump->getName();
    text += " History</title>\n";
    text += "<body>\n";
    text += "<style>\n";
    text += "th, td { padding-left: 12px; padding-right: 12px; }\n";
    text += "</style>\n";
	text += "<b>";
	text +=  drain_pump->getName();
	text += " History Items</b><br><br>\n";
	text += "<table border='1' padding='6' style='border-collapse:collapse'>\n";
	text += "<tr><th>num</th><th>time</th><th>dur</th><th>ago</th></th><th>interval</th><th>error</th></tr>\n";
	if (!myiot_web_server->writeBinaryData(text.c_str(),text.length()))
		return "";

	int num = 0;
	int end = head - 1;
	if (end < 0)
		end = MAX_HTML_HISTORY - 1;
	const time_t time_now = time(NULL);
	while (!done)
	{
		const htmlHistory_t *prev_rec = 0;
		const htmlHistory_t *rec = &html_history[end];
		int prev = end == tail ? -2 : end-1;
		if (prev >= -1)
		{
			if (prev == -1)
				prev = MAX_HTML_HISTORY - 1;
			prev_rec = &html_history[prev];
		}

		if (!sendRecordHTML(++num,time_now,rec,prev_rec))
			return "";
		
		if (end == tail)
			done = 1;
		else
		{
			end--;
			if (end < 0)
				end = MAX_HTML_HISTORY - 1;
		}
	}

    text = "</table>";
    text += "</body>\n";
    if (!myiot_web_server->writeBinaryData(text.c_str(),text.length()))
        return "";

    myiot_web_server->finishBinaryResponse();
    LOGD("getHistoryHTML() sent %d records",num);
    return RESPONSE_HANDLED;
}





//------------------------------------------------------------------------
// Chart History
//------------------------------------------------------------------------

#define MAX_LOW  2550
#define MAX_HIGH 1270


extern myIOTDataLog drainPump_datalog;
	// defined in drainPump.ino

typedef struct		// in memory record = 8 bytes per record
{
	uint32_t	dt;
	uint8_t		low;	// low sensor scaled from 0..2550 to 0..255
	uint8_t		high;	// high sensor scaled from 0..1270 to 0..127 with pump state in high bit
} chartHistory_t;


// expanded record matches chart columns
// note that series are drawn in ordeer and
// we want the temperatures on top, so this
// order is reversed from the raw bytes

typedef struct
{
	uint32_t	dt;
	uint32_t	low;		// green
	uint32_t	high;		// blue
	uint32_t	pump;		// red
} sendHistory_t;


static chartHistory_t chart_history[NUM_CHART_RECS];
static volatile int chart_head;
static volatile int chart_tail;

// compressed last values

static uint8_t last_low;
static uint8_t last_high;
static bool	   last_pump_on;


static String series_colors = "[ \"#00ff00\", \"#0000ff\", \"#ff0000\", \"#888888\" ]";



static void addDrainHistoryRec(uint32_t dt, uint8_t low, uint8_t high,  bool pump_on)
{
	int new_head = chart_head + 1;
	if (new_head >= NUM_CHART_RECS)
		new_head = 0;
	if (chart_tail == new_head)
	{
		chart_tail++;
		if (chart_tail >= NUM_CHART_RECS)
			chart_tail = 0;
	}
	chartHistory_t *hist = &chart_history[chart_head];
	hist->dt 	 = dt;
	hist->low 	 = low;
	hist->high 	 = high;
	if (pump_on)
		hist->high |= 0x80;
		
	chart_head = new_head;
	LOGV("addChartHistoryRecord(%d)",chart_head);
}



void addDrainHistory(bool pump_on, int sensor_low, int sensor_high)
	// extern'd in airco.cpp
{
	uint32_t dt = time(NULL);
	uint8_t low = sensor_low / 10;
	uint8_t high = sensor_high / 10;
	if (sensor_low > MAX_LOW)
	{
		LOGE("SENSOR_LOW too high for chart(%d)",sensor_low);
		sensor_low = 255;
	}
	if (sensor_high > MAX_HIGH)
	{
		LOGE("SENSOR_HIGH too high for chart(%d)",sensor_high);
		sensor_high = 127;
	}

	if (pump_on != last_pump_on ||
		low != last_low ||
		high != last_high)
	{
		last_pump_on = pump_on;
		last_low = low;
		last_high = high;
		addDrainHistoryRec(dt,low,high,pump_on);
	}
}


static bool sendOne(uint32_t cutoff, chartHistory_t *in_rec)
{
	if (in_rec->dt >= cutoff)
	{
		sendHistory_t out_rec;
		out_rec.dt = in_rec->dt;
		out_rec.low = in_rec->low * 10;
		out_rec.high = (in_rec->high & 0x7f) * 10;
		out_rec.pump = (in_rec->high & 0x80) ? 1 : 0;
		if (!myiot_web_server->writeBinaryData((const char*)&out_rec, sizeof(sendHistory_t)))
			return false;
	}
	return true;
}


//------------------------------------------------------------------------
// Common onCustomLink method
//------------------------------------------------------------------------


String drainPump::onCustomLink(const String &path,  const char **mime_type)
	// called from myIOTHTTP.cpp::handleRequest()
	// for any paths that start with /custom/
{
	LOGD("drainPump::onCustomLink(%s)",path.c_str());

	// CHART stuff
	
	if (path.startsWith("chart_html/drainData"))
	{
		// only used by drain_chart.html inasmuch as the
		// chart html is baked into the myIOT widget
		int height = myiot_web_server->getArg("height",400);
		int width  = myiot_web_server->getArg("width",800);
		int period = myiot_web_server->getArg("period",7 * 86400);	// week default
		int refresh = myiot_web_server->getArg("refresh",0);
		return drainPump_datalog.getChartHTML(height,width,period,refresh);
	}
	else if (path.startsWith("chart_header/drainData"))
	{
		*mime_type = "application/json";
		return drainPump_datalog.getChartHeader(&series_colors,1);
			// 1 = supports incremental update
	}
	else if (path.startsWith("chart_data/drainData") ||
			 path.startsWith("update_chart_data/drainData"))
	{
		uint32_t cutoff = 0;
		if (path.startsWith("chart_data/drainData"))
		{
			uint32_t secs = myiot_web_server->getArg("secs",0);
			cutoff = time(NULL) - secs;
				// UPDATE means "later than or equal" to dt
		}
		else
		{
			cutoff = myiot_web_server->getArg("since",0) + 1;
				// SINCE means "later than" to dt
		}

		int tail = chart_tail;
		int head = chart_head;

		if (!myiot_web_server->startBinaryResponse("application/octet-stream", CONTENT_LENGTH_UNKNOWN))
			return "";

		if (head < tail)
		{
			while (tail < NUM_CHART_RECS)
			{
				if (!sendOne(cutoff,&chart_history[tail++]))
					return "";
			}
			tail = 0;
		}
		while (tail < head)
		{
			if (!sendOne(cutoff,&chart_history[tail++]))
				return "";
		}

		return RESPONSE_HANDLED;
	}

	// HTML History

    else if (path.startsWith("getHistory"))
	{
 		if (!num_runs)
			return "There is no drainPump chart_history at this time";
		else
			return buildHTML();
	}

	// default (Error)

	else
		return "";

}	// drainPump::onCustomLink()
