//----------------------------------------------
// constants for drainPump.ino
//----------------------------------------------

#pragma once

#define WITH_PLOT	1

#include <myIOTDevice.h>


//=========================================================
// pins
//=========================================================
// Note that the PCB was designed using LOW=gpio34 AND
// HIGH=gpio33, but I thought there was a problem and hand
// modified the PCB to use 34/35 as shown here.
// Turns out the problem was (apparently) coupling from
// the jumper that crosses HIGH over the DRIVE signal,
// which could/should be "fixed" in future revisions of
// the board by making the pins DRIVE,HIGH,LOW, instead of
// HIGH/DRIVE/LOW.

#define PIN_PUMP		17		// inverted logic 0=on, 1=off
#define PIN_SENSOR_LOW	34
#define PIN_SENSOR_HIGH	35
#define PIN_SDRIVE		26
#define PIN_LED			16

//------------------------
// myIOT definition
//------------------------
// The pump can turn on based on two different conditions HIGH or LOW.
// The pump can turn off based on a timer or low>LOW_OFF_THRESH
// There is protection against overly long runs with MAX_TIME.
// There is added hysterisis protection with COOLDOWN_TIME

#define DRAIN_PUMP				"drain_pump"
#define DRAIN_PUMP_VERSION		"dp1.0"
#define DRAIN_PUMP_URL			"https://github.com/phorton1/Arduino-boat-drainPump"

#define DRAIN_MODE_OFF			0
#define DRAIN_MODE_FORCE		1
#define DRAIN_MODE_HIGH			2	// turns on at high>HIGH_THRESH
#define DRAIN_MODE_LOW			3	// turns on at low>LOW_THRESH
#define DRAIN_MODE_BOTH			4	// turn on at either HIGH or LOW

#define ERROR_NONE				0
#define ERROR_TOO_LONG			1	// ran for MAX_TIME seconds waiting for low to go dry
#define ERROR_ILLEGAL			2	// used to force redisplay

// CONFIGURATION

#define ID_DRAIN_MODE			"DRAIN_MODE"

#define ID_UI_INTERVAL			"UI_INTERVAL"	// int milliseconds; default=1000; min=1000; max=30000 (5 minutes)
	// How often do we update the webUI.

#define ID_CHK_INTERVAL			"CHK_INTERVAL"	// int milliseconds; Default=5000; min=100; max=30000 (30 seconds)
	// How often do we sample the sensors into the circular buffers when the pump is off
	// We sense once per second once the pump is on.

#define ID_NUM_SAMPLES			"NUM_SAMPLES"	// int; default=5, min=1, max=60;
	// The number of samples in the circular buffer.
	// This is coupled with CHK_INTERVAL to determine the actual update frequency for turning the pump ON,
	// and the one second fixed interval for turning the pump off

#define ID_HIGH_THRESH			"HIGH_THRESH"		// int; default=20;   min=1; max=4094;
#define ID_LOW_THRESH			"LOW_THRESH"		// int; default=500;  min=1; max=4094;
#define ID_LOW_OFF_THRESH		"LOW_OFF_THRESH"	// int; default=50;	  min=10; max=4094;
	// Thresholds for turning the pump on and off.
	// LOW_OFF_THRESH must be substantially below LOW_THRESH

#define ID_RUN_TIME				"RUN_TIME"				// int seconds; Default=0; min=0; max=180 (3 minutes)
	// If non-zero this will put the pump in "timer" mode where it will turn off after running for
	// this many seconds; If zero the pump will turn off based on LOW_OFF_THRESH.
	// Must be less than MAX_TIME if non-zero

#define ID_MAX_TIME				"MAX_TIME"			// int seconds; Default=120; min=30; Max=360	(6 minutes)
	// In any automatic mode the pump will be turned off after this many seconds in case the LOW (SENSOR_LOW).
	// never indicates dry.

#define ID_COOLDOWN_TIME		"COOLDOWN_TIME"		// int seconds; Default=30 seconds; Min=10; Max=900 (15 minutes)
	// After a HIGH/BOTH pump run, we will wait this many seconds before begining
	// another HIGH/BOTH pump run.  The counter is cleared when the DRAIN_MODE is changed


// USER INTERFACE

#define ID_CLEAR_ERROR			"CLEAR_ERROR"		// a UI command to clear the error state, if any
#define ID_LED_BRIGHTNESS		"LED_BRIGHTNESS"	// int; Default=32; min=10; max=255
#define ID_HISTORY_LINK     	"HISTORY"
#define ID_CHART_LINK			"CHART"


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
	static int		_high_thresh;		// vs average of analog reads
	static int		_low_thresh;		// vs average of analog reads
	static int		_low_off_thresh;	// vs average of analog reads
	static int		_run_time;			// seconds
	static int		_max_time;			// seconds
	static int		_cooldown_time;		// seconds

	static String 	_state_string;		// built string
 	static uint32_t	_error_code;		// enum
	static int		_led_brightness;	// 1..254
	static String 	_history_link;		// built string
	static String 	_chart_link;		// built string

    static time_t   _time_last_run;
    static int      _since_last_run;
    static int      _dur_last_run;

	static void onDrainModeChanged(const myIOTValue *value, uint32_t val);
	static void onRunTimeChanged(const myIOTValue *value, int val);
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

	#if WITH_PLOT
		virtual bool hasPlot() override    { return true; }
	#endif

};






extern enumValue errorCodes[];

extern drainPump *drain_pump;
