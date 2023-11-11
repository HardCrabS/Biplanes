#include "events/Dispatcher.h"

std::unordered_map<EventID, std::vector<Dispatcher::SlotType>> Dispatcher::mObservers{};

void Dispatcher::subscribe(EventID eventID, const SlotType& slot)
{
	mObservers[eventID].push_back(slot);
}

void Dispatcher::notify(const Event& event)
{
	if (mObservers.find(event.getEventID()) == mObservers.end())
		return;

	for (auto&& observer : mObservers[event.getEventID()]) {
		observer(event);
	}
}
