#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>

typedef std::map<std::string, sf::Texture> TextureMap;
class TextureManager {

	explicit TextureManager(void) {}

	protected:
	static TextureMap textures;

	public:
	static sf::Texture& getTexture(const std::string& filepath);
};

#endif