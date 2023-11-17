#pragma once
#include <unordered_map>
#include "Event.h"
#include <functional>

class Dispatcher
{
	using SlotType = std::function<void(const Event&)>;
public:
	Dispatcher() {}
	static void subscribe(EventID eventID, const SlotType& slot);
	static void notify(const Event& event);
private:
	static std::unordered_map<EventID, std::vector<SlotType>> mObservers;
};