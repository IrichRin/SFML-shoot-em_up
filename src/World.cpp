#include "include/Game/World.h"

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
	leftEscort->setPosition(-40.f,  60.f);
	this->mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::pewpew, mTextures));
	rightEscort->setPosition(40.f, 60.f);
	this->mPlayerAircraft->attachChild(std::move(rightEscort));
}


void World::draw()
{
	this->mWindow.setView(mWorldView);
	this->mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return this->mCommandQueue;
}

void World::update(sf::Time dt)
{
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	mPlayerAircraft->setVelocity(0.f, 0.f);

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
	
	mPlayerAircraft->accelerate(0.f, mScrollSpeed);

	mSceneGraph.update(dt);
	
	adaptPlayerPosition();
}

void World::adaptPlayerPosition()
{
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
		mWorldView.getSize());
	const float borderDistance = 40.f;
	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}


