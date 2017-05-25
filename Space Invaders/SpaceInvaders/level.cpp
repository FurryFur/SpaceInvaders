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
#include "Playership.h"
#include "Alien.h"
#include "Bullet.h"
#include "Utils.h"
#include "Backbuffer.h"
#include "Framecounter.h"
#include "Background.h"

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

//#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: m_iAliensRemaining(0)
, m_pPlayerShip(0)
, m_pBullet(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
{

}

CLevel::~CLevel()
{
    while (m_vecAliens.size() > 0)
    {
        CAlien* pAlien = m_vecAliens[m_vecAliens.size() - 1];

        m_vecAliens.pop_back();

        delete pAlien;
    }

    delete m_pPlayerShip;
    m_pPlayerShip = 0;

    delete m_pBullet;
    m_pBullet = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

    const float fBulletVelX = 200.0f;
    const float fBulletVelY = 75.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	m_pBullet = new CBullet();
    VALIDATE(m_pBullet->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f, fBulletVelX, fBulletVelY));

    m_pPlayerShip = new CPlayerShip();
    VALIDATE(m_pPlayerShip->Initialise());

    // Set the PlayerShip's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    m_pPlayerShip->SetX(_iWidth / 2.0f);
    m_pPlayerShip->SetY(_iHeight - ( 1.5 * m_pPlayerShip->GetHeight()));

    const int kiNumAliens = 36;
    const int kiStartX = 20;
    const int kiGap = 5;

    int iCurrentX = kiStartX;
    int iCurrentY = kiStartX;

    for (int i = 0; i < kiNumAliens; ++i)
    {
        CAlien* pAlien = new CAlien();
        VALIDATE(pAlien->Initialise());

        pAlien->SetX(static_cast<float>(iCurrentX));
        pAlien->SetY(static_cast<float>(iCurrentY));

        iCurrentX += static_cast<int>(pAlien->GetWidth()) + kiGap;

        if (iCurrentX > _iWidth)
        {
            iCurrentX = kiStartX;
            iCurrentY += 20;
        }

        m_vecAliens.push_back(pAlien);
    }

    SetAliensRemaining(kiNumAliens);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < m_vecAliens.size(); ++i)
    {
        m_vecAliens[i]->Draw();
    }

    m_pPlayerShip->Draw();
    m_pBullet->Draw();

    DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{
	m_pBackground->Process(_fDeltaTick);
	m_pBullet->Process(_fDeltaTick);
	m_pPlayerShip->Process(_fDeltaTick);
	ProcessBulletWallCollision();
	//ProcessPlayerShipWallCollison();
    ProcessBulletPlayerShipCollision();
    ProcessBulletAlienCollision();

    ProcessCheckForWin();
	ProcessBulletBounds();

    for (unsigned int i = 0; i < m_vecAliens.size(); ++i)
    {
        m_vecAliens[i]->Process(_fDeltaTick);
    }
	
   
    
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CPlayerShip* 
CLevel::GetPlayerShip() const
{
    return (m_pPlayerShip);
}

void 
CLevel::ProcessBulletWallCollision()
{
    float fBulletX = m_pBullet->GetX();
    float fBulletY = m_pBullet->GetY();
    float fBulletW = m_pBullet->GetWidth();
    float fBulletH = m_pBullet->GetHeight();

    float fHalfBulletW = fBulletW / 2;
	float fHalfBulletH = fBulletH / 2;

    if (fBulletX < fHalfBulletW) //represents the situation when the Bullet has hit the left wall
    {
        m_pBullet->SetVelocityX(m_pBullet->GetVelocityX() * -1); //reverse the Bullet's x velocity
    }
    else if (fBulletX > m_iWidth - fHalfBulletW) //represents the situation when the Bullet has hit the right wall
    {
        m_pBullet->SetVelocityX(m_pBullet->GetVelocityX() * -1); //reverse the Bullet's x velocity direction
    }

	if (fBulletY < fHalfBulletH) //represents the situation when the Bullet has hit the top wall
    {
        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //reverse the Bullet's y velocity
    }

#ifdef CHEAT_BOUNCE_ON_BACK_WALL
	if (fBulletY  > m_iHeight - fHalfBulletH)  //represents the situation when the Bullet has hit the bottom wall
    {
        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //reverse the Bullet's y velocity
    }
#endif //CHEAT_BOUNCE_ON_BACK_WALL
}




void
CLevel::ProcessBulletPlayerShipCollision()
{
    float fBulletR = m_pBullet->GetRadius();

    float fBulletX = m_pBullet->GetX();
    float fBulletY = m_pBullet->GetY(); 

    float fPlayerShipX = m_pPlayerShip->GetX();
    float fPlayerShipY = m_pPlayerShip->GetY();

    float fPlayerShipH = m_pPlayerShip->GetHeight();
    float fPlayerShipW = m_pPlayerShip->GetWidth();

    if ((fBulletX + fBulletR > fPlayerShipX - fPlayerShipW / 2) && //Bullet.right > PlayerShip.left
        (fBulletX - fBulletR < fPlayerShipX + fPlayerShipW / 2) && //Bullet.left < PlayerShip.right
        (fBulletY + fBulletR > fPlayerShipY - fPlayerShipH / 2) && //Bullet.bottom > PlayerShip.top
        (fBulletY - fBulletR < fPlayerShipY + fPlayerShipH / 2))  //Bullet.top < PlayerShip.bottom
    {
        m_pBullet->SetY((fPlayerShipY - fPlayerShipH / 2) - fBulletR);  //Set the Bullet.bottom = PlayerShip.top; to prevent the Bullet from going through the PlayerShip!
        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //Reverse Bullet's Y direction
    }
}

void
CLevel::ProcessBulletAlienCollision()
{
    for (unsigned int i = 0; i < m_vecAliens.size(); ++i)
    {
        if (!m_vecAliens[i]->IsHit())
        {
            float fBulletR = m_pBullet->GetRadius();

            float fBulletX = m_pBullet->GetX();
            float fBulletY = m_pBullet->GetY(); 

            float fAlienX = m_vecAliens[i]->GetX();
            float fAlienY = m_vecAliens[i]->GetY();

            float fAlienH = m_vecAliens[i]->GetHeight();
            float fAlienW = m_vecAliens[i]->GetWidth();

            if ((fBulletX + fBulletR > fAlienX - fAlienW / 2) &&
                (fBulletX - fBulletR < fAlienX + fAlienW / 2) &&
                (fBulletY + fBulletR > fAlienY - fAlienH / 2) &&
                (fBulletY - fBulletR < fAlienY + fAlienH / 2))
            {
                //Hit the front side of the Alien...
                m_pBullet->SetY((fAlienY + fAlienH / 2.0f) + fBulletR);
                m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1);
                m_vecAliens[i]->SetHit(true);

                SetAliensRemaining(GetAliensRemaining() - 1);
            }
        }
    }
}

void
CLevel::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < m_vecAliens.size(); ++i)
    {
        if (!m_vecAliens[i]->IsHit())
        {
            return;
        }
    }

    CGame::GetInstance().GameOverWon();
}

void
CLevel::ProcessBulletBounds()
{
	if (m_pBullet->GetX() < 0)
    {
        m_pBullet->SetX(0);
    }
	else if (m_pBullet->GetX() > m_iWidth)
    {
        m_pBullet->SetX(static_cast<float>(m_iWidth));
    }

    if (m_pBullet->GetY() < 0)
    {
        m_pBullet->SetY(0.0f);
    }
    else if (m_pBullet->GetY() > m_iHeight)
    {
        CGame::GetInstance().GameOverLost();
        //m_pBullet->SetY(static_cast<float>(m_iHeight));
    }
}

int 
CLevel::GetAliensRemaining() const
{
    return (m_iAliensRemaining);
}

void 
CLevel::SetAliensRemaining(int _i)
{
    m_iAliensRemaining = _i;
    UpdateScoreText();
}

void
CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void 
CLevel::UpdateScoreText()
{
    m_strScore = "Aliens Remaining: ";

    m_strScore += ToString(GetAliensRemaining());
}


void 
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}
