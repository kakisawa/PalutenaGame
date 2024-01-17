#include "ShotLineMove.h"
#include "Player.h"
#include "DxLib.h"
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

ShotLineMove::ShotLineMove():
	m_stopFrame(0),
	m_energy(28)
{
	m_handle = LoadGraph("data/image/Shot/shotLineMove.png");
}

ShotLineMove::~ShotLineMove()
{
}

void ShotLineMove::Init()
{
	m_stopFrame = 60;
}

void ShotLineMove::Update()
{
	// 弾が存在しなければ終了する
	if (!m_isExist) return;

	// プレイヤーのポインタが設定されていないとき止まる
	assert(m_pPlayer);

	// 静止時間を減らす
	m_stopFrame--;

	// 静止時間が0になったら動かす
	if (m_stopFrame < 0)
	{
		m_pos += m_vec;		// 現在位置を更新
	}

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);

	// TODO:障害物に当たったら消える
	//if ()
	//{
	//	m_isExist = false;
	//	return;	// 終了が確定したら以降の処理は行わない
	//}

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうか		true:画面外、false:画面内
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true;					// 画面左端
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true;	// 画面右端

	// チェック中の座標が画面内ならここで終了
	if (!isOut) return;

	// ここに来たということは画面外にいる
	m_isExist = false;
}

void ShotLineMove::Draw()
{
	if (!m_isExist) return;

	DrawGraph(m_pos.x, m_pos.y, m_handle, true);

#ifdef _DEBUG
	// 弾の当たり判定デバッグ表示
	m_colRect.Draw(0xff0000, false);
#endif
}

void ShotLineMove::Start(Vec2 pos)
{
	m_isExist = true;

	// 初期位置の設定
	if (m_pPlayer->GetDir()) // プレイヤーが右を向いている場合
	{
		m_pos.x = pos.x + 40;
		// 1フレームあたりの移動ベクトルを決定する
		m_vec.x = kSpeed;
	}
	else // プレイヤーが左を向いている場合
	{
		m_pos.x = pos.x - 40;
		// 1フレームあたりの移動ベクトルを決定する
		m_vec.x = -kSpeed;
	}
	m_pos.y = (pos.y + kHeight / 2);

	// アイテム2号を静止する時間
	m_stopFrame = 60;
}
