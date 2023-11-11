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
