//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: playership.cpp
// Description	: playership implementation file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

// Library Includes
#include <chrono>

using namespace std::chrono;

// Local Includes
#include "resource.h"
#include "Utils.h"
#include "Bullet.h"
#include "Game.h"
#include "Level.h"

// This Include
#include "Playership.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayerShip::CPlayerShip() :
	m_fFireRate(1),
	m_fDeltaTimeSinceMoved(0),
	m_kszMaxLives(3),
	m_kiSpriteScale(1)
{
	m_szLives = m_kszMaxLives;

	m_pSpriteLife = new CSprite();
	m_pSpriteLife->Initialise(IDB_HEART, IDB_HEARTMASK, 1);
	m_pSpriteLife->SetX(32);
	m_pSpriteLife->SetY(32);
}

CPlayerShip::~CPlayerShip()
{
	delete m_pSpriteLife;
	m_pSpriteLife = nullptr;
}

bool
CPlayerShip::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_PLAYERSHIPSPRITE, IDB_PLAYERSHIPMASK, m_kiSpriteScale));

    return (true);
}

void
CPlayerShip::Draw()
{
    CEntity::Draw();

	// Draw lives
	for (size_t i = 0; i < GetLives(); ++i)
	{
		m_pSpriteLife->SetX(32 + i * 64);
		m_pSpriteLife->Draw();
	}
}

void
CPlayerShip::Process(float _fDeltaTick)
{
	m_fDeltaTimeSinceMoved += _fDeltaTick;

	float fHalfPlayerShipW = m_pSprite->GetWidth() / 2.0;
	CGame& rGame = CGame::GetInstance();
	CLevel* pLevel = rGame.GetLevel();

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 400.0f * _fDeltaTick;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 400.0f * _fDeltaTick;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (m_fDeltaTimeSinceMoved >= 1 / m_fFireRate)
		{
			pLevel->SpawnBullet(m_fX, m_fY + m_pSprite->GetHeight() / 2, 0, -500, true);

			m_fDeltaTimeSinceMoved = 0;
		}
	}
	if (m_fX - fHalfPlayerShipW <= 0)
	{
		m_fX = fHalfPlayerShipW;
	}
	else if (m_fX + fHalfPlayerShipW >= pLevel->GetWidth())
	{
		m_fX = pLevel->GetWidth() - fHalfPlayerShipW;
	}
	
	CEntity::Process(_fDeltaTick);
}

void CPlayerShip::SetLives(size_t _szLives)
{
	if (m_szLives > m_kszMaxLives)
	{
		m_szLives = 3;
	}
	else
	{
		m_szLives = _szLives;
	}
}

size_t CPlayerShip::GetLives() const
{
	return m_szLives;
}

void CPlayerShip::SetFireRate(float _fNewRate)
{
	m_fFireRate = _fNewRate;
}
