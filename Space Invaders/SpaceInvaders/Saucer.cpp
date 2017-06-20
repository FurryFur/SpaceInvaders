//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Saucer.cpp
// Description	: saucer implementation file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//
// Library Includes
#include <Windows.h>
#include <math.h>

// Local Includes
#include "resource.h"
#include "Utils.h"

// This Include
#include "Saucer.h"
#include "game.h"
#include "level.h"
#include "Sprite.h"

// Static Variables

// Static Function Prototypes

// Implementation


CSaucer::CSaucer() :
	m_fDeltaTimeSinceMoved(0),
	m_kiSpriteScale(3),
	m_fMoveSpeed(100.0f)
{
	m_iFrameCount = 0;
}

CSaucer::~CSaucer()
{

}

bool CSaucer::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_BITMAP7, IDB_ALIENMASK, m_kiSpriteScale));

	m_pSprite->SetFrames(2);

	return (true);
}

void CSaucer::Draw()
{
	//CEntity::Draw();
	CEntity::DrawAnimated(2, (m_iFrameCount % 2) + 1);
}

void CSaucer::Process(float _fDeltaTick)
{

  	m_fX += m_fMoveSpeed * _fDeltaTick;
	IncrementFrameCount();

	// Reset timer
	m_fDeltaTimeSinceMoved = 0;

	CEntity::Process(_fDeltaTick);
}

void CSaucer::IncrementFrameCount()
{
	m_iFrameCount++;
}

float CSaucer::GetMoveSpeed()
{
	return m_fMoveSpeed;
}
