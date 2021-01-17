#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Player,
			Obstacle,
			HallObstacle,
			BackgroundHome,
			BackgroundHall,
			BackgroundPet,
			Dog,
			DogFood,
			Checklist,
			HappinessBar,
			Coin,
			Count
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player: return "player1.png";
		case eTexture::Obstacle: return "jackie.png";
		case eTexture::BackgroundHome: return "BackgroundHome.png";
		case eTexture::BackgroundHall: return "BackgroundHall.png";
		case eTexture::BackgroundPet: return "BackgroundPet.jpg";
		case eTexture::Dog: return "George.png";
<<<<<<< HEAD
		case eTexture::HallObstacle: return "Hallwayobstacle.png";
=======
		case eTexture::DogFood: return "DogFood.png";
>>>>>>> e1e1709c08cd934a90f26dd9039d9463d147a619
		case eTexture::Checklist: return "checklist.png";
		case eTexture::HappinessBar: return "Bar.png";
		case eTexture::Coin: return "Coin.png";
		}
		return "UnknownTexType";
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture);
}

