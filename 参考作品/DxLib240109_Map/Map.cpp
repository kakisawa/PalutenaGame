#include "Map.h"
#include "Player.h"
#include "DxLib.h"

namespace
{
	// スクリーンサイズ		// 本来ここに書くのはよくない(ゲームヘッダーを作ろう)
	constexpr int kScreenWidth = 640;
	constexpr int kScreenHeight = 480;

	// チップ1つのサイズ
	constexpr int kChipW = 32;
	constexpr int kChipH = 32;

	// 縦横のチップの数
	// スクロールさせたいので画面サイズ640*480より広く
	constexpr int kChipNumX = 40;
	constexpr int kChipNumY = 30;

	// チップのサイズ、数からマップの広さを計算
	constexpr int kMapWidth = kChipW * kChipNumX;
	constexpr int kMapHeight = kChipH * kChipNumY;

	// チップの配置情報
	// 0:チップなし		1:壁
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

}


void Map::Update()
{
}

void Map::Draw()
{
	// プレイヤーの位置に応じたスクロール量を決定
	int scrollX = GetScrollX();
	int scrollY = GetScrollY();


	for (int x = 0; x < kChipNumX; x++)
	{
		// 画面外を描画しない処理は、ここで弾くと、もっと処理が効率化できる

		for (int y = 0; y < kChipNumY; y++)
		{
			int posX = kChipW * x - scrollX;
			int posY = kChipH * y - scrollY;

			// 画面外を描画しない
			if (posX < 0 - kChipW)		continue;
			if (posX > kScreenWidth)	continue;
			if (posY < 0 - kChipH)		continue;
			if (posY > kScreenHeight)	continue;



			if (kChipData[y][x] == 1)
			{
				DrawBox(posX, posY, posX + kChipW, posY + kChipH, 0xffffff, true);
			}
			DrawBox(posX, posY, posX + kChipW, posY + kChipH, 0x808080, false);

		}
	}
}

int Map::GetScrollX()
{
	int result = static_cast<int>(m_pPlayer->GetX() - kScreenWidth / 2);
	result = max(0, result);						// 最小値
	result = min(kMapWidth - kScreenWidth, result);	// 最大値

	return result;
}

int Map::GetScrollY()
{
	int result = static_cast<int>(m_pPlayer->GetY() - kScreenHeight / 2);
	if (result < 0) 
	{
		result = 0; 
	}

	if (result >kMapHeight-kScreenHeight)
	{
		result = kMapHeight - kScreenHeight; 
	}
		return result;
}

bool Map::IsColPlayer()
{
	// m_pPlayer
	float playerLeft = m_pPlayer->GetLeft();
	float playerRight = m_pPlayer->GetRight();
	float playerTop = m_pPlayer->GetTop();
	float playerBottom = m_pPlayer->GetBottom();

	for (int x = 0; x < kChipNumX; x++)
	{
		// ここの処理を工夫してもっと処理を早くできる
		for (int y = 0; y < kChipNumY; y++)
		{
			// 壁以外とは当たらない
			if (kChipData[y][x] == 0)continue;

			int chipLeft = kChipW * x;
			int chipRight = chipLeft + kChipW;
			int chipTop = kChipH * y;
			int chipBottom = chipTop + kChipH;

			// 絶対当たらない場合は次へ
			if (chipLeft > playerRight)continue;
			if (chipTop > playerBottom)continue;
			if (chipRight < playerLeft)continue;
			if (chipBottom < playerTop)continue;

			// 何れかのチップと当たっていたら終了
			return true;
		}
	}
	// 全てのチップをチェックして１つも当たっていなければ当たっていない

	return false;
}

bool Map::IsCol(Rect rect, Rect& chipRect)
{
	for (int x = 0; x < kChipNumX; x++)
	{
		// ここの処理を工夫してもっと処理を早くできる
		for (int y = 0; y < kChipNumY; y++)
		{
			// 壁以外とは当たらない
			if (kChipData[y][x] == 0)continue;

			int chipLeft = kChipW * x;
			int chipRight = chipLeft + kChipW;
			int chipTop = kChipH * y;
			int chipBottom = chipTop + kChipH;
			 
			// 絶対当たらない場合は次へ
			if (chipLeft > rect.right)continue;
			if (chipTop > rect.bottom)continue;
			if (chipRight < rect.left)continue;
			if (chipBottom < rect.top)continue;

			// ぶつかったマップチップの矩形を設定する
			chipRect.left = chipLeft;
			chipRect.right = chipRight;
			chipRect.top = chipTop;
			chipRect.bottom = chipBottom;

			// 何れかのチップと当たっていたら終了
			return true;
		}
	}
	// 全てのチップをチェックして１つも当たっていなければ当たっていない

	return false;
}
