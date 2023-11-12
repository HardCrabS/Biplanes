#include "events/Dispatcher.h"

DEFINE_STATIC_LOGGER(Dispatcher, "main")
std::unordered_map<EventID, std::vector<Dispatcher::SlotType>> Dispatcher::mObservers{};

std::string eventIDToString(EventID id)
{
	switch (id)
	{
	case EventID::EntityDestroyed:
		return "EntityDestroyed";
	case EventID::BoardPlane:
		return "BoardPlane";
	}
	return "Unspecified";
}

void Dispatcher::subscribe(EventID eventID, const SlotType& slot)
{
	mObservers[eventID].push_back(slot);
	LogInfo("[Dispatcher] Subscribing new event: " + eventIDToString(eventID))
}

void Dispatcher::notify(const Event& event)
{
	if (mObservers.find(event.getEventID()) == mObservers.end())
		return;

	for (auto&& observer : mObservers[event.getEventID()]) {
		observer(event);
	}
}
