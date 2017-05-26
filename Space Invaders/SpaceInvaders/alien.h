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
	void IncrementFrameCount();
    bool IsHit() const;

protected:

private:
    CAlien(const CAlien& _kr);
    CAlien& operator= (const CAlien& _kr);

    // Member Variables
public:

protected:
    bool m_bHit;
	int m_iFrameCount;
	const float m_kfMoveAmount;
	const DWORD m_kdwMoveTimer;
	DWORD m_dwTimeLastMoved;
	static int s_iAliens;

private:

};


#endif    // __ALIEN_H__

