#include "EnemyToPlayer.h"
#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include <cassert>

namespace 
{
	constexpr float kSpeed = 10.0f;
	//// キャラクターのサイズ
	//constexpr int kWidth = 28;
	//constexpr int kHeight = 34;

	//// キャラクターのアニメーション
	//constexpr int kUseFrame[] = { 0, 1, 2, 1 };
	//// アニメーション1コマのフレーム数
	//constexpr int kAnimFrameNum = 8;
	//// アニメーション1サイクルのフレーム数
	//constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

EnemyToPlayer::EnemyToPlayer() :
	m_pPlayer(nullptr)
//	m_posは引数なしのコンストラクタが呼ばれる
// 引数なしのコンストラクタを呼ぶ場合は省略できる
{
	// m_pPlayerにはSceneMainで既にメモリを確保したPlayerが
	// どこに置かれているのか、の情報を入れておきたいのでここではメモリ確保しない
}

EnemyToPlayer::~EnemyToPlayer()
{
	// m_pPlayerの確保開放はSceneMainが管理するので
	// 同様に開放も行わない
}



void EnemyToPlayer::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;

	m_pos += m_vec;

	// 当たり判定の更新
	UpdateCollision();

	//// ベクトルをいじってみる
	//// 画面中央を超えたら加速する
	//if (m_pos.x < Game::kScreenWidth / 2)
	//{
	//	// 移動ベクトルを変化させることで速度を上げる
	//	// 左に移動する量を大きくすることで早く動いているように見せる
	//	m_vec.x -= 0.5f;
	//}

	// 画面外に出たら存在を消す
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// "左に移動している敵が"画面左から完全に出きった敵を消す
//	if (m_pos.x < 0.0f - width)
	if ((m_vec.x < 0.0f) &&			// 左に移動している敵
		(m_pos.x < 0.0f - width / 2))	// 左から画面外に出た
	{
		m_isExist = false;
	}
	// "右に移動している敵が"画面左から完全に出きった敵を消す
	if ((m_vec.x > 0.0f) &&					// 右に移動している敵
		(m_pos.x > Game::kScreenWidth + width / 2))		// 右から画面外に出た
	{
		m_isExist = false;
	}
	// "上に移動している敵が"画面左から完全に出きった敵を消す
	if ((m_vec.y < 0.0f) &&			// 右に移動している敵
		(m_pos.y < 0.0f - height + height / 2))	// 右から画面外に出た
	{
		m_isExist = false;
	}
	// "下に移動している敵が"画面左から完全に出きった敵を消す
	if ((m_vec.y > 0.0f) &&					// 右に移動している敵
		(m_pos.y > Game::kScreenHeight + height / 2))	// 右から画面外に出た
	{
		m_isExist = false;
	}
	//// 右から出てきて左に消える敵前提の実装担っている
	//if (m_pos.x < 0.0f - width)
	//{
	//	m_isExist = false;
	//}

}

void EnemyToPlayer::Start()
{
	m_isExist = true;

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// 画面右から登場する
//	m_pos.x = static_cast<float>(Game::kScreenWidth);
//	m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));

	// 画面の上下左右いずれかから登場する
	// どこから出てくるかは分からない(ランダム)

	// rand()関数を使用してランダムな数字を生成する
	// rand()関数　ランダムな数字を生成する	範囲は0~RAND_MAX
	// rand()の戻り値を使うととても数字がでかい可能性がある
	// int num = rand() % 4;

	// もっといい感じのランダムを使う為今回は
	// DxLibのGetRand()関数を使用する

	int num = GetRand(3);

	switch  (num)
	{
	case 0:	// 上から
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - width) + width / 2);	// 横位置はランダム
		m_pos.y = static_cast<float>(-height / 2);	// ;画面上から入ってくる
		break;
	case 1:// 左から
		m_pos.x = static_cast<float>(-width / 2);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenWidth - height) + height / 2);
		break;
		case 2:// 下から
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - width) + width / 2);
		m_pos.y = static_cast<float>(Game::kScreenHeight + height / 2);
		break;
	case 3:// 右から
		m_pos.x = static_cast<float>(Game::kScreenWidth + width / 2);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenWidth - height) + height / 2);
		break;
	default:
		assert(false);
		break;
	}

	//// 1フレーム当たりの移動ベクトルを決定する
	//m_vec.x = -kSpeed;
	//m_vec.y = 0.0f;

	// 画面中央を経由して画面外まで一定速度で移動する
	// コンストラクタでnullptrが設定されて、それ以降変更されていなければ止まる
	assert(m_pPlayer);
	
	// ターゲット位置
//	const Vec2 target = Vec2{ Game::kScreenWidth / 2,Game::kScreenHeight / 2 };
	const Vec2 target = m_pPlayer->GetPos();

	// 敵の初期位置からターゲット位置に向かうベクトルを生成する
	// 始点から終点に向かうベクトルを求める場合、終点の座標-始点の座標で求める
	Vec2 toTarget = target - m_pos;

	// ベクトルの長さをkSpeedにしてやる

	// ベクトルの正規化　長さを1にする
	toTarget.normalize();
	// kSpeedでかける
	m_vec = toTarget * kSpeed;
}
