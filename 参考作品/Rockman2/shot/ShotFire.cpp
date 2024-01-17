#include "ShotFire.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "Game.h"
#include <cassert>

// 定数の定義
namespace
{
	// 弾の移動速度
	constexpr float kSpeed = 10.0f;
	// ショットの大きさ
	constexpr float kWidth = 32.0f;
	constexpr float kHeight = 32.0f;
}

ShotFire::ShotFire()
{
	// 弾のグラフィックロード
	m_handle = LoadGraph("data/image/Shot/shotFire.png");
	m_mediumHandle = LoadGraph("data/image/Shot/shotFire2.png");
	m_fullHandle = LoadGraph("data/image/Shot/shotFire3.png");
}

ShotFire::~ShotFire()
{
}

void ShotFire::Init()
{
}

void ShotFire::Update()
{
	// 弾が存在しなければ終了する
	if (!m_isExist) return;

	// プレイヤーのポインタが設定されていないとき止まる
	assert(m_pPlayer);

	// 現在位置の更新
	m_pos += m_vec;

	// 当たり判定の更新
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	// TODO:障害物に当たったら消える
	//if ()
	//{
	//	m_isExist = false;
	//	return;	// 終了が確定したら以降の処理は行わない
	//}

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // 画面左端
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // 画面右端

	// チェック中の座標が画面内ならここで終了
	if (!isOut) return;

	// ここに来たということは画面外にいる
	m_isExist = false;
}

void ShotFire::Draw()
{
	if (!m_isExist) return;

	if (m_pPlayer->GetPressTime() < 2000) // 長押し時間が2秒以下
	{
		DrawGraph(m_pos.x, m_pos.y, m_handle, true); // 通常サイズの弾を描画
	}
	else if (m_pPlayer->GetPressTime() < 5000) // 長押し時間が5秒以下
	{
		if (m_pPlayer->GetFireEnergy() - 6 < 0) // 弾エネルギーが足りない場合
		{
			DrawGraph(m_pos.x, m_pos.y, m_handle, true); // 通常サイズの弾を描画
		}
		else
		{
			DrawGraph(m_pos.x, m_pos.y, m_mediumHandle, true); // 中サイズの弾を描画
		}
	}
	else // 長押し時間が5秒以上
	{
		if (m_pPlayer->GetFireEnergy() - 10 < 0) // 弾エネルギーが足りない場合
		{
			DrawGraph(m_pos.x, m_pos.y, m_handle, true); // 通常サイズの弾を描画
		}
		else
		{
			DrawGraph(m_pos.x, m_pos.y, m_fullHandle, true); //大サイズの弾を描画
		}
	}

#ifdef _DEBUG
	// 弾の当たり判定デバッグ表示
	m_colRect.Draw(0xff0000, false);
#endif
}

void ShotFire::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	m_pos = pos;

	// 1フレームあたりの移動ベクトルを決定する
	if (m_pPlayer->GetDir()) // プレイヤーが右を向いている場合
	{
		m_vec.x = kSpeed;
	}
	else // プレイヤーが左を向いている場合
	{
		m_vec.x = -kSpeed;
	}
}
