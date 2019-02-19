#pragma once
class Timer
{
private:
	int _time;
	float _delay;
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
		DWORD tick = GetTickCount();

		if (_delay + _time <= tick)
		{
			_time = tick;
			return true;
		}

		return false;
	}
};

