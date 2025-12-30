//-----------------------------------------------------------------------
// drainPump.ino
//-----------------------------------------------------------------------
// myIOT device to handle air conditioner condensate pump.
// Foregoes "logging" and "graphing" to produce simple in-memory
// HTML history of the most recent MAX_LOG_RUNS runs.


#include "drainPump.h"
#include <myIOTLog.h>
#include <myIOTDataLog.h>
#include <Adafruit_NeoPixel.h>


//---------------------------------
// static state machine variables
//---------------------------------

#define MAX_SAMPLES		60
	// this MUST jive with the allowed maximum in the UI!!

enum PumpState { PUMP_OFF, PUMP_ON, PUMP_COOLDOWN, PUMP_ILLEGAL };
static const char *pump_state_names[] = { "PUMP_OFF", "PUMP_ON", "COOLDOWN" };

static PumpState pump_state = PUMP_OFF;

static uint32_t last_ui = 0;
static uint32_t last_chk = 0;
static uint32_t pump_start = 0;
static uint32_t cooldown_end = 0;

static int 		pump_on = 0;
static int		high_wet = 0;
static int		low_wet = 0;
static int		low_off = 0;
static int 		sensor_low = 0;
static int 		sensor_high = 0;

static int circ_buf1[MAX_SAMPLES] = {0};
static int circ_buf2[MAX_SAMPLES] = {0};
static int circ_ptr1 = 0;
static int circ_ptr2 = 0;

static PumpState last_pump_state = PUMP_ILLEGAL;
static int 		last_pump_on = -1;
static int		last_high_wet = -1;
static int		last_low_wet = -1;
static int		last_low_off = -1;
static int 		last_sensor_low = -1;
static int 		last_sensor_high = -1;


//----------------------------------
// plotting
//----------------------------------
#if WITH_PLOT
	static const char *plot_legend = "high,low,pump,max";
#endif

//--------------------------------
// pixels
//--------------------------------

#define DEFAULT_LED_BRIGHTNESS	32
#define INITIAL_LED_BRIGHTNESS 	128

#define PIXEL_SYSTEM    0
#define PIXEL_STATE     1
#define NUM_PIXELS		2

#define MY_LED_BLACK    0x000000
#define MY_LED_RED      0x440000
#define MY_LED_GREEN    0x003300
#define MY_LED_BLUE     0x000044
#define MY_LED_CYAN     0x003322
#define MY_LED_YELLOW   0x333300
#define MY_LED_MAGENTA  0x440044
#define MY_LED_WHITE    0x444444
#define MY_LED_ORANGE   0x402200
#define MY_LED_REDMAG   0x400022
#define MY_LED_PURPLE   0x220022
#define MY_LED_BLUECYAN 0x002240

static Adafruit_NeoPixel pixels(NUM_PIXELS,PIN_LED);
static uint32_t last_sys_pixel = MY_LED_BLACK;
static uint32_t last_state_pixel = MY_LED_BLACK;
static bool force_pixels = 0;

static void showPixels()						{pixels.show();}
static void clearPixels()						{pixels.clear();}
static void setPixelsBrightness(int val)		{pixels.setBrightness(val);}
static void setPixel(int num, uint32_t color)	{pixels.setPixelColor(num,color);}


//------------------------------
// myIOT setup
//------------------------------

enumValue drainModes[] = {
	"Off",
	"FORCE",
	"HIGH_ON",
	"LOW_ON",
	"BOTH",
    0};

enumValue errorCodes[] = {
	"",
	"TOO_LONG",
    0};


static valueIdType dash_items[] = {
	ID_DRAIN_MODE,
	ID_STATE_STRING,
	ID_ERROR_CODE,
	ID_CLEAR_ERROR,
    ID_TIME_LAST_RUN,
	ID_SINCE_LAST_RUN,
    ID_DUR_LAST_RUN,
	ID_LED_BRIGHTNESS,
	ID_HISTORY_LINK,
	ID_CHART_LINK,
    0
};

