#include "Time.h"
#include "Player.h"
#include "Game.h"
#include "DxLib.h"

Time::Time():
	Count(0.0f),
	Second(0.0f),
	isTimeUp(false)		// ”Û’è‚Ìfalse‚ğ‘}“ü
{
}

Time::~Time()
{
}

void Time::Init()
{
	Second = 300.0f;		// –{—ˆ‚Í60•b*60
							// Œ»İ‚Í‰¼‚Å10•b*60
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
	SetFontSize(32);
	DrawFormatString(kScreenWidth*0.4, kScreenHeight*0.2, GetColor(255, 255, 255),
		"c‚èŠÔ:%.1f", Second/60);
}
