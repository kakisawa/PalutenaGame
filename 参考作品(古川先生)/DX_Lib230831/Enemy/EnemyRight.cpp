#include "EnemyRight.h"
#include "DxLib.h"
#include "Game.h"

namespace 
{
	constexpr float kSpeed = 4.0f;
}

EnemyRight::EnemyRight()
//	m_posは引数なしのコンストラクタが呼ばれる
// 引数なしのコンストラクタを呼ぶ場合は省略できる
{
}

EnemyRight::~EnemyRight()
{
}

void EnemyRight::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	//	m_pos.x -= kSpeed;
	m_pos += m_vec;

	// 当たり判定の更新
	UpdateCollision();

	// ベクトルをいじってみる
	// 画面中央を超えたら加速する
	if (m_pos.x < Game::kScreenWidth / 2)
	{
		// 移動ベクトルを変化させることで速度を上げる
		// 左に移動する量を大きくすることで早く動いているように見せる
		m_vec.x -= 0.5f;
	}

	// 画面外に出たら存在を消す
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	if (m_pos.x < 0.0f - width /2)
	{
		m_isExist = false;
	}
}

void EnemyRight::Start()
{
	m_isExist = true;

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	m_pos.x = static_cast<float>(Game::kScreenWidth + width / 2);
	m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height) + height / 2);

	// 1フレーム当たりの移動ベクトルを決定する
	m_vec.x = -kSpeed;
	m_vec.y = 0.0f;
}
