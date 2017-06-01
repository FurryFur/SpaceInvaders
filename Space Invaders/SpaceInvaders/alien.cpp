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
const float CAlien::s_kfTimeToMove = 0.2f;

CAlien::CAlien() :
	m_bHit(false),
	m_fElapsedTime(0)
{
	s_iAliens++;
	m_iFrameCount = s_iAliens;
}

CAlien::~CAlien()
{

}

bool CAlien::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_ALIENSPRITE, IDB_ALIENMASK));

    return (true);
}

void CAlien::Draw()
{
    if (!m_bHit)
    {
		//CEntity::Draw();
		CEntity::DrawAnimated(2, (m_iFrameCount % 2) + 1);
    }
}

void CAlien::Process(float _fDeltaTick)
{
	m_fElapsedTime += _fDeltaTick;

    if (!m_bHit)
    {
		if (m_fElapsedTime >= s_kfTimeToMove)
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
			m_fElapsedTime = 0;
		}

        CEntity::Process(_fDeltaTick);
    }
}

void CAlien::SetHit(bool _b)
{
    m_bHit = _b;
}

void CAlien::IncrementFrameCount()
{
	m_iFrameCount++;
}

bool CAlien::IsHit() const
{
    return (m_bHit);
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

