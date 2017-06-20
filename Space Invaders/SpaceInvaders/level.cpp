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
#include <algorithm>

// Local Includes
#include "Game.h"
#include "Playership.h"
#include "Alien.h"
#include "Bullet.h"
#include "Utils.h"
#include "Backbuffer.h"
#include "Framecounter.h"
#include "Shader.h"
#include "Bunker.h"

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

//#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: m_pPlayerShip(0)
, m_listpBullets(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
, m_fDeltaTimeAliensMoved(0),
m_iScore(0)
{
	UpdateScoreText();
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

	for (CBullet* pBullet : m_listpBullets)
	{
		delete pBullet;
	}
    m_listpBullets.clear();

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pShader;
	m_pShader = 0;

}

bool CLevel::Initialise(int _iWidth, int _iHeight)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

    const float fBulletVelX = 200.0f;
    const float fBulletVelY = 75.0f;

	m_pShader = new CShader();
	VALIDATE(m_pShader->Initialise(3));
	//Set the shader position to start from {0,0}
	m_pShader->SetX((float)m_iWidth / 2);
	m_pShader->SetY((float)m_iHeight / 2);

    m_pPlayerShip = new CPlayerShip();
    VALIDATE(m_pPlayerShip->Initialise());

    // Set the PlayerShip's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    m_pPlayerShip->SetX(_iWidth / 2.0f);
    m_pPlayerShip->SetY(_iHeight - ( 1.5 * m_pPlayerShip->GetHeight()));

	// Spawns the bunkers at the desired positions
	int iBunkerCentreX = 32;
	CreateBunker(_iWidth - (_iWidth / 5) - iBunkerCentreX, _iHeight - (_iHeight / 4));
	CreateBunker(_iWidth - (2 * (_iWidth / 5)) - iBunkerCentreX, _iHeight - (_iHeight / 4));
	CreateBunker(_iWidth - (3 * (_iWidth / 5)) - iBunkerCentreX, _iHeight - (_iHeight / 4));
	CreateBunker(_iWidth - (4 * (_iWidth / 5)) - iBunkerCentreX, _iHeight - (_iHeight / 4));

    const int kiNumAliens = 60;
	const int kiAliensPerRow = 12;
	const int kiStartX = 50;
	const int kiStartY = 50;
    const int kiHGap = 20;
	const int kiVGap = 20;

    for (int i = 0; i < kiNumAliens; ++i)
    {
		CAlien* pAlien = new CAlien();
		if (i < kiAliensPerRow)
		{
			pAlien->SetType(JELLYFISH);
		}
		else if (i < kiAliensPerRow * 3)
		{
			pAlien->SetType(SPIDER);
		}
		else
		{
			pAlien->SetType(GHOST);
		}
        
        VALIDATE(pAlien->Initialise());

		int iCurRow = i / kiAliensPerRow;
		int iCurCol = i % kiAliensPerRow;
		int iCurrentX = kiStartX + iCurCol * (static_cast<int>(pAlien->GetWidth()) + kiHGap);
		int iCurrentY = kiStartY + iCurRow * (static_cast<int>(pAlien->GetHeight()) + kiVGap);

        pAlien->SetX(static_cast<float>(iCurrentX));
        pAlien->SetY(static_cast<float>(iCurrentY));

        m_vecAliens.push_back(pAlien);
    }

	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void CLevel::Draw()
{
	for (unsigned int i = 0; i < m_vecAliens.size(); ++i)
    {
        m_vecAliens[i]->Draw();
    }

	for (unsigned int i = 0; i < m_vecBunkers.size(); ++i)
	{
		m_vecBunkers[i]->Draw();
	}

    m_pPlayerShip->Draw();
	for (CBullet* pBullet : m_listpBullets)
	{
		pBullet->Draw();
	}

	m_pShader->DrawShader();
    DrawScore();
	DrawFPS();
}

void CLevel::Process(float _fDeltaTick)
{
	m_pShader->Process(_fDeltaTick);
	for (CBullet* pBullet : m_listpBullets)
	{
		pBullet->Process(_fDeltaTick);
	}
	m_pPlayerShip->Process(_fDeltaTick);
    ProcessBulletPlayerShipCollision();
    ProcessBulletAlienCollision();
	ProcessBulletBunkerCollision();

    ProcessCheckForWin();
	ProcessBulletBounds();
	ProcessAlienBounds(_fDeltaTick);

    for (unsigned int i = 0; i < m_vecAliens.size(); ++i)
    {
        m_vecAliens[i]->Process(_fDeltaTick);
    }

	for (unsigned int i = 0; i < m_vecBunkers.size(); ++i)
	{
		m_vecBunkers[i]->Process(_fDeltaTick);
	}
    
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);

	//TEMPORARY swapping shaders
	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
	{
		SwapBackground(1);
	}
	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
	{
		SwapBackground(2);
	}
	if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
	{
		SwapBackground(3);
	}
	if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
	{
		SwapBackground(4);
	}
	if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
	{
		SwapBackground(5);
	}
}

