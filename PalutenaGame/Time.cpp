#include "Time.h"
#include "Player.h"
#include "DxLib.h"

Time::Time():
	Count(0),
	Second(0),
	isTimeUp(false)		// �ے��false��}��
{
}

Time::~Time()
{
}

void Time::Init()
{
	Second = 300.0f;		// �{����60�b*60
							// ���݂͉���10�b*60
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
		"�c�莞��:(%.2f)", Second/60);
}
