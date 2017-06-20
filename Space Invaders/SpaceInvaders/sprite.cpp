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
m_iScreenHeight(540),
m_iFrames(1),
m_iScale(1)
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
CSprite::Initialise(int _iSpriteResourceID, int _iMaskResourceID, int _iScale)
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

	m_iScale = _iScale;

    return (true);
}

void
CSprite::Draw()
{
	int iWSrc = GetWidth() / m_iScale;
	int iHSrc = GetHeight() / m_iScale;

	int iWDest = GetWidth();
	int iHDest = GetHeight();

	int iX = m_iX - (iWDest / 2);
	int iY = m_iY - (iHDest / 2);

	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

	StretchBlt(pBackBuffer->GetBFDC(), iX, iY, iWDest, iHDest, s_hSharedSpriteDC, 0, 0, iWSrc, iHSrc, SRCAND);

	SelectObject(s_hSharedSpriteDC, m_hSprite);

	StretchBlt(pBackBuffer->GetBFDC(), iX, iY, iWDest, iHDest, s_hSharedSpriteDC, 0, 0, iWSrc, iHSrc, SRCPAINT);

	SelectObject(s_hSharedSpriteDC, hOldObj);
}

void CSprite::DrawAnimated(int _iSpriteIndexes, int _iSpriteIndexToDraw)
{
	int iWSrc = GetWidth() / m_iScale;
	int iHSrc = GetHeight() / m_iScale;

	int iWDest = GetWidth();
	int iHDest = GetHeight();

	int iX = m_iX - (iWDest / 2);
	int iY = m_iY - (iHDest / 2);

	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

	StretchBlt(pBackBuffer->GetBFDC(), iX, iY, iWDest, iHDest, s_hSharedSpriteDC, iWSrc * (_iSpriteIndexToDraw - 1), 0, iWSrc, iHSrc, SRCAND);

	SelectObject(s_hSharedSpriteDC, m_hSprite);

	StretchBlt(pBackBuffer->GetBFDC(), iX, iY, iWDest, iHDest, s_hSharedSpriteDC, iWSrc * (_iSpriteIndexToDraw - 1), 0, iWSrc, iHSrc, SRCPAINT);

	SelectObject(s_hSharedSpriteDC, hOldObj);
}

void CSprite::DrawShader()
{
	int iWSrc = GetWidth() / m_iScale;
	int iHSrc = GetHeight() / m_iScale;

	int iWDest = GetWidth();
	int iHDest = GetHeight();

	int iX = m_iX - (iWDest / 2);
	int iY = m_iY - (iHDest / 2);

	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

	/*HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);*/

	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hSprite);


	StretchBlt(pBackBuffer->GetBFDC(), 0, 0, 960, 540, s_hSharedSpriteDC, 0, 0, iWSrc, iHSrc, SRCAND);
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
    return (m_bitmapSprite.bmWidth) * m_iScale / m_iFrames;
}

int
CSprite::GetHeight() const
{
    return (m_bitmapSprite.bmHeight) * m_iScale;
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

void CSprite::SetFrames(int _iFrames)
{
	m_iFrames = _iFrames;
}
