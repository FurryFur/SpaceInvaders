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
	m_fDeltaTimeSinceMoved += _fDeltaTick;

    if (!m_bHit)
    {
		if (m_fDeltaTimeSinceMoved >= s_kfTimeToMove)
		{
			m_fX += s_fMoveAmount;
			IncrementFrameCount();

			// Reset timer
			m_fDeltaTimeSinceMoved = 0;
		}

        CEntity::Process(_fDeltaTick);
    }
}

void CAlien::SetHit(bool _b)
{
    m_bHit = _b;
}

void CAlien::SetType(ETYPE _eType)
{
	m_eType = _eType;
}

ETYPE CAlien::GetType()
{
	return m_eType;
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

