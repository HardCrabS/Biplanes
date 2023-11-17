#pragma once
#include <string>
#include "Constants.h"
#include "SFML/Graphics.hpp"

std::string teamToString(Team team);

sf::FloatRect combineRectangles(const sf::FloatRect& rect1, const sf::FloatRect& rect2);