static valueIdType config_items[] = {
	ID_UI_INTERVAL,
    ID_CHK_INTERVAL,
	ID_NUM_SAMPLES,
	ID_HIGH_THRESH,
	ID_LOW_THRESH,
	ID_LOW_OFF_THRESH,
	ID_RUN_TIME,
	ID_MAX_TIME,
	ID_COOLDOWN_TIME,
	0
};


const valDescriptor drain_pump_values[] =
{
    {ID_DEVICE_NAME,	VALUE_TYPE_STRING,	VALUE_STORE_PREF,	VALUE_STYLE_REQUIRED,	NULL,	NULL,	DRAIN_PUMP },
        // override base class element
	{ID_DRAIN_MODE,		VALUE_TYPE_ENUM,	VALUE_STORE_PREF,	VALUE_STYLE_NONE,		(void *) &drainPump::_drain_mode,		(void *) drainPump::onDrainModeChanged, 	{ .enum_range = { 0, drainModes }} },
 	{ID_STATE_STRING,   VALUE_TYPE_STRING,  VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_state_string,    	},
  	{ID_ERROR_CODE,     VALUE_TYPE_ENUM,  	VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_error_code,    	NULL,										{ .enum_range = { 0, errorCodes }} },
	{ID_CLEAR_ERROR,    VALUE_TYPE_COMMAND, VALUE_STORE_SUB,    VALUE_STYLE_NONE,       NULL,                     				(void *) drainPump::clearError },

 	{ID_UI_INTERVAL,  	VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_ui_interval,		NULL,	{ .int_range = {1000,1000,30000}}, 	},
 	{ID_CHK_INTERVAL,  	VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_chk_interval,		NULL,	{ .int_range = {5000,100, 30000}}, 	},
 	{ID_NUM_SAMPLES,  	VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_num_samples,		NULL,	{ .int_range = {5,	 1,   MAX_SAMPLES}}, 	},
 	{ID_HIGH_THRESH,  	VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_high_thresh,		NULL,	{ .int_range = {20,  0,   4094}}, 	},
 	{ID_LOW_THRESH,  	VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_low_thresh,		NULL,	{ .int_range = {500, 0,   4094}}, 	},
 	{ID_LOW_OFF_THRESH, VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_low_off_thresh,	NULL,	{ .int_range = {50,  0,   4094}}, 	},
 	{ID_RUN_TIME,		VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_run_time,			NULL,	{ .int_range = {0,   0,   180}}, 	},
 	{ID_MAX_TIME,		VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_max_time,			NULL,	{ .int_range = {120, 30,  360}}, 	},
 	{ID_COOLDOWN_TIME,  VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_cooldown_time,    NULL,	{ .int_range = {30,  10,  900}}, 	},

	{ID_LED_BRIGHTNESS, VALUE_TYPE_INT, 	VALUE_STORE_PREF,	VALUE_STYLE_NONE,		(void *) &drainPump::_led_brightness,	(void *) drainPump::onBrightnessChanged, { .int_range = { DEFAULT_LED_BRIGHTNESS,  10,  255}} },

    {ID_TIME_LAST_RUN,  VALUE_TYPE_TIME,    VALUE_STORE_PUB,    VALUE_STYLE_READONLY,   (void *) &drainPump::_time_last_run, },
    {ID_SINCE_LAST_RUN, VALUE_TYPE_INT,     VALUE_STORE_PUB,    VALUE_STYLE_HIST_TIME,  (void *) &drainPump::_since_last_run,NULL,   { .int_range = { 0, DEVICE_MIN_INT, DEVICE_MAX_INT}}  },
    {ID_DUR_LAST_RUN,   VALUE_TYPE_INT,     VALUE_STORE_PUB,    VALUE_STYLE_READONLY,   (void *) &drainPump::_dur_last_run,  NULL,   { .int_range = { 0, 0, DEVICE_MAX_INT}}  },
    {ID_HISTORY_LINK,   VALUE_TYPE_STRING,  VALUE_STORE_PUB,    VALUE_STYLE_READONLY,   (void *) &drainPump::_history_link, },
	{ID_CHART_LINK,		VALUE_TYPE_STRING,	VALUE_STORE_PUB,	VALUE_STYLE_READONLY,	(void *) &drainPump::_chart_link, },

};


