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
			Agenda,
			AgendaHover,
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
			Table1,
			Table2,
			Table3,
			Desk,
			DogPillow,
			Count
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player: return "player1.png";
		case eTexture::Obstacle: return "jackie.png";
		case eTexture::BackgroundHome: return "main.jpg";
		case eTexture::BackgroundHall: return "BackgroundHall.png";
		case eTexture::BackgroundPet: return "BackgroundPet.jpg";
		case eTexture::Dog: return "George.png";
		case eTexture::HallObstacle: return "Hallwayobstacle.png";
		case eTexture::DogFood: return "DogFood.png";
		case eTexture::Checklist: return "chalkboard.png";
		case eTexture::HappinessBar: return "Bar.png";
		case eTexture::Coin: return "Coin.png";
		case eTexture::Agenda: return "Agenda.png";
		case eTexture::AgendaHover: return "AgendaHover.png";
		case eTexture::Table1: return "table1.png";
		case eTexture::Table2: return "table2.png";
		case eTexture::Table3: return "table3.png";
		case eTexture::Desk: return "desk.png";
		case eTexture::DogPillow: return "DogPillow.png";
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

