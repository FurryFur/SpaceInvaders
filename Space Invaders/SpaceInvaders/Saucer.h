//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Saucer.h
// Description	: saucer header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//
#ifndef SAUCER_H
#define SAUCER_H

#include "entity.h"
#include "alien.h"

class CSaucer : public CEntity
{
public:
	CSaucer();
	virtual ~CSaucer();
	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void IncrementFrameCount();

	float GetMoveSpeed();

protected:

private:
	CSaucer(const CSaucer& _kr);
	CSaucer& operator= (const CSaucer& _kr);

	// Member Variables
public:

protected:
	int m_iFrameCount;
	float m_fDeltaTimeSinceMoved;
	const int m_kiSpriteScale;

	float m_fMoveSpeed;
};

#endif // SAUCER_H

