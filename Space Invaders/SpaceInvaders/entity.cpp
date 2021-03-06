//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: entity.cpp
// Description	: entity implementation file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "Sprite.h"
#include "Utils.h"

// This Include
#include "Entity.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEntity::CEntity()
: m_fX(0.0f)
, m_fY(0.0f)
{

}

CEntity::~CEntity()
{
    delete m_pSprite;
    m_pSprite = 0;
}

bool
CEntity::Initialise(const int _kiSpriteID, const int _kiMaskID, int _iSpriteScale)
{
    m_pSprite = new CSprite();
    VALIDATE(m_pSprite->Initialise(_kiSpriteID, _kiMaskID, _iSpriteScale));

    return (true);
}

void
CEntity::Draw()
{
    m_pSprite->Draw();
}

void
CEntity::DrawShader()
{
	m_pSprite->DrawShader();
}

void
CEntity::DrawAnimated(int _iSpriteIndexes, int _iSpriteIndexToDraw)
{
	m_pSprite->DrawAnimated(_iSpriteIndexes, _iSpriteIndexToDraw);
}

void
CEntity::Process(float _fDeltaTick)
{
    m_pSprite->SetX(static_cast<int>(m_fX));
    m_pSprite->SetY(static_cast<int>(m_fY));

    m_pSprite->Process(_fDeltaTick);
}

float 
CEntity::GetX() const
{
    return (m_fX);
}

float 
CEntity::GetY() const
{
    return (m_fY);
}

CSprite * CEntity::GetSprite()
{
	return m_pSprite;
}

int 
CEntity::GetWidth() const
{
    return (static_cast<float>(m_pSprite->GetWidth()));
}

int 
CEntity::GetHeight() const
{
    return (static_cast<float>(m_pSprite->GetHeight()));
}

void
CEntity::SetX(float _f)
{
    m_fX = _f;
	m_pSprite->SetX((int)_f);
}

void
CEntity::SetY(float _f)
{
    m_fY = _f;
	m_pSprite->SetY((int)_f);
}
