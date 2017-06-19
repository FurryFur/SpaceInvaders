#ifndef MAINMENU_H
#define MAINMENU_H

#include <Windows.h>
#include <vector>

#include "MenuButton.h"

class CMainMenu
{
public:
	CMainMenu();
	virtual ~CMainMenu();
	
	virtual bool Initialise(int _iWidth, int _iHeight, HWND _hMainWindow);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	int GetWidth() const;
	int GetHeight() const;

protected:
	void ProcessButtonPress(POINT _poiMousePos);

private:
	CMainMenu(const CMainMenu& _kr);
	CMainMenu& operator= (const CMainMenu& _kr);

protected:
	int m_iWidth;
	int m_iHeight;
	HWND m_hMainWindow;
	std::vector<CMenuButton*> m_pvecMenuButtons;
};
#endif // MAINMENU_H
