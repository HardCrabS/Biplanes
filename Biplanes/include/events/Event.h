#pragma once
#include "Entity.h"

enum class EventID
{
	EntityDestroyed,
};

class Event
{
public:
	virtual EventID getEventID() const = 0;
};

class EntityDestroyedEvent : public Event
{
public:
	EntityDestroyedEvent(Entity* entityDestroyed) : entity(entityDestroyed) {}
	EventID getEventID() const override
	{
		return EventID::EntityDestroyed;
	}
	Entity* entity;
};