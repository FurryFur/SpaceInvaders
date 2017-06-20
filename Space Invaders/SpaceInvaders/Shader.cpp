//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Shader.cpp
// Description	: shader implementation file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#include "Shader.h"

// Local Includes
#include "resource.h"
#include "Utils.h"
#include "Backbuffer.h"
#include "Game.h"


CShader::CShader()
{
}


CShader::~CShader()
{
}

bool CShader::Initialise(int _iImageIndex)
{
	switch (_iImageIndex)
	{
	case(1):
		VALIDATE(CEntity::Initialise(IDB_BITMAP9, IDB_BACKGROUNDMASK, 1));
		break;
	case(2):
		VALIDATE(CEntity::Initialise(IDB_BITMAP16, IDB_BACKGROUNDMASK, 1));
		break;
	case(3):
		VALIDATE(CEntity::Initialise(IDB_BITMAP17, IDB_BACKGROUNDMASK, 1));
		break;
	case(4):
		VALIDATE(CEntity::Initialise(IDB_BITMAP18, IDB_BACKGROUNDMASK, 1));
		break;
	case(5):
		VALIDATE(CEntity::Initialise(IDB_BITMAP19, IDB_BACKGROUNDMASK, 1));
		break;
	default:
		VALIDATE(CEntity::Initialise(IDB_BITMAP16, IDB_BACKGROUNDMASK, 1));
		break;
	}

	return (true);
}

void CShader::Draw()
{
	CEntity::DrawShader();
}

void CShader::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}
