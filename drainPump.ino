//-----------------------------------------------------------------------
// drainPump.ino
//-----------------------------------------------------------------------
// myIOT device to handle air conditioner condensate pump

#include "drainPump.h"
#include <myIOTLog.h>


// static state machine variables

enum PumpState { PUMP_OFF, PUMP_ON, PUMP_COOLDOWN };

static PumpState pump_state = PUMP_OFF;

static uint32_t last_chk = 0;
static uint32_t last_log = 0;
static uint32_t pump_start = 0;
static uint32_t cooldown_end = 0;

static bool sensor1;
static bool sensor2;
static bool pump_on;
static bool error_code;


//------------------------------
// myIOT setup
//------------------------------

enumValue drainModes[] = {
	"Off",
	"FORCE",
	"HIGH",
	"BOTH",
    0};


static valueIdType dash_items[] = {
	ID_DRAIN_MODE,
	ID_ERROR_CODE,
	ID_CLEAR_ERROR,

	ID_PUMP_ON,
	ID_SENSOR2,
	ID_SENSOR1,

	ID_LOG_INTERVAL,
    ID_CHK_INTERVAL,
	ID_HIGH_TIME,
	ID_MAX_TIME,
	ID_COOLDOWN_TIME,
    0
};


static valueIdType config_items[] = {
	0
};

const valDescriptor drain_pump_values[] =
{
    {ID_DEVICE_NAME,	VALUE_TYPE_STRING,	VALUE_STORE_PREF,	VALUE_STYLE_REQUIRED,	NULL,	NULL,	DRAIN_PUMP },
        // override base class element
	{ID_DRAIN_MODE,		VALUE_TYPE_ENUM,	VALUE_STORE_PREF,	VALUE_STYLE_NONE,		(void *) &drainPump::_drain_mode,		(void *) drainPump::onDrainModeChanged, 	{ .enum_range = { 0, drainModes }} },
 	{ID_ERROR_CODE,     VALUE_TYPE_BOOL,  	VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_error_code,    	},
	{ID_CLEAR_ERROR,    VALUE_TYPE_COMMAND, VALUE_STORE_SUB,    VALUE_STYLE_NONE,       NULL,                     				(void *) drainPump::clearError },


 	{ID_PUMP_ON,     	VALUE_TYPE_BOOL,  	VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_pump_on,    		},
 	{ID_SENSOR2,     	VALUE_TYPE_BOOL,  	VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_sensor2,    		},
 	{ID_SENSOR1,     	VALUE_TYPE_BOOL,  	VALUE_STORE_PUB, 	VALUE_STYLE_READONLY,	(void *) &drainPump::_sensor1,    		},


 	{ID_LOG_INTERVAL,   VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_log_interval,    	NULL,	{ .int_range = {30,  1,  300}}, 	},
 	{ID_CHK_INTERVAL,  	VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_chk_interval,		NULL,	{ .int_range = {1000,200,30000}}, 	},
 	{ID_HIGH_TIME,		VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_high_time,		NULL,	{ .int_range = {12,  3,  120}}, 	},
 	{ID_MAX_TIME,		VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_max_time,			NULL,	{ .int_range = {30,  10, 150}}, 	},
 	{ID_COOLDOWN_TIME,  VALUE_TYPE_INT,  	VALUE_STORE_PREF, 	VALUE_STYLE_NONE,		(void *) &drainPump::_cooldown_time,    NULL,	{ .int_range = {30,  10, 900}}, 	},
};



#define NUM_DRAIN_PUMP_VALUES (sizeof(drain_pump_values)/sizeof(valDescriptor))

drainPump *drain_pump;

uint32_t	drainPump::_drain_mode;
bool   		drainPump::_sensor1;
bool   		drainPump::_sensor2;
bool   		drainPump::_pump_on;
bool   		drainPump::_error_code;
int   		drainPump::_log_interval;
int   		drainPump::_chk_interval;
int   		drainPump::_high_time;
int   		drainPump::_max_time;
int   		drainPump::_cooldown_time;


//--------------------------------
// main
//--------------------------------

