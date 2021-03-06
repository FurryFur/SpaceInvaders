//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: bunker.h
// Description	: bunker header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#pragma once

#if !defined(__BUNCER_H__)
#define __BUNCER_H__

// Library Includes

// Local Includes
#include "Entity.h"

// Types
enum EBUNKERTYPE
{
	BLOCK,
	TURNLEFT,
	TURNRIGHT,
	ARCLEFT,
	ARCRIGHT
};

// Constants

// Prototypes

class CBunker : public CEntity
{
	// Member Functions
public:
	CBunker(EBUNKERTYPE _eType);
	virtual ~CBunker();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetType(EBUNKERTYPE _eType);
	EBUNKERTYPE GetType();
	int GetCurrentFrame();
	void IncrementFrameCount();

protected:

private:
	CBunker(const CBunker& _kr);
	CBunker& operator= (const CBunker& _kr);

	// Member Variables
public:

protected:

	int m_iFrameCount;
	EBUNKERTYPE m_eType;
	const int m_kiSpriteScale;

private:

};


#endif    // __ALIEN_H__