#define NUM_DRAIN_PUMP_VALUES (sizeof(drain_pump_values)/sizeof(valDescriptor))

//----------------------------------------
// chart stuff
//----------------------------------------
// 2025-12-17 made 4 changes, retaining
// the scaling by 10 and current sampling scheme.
//
//	(a) Only chart upward moves when the pump is off
//  (b) Chart every move when the pump is on
//  (c) Always chart the most current actual point
//  (d) Most difficult: add "since" JS param to ADD
//      only new points since the (the one before) the
//      last one displayed.


extern void addDrainHistory(bool pump_on, int sensor_low, int sensor_high);
	// defined in drainHistory.h

logColumn_t  drain_cols[] = {
	{"low",		LOG_COL_TYPE_UINT32,		200,},
	{"high",	LOG_COL_TYPE_UINT32,		200,},
	{"pump",	LOG_COL_TYPE_UINT32,		1,},
};

myIOTDataLog datalog("drainData",3,drain_cols,0);
	// extern'd in aircoHistory.cpp
	// 0 = debug_send_data level



//----------------------------------------
// vars
//----------------------------------------

drainPump *drain_pump;

uint32_t	drainPump::_drain_mode;
String		drainPump::_state_string;
uint32_t   	drainPump::_error_code = ERROR_ILLEGAL;
int   		drainPump::_ui_interval;
int   		drainPump::_chk_interval;
int   		drainPump::_num_samples;
int   		drainPump::_high_thresh;
int   		drainPump::_low_thresh;
int   		drainPump::_low_off_thresh;
int   		drainPump::_run_time;
int   		drainPump::_max_time;
int   		drainPump::_cooldown_time;
int			drainPump::_led_brightness;
time_t   	drainPump::_time_last_run;
int      	drainPump::_since_last_run;
int      	drainPump::_dur_last_run;
String   	drainPump::_history_link;
String   	drainPump::_chart_link;

time_t 		drainPump::m_run_start;
uint32_t 	drainPump::m_error_code = ERROR_NONE;


//--------------------------------
// main
//--------------------------------

void setup()
{
	drainPump::pumpOn(0);

	setPixelsBrightness(INITIAL_LED_BRIGHTNESS);
	setPixel(PIXEL_SYSTEM,MY_LED_CYAN);
	setPixel(PIXEL_STATE,MY_LED_CYAN);
	showPixels();

	pinMode(PIN_SDRIVE,OUTPUT);
	digitalWrite(PIN_SDRIVE,0);

	pinMode(PIN_SENSOR_LOW,INPUT);
	pinMode(PIN_SENSOR_HIGH,INPUT);

    Serial.begin(MY_IOT_ESP32_CORE == 3 ? 115200 : 921600);
    delay(1000);

    LOGU("drainPump.ino setup() started on core(%d)",xPortGetCoreID());
    drain_pump = new drainPump();
    drain_pump->addValues(drain_pump_values,NUM_DRAIN_PUMP_VALUES);
    drain_pump->setTabLayouts(dash_items,config_items);

    LOGU("calling drain_pump->setup()",0);
	setPixel(PIXEL_STATE,MY_LED_GREEN);
	showPixels();
    drain_pump->setup();

    drain_pump->_history_link = "<a href='/custom/getHistory?uuid=";
    drain_pump->_history_link += drain_pump->getUUID();
    drain_pump->_history_link += "' target='_blank'>History</a>";

#if WITH_PLOT
	drain_pump->setPlotLegend(plot_legend);
#endif

	LOGI("Inititalizing drainPump Chart");
	drain_pump->_chart_link = "<a href='/spiffs/chart.html?uuid=";
	drain_pump->_chart_link += drain_pump->getUUID();
	drain_pump->_chart_link += "' target='_blank'>Chart</a>";

	setPixelsBrightness(drain_pump->_led_brightness);
	setPixel(PIXEL_SYSTEM,MY_LED_BLACK);
	setPixel(PIXEL_STATE,MY_LED_BLACK);
	showPixels();

	LOGU("drainPump.ino setup() finished",0);
}


void loop()
{
    drain_pump->loop();			// handle myIOT device
	drain_pump->handlePump();	// handle device specific behavior
}


