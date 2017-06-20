#ifndef MAINMENU_H
#define MAINMENU_H

#include <Windows.h>
#include <vector>

#include "MenuButton.h"

class CMainMenu
{
public:
	virtual ~CMainMenu();
	
	virtual bool Initialise(int _iWidth, int _iHeight, HWND _hMainWindow);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	int GetWidth() const;
	int GetHeight() const;

	bool m_bClickToHandle;
	bool m_bClickReleaseToHandle;

	// Singleton Methods
	static CMainMenu& GetInstance();

protected:
	void ProcessButtonPress(POINT _poiMousePos);
	void ProcessButtonRelease(POINT _poiMousePos);

private:
	CMainMenu();
	CMainMenu(const CMainMenu& _kr);
	CMainMenu& operator= (const CMainMenu& _kr);
	void DrawScore();

protected:
	int m_iWidth;
	int m_iHeight;
	HWND m_hMainWindow;
	std::vector<CMenuButton*> m_pvecMenuButtons;

	// Singleton Instance
	static CMainMenu* s_pMainMenu;
};
#endif // MAINMENU_H
