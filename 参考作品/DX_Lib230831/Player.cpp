#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include "Pad.h"
#include "SceneMain.h"

#include "ShotMagicWand.h"
#include "ShotBible.h"

#include <cmath>

// Playerで使用する
namespace
{
	// 移動速度
	constexpr float kSpeed = 3.0f;

	// キャラクターのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,1 };
	// アニメーションの1コマのフレーム数
	constexpr int kAnimFrameNum = 8;
	// アニメーション1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;
	// 魔法の杖の発射間隔
	constexpr int kMagicWandFrame = 30;
}

Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_handle(-1),
	m_pos(Game::kScreenWidth / 2, Game::kScreenHeight / 2),
	m_dir(kDirDown),
	m_walkAnimFrame(0),
	m_magicWandFrame(0),
	m_damageFrame(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	// ダメージ演出の進行
	m_damageFrame--;
	if (m_damageFrame < 0)	m_damageFrame = 0;

	// パッドの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool isMove = false;	// 移動中かどうか
	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	if (pad & PAD_INPUT_UP)
	{
		// m_pos.y -= kSpeed;
		move.y -= kSpeed;
		m_dir = kDirUp;
		isMove = true;
	}
	if (pad & PAD_INPUT_DOWN)
	{
		//m_pos.y += kSpeed;
		move.y += kSpeed;
		m_dir = kDirDown;
		isMove = true;
	}
	if (pad & PAD_INPUT_LEFT)
	{
		// m_pos.x -= kSpeed;
		move.x -= kSpeed;
		m_dir = kDirLeft;
		isMove = true;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		// m_pos.x += kSpeed;
		move.x += kSpeed;
		m_dir = kDirRight;
		isMove = true;
	}

	// 斜め移動の場合も同じ速さで移動するようにする
		/*
	// ベクトルの正規化を行う為にベクトルの長さを求める
	float moveLength = move.length();
	sqrt(1.0);		// double型の平方根を求めたい場合はこっち
	sqrtf(1.0f);	// float型の場合はこっち
	moveLength = sqrtf(moveLength);	// 平方根を求めて長さに
	*/

	// ベクトルの正規化
	move.normalize();
	/*
	// moveLength(ベクトルの長さ)が0.0の可能性がある
	if (moveLength > 0.0f)
	
		
	// ベクトルの長さでベクトルを割る
		move.x /= moveLength;
		move.y /= moveLength;

	*/

	// ベクトルの長さをkSpeedにする
	move *= kSpeed;
	/*
	move.x *= kSpeed;
	move.y *= kSpeed;	
	move = move.mul(kSpeed);
*/

	// 座標とベクトルの足し算
	m_pos += move;
	/*
	m_pos.x += move.x;
	m_pos.y += move.y;
	m_pos = m_pos.puls(move);
	m_pos += move;*/

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
	
	if (isMove)
	{
		// 歩きアニメーション
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}
	}

	// ショット
	m_magicWandFrame++;
	if (m_magicWandFrame >= kMagicWandFrame)
	{
		m_magicWandFrame = 0;

		// 魔法の杖生成
		ShotMagicWand* pShot = new ShotMagicWand;

		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(GetPos());
		// 以降更新やメモリの開放はSceneMainに任せる
		m_pMain->AddShot(pShot);
	}

	// 聖書テスト実装
	// ボタンを押したら発生するようにする
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// 聖書メモリの確保
		ShotBible* pShot = new ShotBible;

		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(GetPos());
		// 以降更新やメモリの開放はSceneMainに任せる
		m_pMain->AddShot(pShot);
	}
}


void Player::Draw()
{
	// ダメージ演出 2フレーム間隔で表示非表示切り替え
	// 0: 表示される
	// 1:表示される
	// 2:非表示
	// 3:非表示
	// 4:表示される	...
	// %4することで012301230123...に変換する
	if (m_damageFrame % 4 >= 2) return;

	// DrawGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, true);	// C++のキャストは少し複雑

	int animFrame = m_walkAnimFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

#if false
	switch (m_dir)
	{
	case kDirDown:
		srcY = 32 * 0;
		break;
	case kDirLeft:
		srcY = 32 * 1;
		break;
	case kDirRight:
		srcY = 32 * 2;
		break;
	case kDirUp:
		srcY = 32 * 3;
		break;
	}
#endif

//	DrawRectGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
//		srcX, srcY, kWidth, kHeight, m_handle, true);
	
	// Dxライブラリにはリファレンスページに書かれていない関数が多数存在する
	// DxLib.hを確認してそれっぽい関数を探したり検索してみよう
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		srcX, srcY, kWidth, kHeight,
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void Player::OnDamage()
{
	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0)	return;
	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;
}
