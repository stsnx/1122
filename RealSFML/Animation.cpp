#include "Animation.h"
Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.y = 0;
	currentImage.x = 0;
	xyRect.width = texture->getSize().x / float(imageCount.x);
	xyRect.height = texture->getSize().y / float(imageCount.y);
}
void Animation::Updateyx(int row, float time)
{
	currentImage.x = row;
	totalTime += time;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.y++;
		if (currentImage.y >= imageCount.y) currentImage.y = 0;
	}
	xyRect.left = currentImage.x * xyRect.width;
	xyRect.top = currentImage.y * xyRect.height;

}
void Animation::Updatexy(int row, float time)
{
	currentImage.y = row;
	totalTime += time;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) currentImage.x = 0;
	}
	xyRect.left = currentImage.x * xyRect.width;
	xyRect.top = currentImage.y * xyRect.height;
}