#include "DxLib.h"
#include "Back.h"

Back::Back():
	x(0),
	y(0)
{
}

Back::~Back()
{
}

void Back::Init()
{
	// �w�i�摜�ǂݍ���
	Bg = LoadGraph("data/Map/Back.png");
}

void Back::Update()
{
}

void Back::Draw()
{
	DrawGraph(x, y, Bg, FALSE);
}
