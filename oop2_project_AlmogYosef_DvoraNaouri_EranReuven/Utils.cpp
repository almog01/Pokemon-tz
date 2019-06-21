#include "Utils.h"

void Utils::setOrigin(Sprite & sprite, SPOT spot) //set origins by the spot enums
{
	switch (spot) //cases will hanle by spot enum which origin we want for each
				  //spot enum. it has been used over screens classes and such
	{
	case TOP_LEFT:
		sprite.setOrigin(0, 0);
		break;
	case TOP_MIDDLE:
		sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, 0);
		break;
	case TOP_RIGHT:
		sprite.setOrigin(sprite.getGlobalBounds().width, 0);
		break;
	case LEFT_MIDDLE:
		sprite.setOrigin(0, sprite.getGlobalBounds().height / 2.f);
		break;
	case MIDDLE:
		sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
		break;
	case RIGHT_MIDDLE:
		sprite.setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height / 2.f);
		break;
	case BOTTOM_LEFT:
		sprite.setOrigin(0, sprite.getGlobalBounds().height);
		break;
	case BOTTOM_MIDDLE:
		sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height);
		break;
	case BOTTOM_RIGHT:
		sprite.setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
		break;
	default:
		break;
	}
}
