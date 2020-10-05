#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"
#include"Videoplayer.h"
	using namespace sf;
class Eliminate
{
public:
	Eliminate(Texture* texture, Vector2u imageCount, float switchTime, Vector2f position);
	void Draw(RenderWindow& window);
	void Update(float time);
	Collider GetCollider() { return Collider(body); }
	Vector2f GetPosition() { return body.getPosition(); }
	int getValue() { return value; }
private:
	RectangleShape body;
	Videoplayer animation;
	Vector2f velocity;
	unsigned int row;
	int value;
};

