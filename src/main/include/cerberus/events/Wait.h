#pragma once

#include <cerberus/Event.h>

class Wait : public Events::Event {
	public:
	Wait(long time);

	private:
	long time;

};

