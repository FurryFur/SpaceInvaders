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
#include <Windows.h>

// Local Includes
#include "resource.h"
#include "Utils.h"

// This Include
#include "Alien.h"
#include "game.h"
#include "level.h"
#include "Sprite.h"

// Static Variables

// Static Function Prototypes

// Implementation

int CAlien::s_iAliens = 0;
float CAlien::s_fMoveAmount = 8;

CAlien::CAlien() :
	m_bHit(false),
	m_kdwMoveTimer(0.2f)
{
	m_dwTimeLastMoved = timeGetTime();
	s_iAliens++;
	m_iFrameCount = s_iAliens;
}

CAlien::~CAlien()
{

}

bool
CAlien::Initialise()
{
	switch (m_eType)
	{
	case JELLYFISH:
		VALIDATE(CEntity::Initialise(IDB_BITMAP2, IDB_ALIENMASK));
		break;
	case SPIDER:
		VALIDATE(CEntity::Initialise(IDB_BITMAP4, IDB_ALIENMASK));
		break;
	case GHOST:
		VALIDATE(CEntity::Initialise(IDB_BITMAP1, IDB_ALIENMASK));
		break;
	case SAUCER:
		VALIDATE(CEntity::Initialise(IDB_BITMAP3, IDB_ALIENMASK));
		break;
	default:
		break;
	}

    return (true);
}

void
CAlien::Draw()
{
    if (!m_bHit)
    {
		//CEntity::Draw();
		CEntity::DrawAnimated(2, (m_iFrameCount % 2) + 1);
    }
}

void
CAlien::Process(float _fDeltaTick)
{
    if (!m_bHit)
    {
		DWORD dwTimeNow = timeGetTime();
		double dwDtime = (dwTimeNow - m_dwTimeLastMoved) * 0.001f; // Delta time in seconds

		if (dwDtime >= m_kdwMoveTimer)
		{
			CLevel* pLevel = CGame::GetInstance().GetLevel();
			if (m_fX + s_fMoveAmount + m_pSprite->GetWidth() >= pLevel->GetWidth()
			 || m_fX + s_fMoveAmount <= 0)
			{
				s_fMoveAmount *= -1;
			}

			m_fX += s_fMoveAmount;
			IncrementFrameCount();

			// Reset timer
			m_dwTimeLastMoved = dwTimeNow;
		}

        CEntity::Process(_fDeltaTick);
    }
}

void
CAlien::SetHit(bool _b)
{
    m_bHit = _b;
}

void CAlien::SetType(ETYPE _eType)
{
	m_eType = _eType;
}

void CAlien::IncrementFrameCount()
{
	m_iFrameCount++;
}

bool
CAlien::IsHit() const
{
    return (m_bHit);
}

