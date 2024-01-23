#include "Time.h"
#include "DxLib.h"

Time::Time():
	Count(0),
	Second(0),
	isTimeUp(false)		// ”Û’è‚Ìfalse‚ð‘}“ü
{
}

Time::~Time()
{
}

void Time::Init()
{
	Second = 3600.0f;		// 60•b*60
}

void Time::Update()
{
	/*Second -= Count;
	Count++;*/

	Second--;

	//Second =Second/ 60;
}

void Time::Draw()
{
	DrawFormatString(80, 100, GetColor(255, 255, 255),
		"Žc‚èŽžŠÔ:(%.2f)", Second/60);
}
