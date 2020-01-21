#include <cerberus/Event.h>
#include <cerberus/events/WaitForAll.h>

#include <vector>

WaitForAll::WaitForAll (std::vector<Event> &events) : events(events) { }

