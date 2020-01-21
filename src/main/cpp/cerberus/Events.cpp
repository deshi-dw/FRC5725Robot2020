#include <cerberus/Events.h>
#include <cerberus/Event.h>

namespace Events {

int Add(Event& event) {
    if (isUpdating == false) {
		// If the events aren't being updated, add the event to the event list.
        events.push_back(event);
        // TODO: Check that returning events.size() is corrent here. It might be events.size() - 1 instead.
		// Return the index of the event added.
        return events.size();
    } else {
        afterUpdate.push_back([&event]() -> void { Add(event); });
		// TODO: Check that returning events.size() + 1 is corrent here. It might be events.size() instead.
		// Return the *future* index of the event added.
		return events.size() + 1;
    }
}

void Remove(int id) {
    if (isUpdating == false) {
        // If the events aren't being updated, remove the requested event.
        events.erase(events.begin() + id);
    } else {
        // If the events are being updated, schedule the requested event to be removed after the
        // update.
        afterUpdate.push_back([id]() -> void { Remove(id); });
    }
}

void Clear() {
    if (isUpdating == false) {
        // If the events aren't being updated, clear them.
        events.clear();
    } else {
        // If the events are being updated, schedule them to be cleared after the update.
        afterUpdate.push_back(Clear);
    }
}

void Update() {
    // Loop through each stored event.
    isUpdating = true;
    for (Event event : events) {
        if (event.isEnabled == true && event.Condition() == true) {
            // If the event condition is true and the event is enabled,
            if (event.hasFiredOnce == true) {
                // If initalize has been called, update the event.
                event.Update();
            } else {
                // If the event hasn't been called since condition was true, call initalize.
                event.Initialize();
                event.hasFiredOnce = true;
            }
        } else if (event.hasFiredOnce == true) {
            // If the event's condition is false and it has fired before, set has fired to false.
            event.hasFiredOnce = false;
        }
    }
    isUpdating = false;

    // Do the tasks that were assigned to be completed after update and then clear them.
    for (std::function<void()> func : afterUpdate) {
        func();
    }
    afterUpdate.clear();
}

}  // namespace Events