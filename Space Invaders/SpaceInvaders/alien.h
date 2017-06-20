//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: alien.h
// Description	: alien header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//
#ifndef ALIEN_H
#define ALIEN_H

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
	void SetShootChance(float _fNewChance);

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
	const int m_kiSpriteScale;

	static float m_fShootChance;
	static float s_fMoveAmount;
	EALIENTYPE m_eType;
	static float s_fTimeToMove;
	static int s_iAliens;
	static const float s_kfMoveDownAmount;

private:

};


#endif    // __ALIEN_H__

