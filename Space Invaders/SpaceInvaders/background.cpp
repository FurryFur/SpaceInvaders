//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: backgroun.cpp
// Description	: backgroun implementation file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "Utils.h"
#include "Backbuffer.h"
#include "Game.h"

// This Include
#include "background.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBackGround::CBackGround()
{

}

CBackGround::~CBackGround()
{

}

bool
CBackGround::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_BACKGROUND, IDB_BACKGROUNDMASK, 1));

	return (true);
}

void
CBackGround::Draw()
{
	CEntity::Draw();
}

void
CBackGround::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}
