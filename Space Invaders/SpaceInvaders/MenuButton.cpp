//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: MenuButton.cpp
// Description	: menu button implementation file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#include "MenuButton.h"
#include "Entity.h"
#include "Utils.h"
#include "resource.h"
#include "sprite.h"
#include "game.h"

CMenuButton::CMenuButton(BUTTONTYPE _eButtonType):
	m_eButtonType(_eButtonType),
	m_kiSpriteScale(1)
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
		VALIDATE(CEntity::Initialise(IDB_PLAYBUTTON, IDB_BUTTONALPHA, m_kiSpriteScale));
	}
		break;
	case HIGHSCORE:
	{
		VALIDATE(CEntity::Initialise(IDB_HISCOREBUTTON, IDB_BUTTONALPHA, m_kiSpriteScale));
	}
		break;
	case QUIT:
	{
		VALIDATE(CEntity::Initialise(IDB_QUITBUTTON, IDB_BUTTONALPHA, m_kiSpriteScale));
	}
		break;
	case BACK:
	{
		VALIDATE(CEntity::Initialise(IDB_BACKBUTTON, IDB_BUTTONALPHA, m_kiSpriteScale));
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
		CEntity::DrawAnimated(2, 1 + GetIsSelected());
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
	}
		break;
	case QUIT:
	{
		PostQuitMessage(0);
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
