#pragma once
class Timer
{
private:
	ULONGLONG _time;
	ULONGLONG _delay;
public:
	Timer();
	~Timer();

	HRESULT initialize(float delay)
	{
		_delay = delay;
		_time = 0;

		return S_OK;
	}

	bool getTiming()
	{
		ULONGLONG tick = GetTickCount64();

		if (_delay + _time <= tick)
		{
			_time = tick;
			return true;
		}

		return false;
	}

};

