//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: MainMenu.cpp
// Description	: main menu implementation file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#include <string>
#include "MainMenu.h"
#include "game.h"
#include "Backbuffer.h"

int iButtonOffset = 100;

// Static variables
static POINT s_poiMousePos;
CMainMenu* CMainMenu::s_pMainMenu = 0;

CMainMenu::CMainMenu():
m_bClickToHandle(false),
m_bClickReleaseToHandle(false)
{
}

void CMainMenu::DrawScore()
{
	std::string blarg = "High Score";
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	SetTextColor(hdc, RGB(255, 255, 255));

	const int kiX = m_iWidth/5;
	const int kiY = m_iHeight/10;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX, kiY, blarg.c_str(), static_cast<int>(blarg.size()));
}


CMainMenu::~CMainMenu()
{
	if (s_pMainMenu != 0)
	{
		delete s_pMainMenu;
	}
	for (CMenuButton* pbutButton : m_pvecMenuButtons)
	{
		if (pbutButton != nullptr)
		{
			delete pbutButton;
		}
	}
}

bool CMainMenu::Initialise(int _iWidth, int _iHeight, HWND _hMainWindow)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;
	m_hMainWindow = _hMainWindow;

	CMenuButton* pmenMenuButton = new CMenuButton(BUTTONTYPE::PLAY);
	pmenMenuButton->SetIsActive(true);
	m_pvecMenuButtons.push_back(pmenMenuButton);

	pmenMenuButton = new CMenuButton(BUTTONTYPE::HIGHSCORE);
	pmenMenuButton->SetIsActive(true);
	m_pvecMenuButtons.push_back(pmenMenuButton);

	pmenMenuButton = new CMenuButton(BUTTONTYPE::QUIT);
	pmenMenuButton->SetIsActive(true);
	m_pvecMenuButtons.push_back(pmenMenuButton);

	pmenMenuButton = new CMenuButton(BUTTONTYPE::BACK);
	pmenMenuButton->SetIsActive(false);
	m_pvecMenuButtons.push_back(pmenMenuButton);

	int i = 1;
	for (CMenuButton* pmenButton: m_pvecMenuButtons)
	{
		pmenButton->Initialise();
		pmenButton->SetX(GetWidth() / 2);
		pmenButton->SetY(iButtonOffset * i);
		++i;
	}

	return true;
}

void CMainMenu::Draw()
{
	for (CMenuButton* pmenButton : m_pvecMenuButtons)
	{
		pmenButton->Draw();
	}

	if (m_pvecMenuButtons.at(3)->GetIsActive())
	{
		DrawScore();
	}
}

void CMainMenu::Process(float _fDeltaTick)
{
	GetCursorPos(&s_poiMousePos);
	ScreenToClient(m_hMainWindow, &s_poiMousePos);

	if (m_bClickToHandle)
	{
		ProcessButtonPress(s_poiMousePos);
	}
	if (m_bClickReleaseToHandle)
	{
		ProcessButtonRelease(s_poiMousePos);
	}
}

int CMainMenu::GetWidth() const
{
	return m_iWidth;
}

int CMainMenu::GetHeight() const
{
	return m_iHeight;
}

CMainMenu & CMainMenu::GetInstance()
{
	if (s_pMainMenu == 0)
	{
		s_pMainMenu = new CMainMenu();
	}

	return (*s_pMainMenu);
}

void CMainMenu::ProcessButtonPress(POINT _poiMousePos)
{
	RECT recButton;
	for (CMenuButton* pbutButton : m_pvecMenuButtons)
	{
		if (pbutButton->GetIsActive())
		{
			recButton = pbutButton->GetBoundingBox();

			if (_poiMousePos.x > recButton.left && _poiMousePos.x < recButton.right &&
				_poiMousePos.y > recButton.top && _poiMousePos.y < recButton.bottom)
			{
				pbutButton->SetIsSelected(true);
			}
		}
	}
	m_bClickToHandle = false;
}

void CMainMenu::ProcessButtonRelease(POINT _poiMousePos)
{
	RECT recButton;
	for (CMenuButton* pbutButton : m_pvecMenuButtons)
	{
		if (pbutButton->GetIsActive())
		{
			recButton = pbutButton->GetBoundingBox();

			if (_poiMousePos.x > recButton.left && _poiMousePos.x < recButton.right &&
				_poiMousePos.y > recButton.top && _poiMousePos.y < recButton.bottom)
			{
				if (pbutButton->GetIsSelected())
				{
					pbutButton->ButtonPressed(m_pvecMenuButtons);
				}
			}
		}
		pbutButton->SetIsSelected(false);
	}
	m_bClickReleaseToHandle = false;
}
