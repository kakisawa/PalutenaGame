#include "ShotMagicWand.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include <cassert>

namespace
{
	// 定数の定義

	constexpr float kSpeed = 8.0f;	// 弾の移動速度

	// ショットの大きさ
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;

	// 覚えておく過去の位置情報の数
	constexpr int kPosLogNum = 8;
}

ShotMagicWand::ShotMagicWand()
{
	m_posLog.resize(kPosLogNum);
}

ShotMagicWand::~ShotMagicWand()
{
}

void ShotMagicWand::Init()
{
}

void ShotMagicWand::Update()
{
	if (!m_isExist) return;

	// 位置のログをずらす
//	for (int i = 1; i < m_posLog.size(); i++)
	for (int i = m_posLog.size() - 1; i >= 1; i--)
	{
		m_posLog[i] = m_posLog[i - 1];
	}
	// 1フレーム前の位置情報を入れる
	m_posLog[0] = m_pos;

	m_pos += m_vec;
	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	// 画面外に出た処理
	// 過去の表示位置も含めてすべて画面外に出たら終了
	bool isOut = false;	// チェック中の座標が画面外かどうかフラグ

	if (m_pos.x < 0.0f - kWidth / 2)	isOut = true;
	if (m_pos.x > Game::kScreenWidth + kWidth / 2)	isOut = true;
	if (m_pos.y < 0.0f - kHeight / 2)	isOut = true;
	if (m_pos.y > Game::kScreenHeight + kHeight / 2)	isOut = true;
	// チェック中の座標が画面内ならここで終了
	if (isOut) return;

	// 過去ログも画面内にあるかをチェックする
	for (int i = 0; i < m_posLog.size(); i++)
	{
		isOut = false;
		if (m_posLog[i].x < 0.0f - kWidth / 2)	isOut = true;
		if (m_posLog[i].x > Game::kScreenWidth + kWidth / 2)	isOut = true;
		if (m_posLog[i].y < 0.0f - kHeight / 2)	isOut = true;
		if (m_posLog[i].y > Game::kScreenHeight + kHeight / 2)		isOut = true;
		// チェック中の座標が画面内ならここで終了
		if (isOut) return;
	}

	// ここに来たという事は画面外にいる
	m_isExist = false;
	//if ((m_vec.x < 0.0f) &&
	//	(m_pos.x < 0.0f - kWidth / 2))
	//{
	//	m_isExist = false;
	//}
	//if ((m_vec.x > 0.0f) &&
	//	(m_pos.x > Game::kScreenWidth / 2))
	//{
	//	m_isExist = false;
	//}
	//if ((m_vec.y < 0.0f) &&
	//	(m_pos.y < 0.0f - kHeight / 2))
	//{
	//	m_isExist = false;
	//}
	//if ((m_vec.y > 0.0f) &&
	//	(m_pos.y > Game::kScreenHeight / 2))
	//{
	//	m_isExist = false;
	//}
}

void ShotMagicWand::Draw()
{
	if (!m_isExist) return;

#if false
	// 残像の表示
	// 0が最新、7が古い
	// 0が濃く表示、7が薄く表示
	for (int i = 0; i < m_posLog.size(); i++)
	{
		int alpha = 255 - (20 * (i + 1));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(m_posLog[i].x - kWidth / 2, m_posLog[i].y - kHeight / 2,
			m_posLog[i].x + kWidth / 2, m_posLog[i].y + kHeight / 2, GetColor(255, 255, 0), true);
	}
	// 表示モードを基に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	// 弾の実体
	DrawBox(m_pos.x - kWidth / 2, m_pos.y - kHeight / 2, 
		m_pos.x + kWidth / 2, m_pos.y + kHeight / 2 , GetColor(255, 255, 0), true);
#else
	
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 1; i < m_posLog.size(); i++)
	{
		for (int listNum = 0; listNum < 8; listNum++)
		{
			int startX = m_pos.x;
			int startY = m_pos.y;
			int endX = m_posLog[i].x;
			int endY = m_posLog[i].y;

			// ここはやってない内容
			// かっこよくするために使う
			float angle = GetRand(359) / 360.0f* DX_TWO_PI_F ;
			float len = GetRand(3) - 1;
			startX += cosf(angle) * len;
			startY += sinf(angle) * len;
			/*angle = GetRand(359) / 360.0f * DX_TWO_PI_F;
			len = GetRand(4) - 2;*/
			endX += cosf(angle) * len;
			endY += sinf(angle) * len;

			DrawLine(startX, startY, endX, endY,
				GetColor(16, 4, 1), kWidth);
		}
	}
	// 表示モードを基に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif
#ifdef _DEBUG
	// 弾の当たり判定デバッグ表示
	m_colRect.Draw(GetColor(0, 0, 0), false);
#endif
}

void ShotMagicWand::Start(Vec2 pos)
{
	// SceneMainの設定忘れチェック
	assert(m_pMain);	// m_pMain == nullptrなら止まる

	m_isExist = true;
	// 初期位置の設定
	m_pos = pos;

	// 過去の位置情報を初期化時点では初期化位置と同じにしてしまう
	// 残像が変な位置に表示されないようにする為
	for (int i = 0; i < m_posLog.size(); i++)
	{
		m_posLog[i] = m_pos;
	}

	// 一番近い敵の方向に移動する

	// ターゲット位置
	// 弾の発射位置から一番近くにいる敵の座標を取得する
	// SceneMainに実装した関数を利用する
	const Vec2 target = m_pMain->GetNearEnemyPos(m_pos);

	// 発射位置からターゲットに向かうベクトル
	Vec2 toTarget = target - m_pos;
	// 正規化
	toTarget.normalize();
	// 弾の速度をkSpeedに
	m_vec = toTarget * kSpeed;

	//// 仮実装　右向きに移動させる
	//m_vec.x = kSpeed;
	//m_vec.y = 0.0f;
}