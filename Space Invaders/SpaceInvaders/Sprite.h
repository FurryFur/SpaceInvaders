//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: sprite.h
// Description	: sprite header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#pragma once

#if !defined(__SPRITE_H__)
#define __SPRITE_H__

// Library Includes
#include "windows.h"

// Local Includes

// Types

// Constants

// Prototypes
class CSprite
{
    // Member Functions
public:
    CSprite();
    ~CSprite();

    bool Initialise(int _iResourceID, int _iMaskResourceID, int _iScale);

    void Draw();
	void DrawAnimated(int _iSpriteIndexes, int _iSpriteIndexToDraw);
	void DrawShader();
    void Process(float _fDeltaTick);
	void SetFrames(int _iFrames);

    int GetWidth() const;
    int GetHeight() const;

    int GetX() const;
    int GetY() const;
    void SetX(int _i);
    void SetY(int _i);

    void TranslateRelative(int _iX, int _iY);
    void TranslateAbsolute(int _iX, int _iY);

protected:
	

private:
    CSprite(const CSprite& _kr);
    CSprite& operator= (const CSprite& _kr);

    // Member Variables
public:
	
protected:
    //Center handle
    int m_iX;
    int m_iY;
	int m_iScreenWidth;
	int m_iScreenHeight;
	int m_iFrames;
	int m_iScale;

    HBITMAP m_hSprite;
    HBITMAP m_hMask;

    BITMAP m_bitmapSprite;
    BITMAP m_bitmapMask;

    static HDC s_hSharedSpriteDC;
    static int s_iRefCount;

private:
};

#endif    // __SPRITE_H__
