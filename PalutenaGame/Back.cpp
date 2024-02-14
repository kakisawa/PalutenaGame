#include "DxLib.h"
#include "Back.h"
#include "Game.h"

Back::Back():
	Bg(0),
	x(0),
	y(0)
{
}

Back::~Back()
{
}

void Back::DrawBg()
{
	DrawGraph(x, y, Bg, false);
}

void Back::DrawGround()
{
	DrawGraph(0, kScreenHeight - 215, Bg2, true);
}
