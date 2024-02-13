#include "Time.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include "FontManager.h"

Time::Time():
	Count(0.0f),
	Second(0.0f),
	isTimeUp(false)		// 否定のfalseを挿入
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
	Second =1800.0f;		// 本来は60秒*60
						// 現在は仮で10秒*60
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
		m_pFontManager->GetFont2(),"残り時間:%.1f", Second/60);
}