CPlayerShip* CLevel::GetPlayerShip() const
{
    return (m_pPlayerShip);
}

CAlien * CLevel::GetAlien(int _iIdx) const
{
	return m_vecAliens.at(_iIdx);
}

bool CLevel::OverlapsBullet(const CEntity* _pEntity)
{
	for (CBullet*& pBullet : m_listpBullets)
	{
		if (OverlapsBullet(_pEntity, pBullet))
		{
			return true;
		}
	}

	return false;
}

bool CLevel::OverlapsBullet(const CEntity* _pEntity, const CBullet* _pBullet)
{
	float fBulletR = _pBullet->GetRadius();

	float fBulletX = _pBullet->GetX();
	float fBulletY = _pBullet->GetY();

	float fEntityX = _pEntity->GetX();
	float fEntityY = _pEntity->GetY();

	float fEntityH = _pEntity->GetHeight();
	float fEntityW = _pEntity->GetWidth();

	if ((fBulletX + fBulletR > fEntityX - fEntityW / 2) && //Bullet.right > Entity.left
		(fBulletX - fBulletR < fEntityX + fEntityW / 2) && //Bullet.left < Entity.right
		(fBulletY + fBulletR > fEntityY - fEntityH / 2) && //Bullet.bottom > Entity.top
		(fBulletY - fBulletR < fEntityY + fEntityH / 2))  //Bullet.top < Entity.bottom
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CLevel::IsOutsideOfLevel(const CEntity * _pEntity)
{
	if (_pEntity->GetX() + _pEntity->GetWidth() / 2 >= GetWidth() || _pEntity->GetX() - _pEntity->GetWidth() / 2 <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CLevel::ProcessBulletPlayerShipCollision()
{
	for (auto it = m_listpBullets.begin(); it != m_listpBullets.end();)
	{
		CBullet* pBullet = *it;

		if (!pBullet->IsPlayerBullet() && OverlapsBullet(m_pPlayerShip, pBullet))
		{
			// Blow up the player ship
			//m_pPlayerShip->Explode();

			// Go to game over screen if the player is dead
			if (m_pPlayerShip->GetLives() <= 0)
			{

			}
			else
			{
				// Decrement the players lives
				m_pPlayerShip->SetLives(m_pPlayerShip->GetLives() - 1);

				// Respawn their ship somewhere else
				m_pPlayerShip->SetX(m_iWidth / 2.0f);

				// Move the ship until we no longer overlap bullets
				int iDirToggle = 1;
				while (OverlapsBullet(m_pPlayerShip))
				{
					m_pPlayerShip->SetX(m_pPlayerShip->GetX() + m_pPlayerShip->GetWidth() * iDirToggle);

					// Keep the ship inside the level
					if (IsOutsideOfLevel(m_pPlayerShip))
					{
						iDirToggle *= -1;
						m_pPlayerShip->SetX((m_pPlayerShip->GetX() + 2 * m_pPlayerShip->GetWidth() * iDirToggle));
					}
				}	
			}

			// Destroy the alien bullet
			it = m_listpBullets.erase(it);

			// Skip incrementing iterator
			continue;
		}

		++it;
	}
}

void CLevel::ProcessBulletAlienCollision()
{
	bool bCollision;
	for (auto itAlien = m_vecAliens.begin(); itAlien != m_vecAliens.end();)
	{
		bCollision = false;
		for (auto itBullet = m_listpBullets.begin(); itBullet != m_listpBullets.end() && itAlien != m_vecAliens.end();)
		{
			bCollision = false;

			if (OverlapsBullet(*itAlien, *itBullet))
			{
				// Collision: destroy bullet and alien
 				itBullet = m_listpBullets.erase(itBullet);
				if ((*itAlien)->GetType() == GHOST)
				{
					SetScore(GetScore() + 10);
				}
				else if ((*itAlien)->GetType() == SPIDER)
				{
					SetScore(GetScore() + 20);
				}
				else if ((*itAlien)->GetType() == JELLYFISH)
				{
					SetScore(GetScore() + 40);
				}
				else if ((*itAlien)->GetType() == SAUCER)
				{
					SetScore(GetScore() + 200);
				}
				itAlien = m_vecAliens.erase(itAlien);
				bCollision = true;
			}

			if (!bCollision)
			{
				++itBullet;
			}
		}
		if (!bCollision)
		{
			++itAlien;
		}
	}
}

void CLevel::ProcessBulletBunkerCollision()
{
	bool bCollision;
	for (auto itBunker = m_vecBunkers.begin(); itBunker != m_vecBunkers.end();)
	{
		bCollision = false;
		for (auto itBullet = m_listpBullets.begin(); itBullet != m_listpBullets.end() && itBunker != m_vecBunkers.end();)
		{
			bCollision = false;

			if (OverlapsBullet(*itBunker, *itBullet))
			{
				// Collision: destroy bullet and damage bunker
				itBullet = m_listpBullets.erase(itBullet);

				if ((*itBunker)->GetCurrentFrame() == 3)
				{
					itBunker = m_vecBunkers.erase(itBunker);
				}
				else
				{
					(*itBunker)->IncrementFrameCount();
				}
				bCollision = true;
			}

			if (!bCollision)
			{
				++itBullet;
			}
		}
		if (!bCollision)
		{
			++itBunker;
		}
	}
}

// Creates a full bunker with x,y as the top left corner
void CLevel::CreateBunker(int _iX, int _iY)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; j++)
		{
			CBunker* pBunker = nullptr;
			switch (j)
			{
			case(0):
				if (i == 0)
				{
					pBunker = new CBunker(EBUNKERTYPE::TURNRIGHT);
				}
				else
				{
					pBunker = new CBunker(EBUNKERTYPE::BLOCK);
				}
				break;
			case(1):
				if (i == 2)
				{
					pBunker = new CBunker(EBUNKERTYPE::ARCRIGHT);
				}
				else
				{
					pBunker = new CBunker(EBUNKERTYPE::BLOCK);
				}
				break;
			case(2):
				if (i == 2)
				{
					pBunker = new CBunker(EBUNKERTYPE::ARCLEFT);
				}
				else
				{
					pBunker = new CBunker(EBUNKERTYPE::BLOCK);
				}
				break;
			case(3):
				if (i == 0)
				{
					pBunker = new CBunker(EBUNKERTYPE::TURNLEFT);
				}
				else
				{
					pBunker = new CBunker(EBUNKERTYPE::BLOCK);
				}
				break;
			default:
				pBunker = new CBunker(EBUNKERTYPE::BLOCK);
				break;
			}


			pBunker->Initialise();

			pBunker->SetX(_iX + (j * 16));
			pBunker->SetY(_iY + (i * 16));
			m_vecBunkers.push_back(pBunker);
		}
	}
}

