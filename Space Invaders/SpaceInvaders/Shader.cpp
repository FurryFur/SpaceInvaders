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

bool CShader::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_BITMAP9, IDB_BACKGROUNDMASK));

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
