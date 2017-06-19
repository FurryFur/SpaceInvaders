#include "MenuButton.h"
#include "Entity.h"
#include "Utils.h"
#include "resource.h"
#include "sprite.h"
#include "game.h"


CMenuButton::CMenuButton(BUTTONTYPE _eButtonType):
	m_eButtonType(_eButtonType)
{
}


CMenuButton::~CMenuButton()
{
}

bool CMenuButton::Initialise()
{
	switch (m_eButtonType)
	{
	case PLAY:
	{
		VALIDATE(CEntity::Initialise(IDB_PLAYBUTTON, IDB_BUTTONALPHA));
	}
		break;
	case HIGHSCORE:
	{
		VALIDATE(CEntity::Initialise(IDB_HISCOREBUTTON, IDB_BUTTONALPHA));
	}
		break;
	case QUIT:
	{
		VALIDATE(CEntity::Initialise(IDB_QUITBUTTON, IDB_BUTTONALPHA));
	}
		break;
	case BACK:
	{
		VALIDATE(CEntity::Initialise(IDB_BACKBUTTON, IDB_BUTTONALPHA));
	}
		break;
	default:
		break;
	}
	GetSprite()->SetFrames(2);
	
	return true;
}

void CMenuButton::Draw()
{
	if (GetIsActive())
	{
		CEntity::DrawAnimated(2, 1 + GetIsSelected(), 1);
	}
}

RECT CMenuButton::GetBoundingBox()
{
	RECT recButtonRect;

	if (GetIsActive())
	{
		recButtonRect.left = GetX() - GetWidth() / 2;
		recButtonRect.top = GetY() - GetHeight() / 2;
		recButtonRect.right = recButtonRect.left + GetWidth();
		recButtonRect.bottom = recButtonRect.top + GetHeight();
	}
	return recButtonRect;
}

void CMenuButton::ButtonPressed(std::vector<CMenuButton*> _pvecMenuButtons)
{
	switch (m_eButtonType)
	{
	case PLAY:
	{
		CGame::GetInstance().SetLevel(CGame::LEVEL);
	}
		break;
	case HIGHSCORE:
	{
		for (CMenuButton* pmenButton : _pvecMenuButtons)
		{
			if (pmenButton->m_eButtonType == BUTTONTYPE::BACK)
			{
				pmenButton->SetIsActive(true);
			}
			else
			{
				pmenButton->SetIsActive(false);
			}
		}
		// Draw scores
	}
		break;
	case QUIT:
	{
		// Quit
	}
		break;
	case BACK:
	{
		for (CMenuButton* pmenButton : _pvecMenuButtons)
		{
			if (pmenButton->m_eButtonType == BUTTONTYPE::BACK)
			{
				pmenButton->SetIsActive(false);
			}
			else
			{
				pmenButton->SetIsActive(true);
			}
		}
	}
		break;
	default:
		break;
	}
}

bool CMenuButton::GetIsActive()
{
	return m_bIsActive;
}

void CMenuButton::SetIsActive(bool _bIsActive)
{
	m_bIsActive = _bIsActive;
}

bool CMenuButton::GetIsSelected()
{
	return m_bIsSelected;
}

void CMenuButton::SetIsSelected(bool _bIsActive)
{
	m_bIsSelected = _bIsActive;
}
