#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <Windows.h>
#include <vector>

#include "entity.h"



// Types
enum BUTTONTYPE
{
	PLAY,
	HIGHSCORE,
	QUIT,
	BACK
};

class CMenuButton : public CEntity
{
public:
	CMenuButton(BUTTONTYPE _eButtonType);
	virtual ~CMenuButton();

	virtual bool Initialise();
	virtual void Draw();
	RECT GetBoundingBox();
	void ButtonPressed(std::vector<CMenuButton*> _pvecMenuButtons);
	bool GetIsActive();
	void SetIsActive(bool _bIsActive);
	bool GetIsSelected();
	void SetIsSelected(bool _bIsActive);

private:
	bool m_bIsActive;
	bool m_bIsSelected;
	const int m_kiSpriteScale;

protected:
	BUTTONTYPE m_eButtonType;
};
#endif // MENUBUTTON_H
