#include <cerberus/Event.h>
#include <cerberus/Events.h>

#include <typeinfo>

namespace events {
const int add(Event* event) {
    if (isUpdating == false) {
        // If the events aren't being updated, add the event to the event list.
        m_events.push_back(event);
        // TODO: Check that returning events.size() is corrent here. It might be events.size() - 1 instead.
        // Return the index of the event added.
        return m_events.size();
    } else {
        afterUpdate.push_back([&event]() -> void { add(event); });
        // TODO: Check that returning events.size() + 1 is corrent here. It might be events.size() instead.
        // Return the *future* index of the event added.
        return m_events.size() + 1;
    }
}

void remove(int id) {
    if (isUpdating == false) {
        // If the events aren't being updated, remove the requested event.
        m_events.erase(m_events.begin() + id);
    } else {
        // If the events are being updated, schedule the requested event to be removed after the
        // update.
        afterUpdate.push_back([id]() -> void { remove(id); });
    }
}

const Event* get(int id) {
    return m_events[id];
}

const Event* get(const std::type_info& type) {
    for (std::size_t i = 0; i < m_events.size(); i++) {
        if (type == typeid(*m_events[i])) {
            return m_events[i];
        }
    }

    return nullptr;
}

void clear() {
    if (isUpdating == false) {
        // If the events aren't being updated, clear them.
        m_events.clear();
    } else {
        // If the events are being updated, schedule them to be cleared after the update.
        afterUpdate.push_back(clear);
    }
}

const std::size_t size() {
    return m_events.size();
}

void update() {
    // Loop through each stored event.
    isUpdating = true;
    for (int i = 0; i < m_events.size(); i++) {
        // FIXME: Add check to make sure events[i] isn't a nullptr.
        if (m_events[i]->isEnabled == true && m_events[i]->condition() == true) {
            // If the event condition is true and the event is enabled,
            if (m_events[i]->hasFiredOnce == true) {
                // If initalize has been called, update the event.
                m_events[i]->update();
            } else {
                // If the event hasn't been called since condition was true, call initalize.
                m_events[i]->initialize();
                m_events[i]->hasFiredOnce = true;
            }
        } else if (m_events[i]->hasFiredOnce == true) {
            // If the event's condition is false and it has fired before, set has fired to false.
            m_events[i]->hasFiredOnce = false;
            m_events[i]->deinitialize();
        }
    }
    isUpdating = false;

    // Do the tasks that were assigned to be completed after update and then clear them.
    for (std::function<void()> func : afterUpdate) {
        if (func) {
            func();
        }
    }
    afterUpdate.clear();
}

}  // namespace events