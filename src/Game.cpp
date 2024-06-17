#include "Game.h"

Game::Game()
: mWindow(sf::VideoMode(400, 300), "shoot-em up"),
mPlayer(),
mIsMovingDown(false), 
mIsMovingUp(false),
mIsMovingRight(false),
mIsMovingLeft(false),
mSpeed(150.f)
{
	this->loadFonts(); 
	this->loadTextures();

	//------ fps ------// 
	this->mFPS.setFont(this->mFonts.get(Fonts::ArcadeClassic));
	this->mFPS.setPosition(sf::Vector2f(0, 0));
	this->mFPS.setCharacterSize(12);

	//------ player ------//
	sf::Vector2u textureSize = this->mTextures.get(Textures::Airplane).getSize();
	textureSize.x /= 5; 
	textureSize.y /= 2; 

	this->mPlayer.setTexture(this->mTextures.get(Textures::Airplane));
	this->mPlayer.setTextureRect(sf::IntRect(textureSize.x * 3, textureSize.y * 1, textureSize.x, textureSize.y));
	this->mPlayer.setPosition(sf::Vector2f(200, 250));
	
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (mWindow.isOpen())
	{
		this->pollEvent();
		timeSinceLastUpdate += clock.restart();

		this->mFPS.setString(std::to_string(144) + " fps");

		while(timeSinceLastUpdate > sf::seconds(1.f/144.f))
		{
			timeSinceLastUpdate -= sf::seconds(1.f/144.f);
			this->pollEvent();
			this->update(sf::seconds(1.f/144.f));
		}
		this->render();
	}
}


void Game::loadFonts()
{
	this->mFonts.load(Fonts::ArcadeClassic, "assets/fonts/ARCADECLASSIC.ttf");
}

void Game::loadTextures()
{
	this->mTextures.load(Textures::Airplane, "assets/spritesheets/pewpew.png");
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		this->mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		this->mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		this->mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		this->mIsMovingRight = isPressed;
}

//----PRIVATE FUNCTIONS----//
void Game::pollEvent()
{
	sf::Event ev;
	while (mWindow.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
			this->handleInput(ev.key.code, true);
			break;
		case sf::Event::KeyReleased:
			this->handleInput(ev.key.code, false);
			break;
		}
	}
}

void Game::update(sf::Time delta)
{
	sf::Vector2f movement(0.f, 0.f);
	if (this->mIsMovingUp)
		movement.y -= this->mSpeed;
	if (this->mIsMovingDown)
		movement.y += this->mSpeed;
	if (this->mIsMovingLeft)
		movement.x -= this->mSpeed;
	if (this->mIsMovingRight)
		movement.x += this->mSpeed;

	this->mPlayer.move(movement * delta.asSeconds());
}

void Game::render()
{
	mWindow.clear(sf::Color(0, 0, 0, 255));
	mWindow.draw(this->mFPS);
	mWindow.draw(this->mPlayer);
	mWindow.display();
}
