//-----------------------------------------------------------------------
// drainPump.ino
//-----------------------------------------------------------------------
// myIOT device to handle air conditioner condensate pump.
// Foregoes "logging" and "graphing" to produce simple in-memory
// HTML history of the most recent MAX_LOG_RUNS runs.


#include "drainPump.h"
#include <myIOTLog.h>
#include <Adafruit_NeoPixel.h>


//---------------------------------
// static state machine variables
//---------------------------------

#define MAX_SAMPLES		60
	// this MUST jive with the allowed maximum in the UI!!

enum PumpState { PUMP_OFF, PUMP_ON, PUMP_COOLDOWN };

static PumpState pump_state = PUMP_OFF;

static uint32_t last_chk = 0;
static uint32_t last_ui = 0;
static uint32_t pump_start = 0;
static uint32_t cooldown_end = 0;

static bool 	sensor_low = 0;
static bool 	sensor_high = 0;
static bool 	pump_on = 0;

static int circ_buf1[MAX_SAMPLES] = {0};
static int circ_buf2[MAX_SAMPLES] = {0};
static int circ_ptr1 = 0;
static int circ_ptr2 = 0;


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
	"HIGH",
	"BOTH",
    0};

enumValue errorCodes[] = {
	"",
	"TOO_LONG_BOTH",
	"HIGH_CYCLING",
    0};


static valueIdType dash_items[] = {
	ID_DRAIN_MODE,
	ID_ERROR_CODE,
	ID_CLEAR_ERROR,

	ID_PUMP_ON,
	ID_SENSOR_HIGH,
	ID_SENSOR_LOW,

	ID_HISTORY_LINK,

    ID_TIME_LAST_RUN,
	ID_SINCE_LAST_RUN,
    ID_DUR_LAST_RUN,

	ID_LED_BRIGHTNESS,
    0
};


static valueIdType config_items[] = {
	ID_UI_INTERVAL,
    ID_CHK_INTERVAL,
	ID_NUM_SAMPLES,
	ID_HIGH_TIME,
	ID_MAX_TIME,
	ID_COOLDOWN_TIME,

	0
};

const valDescriptor drain_pump_values[] =
{
    {ID_DEVICE_NAME,	VALUE_TYPE_STRING,	VALUE_STORE_PREF,	VALUE_STYLE_REQUIRED,	NULL,	NULL,	DRAIN_PUMP },
        // override base class element
	{ID_DRAIN_MODE,		VALUE_TYPE_ENUM,	VALUE_STORE_PREF,	VALUE_STYLE_NONE,		(void *) &drainPump::_drain_mode,		(void *) drainPump::onDrainModeChanged, 	{ .enum_range = { 0, drainModes }} },
 	{ID_ERROR_CODE,     VALUE_TYPE_ENUM,  	VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_error_code,    	NULL,										{ .enum_range = { 0, errorCodes }} },
	{ID_CLEAR_ERROR,    VALUE_TYPE_COMMAND, VALUE_STORE_SUB,    VALUE_STYLE_NONE,       NULL,                     				(void *) drainPump::clearError },

 	{ID_PUMP_ON,     	VALUE_TYPE_BOOL,  	VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_pump_on,    		},
 	{ID_SENSOR_HIGH,    VALUE_TYPE_BOOL,  	VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_sensor_high,    	},
 	{ID_SENSOR_LOW,    	VALUE_TYPE_BOOL,  	VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_sensor_low,    	},

 	{ID_UI_INTERVAL,  	VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_ui_interval,		NULL,	{ .int_range = {1000,1000,30000}}, 	},
 	{ID_CHK_INTERVAL,  	VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_chk_interval,		NULL,	{ .int_range = {200, 100, 30000}}, 	},
 	{ID_NUM_SAMPLES,  	VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_num_samples,		NULL,	{ .int_range = {20,	 1,   MAX_SAMPLES}}, 	},
 	{ID_HIGH_TIME,		VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_high_time,		NULL,	{ .int_range = {30,  10,  180}}, 	},
 	{ID_MAX_TIME,		VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_max_time,			NULL,	{ .int_range = {90,  30,  300}}, 	},
 	{ID_COOLDOWN_TIME,  VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_cooldown_time,    NULL,	{ .int_range = {30,  10,  900}}, 	},

	{ID_LED_BRIGHTNESS, VALUE_TYPE_INT, 	VALUE_STORE_PREF,	VALUE_STYLE_NONE,		(void *) &drainPump::_led_brightness,	(void *) drainPump::onBrightnessChanged, { .int_range = { DEFAULT_LED_BRIGHTNESS,  10,  255}} },

    {ID_TIME_LAST_RUN,  VALUE_TYPE_TIME,    VALUE_STORE_PUB,    VALUE_STYLE_READONLY,   (void *) &drainPump::_time_last_run, },
    {ID_SINCE_LAST_RUN, VALUE_TYPE_INT,     VALUE_STORE_PUB,    VALUE_STYLE_HIST_TIME,  (void *) &drainPump::_since_last_run,NULL,   { .int_range = { 0, DEVICE_MIN_INT, DEVICE_MAX_INT}}  },
    {ID_DUR_LAST_RUN,   VALUE_TYPE_INT,     VALUE_STORE_PUB,    VALUE_STYLE_READONLY,   (void *) &drainPump::_dur_last_run,  NULL,   { .int_range = { 0, 0, DEVICE_MAX_INT}}  },
    {ID_HISTORY_LINK,   VALUE_TYPE_STRING,  VALUE_STORE_PUB,    VALUE_STYLE_READONLY,   (void *) &drainPump::_history_link, },

};



