//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: entity.h
// Description	: entity header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#pragma once

#if !defined(__ENTITY_H__)
#define __ENTITY_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
class CSprite;

class CEntity
{
	// Member Functions
public:
	CEntity();
	virtual ~CEntity();

	virtual bool Initialise(const int _kiSpriteID, const int _kiMaskID, int _iSpriteScale);

	virtual void Draw() = 0;
	virtual void DrawShader();
	virtual void DrawAnimated(int _iSpriteIndexes, int _iSpriteIndexToDraw);
	virtual void Process(float _fDeltaTick);

	void SetX(float _f);
	void SetY(float _f);

	float GetX() const;
	float GetY() const;
	CSprite* GetSprite();

	int GetHeight() const;
	int GetWidth() const;

protected:

private:
	CEntity(const CEntity& _kr);
	CEntity& operator= (const CEntity& _kr);

	// Member Variables
public:

protected:
	CSprite* m_pSprite;
	
	float m_fX;
	float m_fY;

private:

};


#endif    // __ENTITY_H__