void setup()
{
	pinMode(PIN_PUMP,OUTPUT);
	digitalWrite(PIN_PUMP,0);

	if (0)
	{
		pinMode(PIN_SDRIVE,OUTPUT);
		digitalWrite(PIN_SDRIVE,1);
	}
	else
	{
		ledcSetup(0, 2000, 1);   // channel 0, 2 kHz, 1-bit resolution
		ledcAttachPin(PIN_SDRIVE, 0);
		ledcWrite(0, 1);          // 50% duty (1 of 2 at 1-bit)
	}

	// pinMode(PIN_SENSOR1,INPUT);
	pinMode(PIN_SENSOR2,INPUT);

    Serial.begin(MY_IOT_ESP32_CORE == 3 ? 115200 : 921600);
    delay(1000);

    LOGU("drainPump.ino setup() started on core(%d)",xPortGetCoreID());
    drain_pump = new drainPump();
    drain_pump->addValues(drain_pump_values,NUM_DRAIN_PUMP_VALUES);
    drain_pump->setTabLayouts(dash_items,config_items);

    LOGU("calling drain_pump->setup()",0);
    drain_pump->setup();

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
	// called AFTER the member variable has changed
	// asynchrounous to loop()
{
	LOGU("onDrainModeChanged(%d)",val);

	// re-initialize state machine on any mode changes

	drain_pump->_sensor1 = 0;
	drain_pump->_sensor2 = 0;
	drain_pump->_pump_on = 0;
	last_chk = 0;
	last_log = 0;
	cooldown_end = 0;
}


void drainPump::clearError()
{
	LOGU("clearError()");
	drain_pump->setBool(ID_ERROR_CODE,0);
}


void drainPump::updateUI()
{
	if (sensor1 != _sensor1)
		setBool(ID_SENSOR1,sensor1);
	if (sensor2 != _sensor2)
		setBool(ID_SENSOR2,sensor2);
	if (pump_on != _pump_on)
		setBool(ID_PUMP_ON,pump_on);
	if (error_code != _error_code)
		setBool(ID_ERROR_CODE,error_code);
}


void drainPump::updateLog()
{
	// TBD by me
}



//-----------------------------------------------------------------------
// handlePump()
//-----------------------------------------------------------------------

void drainPump::handlePump()
{
    uint32_t now = millis();

    //--------------------------------------
    // Sample sensors on interval
    //--------------------------------------

    if (now - last_chk >= _chk_interval)
    {
        last_chk = now;
        sensor1 = readSensor(PIN_SENSOR1);
        sensor2 = readSensor(PIN_SENSOR2);
		LOGD("drain_mode(%d) error(%d) pump_on(%d) pump_state(%d) sensor1(%d) sensor2(%d)",
			 _drain_mode,
			 error_code,
			 pump_on,
			 pump_state,
			 sensor1,
			 sensor2);
        updateUI();
    }

    //--------------------------------------
    // Periodic logging
    //--------------------------------------

	if (now - last_log >= (_log_interval * 1000))
    {
        last_log = now;
        updateLog();
    }

    //--------------------------------------
    // Mode overrides
    //--------------------------------------

    switch (_drain_mode)
    {
        case DRAIN_MODE_OFF:
            if (pump_on)
            {
				LOGU("PUMP OFF due to DRAIN_MODE_OFF");
                pump_on = false;
                digitalWrite(PIN_PUMP, LOW);
                updateUI();
            }
            return;

        case DRAIN_MODE_FORCE:
            if (!pump_on)
            {
				LOGU("PUMP ON due to DRAIN_MODE_FORCE");
                pump_on = true;
                digitalWrite(PIN_PUMP, HIGH);
                updateUI();
            }
            return;
    }

    //--------------------------------------
    // AUTO state machine
    //--------------------------------------

    switch (pump_state)
    {
        case PUMP_OFF:
            if (sensor2)   // high sensor wet
            {
				LOGU("PUMP ON");
                pump_on = true;
                digitalWrite(PIN_PUMP, HIGH);
                updateUI();
                pump_start = now;
                pump_state = PUMP_ON;
            }
            break;

        case PUMP_ON:
            if (_drain_mode == DRAIN_MODE_HIGH)
            {
                if (now - pump_start >= (_high_time * 1000))
                {
					LOGU("PUMP OFF (due to HIGH_TIME)");
                    pump_state = PUMP_COOLDOWN;
                }
            }
            else if (_drain_mode == DRAIN_MODE_BOTH)
            {
                if (!sensor1)   // low sensor dry
                {
					LOGU("PUMP OFF (due to SENSOR1 dry)");
                    pump_state = PUMP_COOLDOWN;
                }
                else if (now - pump_start >= (_max_time * 1000))
                {
					LOGU("PUMP OFF (due to MAX_TIME)");
                    error_code = true;
                    pump_state = PUMP_COOLDOWN;
                }
            }
			if (pump_state == PUMP_COOLDOWN)
			{
				LOGI("starting COOLDOWN %d seconds",_cooldown_time);
				pump_on = false;
				digitalWrite(PIN_PUMP, LOW);
				updateUI();
                cooldown_end = now + (_cooldown_time * 1000);
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


static bool readSensor(int pin)
{
    const int buf_size = 1;
    static int buf1[buf_size] = {0};
    static int buf2[buf_size] = {0};
    static int ptr1 = 0;
    static int ptr2 = 0;

    int val = digitalRead(pin);

    if (pin == PIN_SENSOR1)
    {
        buf1[ptr1++ % buf_size] = val;
        int sum = 0;
        for (int i=0; i<buf_size; i++) sum += buf1[i];
        return (sum > (buf_size/2));
    }
    else
    {
        buf2[ptr2++ % buf_size] = val;
        int sum = 0;
        for (int i=0; i<buf_size; i++) sum += buf2[i];
        return (sum > (buf_size/2));
    }
}


