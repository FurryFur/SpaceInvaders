#pragma once

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

