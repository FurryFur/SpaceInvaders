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

CPlayerShip::CPlayerShip()
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
    
	float fHalfPlayerShipW = m_pSprite->GetWidth() / 2.0;

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
		static seconds s_secTimeLastFired = seconds(0);
		seconds secTimeNow = duration_cast<seconds>(steady_clock::now().time_since_epoch());

		if ((secTimeNow - s_secTimeLastFired) >= (seconds(1) / m_fFireRate))
		{
			CGame& rGame = CGame::GetInstance();
			CLevel* pLevel = rGame.GetLevel();
			pLevel->SpawnBullet(m_fX, m_fY + m_pSprite->GetHeight() / 2, 0, 500);

			s_secTimeLastFired = secTimeNow;
		}
	}
	if (m_fX - fHalfPlayerShipW <= 0)
	{
		m_fX = fHalfPlayerShipW;
	}
	else if (m_fX + fHalfPlayerShipW >= 385)
	{
		m_fX = 385-fHalfPlayerShipW;
	}
	
	CEntity::Process(_fDeltaTick);
}
