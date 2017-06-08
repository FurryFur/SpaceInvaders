//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Game.h"
#include "BackBuffer.h"
#include "utils.h"

// This include
#include "Sprite.h"

// Static Variables
HDC CSprite::s_hSharedSpriteDC = 0;
int CSprite::s_iRefCount = 0;

// Static Function Prototypes

// Implementation

CSprite::CSprite()
: m_iX(0)
, m_iY(0),
m_iScreenWidth(960),
m_iScreenHeight(540)
{
    ++s_iRefCount;
}

CSprite::~CSprite()
{
    DeleteObject(m_hSprite);
    DeleteObject(m_hMask);

    --s_iRefCount;

    if (s_iRefCount == 0)
    {
        DeleteDC(s_hSharedSpriteDC);
        s_hSharedSpriteDC =  0;
    }
}

bool
CSprite::Initialise(int _iSpriteResourceID, int _iMaskResourceID)
{
    HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

    if (!s_hSharedSpriteDC)
    {
        s_hSharedSpriteDC = CreateCompatibleDC(NULL);
    }

    m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(_iSpriteResourceID));
    VALIDATE(m_hSprite);
    m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
    VALIDATE(m_hMask);

    GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
    GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

    return (true);
}

void
CSprite::Draw()
{
    int iW = GetWidth();
    int iH = GetHeight();

    int iX = m_iX - (iW / 2);
    int iY = m_iY - (iH / 2);

    CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

    HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);
    //StretchBlt(pBackBuffer->GetBFDC(), iX, iY, iW * (400 / m_iScreenWidth), iH * (400 / m_iScreenHeight), s_hSharedSpriteDC, 0, 0, iW, iH, SRCAND);

    SelectObject(s_hSharedSpriteDC, m_hSprite);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCPAINT);
	//StretchBlt(pBackBuffer->GetBFDC(), iX, iY, iW * (400 / m_iScreenWidth), iH * (400 / m_iScreenHeight), s_hSharedSpriteDC, 0, 0, iW, iH, SRCPAINT);
	
    SelectObject(s_hSharedSpriteDC, hOldObj);
}

void CSprite::DrawAnimated(int _iSpriteIndexes, int _iSpriteIndexToDraw, int _iScaler)
{
	int iW = GetWidth() / _iSpriteIndexes;
	int iH = GetHeight();

	int iX = m_iX - (iW / 2);
	int iY = m_iY - (iH / 2);

	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	/*HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);*/

	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hSprite);


	StretchBlt(pBackBuffer->GetBFDC(), iX, iY, iW * _iScaler, iH * _iScaler, s_hSharedSpriteDC, iW * (_iSpriteIndexToDraw - 1), 0, iW, iH, SRCPAINT);

	SelectObject(s_hSharedSpriteDC, hOldObj);
}

void CSprite::DrawShader()
{
	int iW = GetWidth();
	int iH = GetHeight();

	int iX = m_iX - (iW / 2);
	int iY = m_iY - (iH / 2);

	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	/*HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);*/

	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hSprite);


	StretchBlt(pBackBuffer->GetBFDC(), 0, 0, 960, 540, s_hSharedSpriteDC, 0, 0, iW, iH, SRCAND);
	//StretchBlt(pBackBuffer->GetBFDC(), -10, -10, 960 + 10, 540 + 10, pBackBuffer->GetBFDC(), 0, 0, 960, 540, SRCINVERT);

	SelectObject(s_hSharedSpriteDC, hOldObj);
}

void
CSprite::Process(float _fDeltaTick)
{

}

int
CSprite::GetWidth() const
{
    return (m_bitmapSprite.bmWidth);
}

int
CSprite::GetHeight() const
{
    return (m_bitmapSprite.bmHeight);
}

int 
CSprite::GetX() const
{
    return (m_iX);
}

int 
CSprite::GetY() const
{
    return (m_iY);
}

void 
CSprite::SetX(int _i)
{
    m_iX = _i;
}

void 
CSprite::SetY(int _i)
{
    m_iY = _i;
}

void 
CSprite::TranslateRelative(int _iX, int _iY)
{
    m_iX += _iX;
    m_iY += _iY;
}

void 
CSprite::TranslateAbsolute(int _iX, int _iY)
{
    m_iX = _iX;
    m_iY = _iY;
}