//-------------------------------------------
// myIOT implementation
//-------------------------------------------

void drainPump::pumpOn(bool on)
{
	LOGI("pumpON(%d)",on);
	pinMode(PIN_PUMP,OUTPUT);
	digitalWrite(PIN_PUMP,on?0:1);
	if (!on)
		pinMode(PIN_PUMP,INPUT);
			// go to floating state
			// and let 3.3V pullup thru 10K keep it there
	pump_on = on;
}


static void initChange()
{
	// re-initialize state machine on any mode changes

	last_ui = 0;
	last_chk = 0;
	pump_start = 0;
	cooldown_end = 0;

	pump_on = 0;
	high_wet = 0;
	low_wet = 0;
	sensor_low = 0;
	sensor_high = 0;

	// memset(circ_buf1,0,MAX_SAMPLES * sizeof(int));
	// memset(circ_buf2,0,MAX_SAMPLES * sizeof(int));
	// circ_ptr1 = 0;
	// circ_ptr2 = 0;

	last_pump_on = -1;
	last_high_wet = -1;
	last_low_wet = -1;
	last_sensor_low = -1;
	last_sensor_high = -1;

	last_pump_state = PUMP_ILLEGAL;

	drain_pump->_error_code = ERROR_ILLEGAL;
	drain_pump->m_error_code = ERROR_NONE;

	drainPump::pumpOn(0);
	drain_pump->updateUI();
}


void drainPump::onDrainModeChanged(const myIOTValue *value, uint32_t val)
	// called BEFORE the member variable has changed
	// asynchrounous to loop(); since this takes some time,
	// we explicitly set _drain_mode as soon as practicalble
{
	LOGU("onDrainModeChanged(%d)",val);
	if (pump_on)
		drain_pump->endRun(time(NULL));
	drain_pump->_drain_mode = val;
	initChange();
}

void drainPump::onRunTimeChanged(const myIOTValue *value, int val)
{
	LOGU("onDrainModeChanged(%d)",val);
	if (pump_on)
		drain_pump->endRun(time(NULL));
	drain_pump->_run_time = val;
	initChange();
}


void drainPump::onBrightnessChanged(const myIOTValue *desc, uint32_t val)
{
	LOGU("onBrightnessChanged(%d)",val);
	setPixelsBrightness(val);
	force_pixels = 1;
}

void drainPump::clearError()
{
	LOGU("clearError()");
	drain_pump->m_error_code = ERROR_NONE;
	drain_pump->setEnum(ID_ERROR_CODE,ERROR_NONE);
}


void drainPump::updateUI()
{
	if (last_pump_on		!= pump_on		||
		last_high_wet	    != high_wet	    ||
		last_low_wet	    != low_wet	    ||
		last_low_off		!= low_off		||
		last_sensor_low	    != sensor_low	||
		last_sensor_high	!= sensor_high  ||
		last_pump_state	    != pump_state	)
	{
		last_pump_on		= pump_on	     ;
		last_high_wet	    = high_wet	     ;
		last_low_wet	    = low_wet	     ;
		last_low_off		= low_off		 ;
		last_sensor_low	    = sensor_low     ;
		last_sensor_high	= sensor_high    ;
		last_pump_state	    = pump_state     ;

		static char buf[255];
		sprintf(buf,"%s pump_on(%d) low_off=%d low(%d)=%s high(%d)=%s",
			pump_state_names[(int)pump_state],
			pump_on,
			low_off,
			sensor_low,
			(low_wet?"wet":"dry"),
			sensor_high,
			(high_wet?"wet":"dry"));

		setString(ID_STATE_STRING,buf);
	}
	if (m_error_code != _error_code)
		setEnum(ID_ERROR_CODE,m_error_code);
}


