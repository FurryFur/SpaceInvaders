#include "MenuButton.h"
#include "Entity.h"
#include "Utils.h"
#include "resource.h"


CMenuButton::CMenuButton(BUTTONTYPE _eButtonType):
	m_eButtonType(_eButtonType)
{
}


CMenuButton::~CMenuButton()
{
}

bool CMenuButton::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_BITMAP2, IDB_ALIENMASK)); // Change these
	return true;
}

void CMenuButton::Draw()
{
	if (GetIsActive())
	{
		CEntity::DrawAnimated(2, !GetIsSelected(), 1);
	}
}

RECT CMenuButton::GetBoundingBox()
{
	RECT recButtonRect;

	if (GetIsActive())
	{
		recButtonRect.left = GetX();
		recButtonRect.top = GetY();
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
		// Set active scene to level
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