#define NUM_DRAIN_PUMP_VALUES (sizeof(drain_pump_values)/sizeof(valDescriptor))

drainPump *drain_pump;

uint32_t	drainPump::_drain_mode;
bool   		drainPump::_sensor_low = -1;
bool   		drainPump::_sensor_high = -1;
bool   		drainPump::_pump_on = -1;
uint32_t   	drainPump::_error_code = ERROR_ILLEGAL;
int   		drainPump::_ui_interval;
int   		drainPump::_chk_interval;
int   		drainPump::_num_samples;
int   		drainPump::_high_time;
int   		drainPump::_max_time;
int   		drainPump::_cooldown_time;
int			drainPump::_led_brightness;
time_t   	drainPump::_time_last_run;
int      	drainPump::_since_last_run;
int      	drainPump::_dur_last_run;
String   	drainPump::_history_link;

time_t 		drainPump::m_run_start;
uint32_t 	drainPump::m_error_code = ERROR_NONE;


//--------------------------------
// main
//--------------------------------

void setup()
{
	pinMode(PIN_PUMP,OUTPUT);
	digitalWrite(PIN_PUMP,0);

	setPixelsBrightness(INITIAL_LED_BRIGHTNESS);
	setPixel(PIXEL_SYSTEM,MY_LED_CYAN);
	setPixel(PIXEL_STATE,MY_LED_CYAN);
	showPixels();

	ledcSetup(0, 2000, 1);   	// channel 0, 2 kHz, 1-bit resolution
	ledcAttachPin(PIN_SDRIVE, 0);
	ledcWrite(0, 1);          	// 50% duty (1 of 2 at 1-bit)

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


void drainPump::onDrainModeChanged(const myIOTValue *value, uint32_t val)
	// called BEFORE the member variable has changed
	// asynchrounous to loop(); since this takes some time,
	// we explicitly set _drain_mode as soon as practicalble
{
	LOGU("onDrainModeChanged(%d)",val);
	if (pump_on)
		drain_pump->endRun(time(NULL));
	drain_pump->_drain_mode = val;

	// re-initialize state machine on any mode changes

	drain_pump->_sensor_low = -1;
	drain_pump->_sensor_high = -1;
	drain_pump->_pump_on = -1;
	drain_pump->_error_code = ERROR_ILLEGAL;
	drain_pump->m_error_code = ERROR_NONE;

	memset(circ_buf1,0,MAX_SAMPLES * sizeof(int));
	memset(circ_buf2,0,MAX_SAMPLES * sizeof(int));
	circ_ptr1 = 0;
	circ_ptr2 = 0;

	last_chk = 0;
	last_ui  = 0;
	pump_start = 0;
	cooldown_end = 0;

	sensor_low = 0;
	sensor_high = 0;
	pump_on = 0;
	digitalWrite(PIN_PUMP,0);
	drain_pump->updateUI();
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
	if (sensor_low != _sensor_low)
		setBool(ID_SENSOR_LOW,sensor_low);
	if (sensor_high != _sensor_high)
		setBool(ID_SENSOR_HIGH,sensor_high);
	if (pump_on != _pump_on)
		setBool(ID_PUMP_ON,pump_on);
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

    //--------------------------------------
    // Sample sensors on interval
    //--------------------------------------

    if (now - last_chk >= _chk_interval)
    {
        last_chk = now;
        sensor_low = readSensor(PIN_SENSOR_LOW);
        sensor_high = readSensor(PIN_SENSOR_HIGH);
		LOGV("drain_mode(%d) error(%d) pump_on(%d) pump_state(%d) sensor_low(%d) sensor_high(%d)",
			 _drain_mode,
			 m_error_code,
			 pump_on,
			 pump_state,
			 sensor_low,
			 sensor_high);
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

	drain_pump->handlePixels();
    switch (_drain_mode)
    {
        case DRAIN_MODE_OFF:
            if (pump_on)
            {
				LOGU("PUMP OFF due to DRAIN_MODE_OFF");
                pump_on = false;
                digitalWrite(PIN_PUMP, LOW);
            }
            return;

        case DRAIN_MODE_FORCE:
            if (!pump_on)
            {
				LOGU("PUMP ON due to DRAIN_MODE_FORCE");
                pump_on = true;
                digitalWrite(PIN_PUMP, HIGH);
				drain_pump->m_run_start = time_now;
            }
            return;
    }

    //--------------------------------------
    // AUTO state machine
    //--------------------------------------

    switch (pump_state)
    {
        case PUMP_OFF:
            if (sensor_high)   // high sensor wet
            {
				LOGU("PUMP ON");
                pump_on = true;
                digitalWrite(PIN_PUMP, HIGH);
                pump_start = now;
                pump_state = PUMP_ON;
				drain_pump->m_run_start = time_now;
            }
            break;

        case PUMP_ON:
            if (_drain_mode == DRAIN_MODE_HIGH)
            {
                if (now - pump_start >= (_high_time * 1000))
                {
					LOGU("PUMP OFF (due to HIGH_TIME)");
                    pump_state = PUMP_COOLDOWN;
					if (sensor_high)
					{
						LOGE("HIGH_CYCLING - sensor_high was stil 'wet' when HIGH_TIME was reached");
						m_error_code = ERROR_HIGH_CYCLING;
					}
                }
            }
            else if (_drain_mode == DRAIN_MODE_BOTH)
            {
                if (!sensor_low)   // low sensor dry
                {
					LOGU("PUMP OFF (due to SENSOR_LOW dry)");
                    pump_state = PUMP_COOLDOWN;
                }
                else if (now - pump_start >= (_max_time * 1000))
                {
					LOGE("PUMP OFF (due to MAX_TIME)");
                    m_error_code = ERROR_TOO_LONG_BOTH;
                    pump_state = PUMP_COOLDOWN;
                }
            }
			if (pump_state == PUMP_COOLDOWN)
			{
				LOGI("starting COOLDOWN %d seconds",_cooldown_time);
				pump_on = false;
				digitalWrite(PIN_PUMP, LOW);
                cooldown_end = now + (_cooldown_time * 1000);
				drain_pump->endRun(time_now);
			}
            break;

        case PUMP_COOLDOWN:
            if (now >= cooldown_end)
            {
				LOGU("COOLDOWN time complete");
                pump_state = PUMP_OFF;
            }
            break;
    }
}



//-----------------------------------------------------------------------
// readSensor()
//-----------------------------------------------------------------------
// simple rolling average debounce
// This *should* be set to approximately 1 over CHK_INTERVAL, i.e.
// if check interval is 200ms, then we would average 5 samples to
// get a one second window.


bool drainPump::readSensor(int pin)
{
    int val = digitalRead(pin);

    if (pin == PIN_SENSOR_LOW)
    {
        circ_buf1[circ_ptr1++ % _num_samples] = val;
        int sum = 0;
        for (int i=0; i<_num_samples; i++) sum += circ_buf1[i];
        return (sum > (_num_samples/2));
    }
    else
    {
        circ_buf2[circ_ptr2++ % _num_samples] = val;
        int sum = 0;
        for (int i=0; i<_num_samples; i++) sum += circ_buf2[i];
        return (sum > (_num_samples/2));
    }
}



