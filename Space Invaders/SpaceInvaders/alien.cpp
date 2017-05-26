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

// Local Includes
#include "resource.h"
#include "Utils.h"

// This Include
#include "Alien.h"

// Static Variables

// Static Function Prototypes

// Implementation

int CAlien::s_iAliens = 0;

CAlien::CAlien()
: m_bHit(false)
{
	s_iAliens++;
	m_iFrameCount = s_iAliens;
}

CAlien::~CAlien()
{

}

bool
CAlien::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_ALIENSPRITE, IDB_ALIENMASK));

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
        CEntity::Process(_fDeltaTick);
    }
}

void
CAlien::SetHit(bool _b)
{
    m_bHit = _b;
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

