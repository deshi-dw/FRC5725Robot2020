#pragma once

#include <cerberus/Event.h>

#include <vector>

class WaitForAll : public events::Event {
   public:
    WaitForAll(std::vector<Event>& events);

   private:
    std::vector<Event>& events;
};
