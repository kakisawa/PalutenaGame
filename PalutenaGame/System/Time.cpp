#include "Time.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include "FontManager.h"
#include "ColorManager.h"

namespace
{
	// �c�莞�ԕ`��ʒu
	constexpr int kTimeX = kScreenWidth * 0.33f;
	constexpr int kTimeY = kScreenHeight * 0.2f;
}

Time::Time():
	Count(0.0f),
	Second(0.0f),
	isTimeUp(false)		// �ے��false��}��
{
	// �������m��
	m_pFontManager = new FontManager;
	m_pColorManager = new ColorManager;
}

Time::~Time()
{
	// ���������
	delete m_pFontManager;
	m_pFontManager = nullptr;
	delete m_pColorManager;
	m_pColorManager = nullptr;
}

void Time::Init()
{
	Second =1800.0f;
	isTimeUp = false;
}

void Time::Update()
{
	if (Second <= 0.0f)
	{
		isTimeUp = true;
	}
	Second--;
}

void Time::Draw()
{
	DrawFormatStringToHandle(kTimeX+2, kTimeY+2,
		m_pColorManager->GetColorWhite(), m_pFontManager->GetFont3(),
		"�c�莞��:%.1f", Second / 60);
	DrawFormatStringToHandle(kTimeX, kTimeY,
		m_pColorManager->GetColorBlack(), m_pFontManager->GetFont3(),
		"�c�莞��:%.1f", Second / 60);
}