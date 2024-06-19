#include "World.h"

World::World(sf::RenderWindow& window)
	: mWindow(window),
	mWorldView(window.getDefaultView()),
	mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f),
	mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y /2.f),
	mScrollSpeed(-50),
	mPlayerAircraft(nullptr)
{
	loadTexture();
	buildScene();

	this->mWorldView.setCenter(mSpawnPosition);
}

void World::loadTexture()
{
	this->mTextures.load(Textures::red, "assets/spritesheets/red.png");
	this->mTextures.load(Textures::pewpew, "assets/spritesheets/pewpew.png");
	this->mTextures.load(Textures::Desert, "assets/background/desert.png");
}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	this->mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::red, mTextures));
	this->mPlayerAircraft = leader.get();

	this->mPlayerAircraft->setPosition(mSpawnPosition);
	this->mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	this->mSceneLayers[Air]->attachChild(std::move(leader));

	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::pewpew, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	this->mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::pewpew, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	this->mPlayerAircraft->attachChild(std::move(rightEscort));
}

void World::draw()
{
	this->mWindow.setView(mWorldView);
	this->mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt)
{
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if (position.x <= mWorldBounds.left + 150
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150)
	{
		velocity.x *= -1; 
		mPlayerAircraft->setVelocity(velocity);
	}

	mSceneGraph.update(dt);
}


