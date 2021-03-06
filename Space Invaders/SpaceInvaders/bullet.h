//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: bullet.h
// Description	: bullet header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#pragma once

#if !defined(__BULLET_H__)
#define __BULLET_H__

// Library Includes

// Local Includes
#include "Entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CBullet : public CEntity
{
    // Member Functions
public:
    CBullet();
    virtual ~CBullet();

    virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY, bool _bPlayerBullet);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	bool IsPlayerBullet() const;
    float GetVelocityX() const;
    float GetVelocityY() const;
    void SetVelocityX(float _fX);
    void SetVelocityY(float _fY);

    float GetRadius() const;

protected:

private:
    CBullet(const CBullet& _kr);
    CBullet& operator= (const CBullet& _kr);

    // Member Variables
public:

protected:
    float m_fVelocityX;
    float m_fVelocityY;
	bool m_bIsPlayerBullet;
	const int m_kiSpriteScale;

private:

};


#endif    // __BULLET_H__
