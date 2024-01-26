#include "Time.h"
#include "Player.h"
#include "DxLib.h"

Time::Time():
	Count(0),
	Second(0),
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
	if (Second <= 0)
	{
		isTimeUp = true;
	}

	Second--;
}

void Time::Draw()
{
	DrawFormatString(80, 100, GetColor(255, 255, 255),
		"c‚èŠÔ:(%.2f)", Second/60);
}
