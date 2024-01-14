#include "DxLib.h"
#include "Back.h"

Back::Back():
	Bg(0),
	x(0),
	y(0)
{
}

Back::~Back()
{
}

void Back::Init()
{
}

void Back::Update()
{
}

void Back::Draw()
{
	DrawGraph(x, y, Bg, FALSE);
}
