#include "Score.h"
#include "GameScene.h"
#include <sstream>

Score::Score(sf::Vector2f pos)
{
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(pos);
	text_.setCharacterSize(24);
	text_.setFillColor(sf::Color::Red);
	assignTag("score");
}

void Score::draw()
{
	GAME.getRenderWindow().draw(text_);
}

void Score::update(sf::Time& elapsed) {
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	std::stringstream stream;
	stream << "booger is a funny word: " << scene.getScore();

	text_.setString(stream.str());
}