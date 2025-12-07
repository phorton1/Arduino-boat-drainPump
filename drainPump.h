//----------------------------------------------
// constants for drainPump.ino
//----------------------------------------------

#pragma once

#include <myIOTDevice.h>


//=========================================================
// pins
//=========================================================

#define PIN_PUMP		19		// inverted logic 0=on, 1=off
#define PIN_SENSOR_LOW	33
#define PIN_SENSOR_HIGH	35
#define PIN_SDRIVE		17
#define PIN_LED			16

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

// CONFIGURATION

#define ID_DRAIN_MODE			"DRAIN_MODE"
	// enum: OFF, FORCE, HIGH, or BOTH
	// OFF will turns the pump off
	// FORCE will force the pump ON
	// HIGH/BOTH modes use CHK_INTERVAL to check the sensors and possibly turn the pump ON/OFF
	// HIGH turns the pump on when SENSOR_HIGH is wet and runs it for HIGH_TIME seconds
	// BOTH turns the pump on when SENSOR_HIGH is wet and turns it off when SENSOR_LOW is dry

#define ID_UI_INTERVAL			"UI_INTERVAL"	// int milliseconds; default=1000; min=1000; max=30000 (5 minutes)
	// How often do we update the webUI.
	
#define ID_CHK_INTERVAL			"CHK_INTERVAL"	// int milliseconds; Default=200; min=100; max=30000 (30 seconds)
	// How often do we sample the sensors into the circular buffers, and, if HIGH or BOTH
	// how often we check to turn the pump on or off based on the CONFIGURATION values.

#define ID_NUM_SAMPLES			"NUM_SAMPLES"	// int; default=20, min=1, max=60;
	// The number of samples in the circular buffer.
	// This is coupled with CHK_INTERVAL to determin the actual update frequency for turning the pump ON/OFf.

#define ID_HIGH_THRESH			"HIGH_THRESH"	// int; default=100;  min=0; max=4094;
#define ID_LOW_THRESH			"LOW_THRESH"	// int; default=100;  min=0; max=4094;
	// In HIGH/BOTH modes, the pump is turned on if SENSOR_HIGH (average) is > HIGH_THRESH
	// In BOTH mode the pump is turned off if was turned on at high and the SENSOR_LOW (average is <= LOW_THRESH.

#define ID_HIGH_TIME			"HIGH_TIME"		// int seconds; Default=30; min=10; Max=180 (23 minutes)
	// In HIGH mode this determines how long the pump will run.
	// If the high sensor is still "wet" after this period, thw UI will recieve ERROR_HIGH_CYCLING

#define ID_MAX_TIME				"MAX_TIME"		// int seconds; Default=90; min=30; Max=300	(5 minutes)
	// In BOTH mode the pump will be turned off after this many seconds in case the LOW (SENSOR_LOW) never indicates dry.
	// If this occurs the UI will recieve ERROR_TOO_LONG_BOTH

#define ID_COOLDOWN_TIME		"COOLDOWN_TIME"		// int seconds; Default=30 seconds; Min=10; Max=900 (15 minutes)
	// After a HIGH/BOTH pump run, we will wait this many seconds before begining
	// another HIGH/BOTH pump run.  The counter is cleared when the DRAIN_MODE is changed


// USER INTERFACE

#define ID_CLEAR_ERROR			"CLEAR_ERROR"		// a UI command to clear the error state, if any
#define ID_LED_BRIGHTNESS		"LED_BRIGHTNESS"	// int; Default=32; min=10; max=255
#define ID_HISTORY_LINK     	"HISTORY_LINK"


// STATE

#define ID_STATE_STRING			"STATE_STRING"		// readonly string formatted according to the state upon changes
#define ID_ERROR_CODE			"ERROR_CODE"		// enum; default "", "TOO_LONG"	cleared with clearError() UI command

#define ID_TIME_LAST_RUN    	"TIME_LAST_RUN"		// statistics regarding the last completed run
#define ID_DUR_LAST_RUN     	"DUR_LAST_RUN"
#define ID_SINCE_LAST_RUN   	"SINCE_LAST_RUN"




class drainPump : public myIOTDevice
{
public:

    drainPump() {}
    ~drainPump() {}

	static uint32_t _drain_mode;		// enum
	static int		_ui_interval;		// milliseconds
	static int		_chk_interval;		// milliseconds
	static int		_num_samples;		// int
	static int 		_high_thresh;		// vs average of analog reads
	static int 		_low_thresh;		// vs average of analog reads
	static int		_high_time;			// seconds
	static int		_max_time;			// seconds
	static int		_cooldown_time;		// seconds

	static String 	_state_string;		// built string
 	static uint32_t	_error_code;		// enum
	static int		_led_brightness;	// 1..254
	static String 	_history_link;		// built string

    static time_t   _time_last_run;
    static int      _since_last_run;
    static int      _dur_last_run;

	static void onDrainModeChanged(const myIOTValue *value, uint32_t val);
	static void onBrightnessChanged(const myIOTValue *desc, uint32_t val);
	static void clearError();
    virtual String onCustomLink(const String &path,  const char **mime_type) override;

	void updateUI();
	void handlePump();
	void handlePixels();
	void endRun(time_t time_now);
	int readSensor(int pin, int *avg);
	static void pumpOn(bool on);
	
	// public state variables to drainHistory.pm

	static time_t m_run_start;
	static uint32_t m_error_code;

	// plotting


	virtual bool hasPlot() override    { return true; }

};






extern enumValue errorCodes[];

extern drainPump *drain_pump;





