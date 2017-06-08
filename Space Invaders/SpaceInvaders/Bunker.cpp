#include "Bunker.h"

// Local Includes
#include "resource.h"
#include "Utils.h"



CBunker::CBunker(EBUNKERTYPE _eType):
m_iFrameCount(1),
m_eType(_eType)
{

}


CBunker::~CBunker()
{
}

bool CBunker::Initialise()
{
	switch (m_eType)
	{
	case BLOCK:
		VALIDATE(CEntity::Initialise(IDB_BITMAP13, IDB_ALIENMASK));
		break;
	case TURNLEFT:
		VALIDATE(CEntity::Initialise(IDB_BITMAP14, IDB_ALIENMASK));
		break;
	case TURNRIGHT:
		VALIDATE(CEntity::Initialise(IDB_BITMAP15, IDB_ALIENMASK));
		break;
	case ARCLEFT:
		VALIDATE(CEntity::Initialise(IDB_BITMAP11, IDB_ALIENMASK));
		break;
	case ARCRIGHT:
		VALIDATE(CEntity::Initialise(IDB_BITMAP12, IDB_ALIENMASK));
		break;
	default:
		break;
	}

	return true;
}

void CBunker::Draw()
{
	CEntity::DrawAnimated(3, m_iFrameCount);
}

void CBunker::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}

void CBunker::SetType(EBUNKERTYPE _eType)
{
	m_eType = _eType;
}

EBUNKERTYPE CBunker::GetType()
{
	return m_eType;
}

void CBunker::IncrementFrameCount()
{
	if (m_iFrameCount == 3)
	{
		delete this;
	}

	m_iFrameCount++;
}
