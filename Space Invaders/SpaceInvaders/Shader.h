//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Shader.h
// Description	: shader header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//
#ifndef SHADER_H
#define SHADER_H

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

#endif // SHADER_H

