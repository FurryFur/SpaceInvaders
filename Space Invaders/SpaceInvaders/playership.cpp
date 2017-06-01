//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
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
	m_fDeltaTimeSinceMoved(0)
{

}

CPlayerShip::~CPlayerShip()
{

}

bool
CPlayerShip::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_PLAYERSHIPSPRITE, IDB_PLAYERSHIPMASK));

    return (true);
}

void
CPlayerShip::Draw()
{
    CEntity::Draw();
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
			pLevel->SpawnBullet(m_fX, m_fY + m_pSprite->GetHeight() / 2, 0, 500);

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
