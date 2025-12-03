//----------------------------------------------
// constants for drainPump.ino
//----------------------------------------------

#pragma once

#include <myIOTDevice.h>


//=========================================================
// pins
//=========================================================

#define BREADBOARD  	0

#if BREADBOARD
	#define PIN_PUMP		27
	#define PIN_SENSOR_LOW	35
	#define PIN_SENSOR_HIGH	34
	#define PIN_SDRIVE		25
	#define PIN_LED			15
#else
	#define PIN_PUMP		19
	#define PIN_SENSOR_LOW	35
	#define PIN_SENSOR_HIGH	33
	#define PIN_SDRIVE		17
	#define PIN_LED			16
#endif

//------------------------
// myIOT definition
//------------------------
// In the worst case of both sensors constantly reading WET:
// 	in HIGH mode the pump will have a duty cycle of HIGH_TIME on, and COOLDOWN_TIME off;
// 	in LOW mode the pump will have a duty cycle of MAX_TIME on and COOLDOWN_TIME off.
// There is no provision for sensing that the air conditioner is running and the HIGH
//	SENSOR_HIGH never registers as wet.

#define DRAIN_PUMP				"drain_pump"
#define DRAIN_PUMP_VERSION		"dp1.0"
#define DRAIN_PUMP_URL			"https://github.com/phorton1/Arduino-boat-drainPump"


#define DRAIN_MODE_OFF			0
#define DRAIN_MODE_FORCE		1
#define DRAIN_MODE_HIGH			2
#define DRAIN_MODE_BOTH			3

#define ERROR_NONE				0
#define ERROR_TOO_LONG_BOTH		1	// ran for MAX seconds waiting for low to go dry
#define ERROR_HIGH_CYCLING		2	// HIGH sensor was still wet when HIGH_TIME ended
#define ERROR_ILLEGAL			3	// used to force redisplay


#define ID_DRAIN_MODE			"DRAIN_MODE"
	// enum: OFF, FORCE, HIGH, or BOTH
	// OFF will turn the pump off, but will continue logging at LOG_INTERVAL
	// FORCE will force the pump ON will continue logging at LOG_INTERVAL
	// HIGH/BOTH modes use CHK_INTERVAL to check/debounce the sensors and possibly turn the pump ON/OFF
	// HIGH turns the pump on when SENSOR_HIGH is wet and runs it for HIGH_TIME seconds
	// BOTH turns the pump on when SENSOR_HIGH is wet and turns it off when SENSOR_LOW is dry

#define ID_UI_INTERVAL			"UI_INTERVAL"	// int milliseconds; default=1000; min=1000; max=30000 (5 minutes)
	// How often do we update the webUI.
	
#define ID_CHK_INTERVAL			"CHK_INTERVAL"	// int milliseconds; Default=200; min=200; max=30000 (30 seconds)
	// In HIGH/BOTH modes, how often do we add to the circular buffer.
	// This is coupled with NUM_SAMPLES to determine the actual update frequency for turning the pump ON/OFF.
	// The HIGH_TIME and MAX_TIME settings are checked on every loop and not affected by this.
	// The timer is reset when the DRAIN_MODE is changed.

#define ID_NUM_SAMPLES			"NUM_SAMPLES"	// int; default=5, min=1, max=20;
	// The number of samples in the circular buffer.
	// This is coupled with CHK_INTERVAL to determin the actual update frequency for turning the pump ON/OFf.

#define ID_HIGH_TIME			"HIGH_TIME"		// int seconds; Default=12; min=3; Max=120 (2 minutes)
	// In HIGH mode this determines how long the pump will run.

#define ID_MAX_TIME				"MAX_TIME"		// int seconds; Default=30; min=10; Max=150	(2.5 minutes)
	// In BOTH mode the pump will be turned off after this many seconds in case the LOW (SENSOR_LOW) never indicates dry.
	// If this occurs the UI will recieve ERROR=1 and will require the user to use the CLEAR_ERROR button,
	//		or change DRAIN_MODES to remove it from the UI.
	//		However, the error itself will only be logged one time.

#define ID_COOLDOWN_TIME		"COOLDOWN_TIME"		// int seconds; Default=30 seconds; Min=10; Max=900 (15 minutes)
	// After a HIGH/BOTH pump run, we will wait this many seconds before begining
	// another HIGH/BOTH pump run.  The counter is cleared when the DRAIN_MODE is changed


// UI readonly state output variables; these, along with the mode are compressed
// into a single byte for logging along with the date_time for the event

#define ID_SENSOR_LOW			"SENSOR_LOW"	// readonly, 0/1
#define ID_SENSOR_HIGH			"SENSOR_HIGH"	// readonly, 0/1
#define ID_PUMP_ON				"PUMP_ON"		// readonly; 0/1
#define ID_ERROR_CODE			"ERROR_CODE"	// enum; currently "", "TOO_LONG"	cleared with clearError() UI command

#define ID_CLEAR_ERROR			"CLEAR_ERROR"		// a UI command to clear the error state, if any
#define ID_LED_BRIGHTNESS		"LED_BRIGHTNESS"	// int; Default=32; min=10; max=255

// logging

#define ID_TIME_LAST_RUN    "TIME_LAST_RUN"
#define ID_DUR_LAST_RUN     "DUR_LAST_RUN"
#define ID_SINCE_LAST_RUN   "SINCE_LAST_RUN"
#define ID_HISTORY_LINK     "HISTORY_LINK"



class drainPump : public myIOTDevice
{
public:

    drainPump() {}
    ~drainPump() {}

	static uint32_t _drain_mode;		// enum
	static int		_ui_interval;		// milliseconds
	static int		_chk_interval;		// milliseconds
	static int		_num_samples;		// int
	static int		_high_time;			// seconds
	static int		_max_time;			// seconds
	static int		_cooldown_time;		// seconds

	static bool		_sensor_low;		// 0/1
	static bool		_sensor_high;		// 0/1
	static bool		_pump_on;			// 0/1
	static uint32_t	_error_code;		// enum

	static int		_led_brightness;	// 1..254

    static time_t   _time_last_run;
    static int      _since_last_run;   // time_last_run as an int
    static int      _dur_last_run;
    static String 	_history_link;

	static void onDrainModeChanged(const myIOTValue *value, uint32_t val);
	static void onBrightnessChanged(const myIOTValue *desc, uint32_t val);
	static void clearError();

	void updateUI();
	void handlePump();
	void handlePixels();
	void endRun(time_t time_now);
	bool readSensor(int pin);

	// public state variables to drainHistory.pm

	static time_t m_run_start;
	static uint32_t m_error_code;
    virtual String onCustomLink(const String &path,  const char **mime_type) override;

};


extern enumValue errorCodes[];

extern drainPump *drain_pump;





