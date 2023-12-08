#pragma once
#include "Game.h"

class Bg
{public:
	Bg();
	~Bg();

	void Init();
	void Update();
	void Draw();

	// グラフィックの設定
	void SetHandle(int handle) { m_handle = handle; }

private:
	// 定数
	// 
	// マップチップの情報
	static constexpr int kChipWidth = 32;
	static constexpr int kChipHeight = 32;

	// チップを置く数
	static constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	static constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;


private:
	// グラフィックのハンドル
	int m_handle;
	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;

	// マップチップの配置情報
	int m_chipData[kChipNumY][kChipNumX];
};

