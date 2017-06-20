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
const float CAlien::s_kfMoveDownAmount = 10.0f;
float CAlien::s_kfTimeToMove = 0.2f;

CAlien::CAlien() :
	m_fDeltaTimeSinceMoved(0),
	m_kiSpriteScale(3),
	m_fShootChance(2.0f)
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
		VALIDATE(CEntity::Initialise(IDB_BITMAP2, IDB_ALIENMASK, m_kiSpriteScale));
		break;
	case SPIDER:
		VALIDATE(CEntity::Initialise(IDB_BITMAP4, IDB_ALIENMASK, m_kiSpriteScale));
		break;
	case GHOST:
		VALIDATE(CEntity::Initialise(IDB_BITMAP1, IDB_ALIENMASK, m_kiSpriteScale));
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
	CEntity::DrawAnimated(2, (m_iFrameCount % 2) + 1);
}

void CAlien::Process(float _fDeltaTick)
{
	static std::random_device                    s_randDev;
	static std::mt19937                          s_randGen(s_randDev());
	static std::uniform_real_distribution<float> s_randDist(0.0f, 100.0f);

	m_fDeltaTimeSinceMoved += _fDeltaTick;

	if (m_fDeltaTimeSinceMoved >= s_kfTimeToMove)
	{
		m_fX += s_fMoveAmount;
		IncrementFrameCount();
		
		float fRandomNum = s_randDist(s_randGen) * _fDeltaTick;
		if (fRandomNum < m_fShootChance * _fDeltaTick)
		{
			Shoot();
		}

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

float CAlien::GetMoveDownAmount()
{
	return s_kfMoveDownAmount;
}

void CAlien::SetTimeToMove(float _fNewTime)
{
	s_kfTimeToMove = _fNewTime;
}

void CAlien::Shoot()
{
	if (!IsAlienBelow())
	{
		CLevel* pLevel = CGame::GetInstance().GetLevel();
		pLevel->SpawnBullet(m_fX, m_fY + m_pSprite->GetHeight() / 2, 0, 250, false);
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

