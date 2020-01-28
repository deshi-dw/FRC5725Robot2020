#pragma once

#include <cerberus/Event.h>

class WaitFor : public Events::Event {
	public:
	WaitFor(Event& event);

	private:
	Event& event;

};

