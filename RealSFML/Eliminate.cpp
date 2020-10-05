#include "Eliminate.h"

Eliminate::Eliminate(Texture* texture, Vector2u imageCount, float switchTime, Vector2f position)
:animation(texture, imageCount, switchTime)
{

	Vector2f size(40.0f, 50.0f);
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	this->row = 0;
}

void Eliminate::Draw(RenderWindow& window)
{
	window.draw(body);
}

void Eliminate::Update(float time)
{
	animation.Updatexy(row, time);
	this->value = animation.getValue();
	body.setTextureRect(animation.xyRect);
}
