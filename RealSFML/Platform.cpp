#include "Platform.h"
using namespace sf;
Platform::Platform(Texture* texture, Vector2f size, Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

void Platform::Draw(RenderWindow& window)
{
	window.draw(body);
}
