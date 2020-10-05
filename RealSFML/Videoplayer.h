#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Videoplayer
{
public:
	Videoplayer(Texture* texture, Vector2u imageCount, float switchTime);
	IntRect xyRect;
	int Updateyx(int row, float time);
	int Updatexy(int row, float time);
	int getValue() { return value; }
private:
	Vector2u imageCount;
	Vector2u currentImage;
	float totalTime, switchTime;
	int value;

};