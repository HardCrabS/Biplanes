#pragma once
#include "Plane.h"
#include "Player.h"

class AI
{
public:
	AI();
	void setPlayer(Player* player) { mPlayer = player; }
	void setPlane(Plane* plane) { mPlane = plane; }
	void update(float deltaTime);
private:
	void onPlaneDestroyed(const Event& event);
	void onBoardPlane(const Event& event);
private:
	DECLARE_LOGGER
	Player* mPlayer;
	Plane* mPlane;
};