#pragma once
#include "Entity.h"
class CShader :
	public CEntity
{
public:
	CShader();
	~CShader();

	// Member Functions

	virtual bool Initialise(int _iImageIndex);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);
};

