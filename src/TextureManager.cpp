#include <stdexcept>
#include "TextureManager.hpp"

TextureMap TextureManager::textures = TextureMap();

sf::Texture& TextureManager::getTexture(const std::string& filepath) {

	std::pair<TextureMap::iterator, bool> inserted = 
		textures.insert(std::pair<std::string, sf::Texture>(filepath, sf::Texture()));

	sf::Texture& texture = inserted.first->second; 

	if(inserted.second==true) { // texture n'était pas présente

		if(!texture.loadFromFile(filepath)) // chargement de la texture
			throw std::invalid_argument("The file at " + filepath + " cannot be opened ! \n\
			Reinstall the game if this error persists.");
	}

	return texture;
}