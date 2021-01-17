#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}


void AnimationManager::InitStaticGameAnimations()
{
	/*
	//Template definition -> every new animation needs to have an ID and a definition that controls how animation is played
	m_animDefinitions.push_back
	(
	SAnimationDefinition(
	EAnimationId::BirdIdle,
	eTexture::Player,
	sf::Vector2i(0, 0),
	10,
	3)
	);
	*/
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerIdleDown,
			eTexture::Player,
			sf::Vector2i(0, 0),
			1,
			2)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerWalkDown,
			eTexture::Player,
			sf::Vector2i(0, 0),
			4,
			10)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerWalkUp,
			eTexture::Player,
			sf::Vector2i(0, 3),
			4,
			10)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerIdleUp,
			eTexture::Player,
			sf::Vector2i(0, 3),
			1,
			2)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerWalkLeft,
			eTexture::Player,
			sf::Vector2i(0, 1),
			4,
			10)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerIdleLeft,
			eTexture::Player,
			sf::Vector2i(0, 1),
			1,
			2)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerWalkRight,
			eTexture::Player,
			sf::Vector2i(0, 2),
			4,
			10)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerIdleRight,
			eTexture::Player,
			sf::Vector2i(0, 2),
			1,
			2)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::DogIdle,
			eTexture::Dog,
			sf::Vector2i(2, 4),
			2,
			1)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::DogWalkDown,
			eTexture::Dog,
			sf::Vector2i(0, 0),
			4,
			10)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::DogWalkUp,
			eTexture::Dog,
			sf::Vector2i(0, 2),
			4,
			10)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::DogWalkRight,
			eTexture::Dog,
			sf::Vector2i(0, 1),
			4,
			10)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::DogWalkLeft,
			eTexture::Dog,
			sf::Vector2i(0, 3),
			4,
			10)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::DogSleep,
			eTexture::Dog,
			sf::Vector2i(0, 7),
			2,
			1)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::DogSit,
			eTexture::Dog,
			sf::Vector2i(0, 4),
			4,
			4)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BigDog1,
			eTexture::BigDog,
			sf::Vector2i(0, 2),
			6,
			3)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BigDog2,
			eTexture::BigDog,
			sf::Vector2i(0, 0),
			3,
			2)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BigDog3,
			eTexture::BigDog,
			sf::Vector2i(0, 4),
			2,
			2)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BigDog4,
			eTexture::BigDog,
			sf::Vector2i(0, 3),
			3,
			2)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BigDog5,
			eTexture::BigDog,
			sf::Vector2i(0, 1),
			2,
			2)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::BigDog0,
			eTexture::BigDog,
			sf::Vector2i(4, 2),
			2,
			1)
	);
}


void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}