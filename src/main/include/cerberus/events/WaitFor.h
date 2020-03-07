#pragma once

#include <cerberus/Event.h>

namespace cerberus {

class WaitFor : public Event {
   public:
    WaitFor(Event& event);

   private:
    Event& event;
};

}  // namespace cerberus
