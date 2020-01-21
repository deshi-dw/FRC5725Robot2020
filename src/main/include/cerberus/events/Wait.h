#pragma once

#include <cerberus/Event.h>

class Wait : Events::Event {
	public:
	Wait(long time);

	private:
	long time;

};

