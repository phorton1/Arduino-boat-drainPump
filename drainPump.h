//----------------------------------------------
// constants for drainPump.ino
//----------------------------------------------

#pragma once

#include <myIOTDevice.h>


//=========================================================
// pins
//=========================================================

#define PIN_PUMP		27
#define PIN_SENSOR1		35
#define PIN_SENSOR2		34
#define PIN_SDRIVE		25
#define PIN_LED			15


//------------------------
// myIOT definition
//------------------------
// In the worst case of both sensors constantly reading WET:
// 	in HIGH mode the pump will have a duty cycle of HIGH_TIME on, and COOLDOWN_TIME off;
// 	in LOW mode the pump will have a duty cycle of MAX_TIME on and COOLDOWN_TIME off.
// There is no provision for sensing that the air conditioner is running and the HIGH
//	SENSOR2 never registers as wet.

#define DRAIN_PUMP				"drain_pump"
#define DRAIN_PUMP_VERSION		"dp1.0"
#define DRAIN_PUMP_URL			"https://github.com/phorton1/Arduino-boat-drainPump"


#define DRAIN_MODE_OFF			0
#define DRAIN_MODE_FORCE		1
#define DRAIN_MODE_HIGH			2
#define DRAIN_MODE_BOTH			3


#define ID_DRAIN_MODE			"DRAIN_MODE"
	// enum: OFF, FORCE, HIGH, or BOTH
	// OFF will turn the pump off, but will continue logging at LOG_INTERVAL
	// FORCE will force the pump ON will continue logging at LOG_INTERVAL
	// HIGH/BOTH modes use CHK_INTERVAL to check/debounce the sensors and possibly turn the pump ON/OFF
	// HIGH turns the pump on when SENSOR2 is wet and runs it for HIGH_TIME seconds
	// BOTH turns the pump on when SENSOR2 is wet and turns it off when SENSOR1 is dry

#define ID_LOG_INTERVAL			"LOG_INTERVAL"	// int seconds; default=30; min=1; max=300 (5 minutes)
	// How often do we log mode, sensor, and pump states.
	// The frequency vs. ESP32 available memory determines how many log entries can be kept
	// The timer is reset when the DRAIN_MODE is changed.

#define ID_CHK_INTERVAL			"CHK_INTERVAL"	// int milliseconds; Default=1000; min=200; max=30000 (30 seconds)
	// In HIGH/BOTH modes, how often do we check the sensors to turn the pump ON/OFF.
	// This also drives how frequently the UI is updated with state changes.
	// The HIGH_TIME and MAX_TIME settings are checked on every loop and not affected by this.
	// The timer is reset when the DRAIN_MODE is changed.

#define ID_HIGH_TIME			"HIGH_TIME"		// int seconds; Default=12; min=3; Max=120 (2 minutes)
	// In HIGH mode this determines how long the pump will run.

#define ID_MAX_TIME				"MAX_TIME"		// int seconds; Default=30; min=10; Max=150	(2.5 minutes)
	// In BOTH mode the pump will be turned off after this many seconds in case the LOW (SENSOR1) never indicates dry.
	// If this occurs the UI will recieve ERROR=1 and will require the user to use the CLEAR_ERROR button,
	//		or change DRAIN_MODES to remove it from the UI.
	//		However, the error itself will only be logged one time.

#define ID_COOLDOWN_TIME		"COOLDOWN_TIME"		// int seconds; Default=30 seconds; Min=10; Max=900 (15 minutes)
	// After a HIGH/BOTH pump run, we will wait this many seconds before begining
	// another HIGH/BOTH pump run.  The counter is cleared when the DRAIN_MODE is changed


// UI readonly state output variables; these, along with the mode are compressed
// into a single byte for logging along with the date_time for the event

#define ID_SENSOR1				"SENSOR1"		// readonly, 0/1
#define ID_SENSOR2				"SENSOR2"		// readonly, 0/1
#define ID_PUMP_ON				"PUMP_ON"		// readonly; 0/1
#define ID_ERROR_CODE			"ERROR_CODE"	// readonly; 0/1	cleared with clearError() UI command

#define ID_CLEAR_ERROR			"CLEAR_ERROR"	// a UI command to clear the error state, if any



class drainPump : public myIOTDevice
{
public:

    drainPump() {}
    ~drainPump() {}

	static uint32_t _drain_mode;		// enum
	static int		_log_interval;		// seconds
	static int		_chk_interval;		// milliseconds
	static int		_high_time;			// seconds
	static int		_max_time;			// seconds
	static int		_cooldown_time;		// seconds

	static bool		_sensor1;			// 0/1
	static bool		_sensor2;			// 0/1
	static bool		_pump_on;			// 0/1
	static bool		_error_code;		// 0/1

	static void onDrainModeChanged(const myIOTValue *value, uint32_t val);
	static void clearError();

	void updateUI();
	void updateLog();
	void handlePump();

};


extern drainPump *drain_pump;



