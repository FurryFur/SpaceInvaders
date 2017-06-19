//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//


#pragma once

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include <random>

// Local Includes
#include "Clock.h"

// Types

// Constants

// Prototypes
class CLevel;
class CBackBuffer;
class CMainMenu;

class CGame
{
public:
	enum ELEVEL
	{
		MENU,
		LEVEL,
		GAMEOVER
	};
	// Member Functions
public:
	virtual ~CGame();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void ExecuteOneFrame();

	CBackBuffer* GetBackBuffer();
	CLevel* GetLevel();
	HINSTANCE GetAppInstance();
	HWND GetWindow();

	void SetLevel(ELEVEL _eNewLevel);

	void GameOverWon();
	void GameOverLost();

	// Singleton Methods
	static CGame& GetInstance();
	static void DestroyInstance();

protected:

private:
	CGame();
	CGame(const CGame& _kr);
	CGame& operator= (const CGame& _kr);
	
protected:
	CClock* m_pClock;
	CLevel* m_pLevel;
	CMainMenu* m_pMenu;

	CBackBuffer* m_pBackBuffer;

	//Application data
	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	// Singleton Instance
	static CGame* s_pGame;

private:
	ELEVEL m_eCurrentLevel;

};

#endif    // __GAME_H__

