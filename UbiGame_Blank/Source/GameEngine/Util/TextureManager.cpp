#include "TextureManager.h"

using namespace GameEngine;

TextureManager* TextureManager::sm_instance = nullptr;

TextureManager::TextureManager()
{
	for (int a = 0; a < (int)eTexture::Count; ++a)
	{
		m_textures[a] = nullptr;
	}
}


TextureManager::~TextureManager()
{
	UnLoadTextures();
}


void TextureManager::LoadTextures()
{
	for (int a = 0; a < (int)eTexture::Count; ++a)
	{
		sf::Texture* texture = new sf::Texture();
		std::string filePath;
		filePath.append("Resources/");
		filePath.append(GetPath((eTexture::type)a));
		texture->loadFromFile(filePath);

		m_textures[a] = texture;
	}
}


void TextureManager::UnLoadTextures()
{
	for (int a = 0; a < (int)eTexture::Count; ++a)
	{
		delete m_textures[a];
		m_textures[a] = nullptr;
	}
}

namespace TextureHelper
{
	sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player: return sf::Vector2f(32.0f, 48.0f);
			//Add here the tile sizes
		case eTexture::Obstacle: return sf::Vector2f(280.0f, 275.0f);
		case eTexture::Dog: return sf::Vector2f(96.f, 96.f);
		case eTexture::Checklist: return sf::Vector2f(0.f, 0.f);
		case eTexture::HallObstacle: return sf::Vector2f(0.f, 0.f);
		}
		return sf::Vector2f(-1.f, -1.f);
	}
}
