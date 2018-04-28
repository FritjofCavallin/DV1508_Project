#pragma once


/* Construct keeping track of a time interval
*/
struct TimeInterval
{
	/* Start and endtime of the time interval
	*/
	float _startTime, _endTime;
	/* Get the duration of the interval in seconds. */
	float duration() { return _endTime - _startTime; }
	/* Convert the time parameter to relative time in the interval. */
	float toRelative(float parentTime) { return parentTime - _startTime; }


	TimeInterval()
		: _startTime(0.f), _endTime(3.f)
	{
	}
	TimeInterval(float startTime, float endTime)
		: _startTime(startTime), _endTime(endTime)
	{
	}
};