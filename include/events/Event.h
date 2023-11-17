#pragma once
#include "entities/Entity.h"
#include "entities/Plane.h"

enum class EventID
{
	EntityDestroyed,
	BoardPlane,
	RequestPlane,
	LostScore,
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
	EventID getEventID() const override {
		return EventID::EntityDestroyed;
	}
	Entity* entity;
};

class BoardPlaneEvent : public Event
{
public:
	BoardPlaneEvent(Plane* boardedPlane) : plane(boardedPlane) {}
	EventID getEventID() const override {
		return EventID::BoardPlane;
	}
	Plane* plane;
};

class RequestPlaneEvent : public Event
{
public:
	RequestPlaneEvent(Team team) : team(team) {}
	EventID getEventID() const override {
		return EventID::RequestPlane;
	}
	Team team;
};

class LostScoreEvent : public Event
{
public:
	LostScoreEvent(Team team) : team(team) {}
	EventID getEventID() const override {
		return EventID::LostScore;
	}
	Team team;
};