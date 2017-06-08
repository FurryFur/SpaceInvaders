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
		VALIDATE(CEntity::Initialise(IDB_BITMAP9, IDB_BACKGROUNDMASK));
		break;
	case(2):
		VALIDATE(CEntity::Initialise(IDB_BITMAP16, IDB_BACKGROUNDMASK));
		break;
	case(3):
		VALIDATE(CEntity::Initialise(IDB_BITMAP17, IDB_BACKGROUNDMASK));
		break;
	case(4):
		VALIDATE(CEntity::Initialise(IDB_BITMAP18, IDB_BACKGROUNDMASK));
		break;
	default:
		VALIDATE(CEntity::Initialise(IDB_BITMAP16, IDB_BACKGROUNDMASK));
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
