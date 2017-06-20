//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: bullet.cpp
// Description	: bullet implementation file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "Utils.h"

// This Includes
#include "Bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBullet::CBullet()
: m_fVelocityX(0.0f)
, m_fVelocityY(0.0f)
, m_kiSpriteScale(1)
{

}

CBullet::~CBullet()
{

}

bool
CBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY, bool _bPlayerBullet)
{
    VALIDATE(CEntity::Initialise(IDB_BULLETSPRITE, IDB_BULLETMASK, m_kiSpriteScale));
    
    m_fX = _fPosX;
    m_fY = _fPosY;

    m_fVelocityX = _fVelocityX;
    m_fVelocityY = _fVelocityY;

	m_bIsPlayerBullet = _bPlayerBullet;

    return (true);
}

void
CBullet::Draw()
{
    CEntity::Draw();
}

void
CBullet::Process(float _fDeltaTick)
{
    m_fX += m_fVelocityX * _fDeltaTick;
    m_fY += m_fVelocityY * _fDeltaTick;

    CEntity::Process(_fDeltaTick);
}

bool CBullet::IsPlayerBullet() const
{
	return m_bIsPlayerBullet;
}

float
CBullet::GetVelocityX() const
{
    return (m_fVelocityX);
}

float 
CBullet::GetVelocityY() const
{
    return (m_fVelocityY);
}

void 
CBullet::SetVelocityX(float _fX)
{
    m_fVelocityX = _fX;
}

void 
CBullet::SetVelocityY(float _fY)
{
    m_fVelocityY = _fY;
}

float 
CBullet::GetRadius() const
{

	return (GetWidth() / 2.0f);
}
