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
	Second =600.0f;		// 本来は60秒*60
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
	DrawFormatStringToHandle(kScreenWidth * 0.4, kScreenHeight * 0.2, GetColor(255, 255, 255),
		m_pFontManager->GetFont2(),"残り時間:%.1f", Second/60);
}