void drainPump::handlePixels()
	// system LED:  cyan=booting; green=STA; purple=AP; orange=both; magenta=off/error
	// state LED: green=off; red=on; flashing green=error
{
	#define SYS_FLASH_TIME  250

	uint32_t color_system = MY_LED_MAGENTA;
	if (getBool(ID_WIFI))
	{
		iotConnectStatus_t wifi_mode = getConnectStatus();
		if (wifi_mode == IOT_CONNECT_ALL)
			color_system = MY_LED_ORANGE;
		else if (wifi_mode == IOT_CONNECT_AP)
			color_system = MY_LED_MAGENTA;
		else if (wifi_mode == IOT_CONNECT_STA)
			color_system = MY_LED_GREEN;
	}

	bool changed = 0;
	if (last_sys_pixel != color_system)
	{
		last_sys_pixel = color_system;
		setPixel(PIXEL_SYSTEM,color_system);
		changed = 1;
	}

	uint32_t now = millis();
	static int led_error_code = 0;
	static uint32_t state_blink_time = 0;
	static uint32_t state_blink_on = 0;
	uint32_t color_state = pump_on ? MY_LED_RED : MY_LED_GREEN;

	if (last_state_pixel != color_state ||
		led_error_code != m_error_code)
	{
		last_state_pixel = color_state;
		led_error_code = m_error_code;
		state_blink_time = m_error_code ? SYS_FLASH_TIME : 0;
		setPixel(PIXEL_STATE,color_state);
		state_blink_time = now;
		changed = 1;
	}
	else if (led_error_code && (now - state_blink_time >= SYS_FLASH_TIME))
	{
		state_blink_time = now;
		state_blink_on = !state_blink_on;
		setPixel(PIXEL_STATE,state_blink_on?color_state:MY_LED_BLACK);
		changed = 1;
	}
	if (changed || force_pixels)
	{
		force_pixels = 0;
		showPixels();
	}
}



//-----------------------------------------------------------------------
// handlePump()
//-----------------------------------------------------------------------


