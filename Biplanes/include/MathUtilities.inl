#include <SFML/Graphics.hpp>

template <typename T>
float magnitude(const sf::Vector2<T>& vect)
{
	return sqrt(vect.x * vect.x + vect.y * vect.y);
}

template <typename T>
sf::Vector2<T> normalized(const sf::Vector2<T>& vect)
{
	float magn = magnitude(vect);
	return abs(magn) > 0.00001f ? vect / magn : vect;
}

template <typename T>
T clamp(T value, T min, T max)
{
	return value < min ? min : value > max ? max : value;
}