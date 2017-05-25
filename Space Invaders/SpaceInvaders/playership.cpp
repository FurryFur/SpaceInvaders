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
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 400.0f * _fDeltaTick;
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
