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

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <list>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class CBullet;
class CPlayerShip;
class CAlien;
class CBunker;
class CFPSCounter;
class CShader;
class CEntity;

class CLevel
{
    // Member Functions
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    CPlayerShip* GetPlayerShip() const;
	CAlien* GetAlien(int _iIdx) const;
	void SpawnBullet(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY);
	int GetWidth() const;
	int GetHeight() const;

    int GetAliensRemaining() const;
	int GetScore() const;

protected:
    void ProcessBulletPlayerShipCollision();
    void ProcessBulletAlienCollision();
	void ProcessBulletBunkerCollision();
	void CreateBunker(int _iX, int _iY);

    void ProcessCheckForWin();

    void ProcessBulletBounds();
	void ProcessAlienBounds(float _fDeltaTick);

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

	void SetScore(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CShader* m_pShader;
    std::list<CBullet*> m_listpBullets;
	std::list<CEntity*> m_vecpDestroyedEntities;
    CPlayerShip* m_pPlayerShip;
    std::vector<CAlien*> m_vecAliens;
	std::vector<CBunker*> m_vecBunkers;
	CFPSCounter* m_fpsCounter;
	float m_fDeltaTimeAliensMoved;


    int m_iWidth;
    int m_iHeight;

	int m_iScore;

    std::string m_strScore;

private:

};

#endif    // __LEVEL_H__
