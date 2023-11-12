#include "Utils.h"

std::string teamToString(Team team)
{
	switch (team)
	{
	case Team::None:
		return "None";
	case Team::Blue:
		return "Blue";
	case Team::Red:
		return "Red";
	}
	return "";
}

sf::FloatRect combineRectangles(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
	float left = std::min(rect1.left, rect2.left);
	float top = std::min(rect1.top, rect2.top);
	float right = std::max(rect1.left + rect1.width, rect2.left + rect2.width);
	float bottom = std::max(rect1.top + rect1.height, rect2.top + rect2.height);

	return sf::FloatRect(left, top, right - left, bottom - top);
}