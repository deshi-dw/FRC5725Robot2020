#pragma once

#include <cerberus/Event.h>

class WaitFor : public events::Event {
	public:
	WaitFor(Event& event);

	private:
	Event& event;

};

