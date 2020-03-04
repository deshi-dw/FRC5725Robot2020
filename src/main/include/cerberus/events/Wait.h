#pragma once

#include <cerberus/Event.h>

class Wait : public events::Event {
   public:
    Wait(long time);

   private:
    long time;
};
