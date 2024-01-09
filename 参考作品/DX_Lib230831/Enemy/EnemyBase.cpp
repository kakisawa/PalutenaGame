#include "EnemyBase.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace 
{
}

EnemyBase::EnemyBase():
	m_handle(-1),
	m_isExist(false)
//	m_posは引数なしのコンストラクタが呼ばれる
// 引数なしのコンストラクタを呼ぶ場合は省略できる
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;
}

void EnemyBase::Draw()
{
	//float fNum = 1.0f;	// 32bit
	//double dNum = 1.0f;	// 64bit
	
	// 存在しない敵は描画しない
	if (!m_isExist) return;

	// グラフィックが設定されていなければ止まる
	assert(m_handle != -1);

	// DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle, false);
	
	// 中心位置を基準として判定する
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void EnemyBase::Start()
{
	m_isExist = false;
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
//	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
	// 中心座標を指定して当たり判定のRectを生成する
	m_colRect.SetCenter(m_pos.x, m_pos.y, width, height);
}