#pragma once

#include <cerberus/Event.h>

class WaitFor : Events::Event {
	public:
	WaitFor(Event& event);

	private:
	Event& event;

};

