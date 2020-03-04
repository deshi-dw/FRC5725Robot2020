#pragma once

#include <cerberus/Event.h>
#include <cerberus/Networking.h>
#include <stdlib.h>
#include <util/ByteSwap.h>

class EventTest : public Event {
   public:
    EventTest() {}

    bool condition() {
#ifdef OLD_NETWORK_CODE_STUFF
        if (net::buffers.size() > 0 && net::buffers[0] != nullptr) {
            uint16_t msgid;
            memcpy(&msgid, net::buffers[0], 2);
            msgid = byteswap16(msgid);

            // FIXME: Define msgid elsewhere.
            return msgid == 345;
        }
#endif

        return false;
    }

    void initialize() {
// FIXME: Find a better method for reading from a byte buffer.
// Get the message length.
#ifdef OLD_NETWORK_CODE_STUFF
        uint8_t msglen;
        memcpy(&msglen, (void*)(net::buffers[0] + 2), 1);

        // Get the message using the message length.
        char* msg = (char*)malloc(msglen + 1);
        memcpy(msg, (void*)(net::buffers[0] + 3), msglen);

        // add a terminating char to the end of the message.
        msg[msglen] = '\0';

        // Print the message with the clients ip.
        printf("[");
        printf(net::clients[0]->getPeerIP().data());
        printf("] ");
        printf(msg);
        printf("\n");

        // Free the allocated memory.
        // free(&msglen);
        free(msg);

#endif
    }
    void deinitialize() {}

    void update() {}
};
