#include "EnemyLeft.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	constexpr float kSpeed = 4.0f;

	constexpr float kWaveRange = 32.0f;	// 上下の移動量
	constexpr float kWaveSpeed = 0.1f;	// 
}

EnemyLeft::EnemyLeft() :
	EnemyBase(),	// 明示的に呼ぶ場合の例
	m_sinRate(0.0f)
{
	// 基底クラスのコンストラクタを明示的に呼ばなくてもここで呼ばれる
}

EnemyLeft::~EnemyLeft()
{
	// デストラクタも呼ばれるはず…
}

void EnemyLeft::Update()
{
	// 存在しない敵は処理しない
	if (!m_isExist) return;

	m_basePos += m_vec;

	m_pos += m_basePos;

	m_sinRate +=kWaveSpeed;
	m_pos.y += sinf(m_sinRate) * kWaveRange;

	//当たり判定の更新
	UpdateCollision();

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	if (m_pos.x > Game::kScreenWidth + width / 2)
	{
		m_isExist = false;
	}
}

void EnemyLeft::Start()
{
	// 画面中央に敵キャラクターを登場させる
	m_isExist = true;

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	m_basePos.x = static_cast<float>(0 - width / 2);
	m_basePos.y = static_cast<float>(GetRand(Game::kScreenHeight - height) + height / 2);

	m_pos = m_basePos;

	// 1フレーム当たりの移動ベクトルを確定する
	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
}
