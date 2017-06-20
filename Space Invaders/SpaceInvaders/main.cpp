//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: main.cpp
// Description	: the main file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "Utils.h"
#include "Level.h"
#include "Playership.h"
#include "MainMenu.h"
#include "resource.h"
#include "alien.h"


const int kiWidth = 960;
const int kiHeight = 540;
HWND g_hDebugDlg;
HWND g_ComboBox;		 // Handle to the combo box.
bool g_bDebugWindowActive;


#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

LRESULT CALLBACK
WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMsg)
	{
	case WM_MOUSEMOVE:
	{
		int iMouseX = LOWORD(_lParam);
		//CGame::GetInstance().GetLevel()->GetPlayerShip()->SetX(static_cast<float>(iMouseX));
		return (0);
	}
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return(0);
	}
	case WM_LBUTTONDOWN:
	{
		
		CMainMenu::GetInstance().m_bClickToHandle = true;
		return(0);
		break;
	}
	case WM_LBUTTONUP:
	{
		CMainMenu::GetInstance().m_bClickReleaseToHandle = true;
		return(0);
		break;
	}
	case WM_KEYDOWN:
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			g_bDebugWindowActive = true;
			ShowWindow(g_hDebugDlg, SW_SHOWNORMAL);
		}
		return(0);
		break;
	}
		break;

	default:break;
	}

	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

HWND
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, const wchar_t* _pcTitle)
{
	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}

	HWND hwnd;
	hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		_pcTitle,
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		_iWidth, _iHeight,
		NULL,
		NULL,
		_hInstance,
		NULL);

	if (!hwnd)
	{
		// Failed to create.
		return (0);
	}

	return (hwnd);
}

BOOL CALLBACK DebugDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		g_bDebugWindowActive = false;
		return TRUE;
		break;
	}
	case WM_COMMAND:
	{
		static float s_fAlienSpeed = 0.2f;
		static float s_fShootSpeed = 1; // Set to the basic speed 
		static float s_fAlienShootSpeed = 2; // Set to the basic speed 

		switch (LOWORD(_wparam))
		{
		case IDOK:
		{
			switch (ComboBox_GetCurSel(g_ComboBox))		// Switch based on what compute mode is selected
			{
			case(0):
			{
				CGame::GetInstance().GetLevel()->SwapBackground(4);
				break;
			}
			case(1):
			{
				CGame::GetInstance().GetLevel()->SwapBackground(1);
				break;
			}
			case(2):
			{
				CGame::GetInstance().GetLevel()->SwapBackground(3);
				break;
			}
			case(3):
			{
				CGame::GetInstance().GetLevel()->SwapBackground(5);
				break;
			}
			case(4):
			{
				CGame::GetInstance().GetLevel()->SwapBackground(2);
				break;
			}
			default:
				break;
			}

			ShowWindow(_hwnd, SW_HIDE);
			g_bDebugWindowActive = false;

			CGame::GetInstance().GetLevel()->GetAlien(0)->SetTimeToMove(s_fAlienSpeed);
			CGame::GetInstance().GetLevel()->GetPlayerShip()->SetFireRate(s_fShootSpeed);
			CGame::GetInstance().GetLevel()->GetAlien(0)->SetShootChance(s_fAlienShootSpeed);

			break;
		}
		// Radio Button Group 1
		case IDC_RADIO1:
		{
			// AlienSpeed Slow
			s_fAlienSpeed = 0.8f;
			break;
		}
		case IDC_RADIO2:
		{
			// AlienSpeed Medium
			s_fAlienSpeed = 0.2f;
			break;
		}
		case IDC_RADIO3:
		{
			// AlienSpeed Fast
			s_fAlienSpeed = 0.05f;
			break;
		}
		// Radio Button Group 2
		case IDC_RADIO4:
		{
			// Shoot Slow
			s_fShootSpeed = 0.2f;
			break;
		}
		case IDC_RADIO5:
		{
			// Shoot Medium
			s_fShootSpeed = 1.0f;
			break;
		}
		case IDC_RADIO6:
		{
			// Shoot Fast
			s_fShootSpeed = 5.0f;
			break;
		}
		// Radio Button Group 3
		case IDC_RADIO7:
		{
			// AlienShootSpeed slow
			s_fAlienShootSpeed = 1.0f;
			break;
		}
		case IDC_RADIO8:
		{
			// AlienShootSpeed medium
			s_fAlienShootSpeed = 2.0f;
			break;
		}
		case IDC_RADIO9:
		{
			// AlienShootSpeed fast
			s_fAlienShootSpeed = 4.0f;
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return FALSE;
}
int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	MSG msg;
	RECT _rect;
	ZeroMemory(&msg, sizeof(MSG));


	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"SpaceInvaders");

	// Related to the debug window
	g_hDebugDlg = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DebugDlgProc);
	g_bDebugWindowActive = false;
	g_ComboBox = GetDlgItem(g_hDebugDlg, IDC_COMBO1);

	SendMessage(g_ComboBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"GreenDream"));
	SendMessage(g_ComboBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"SwedishSmash"));
	SendMessage(g_ComboBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"PurplePower"));
	SendMessage(g_ComboBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"BlazingBlue"));
	SendMessage(g_ComboBox, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"RockingRocks"));
	ComboBox_SetCurSel(g_ComboBox, 2);

	CGame& rGame = CGame::GetInstance();
	
	GetClientRect(hwnd, &_rect);

	//if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	if (!rGame.Initialise(_hInstance, hwnd, _rect.right, _rect.bottom))
	{
		// Failed
		return (0);
	}

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!g_bDebugWindowActive)
			{
				rGame.ExecuteOneFrame();
			}
		}
	}

	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}
