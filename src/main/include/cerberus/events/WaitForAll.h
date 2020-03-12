#pragma once

#include <cerberus/Event.h>

#include <vector>

namespace cerberus {

class WaitForAll : public Event {
   public:
    WaitForAll(std::vector<Event>& events);

   private:
    std::vector<Event>& events;
};

}  // namespace cerberus