void CLevel::SpawnBullet(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY, bool _bPlayerBullet)
{
	m_listpBullets.push_back(new CBullet);
	m_listpBullets.back()->Initialise(_fPosX, _fPosY, _fVelocityX, _fVelocityY, _bPlayerBullet);
}

void CLevel::SwapBackground(int _iBackgroundImage)
{
	delete m_pShader;

	m_pShader = new CShader();
	m_pShader->Initialise(_iBackgroundImage);
	//Set the shader position to start from {0,0}
	m_pShader->SetX((float)m_iWidth / 2);
	m_pShader->SetY((float)m_iHeight / 2);
}

int CLevel::GetWidth() const
{
	return m_iWidth;
}

int CLevel::GetHeight() const
{
	return m_iHeight;
}

void CLevel::ProcessCheckForWin()
{
	if (GetAliensRemaining() == 0)
	{
		CGame::GetInstance().GameOverWon();
	}
}

void CLevel::ProcessBulletBounds()
{
	for (auto itBullet = m_listpBullets.begin(); itBullet != m_listpBullets.end();)
	{
		if ((*itBullet)->GetY() < 0 || (*itBullet)->GetY() > GetHeight())
		{
			// Outside of screen: destroy bullet
			itBullet = m_listpBullets.erase(itBullet);
		}
		else
		{
			++itBullet;
		}
	}
}

void CLevel::ProcessAlienBounds(float _fDeltaTick)
{
	m_fDeltaTimeAliensMoved += _fDeltaTick;

	if (m_fDeltaTimeAliensMoved >= CAlien::GetTimeToMove())
	{
		for (CAlien* pAlien : m_vecAliens)
		{
			if (pAlien->GetX() + pAlien->GetWidth() / 2 + CAlien::GetMoveAmount() >= GetWidth()
			 || pAlien->GetX() - pAlien->GetWidth() / 2 + CAlien::GetMoveAmount() <= 0)
			{
				CAlien::ChangeMovementDirection();
			}
		}
	}
}

int CLevel::GetAliensRemaining() const
{
	return m_vecAliens.size();
}

int CLevel::GetScore() const
{
	return m_iScore;
}

void CLevel::SetScore(int _i)
{
	m_iScore = _i;
	UpdateScoreText();
}

void CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	SetTextColor(hdc, RGB(255, 255, 255));

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void CLevel::UpdateScoreText()
{
    m_strScore = "Score: ";

    m_strScore += ToString(GetScore());
}


void CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}
