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
#include <math.h>

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
const float CAlien::s_kfTimeToMove = 0.2f;

CAlien::CAlien() :
	m_fDeltaTimeSinceMoved(0)
{
	s_iAliens++;
	m_iFrameCount = s_iAliens;
}

CAlien::~CAlien()
{

}

bool CAlien::Initialise()
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
	m_pSprite->SetFrames(2);

    return (true);
}

void CAlien::Draw()
{
	//CEntity::Draw();
	CEntity::DrawAnimated(2, (m_iFrameCount % 2) + 1, 3);
}

void CAlien::Process(float _fDeltaTick)
{
	m_fDeltaTimeSinceMoved += _fDeltaTick;

	if (m_fDeltaTimeSinceMoved >= s_kfTimeToMove)
	{
		m_fX += s_fMoveAmount;
		IncrementFrameCount();

		Shoot();

		// Reset timer
		m_fDeltaTimeSinceMoved = 0;
	}

    CEntity::Process(_fDeltaTick);
}

void CAlien::SetType(EALIENTYPE _eType)
{
	m_eType = _eType;
}

EALIENTYPE CAlien::GetType()
{
	return m_eType;
}

void CAlien::IncrementFrameCount()
{
	m_iFrameCount++;
}

void CAlien::ChangeMovementDirection()
{
	s_fMoveAmount *= -1;
}

float CAlien::GetTimeToMove()
{
	return s_kfTimeToMove;
}

float CAlien::GetMoveAmount()
{
	return s_fMoveAmount;
}

void CAlien::Shoot()
{
	if (!IsAlienBelow())
	{
		CLevel* pLevel = CGame::GetInstance().GetLevel();
		pLevel->SpawnBullet(m_fX + m_pSprite->GetWidth(), m_fY + m_pSprite->GetHeight() + 20, 0, 500);
	}
}

bool CAlien::IsAlienBelow()
{
	CLevel* pLevel = CGame::GetInstance().GetLevel();
	for (int i = 0; i < pLevel->GetAliensRemaining(); ++i)
	{
		CAlien* pCurAlien = pLevel->GetAlien(i);
		bool bIsLower = pCurAlien->GetY() > m_fY;
		bool bOccupiesSameColumn = abs(pCurAlien->GetX() - m_fX) < m_pSprite->GetWidth();
		if (bIsLower && bOccupiesSameColumn)
		{
			return true;
		}
	}
	return false;
}

