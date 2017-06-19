#include "MainMenu.h"

int iButtonOffset = 20;

// Static variables
static POINT s_poiMousePos;

CMainMenu::CMainMenu()
{
}


CMainMenu::~CMainMenu()
{
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
		pmenButton->SetX((GetWidth() / 2) - (pmenButton->GetWidth()/2));
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
}

void CMainMenu::Process(float _fDeltaTick)
{
	GetCursorPos(&s_poiMousePos);
	ScreenToClient(m_hMainWindow, &s_poiMousePos);

	ProcessButtonPress(s_poiMousePos);
}

int CMainMenu::GetWidth() const
{
	return m_iWidth;
}

int CMainMenu::GetHeight() const
{
	return m_iHeight;
}

void CMainMenu::ProcessButtonPress(POINT _poiMousePos)
{
	//TODO: Loop Through the buttons and check if you click inside their bounding boxes
}
