#include "ShotBuster.h"
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

ShotBuster::ShotBuster()
{
	// 弾のグラフィックロード
	m_handle = LoadGraph("data/image/Shot/shotBuster.png");
}

ShotBuster::~ShotBuster()
{
}

void ShotBuster::Init()
{
}

void ShotBuster::Update()
{
	// 弾が存在しなければ終了する
	if (!m_isExist) return;

	// プレイヤーのポインタが設定されていないとき止まる
	assert(m_pPlayer);

	// 現在位置の更新
	m_pos += m_vec;

	// 当たり判定の更新
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	// 障害物に当たったら消える
	//if ()
	//{
	//	m_isExist = false;
	//	return;	// 終了が確定したら以降の処理は行わない
	//}

	// 画面外に出た処理
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // 画面左端
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // 画面右端

	// 画面内ならここで終了
	if (!isOut) return;

	// 画面外に出た
	m_isExist = false;

}

void ShotBuster::Draw()
{
	if (!m_isExist) return;

	DrawGraph(m_pos.x, m_pos.y, m_handle, true);

#ifdef _DEBUG
	// 弾の当たり判定デバッグ表示
	m_colRect.Draw(0xff0000, false);
#endif
}

void ShotBuster::Start(Vec2 pos)
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
