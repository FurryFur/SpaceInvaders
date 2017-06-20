//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__ALIEN_H__)
#define __ALIEN_H__

// Library Includes

// Local Includes
#include "Entity.h"

// Types
enum EALIENTYPE
{
	JELLYFISH,
	SPIDER,
	GHOST
};
// Constants

// Prototypes

class CAlien : public CEntity
{
    // Member Functions
public:
    CAlien();
    virtual ~CAlien();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	void SetType(EALIENTYPE _eType);
	EALIENTYPE GetType();
	void IncrementFrameCount();

	static void ChangeMovementDirection();
	static float GetTimeToMove();
	void SetTimeToMove(float _fNewTime);
	static float GetMoveAmount();
	static float GetMoveDownAmount();

protected:

private:
    CAlien(const CAlien& _kr);
    CAlien& operator= (const CAlien& _kr);

    // Member Variables
public:

protected:
	void Shoot();
	bool IsAlienBelow();

	int m_iFrameCount;
	float m_fDeltaTimeSinceMoved;
	float m_fShootChance;
	const int m_kiSpriteScale;

	static float s_fMoveAmount;
	EALIENTYPE m_eType;
	static float s_kfTimeToMove;
	static int s_iAliens;
	static const float s_kfMoveDownAmount;

private:

};


#endif    // __ALIEN_H__

