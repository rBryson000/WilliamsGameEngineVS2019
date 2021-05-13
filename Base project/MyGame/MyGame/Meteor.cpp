#include "Meteor.h"
#include "Explosion.h"
#include "GameScene.h"

const float SPEED = 0.25f;

Meteor::Meteor(sf::Vector2f pos)
{
	sprite_.setTexture(GAME.getTexture("Resources/meteor.png"));
	sprite_.setPosition(pos);
	assignTag("meteor");
	setCollisionCheckEnabled(true);
}
sf::FloatRect Meteor::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Meteor::handleCollision(GameObject& otherGameObject)
{
	if (otherGameObject.hasTag("laser"))
	{
		sf::Vector2f pos = sprite_.getPosition();
		float x = pos.x;
		float y = pos.y;
		sf::FloatRect bounds = sprite_.getGlobalBounds();

		float explosionX = x + bounds.width;
		float explosionY = y + (bounds.height / 2.0f);

		ExplosionPtr explosion = std::make_shared<Explosion>(sf::Vector2f(explosionX, explosionY));
		GAME.getCurrentScene().addGameObject(explosion);
		
		GameScene& scene= (GameScene&)GAME.getCurrentScene();
		scene.increaseScore();

		otherGameObject.makeDead();

	}
	makeDead();
}
void Meteor::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Meteor::update(sf::Time& elapsed) {
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;
	int msElapsed = elapsed.asMilliseconds();

	if (pos.x < sprite_.getGlobalBounds().width * -1)
	{
		makeDead();
	}
	else
	{
		sprite_.setPosition(sf::Vector2f(pos.x - SPEED * msElapsed, pos.y));
	}
}
