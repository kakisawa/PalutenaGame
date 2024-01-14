#include "DxLib.h"
#include "Player.h"

#include "Game.h"
#include "Pad_Key.h"

namespace
{
	// キャラクターのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// 移動速度
	constexpr float kSpeed = 3.0f;
	// ジャンプ距離
	constexpr float kJump = 13.0f;

	// キャラクターのアニメーション		// モーションのフレームごとに作り直す
	constexpr int Frame[] = { 0,1,2,3,4,5,4,3,2,1 };
	// アニメーションの1コマのフレーム数
	constexpr int kAnimFrameNum = 8;
	// アニメーション1サイクルのフレーム数
	constexpr int FrameCycle = _countof(Frame) * kAnimFrameNum;
	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;
}

Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	Graph(-1),
	PlayerHP(100),						// プレイヤーの初期HP
	m_pos(kScreenWidth / 2, 100),	// プレイヤーの初期位置
	m_dir(kDirFront),				// プレイヤーの初期方向
	JumpPower(0.0f),				// プレイヤーの初期ジャンプ
	Gravity(0.0f),					// プレイヤーの初期重力
	PlayerAnim(0),					// プレイヤーアニメーションの初期化
	m_damageFrame(0),				// プレイヤー被ダメアニメーション
	isMove(false),					// 移動状態フラグ(否定のfalse)
	isAttack(false)					// 攻撃フラグ(否定のfalse)
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

	// プレイヤーが移動中かどうか
	isMove = false;				// 移動していないのfalse
	// プレイヤーが攻撃ボタンを押したかどうか
	isAttack = false;			// 攻撃していないのfalse
	// プレイヤーがどの方向を向いているか
//	m_dir = kDirFront;			// 正面を向いているの正面を向いているのkDirFront

	// パッド入力取得
	int Pad = GetJoypadInputState(DX_CHECKINPUT_PAD);
	// キー入力取得
	int Key = CheckHitKey(DX_CHECKINPUT_KEY);


	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	// 重力処理
	m_pos.y += Gravity;
	// 落下加速度を加える
	Gravity += 0.3f;

	// もし地面についていたら止まる
	if (m_pos.y > Ground)
	{
		m_pos.y = Ground;

		if (m_pos.y == Ground)
		{
			Gravity = 0;
			JumpPower = 0;

			isJumpFlag = false;
		}
	}

	// 矢印キーを押していたらプレイヤーを移動させる
	// 上向き
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		isMove = false;
		m_dir = kDirUp;

		// デバッグ用
	//	m_pos.y -= kSpeed;

	}
	// 屈む
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		isMove = true;
		m_dir = kDirDown;

		// デバッグ用
		//m_pos.y += kSpeed;
	}
	// 左移動
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		m_pos.x -= kSpeed;
		isMove = true;
		m_dir = kDirLeft;
	}
	// 右移動
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		m_pos.x += kSpeed;
		isMove = true;
		m_dir = kDirRight;
	}
	// ジャンプボタンを押していて、地面についていたらジャンプ
	if (Key::IsTrigger(KEY_INPUT_Z) && m_pos.y == Ground)	//IsTrigger
	{
		// ジャンプ加速度
		for (int i = 0; i < kJump; i++) {
			JumpPower += 0.5f;
		}
		isJumpFlag = true;
		isMove = true;
	}
	// スペースキーを押していたら攻撃
	if (Key::IsTrigger(KEY_INPUT_SPACE))
	{
		isAttack = true;
	}

	// ジャンプ処理
	m_pos.y -= JumpPower;


	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;
	// 座標とベクトルの足し算
	m_pos += move;
	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);

	// x座標...プレイヤーが左右画面外に出ると、反対側からプレイヤーが出てくる
	if (m_pos.x > kScreenWidth - kWidth)
	{
		m_pos.x = 0;
	}
	if (m_pos.x < 0)
	{
		m_pos.x = kScreenWidth - kWidth;
	}


	// 待機&左右移動アニメーションフレーム
	if (isMove == false)	//  && isJumpFlag == false
	{
		// 待機状態アニメーション
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isMove == true)
	{
		// 左右移動アニメーション
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isMove == true && m_dir == kDirDown)
	{
		// しゃがみアニメーション
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isJumpFlag == true)
	{
		// ジャンプアニメーション
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
	}
	else if (isAttack == true)
	{
		// 攻撃アニメーション
		PlayerAnim++;
		if (PlayerAnim >= FrameCycle)
		{
			PlayerAnim = 0;
		}
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

	// プレイヤーアニメーション
	int PlayerFrame = PlayerAnim / kAnimFrameNum;
	int srcX = Frame[PlayerFrame] * 16;
	int srcX2 = Frame[PlayerFrame] * 32;

	// プレイヤーの通常立ち絵(画像の中から切り抜いて拡大する)
	if (isMove == false && isJumpFlag == false && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 64, 13, 16,
			Graph, true);
	}
	// プレイヤー左移動
	else if (isMove == true && m_dir == kDirLeft && isJumpFlag == false && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 97, 79, 13, 16,
			Graph, true);
	}
	// プレイヤー右移動
	else if (isMove == true && m_dir == kDirRight && isJumpFlag == false && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 79, 13, 16,
			Graph, true);
	}
	// プレイヤーしゃがみ
	else if (isMove == true && m_dir == kDirDown && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 32, 13, 16,
			Graph, true);
	}
	// プレイヤージャンプ
	else if (isJumpFlag == true && isAttack == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 97, 64, 13, 16,
			Graph, true);
	}
	// プレイヤー攻撃
	else if (isAttack == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y - kWidth * 1.1,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX2 + 3, 0, 26, 32,
			Graph, true);
	}

	// プレイヤーの現在座標表示
	DrawFormatString(0, 0, GetColor(255, 255, 255),
		"現在座標:(%.2f,%.2f)", m_pos.x, m_pos.y);
	// プレイヤーの現在体力表示
	DrawFormatString(0, 19, GetColor(255, 255, 255),
		"PlayerHP:(%d)", PlayerHP);

	DrawFormatString(0, 38, GetColor(255, 255, 255),
		"isMove:(%d)", isMove);
	DrawFormatString(0, 57, GetColor(255, 255, 255),
		"isAttack:(%d)", isAttack);
	DrawFormatString(0, 76, GetColor(255, 255, 255),
		"m_dir:(%d)", m_dir);

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void Player::OnDamage()
{
	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0)	return;
	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;
}

// 地面処理まで終わってるはず
// 1,プレイヤーのアニメーション
// 4,単押しでジャンプ(優先度低)
// 〇5,当たり判定
// 〇HP管理・表示

// 背景表示
// シーン遷移(タイトル、ゲーム画面)
// スクロール

// ショット

