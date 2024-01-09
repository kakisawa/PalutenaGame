#include "Bg.h"
#include "DxLib.h"
#include "Game.h"

// ファイルの出力に使用する
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>	// 文字の出力
using namespace std;

namespace
{
	// マップチップの情報
	constexpr int kChipWidth = 32;
	constexpr int kChipHeight = 32;

	// チップを置く数
	constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

	// マップチップの配置情報
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
}


Bg::Bg():
	m_handle(-1),
	m_graphChipNumX(0),
	m_graphChipNumY(0)
{
	for (int x = 0; x < kChipNumX; x++)
	{
		for (int y = 0; y < kChipNumY; y++)
		{
			m_chipData[y][x] = kChipData[y][x];
		}
	}

	// m_chipData[kChipNumY][kChipNumX]
}

Bg::~Bg()
{
}

void Bg::Init()
{
	// マップチップの数を数える
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_handle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;

	// デバッグ表示
	//m_graphChipNumX = graphW / kChipWidth;
	//m_graphChipNumY = graphH / kChipHeight;

	// マップチップ配置データの読み込み
	fstream file;
	file.open("data/map/map.bin", ios::in | ios::binary);
	
	// ファイルを開くのに失敗した場合の処理
	if (!file.is_open())
	{
		// ファイルを開くのに失敗した場合の処理
		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
		// ファイルのオープンに成功した
		// ファイルの中身をメモリ上にコピーする
		file.read(reinterpret_cast<char*>(&(m_chipData[0][0])), sizeof(int) * kChipNumX * kChipNumY);
		file.close();
	}
}

void Bg::Update()
{
}

void Bg::Draw()
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// マップ情報から置くチップを取ってくる
			int chipNo = m_chipData[y][x];

			// マップチップの切り出し座標
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			DrawRectGraph(x * kChipHeight, y * kChipWidth,
				srcX, srcY, kChipWidth, kChipHeight,
				m_handle, true);
		}
	}
}
