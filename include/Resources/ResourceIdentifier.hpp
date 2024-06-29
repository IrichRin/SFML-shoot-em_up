#pragma once

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID {
		red,
		pewpew,
		Desert,
		TitleScreen
	};
}

namespace Fonts
{
	enum ID {
		ArcadeClassic
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;