void drainPump::handlePump()
{
    uint32_t now = millis();
    time_t time_now = time(NULL);
	static bool update_chart_history = false;

	//------------------------------------------------------
	// let drainHistory.cpp decide on encoding
	//------------------------------------------------------

	if (update_chart_history)
	{
		update_chart_history = false;
		addDrainHistory(pump_on,sensor_low,sensor_high);
	}

    //--------------------------------------
    // Sample sensors on interval
    //--------------------------------------

	#define CHECK_WHILE_ON	 1000
		// while the pump is on we check once per second, period

    if ((pump_on && (now - last_chk >= CHECK_WHILE_ON)) ||
		(!pump_on && (now - last_chk >= _chk_interval))  )
    {
        last_chk = now;
        int high = readSensor(PIN_SENSOR_HIGH,&sensor_high);
		int low = readSensor(PIN_SENSOR_LOW,&sensor_low);
		update_chart_history = true;

		low_wet = sensor_low > _low_thresh ? 1:0;
		high_wet = sensor_high > _high_thresh ? 1:0;
		low_off = sensor_low < _low_off_thresh ? 1:0;

		LOGV("mode(%d) err(%d) on(%d) state(%d) off=%d cur/avg/wet low(%4d,%4d,%d) high(%4d,%4d,%d)",
			 _drain_mode,
			 m_error_code,
			 pump_on,
			 pump_state,
			 low_off,
			 low,
			 sensor_low,
			 low_wet,
			 high,
			 sensor_high,
			 high_wet);

#if WITH_PLOT
		// if myIOTDevice::_plot_data is ON,
		// created and broadcast the json

		if (_plot_data)
		{
			// static const char *plot_legend = "high,low,hwet,lwet,pump,cool,400,0";
			static char plot_buf[255];

			// set a scaling maximum at least 50 above highest value

			int max = 500;
			if (sensor_low+50 > max)
				max = sensor_low + 50;
			if (sensor_high+50 > max)
				max = sensor_high + max;

			sprintf(plot_buf,"{\"plot_data\":[%d,%d,%d,%d]}",
				sensor_high,
				sensor_low,
				pump_on*300,
				max);
			wsBroadcast(plot_buf);
		}
#endif

    }

    //--------------------------------------
    // Periodic UI update
    //--------------------------------------

	if (now - last_ui >= _ui_interval)
	{
        last_ui = now;
        updateUI();
	}


    //--------------------------------------
    // Mode overrides
    //--------------------------------------
	// with short returns (so pixels must be above this)

	handlePixels();
    switch (_drain_mode)
    {
        case DRAIN_MODE_OFF:
            if (pump_on)
            {
				LOGU("PUMP OFF due to DRAIN_MODE_OFF");
                pumpOn(0);
				updateUI();
				update_chart_history = true;
            }
            return;

        case DRAIN_MODE_FORCE:
            if (!pump_on)
            {
				LOGU("PUMP ON due to DRAIN_MODE_FORCE");
                pumpOn(1);
				m_run_start = time_now;
				updateUI();
				update_chart_history = true;
            }
            return;
    }

    //--------------------------------------
    // AUTO state machine
    //--------------------------------------

    switch (pump_state)
    {
        case PUMP_OFF:
			if (low_wet && (						// low sensor wet
				_drain_mode == DRAIN_MODE_LOW ||
				_drain_mode == DRAIN_MODE_BOTH))
            {
				LOGU("PUMP ON LOW");
                pumpOn(1);
                pump_start = now;
                pump_state = PUMP_ON;
				m_run_start = time_now;
				updateUI();
				update_chart_history = true;
            }
            if (high_wet && (						// high sensor wet
				_drain_mode == DRAIN_MODE_HIGH ||
				_drain_mode == DRAIN_MODE_BOTH))
            {
				LOGU("PUMP ON HIGH");
                pumpOn(1);
                pump_start = now;
                pump_state = PUMP_ON;
				m_run_start = time_now;
				updateUI();
				update_chart_history = true;
            }
            break;

        case PUMP_ON:
            if (_run_time)
            {
                if (now - pump_start >= (_run_time * 1000))
                {
					LOGU("PUMP OFF RUN_TIME");
                    pump_state = PUMP_COOLDOWN;
                }
            }
            else if (low_off)
            {
 				LOGU("PUMP OFF LOW_OFF");
                pump_state = PUMP_COOLDOWN;
            }
			else if (now - pump_start >= (_max_time * 1000))
			{
				LOGE("PUMP OFF MAX");
				m_error_code = ERROR_TOO_LONG;
				pump_state = PUMP_COOLDOWN;
			}

			if (pump_state == PUMP_COOLDOWN)
			{
				LOGI("COOLDOWN %d seconds",_cooldown_time);
				pumpOn(0);
                cooldown_end = now + (_cooldown_time * 1000);
				endRun(time_now);
				updateUI();
				update_chart_history = true;
			}
            break;

        case PUMP_COOLDOWN:
            if (now >= cooldown_end)
            {
				LOGU("COOLDOWN time complete");
                pump_state = PUMP_OFF;
				updateUI();
				update_chart_history = true;
            }
            break;
    }
}



//-----------------------------------------------------------------------
// readSensor()
//-----------------------------------------------------------------------
// There is an "issue" with the topology of the PCB.
// Apparently the jumper from the high-input pin that crosses the drive signal
// results in a lower reading (approx 50%) for the high sensor vs the low sensor.
// I *could* have designed the connector differently and avoided that, but it's
// done now.

int drainPump::readSensor(int pin, int *avg)
{
	int val = 0;
	digitalWrite(PIN_SDRIVE, HIGH);         // drive rod to 3.3 V
	delayMicroseconds(1000);                 // excite for 1ms
		// higher delays here lead directly to higher readings.
		// 1000 ms leads to low reading approx 0..1000 and high
		// approx 0..500.

	volatile int tmp = analogRead(pin);     // discard first read
	val = analogRead(pin);                  // keep second read

	digitalWrite(PIN_SDRIVE, LOW);          // stop drive

	int sum = 0;
	if (pin == PIN_SENSOR_LOW)
	{
		circ_buf1[circ_ptr1++ % _num_samples] = val;
		for (int i = 0; i < _num_samples; i++) sum += circ_buf1[i];
	}
	else
	{
		circ_buf2[circ_ptr2++ % _num_samples] = val;
		for (int i = 0; i < _num_samples; i++) sum += circ_buf2[i];
	}

	*avg = sum / _num_samples;  // average (0..4095 for 12-bit ADC)
	return val;
}
