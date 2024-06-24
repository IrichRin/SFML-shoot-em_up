#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <vector>

#include "../Input/Categories.hpp"

struct Command;

class SceneNode : public sf::Transformable, 
	public sf::Drawable, 
	public sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

	void update(sf::Time dt);

	virtual unsigned int getCategory() const;
	void onCommand(const Command& command, sf::Time dt);

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;

private: 
	
	virtual sf::Transform getWorldTransform() const;
	virtual sf::Vector2f getWorldPosition() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

};

