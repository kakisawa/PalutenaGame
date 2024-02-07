#include "Time.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include "FontManager.h"

Time::Time():
	Count(0.0f),
	Second(0.0f),
	isTimeUp(false)		// ”Û’è‚Ìfalse‚ğ‘}“ü
{
	m_pFontManager = new FontManager;
}

Time::~Time()
{
	delete m_pFontManager;
	m_pFontManager = nullptr;
}

void Time::Init()
{
	Second =120.0f;		// –{—ˆ‚Í60•b*60
						// Œ»İ‚Í‰¼‚Å10•b*60
	isTimeUp = false;
}

void Time::Update()
{
	if (Second <= 0.0f){
		isTimeUp = true;
	}
	Second--;
}

void Time::Draw()
{
	SetFontSize(82);
	DrawFormatStringToHandle(kScreenWidth * 0.47f, kScreenHeight * 0.1f, GetColor(255, 255, 255),
		m_pFontManager->GetFont2(),"c‚èŠÔ:%.1f", Second/60);
}
