//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: playership.h
// Description	: playership header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#pragma once

#if !defined(__PLAYERSHIP_H__)
#define __PLAYERSHIP_H__

// Library Includes

// Local Includes
#include "Entity.h"
#include "Sprite.h"

// Types

// Constants

// Prototypes
class CPlayerShip : public CEntity
{
    // Member Functions
public:
    CPlayerShip();
    virtual ~CPlayerShip();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	void SetLives(size_t);
	size_t GetLives() const;

	void SetFireRate(float _fNewRate);


protected:
	float m_fFireRate; // Per Second
	float m_fDeltaTimeSinceMoved;
	size_t m_szLives;
	const size_t m_kszMaxLives;
	CSprite* m_pSpriteLife;
	const int m_kiSpriteScale;

private:
    CPlayerShip(const CPlayerShip& _kr);
    CPlayerShip& operator= (const CPlayerShip& _kr);

    // Member Variables
public:

protected:

private:

};

#endif    // __PLAYERSHIP_H__
