#pragma once

// class Event;
#include <cerberus/Event.h>

#include <functional>
#include <vector>

class EventManager {
   private:
    /**
 * A list of Event objects. All events in this list will be updated each Update call.
 */
    std::vector<Event*> m_events;

    /**
 * A list of functions to trigger after the event list is updated.
 * 
 * This is mostly used for manipulating the events list within an event from the events list without distrupting the update cycle.
 */
    std::vector<std::function<void()>> afterUpdate;

    /**
 * A simple check to see if the update loop is being executed or not.
 * 
 * Really only used when events within the event loop are trying to manipulate the event list.
 */
    bool isUpdating = false;

   public:
    /**
 * Adds an event to the event list. If the event list is currently being updated, the event will be added after the update.
 * 
 * @param event: The event being added to the event list.
 * @return An integer representing the id to access the event with.
 * 
 * @warning If this function was called during the event cycle, the event will be added to the list after the cycle has passed. This means that the id returned will not be valid until the update is over.
 */
    const int
    add(Event* event);

    /**
 * Removes the event referenced by the id provided. If the event list is being updated, it will be removed after the update.
 * 
 * @param id: The id of the event to remove. This is got from the Event::Add(Event& event) function return value.
 */
    void remove(int id);

    /**
 * Get an event by its id.
 * 
 * @param id: The id of the event to return.
 * @return the Event tied to the provided id.
 */
    const Event* get(int id);

    /**
 * Get an event by its type.
 * 
 * @param type The type of the event. Can be gotton from the operator typeid(type).
 * @return the first event of the specifed type.
 */
    const Event* get(const std::type_info& type);

    /**
 * Clears all events from the event list. If the list is currently being updates, it will be cleared after the update.
 */
    void clear();

    /**
 * Gets the amount of events currently stored.
 * 
 * @return returns the current event count.
 */
    const std::size_t size();

    /**
 * Updates each event added to the event list. This should be called periodically throughout runtime.
 */
    void update();
};