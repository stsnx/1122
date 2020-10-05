#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Animation
{
public:
	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	IntRect xyRect;
	void Updateyx(int row, float time);
	void Updatexy(int row, float time);
private:
	Vector2u imageCount;
	Vector2u currentImage;
	float totalTime, switchTime;

};

