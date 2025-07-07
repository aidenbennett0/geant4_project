#include "event.hh"

/**
 * @brief Sets initial values at beginning of event
 */
EventAction::EventAction(MyRunAction*) {}

/**
 * @brief Reset values at the beginning of event
 */
void EventAction::BeginOfEventAction(const G4Event* /*event*/) {}

/**
 * @brief Perform calculations and/or export data at end of event
 */
void EventAction::EndOfEventAction(const G4Event* /*event*/) {}

EventAction::~EventAction() {}