#pragma once

#include <vector>

#include <cerberus/Event.h>

class WaitForAll : Events::Event {
	public:
	WaitForAll(std::vector<Event> &events);

	private:
	std::vector<Event> &events;

};

