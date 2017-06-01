#pragma once
#include "Entity.h"
class CShader :
	public CEntity
{
public:
	CShader();
	~CShader();

	// Member Functions

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);
};

