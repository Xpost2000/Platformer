#pragma once
#include <SDL2/SDL.h>
/*
	Enumeration for abstraction purposes
*/
enum class TimeMeasure{
	TIME_MILLISECONDS,
	TIME_SECONDS
};
/*
	ClockTimer for delta time
	--- From SomethingToCryAbout1 ---
	--- and from SomthingToCryAbout2 ---

	This is a Clock/Timer class that can do the following.
	- Return Delta Time ( in either milliseconds or seconds )
	- Return total Elapsed time ( in either milliseconds or seconds )
	- *TODO* Return the current frames per second

	USAGE
	- Call the tick function every frame and it will be fine.
*/
class ClockTimer
{
public:
	ClockTimer();
	~ClockTimer();
	/*
		Ticks the timer and calculates the delta time.
		Call every frame.
	*/
	static void Tick();
	/*
		return the calculated delta time in the format of your choosing
	*/
	static float returnDeltatime(const TimeMeasure);
	/*
		return the total elasped time in the format of your choosing
	*/
	static float returnElaspedTime(const TimeMeasure);
	static float returnFramesPerSecond();
private:
	// Delta time variable
	static uint32_t start;
	static uint32_t delta;
	// Previous delta time
	static uint32_t last;
	static uint32_t curFrame;
};

