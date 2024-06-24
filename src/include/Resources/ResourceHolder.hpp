#pragma once

#include <string>
#include <map>
#include <memory>
#include <cassert>
#include <stdexcept>

namespace Textures {
	enum ID {
		red,
		pewpew,
		Desert
	};
}

namespace Fonts
{
	enum ID {
		ArcadeClassic
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder 
{
	
public:

	void load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const; 

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap; 

};

#include <SFML/Graphics/Texture.hpp>;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#include "ResourceHolder.inl";
