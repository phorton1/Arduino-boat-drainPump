//-----------------------------------------------------------------------
// drainHistory.cpp
//-----------------------------------------------------------------------
// Entry points:  endRun() and getHTML()
// Maintains a circular buffer of the history

#include "drainPump.h"
#include <myIOTLog.h>
#include <myIOTWebServer.h>


#define MAX_RUNS		500	// 4K bytes of history; keeps the last 499 runs which should be plenty
	// Note that the head slot is never used

typedef struct {
	time_t 		start;		// starting time
	uint16_t 	dur;		// duration cannot be larger than 65534 (like 18 hours)
	uint16_t	err;		// uint32_t error_code enum compressed into a word
}	history_t;				// 8 bytes


static uint32_t num_runs;			// 4.4 billion; may be an issue at wrap
static int hist_head;
static int hist_tail;
static history_t history[MAX_RUNS];


void drainPump::endRun(time_t time_now)
{
	time_t elapsed = time_now - m_run_start;
	LOGD("endRun elapsed(%u)",elapsed);
	setTime(ID_TIME_LAST_RUN,m_run_start);
	setInt(ID_SINCE_LAST_RUN,m_run_start+elapsed);
    setInt(ID_DUR_LAST_RUN,elapsed);

	// add to circular history buffer;
	// if head collides with tail, bump the tail by one
	// note that the 'head' slot itself is never valid.
	
	int head = hist_head++;
	if (hist_head >= MAX_RUNS)
		hist_head = 0;
	if (hist_tail == hist_head)
	{
		hist_tail++;
		if (hist_tail >= MAX_RUNS)
			hist_tail = 0;
	}
	
	// debugging

	num_runs++;
	uint32_t num_used = hist_head - hist_tail;
	if (hist_tail > hist_head)
		num_used = MAX_RUNS - hist_tail + hist_head;
		// == MAX_RUNS-1

	LOGD("adding history(%u) slot(%u) head(%u) tail(%d) num_used(%u/%u)",
		 num_runs,head,hist_head,hist_tail,num_used,MAX_RUNS);

	history_t *hist = &history[head];
	hist->start = m_run_start;
	hist->dur   = (uint16_t) elapsed;
	hist->err   = (uint16_t) m_error_code;
		
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



static bool sendRecordHTML(int num,time_t time_now,const history_t *rec, const history_t *prev_rec)
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
	text += errorCodes[rec->err];
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
	int tail = hist_tail;
	int head = hist_head;

	uint32_t num_used = head - tail;
	if (tail > head)
		num_used = MAX_RUNS - 1;
    LOGD("buildHTML() num_runs(%u) head(%u) tail(%d) num_used(%u/%u)",
		 num_runs,head,tail,num_used,MAX_RUNS);

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
		end = MAX_RUNS - 1;
	const time_t time_now = time(NULL);
	while (!done)
	{
		const history_t *prev_rec = 0;
		const history_t *rec = &history[end];
		int prev = end == tail ? -2 : end-1;
		if (prev >= -1)
		{
			if (prev == -1)
				prev = MAX_RUNS - 1;
			prev_rec = &history[prev];
		}

		if (!sendRecordHTML(++num,time_now,rec,prev_rec))
			return "";
		
		if (end == tail)
			done = 1;
		else
		{
			end--;
			if (end < 0)
				end = MAX_RUNS - 1;
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




String drainPump::onCustomLink(const String &path,  const char **mime_type)
    // called from myIOTHTTP.cpp::handleRequest()
{
    LOGI("drainPump::onCustomLink(%s)",path.c_str());
    if (path.startsWith("getHistory"))
 		if (!num_runs)
			return "There is no drainPump history at this time";
		else
			return buildHTML();
	else
		return "";
}