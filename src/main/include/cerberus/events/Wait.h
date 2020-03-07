#pragma once

#include <cerberus/Event.h>

namespace cerberus {

class Wait : public Event {
   public:
    Wait(long time);

   private:
    long time;
};

}  // namespace cerberus
