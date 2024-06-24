#include "include/Resources/SceneNode.h"
#include "include/Input/Command.h"

#include <cassert>

typedef std::unique_ptr<SceneNode> Ptr;

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this; 
	this->mChildren.push_back(std::move(child));
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category & this->getCategory())
		command.action(*this, dt);

	for (Ptr& child : mChildren)
		child->onCommand(command, dt);
}

Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
	[&](Ptr& p) -> bool { return p.get() == &node; });

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

SceneNode::SceneNode()
{
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

//PRIVATE DECLARATIONS

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity; 

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform; 

	return transform; 
	
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return this->getWorldTransform() * sf::Vector2f(); 
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);

	for (const Ptr& child : this->mChildren)
		child->draw(target, states);
	
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}


void SceneNode::updateCurrent(sf::Time dt)
{

}

void SceneNode::updateChildren(sf::Time dt)
{
	for (Ptr& child : this->mChildren)
		child->update(dt);
	
}
