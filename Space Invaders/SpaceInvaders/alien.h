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
enum ETYPE
{
	JELLYFISH,
	SPIDER,
	GHOST,
	SAUCER
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

    void SetHit(bool _b);
	void SetType(ETYPE _eType);
	void IncrementFrameCount();
    bool IsHit() const;

	static void ChangeMovementDirection();
	static float GetTimeToMove();
	static float GetMoveAmount();

protected:

private:
    CAlien(const CAlien& _kr);
    CAlien& operator= (const CAlien& _kr);

    // Member Variables
public:

protected:
    bool m_bHit;
	int m_iFrameCount;
	float m_fElapsedTime;
	static float s_fMoveAmount;
	ETYPE m_eType;
	static const float s_kfTimeToMove;
	static int s_iAliens;

private:

};


#endif    // __ALIEN_H__

