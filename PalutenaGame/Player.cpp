#include "DxLib.h"
#include "Player.h"

#include "SceneMain.h"
#include "SceneSecond.h"
#include "MozueyeEnemy.h"
#include "DeathYourEnemy.h"
#include "PumpkinEnemy.h"
#include "Shot/Shot.h"
#include "SoundManager.h"
#include "Game.h"
#include "Pad.h"

namespace
{
	// キャラクターのサイズ
	constexpr int kWidth = 48;
	constexpr int kHeight = 48;

	// プレイヤーHP初期値
	constexpr int kHP = 100;
	// プレイヤーAtk初期値
	constexpr int kAtk = 1;

	// 移動速度
	constexpr float kSpeed = 3.0f;
	// ジャンプ距離
	constexpr float kJump = 18.0f;

	// 基本キャラアニメーション
	constexpr int DefFrame[] = { 0,1,2,3,4,5 };
	// 基本キャラアニメーションの1コマのフレーム数
	constexpr int DefAnimFrameNum = 8;
	// 基本キャラアニメーション1サイクルのフレーム数
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;
	// 攻撃時キャラアニメーション		
	constexpr int AttackFrame[] = { 1,0,2,3,4,5 };
	// 攻撃時キャラアニメーション1コマのフレーム数
	constexpr int AttackAnimFrameNum = 8;
	// 攻撃時キャラアニメーション1サイクルのフレーム数
	constexpr int AttackFrameCycle = _countof(AttackFrame) * AttackAnimFrameNum;
	// 死亡時キャラアニメーション1コマのフレーム数
	constexpr int DeathAnimFrameNum = 4;
	// 死亡時キャラアニメーション1サイクルのフレーム数
	constexpr int DeathFrameCycle = _countof(DefFrame) * DeathAnimFrameNum;
	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;
}

Player::Player() :
	Graph(-1),
	Atk(kAtk)
{
}

Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	Graph(-1),
	Atk(kAtk),
	m_Score(0)			// プレイヤーが獲得しているスコアの初期化
{
	// メモリ確保
	m_pSoundManager = new SoundManager;
	m_pDeathYourEnemy = new DeathYourEnemy;
	m_pMozueyeEnemy = new MozueyeEnemy;
	m_pPumpkinEnemy = new PumpkinEnemy;
}

Player::Player(SceneSecond* pSceneSecond):
	m_pSecond(pSceneSecond),
	Graph(-1),
	Atk(kAtk)
{
	// メモリ確保
	m_pSoundManager = new SoundManager;
	m_pDeathYourEnemy = new DeathYourEnemy;
	m_pMozueyeEnemy = new MozueyeEnemy;
	m_pPumpkinEnemy = new PumpkinEnemy;
}

Player::~Player()
{
	// メモリ解放
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

void Player::Init()
{
	HP = kHP;					// プレイヤーの初期HP
	m_pos.x = kScreenWidth / 2;	// プレイヤーの初期位置x
	m_pos.y = 100;				// プレイヤーの初期位置y
	m_dir = kDirFront;			// プレイヤーの初期方向(正面のflont)
	m_shotDir = kShotDirRight;	// プレイヤーの攻撃初期方向
	JumpPower = 0.0f;			// プレイヤーの初期ジャンプ
	Gravity = 0.0f;				// プレイヤーの初期重力
	m_Score = 0;
	Atk = kAtk;					// プレイヤーの初期攻撃力
	PlayerAnim = 0;				// プレイヤーアニメーションの初期化
	m_damageFrame = 0;			// プレイヤー被ダメアニメーション  
	isMove = false;				// 移動状態フラグ(否定のfalse)
	isTurn = false;				// 左右反転フラグ(否定のfalse)
	isAttack = false;			// 攻撃フラグ(否定のfalse)
	isDeath = false;			// 死亡フラグ(否定のfalse)
	m_damageFrame = 0;

	//サウンドマネージャーの初期化
	m_pSoundManager->Init();
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
	m_dir = kDirFront;			// 正面を向いているの正面を向いているのkDirFront

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

	// プレイヤーが死亡していないときは行動できる
	if (!PlayerDeath()) {

		// 矢印キーを押していたらプレイヤーを移動させる
		// 上向き
		if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			isMove = false;
			m_dir = kDirUp;
			m_shotDir = kShotDirUp;
		}
		// 屈む
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			isMove = true;
			m_dir = kDirDown;
		}
		// 左移動
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			m_pos.x -= kSpeed;
			isMove = true;
			isTurn = true;
			m_dir = kDirLeft;
			m_shotDir = kShotDirLeft;
		}
		// 右移動
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			m_pos.x += kSpeed;
			isMove = true;
			isTurn = false;
			m_dir = kDirRight;
			m_shotDir = kShotDirRight;
		}
		// ジャンプボタンを押していて、地面についていたらジャンプ
		if (Pad::IsTrigger(PAD_INPUT_1) && m_pos.y == Ground)
		{

			// ジャンプ加速度
			for (int i = 0; i < kJump; i++) {
				JumpPower += 0.5f;
			}
			isJumpFlag = true;
			isMove = true;

			m_pSoundManager->SoundJump();
		}
		// スペースキーを押していたら攻撃
		if (Pad::IsTrigger(PAD_INPUT_10))
		{
			// ショットメモリの確保
			Shot* pShot = new Shot();
			
			pShot->SetMain(m_pMain);
			//pShot->SetSecond(m_pSecond);
			pShot->SetPlayer(this);
			pShot->init();
			pShot->Start(m_pos);
			isAttack = true;
			// 以降更新やメモリの開放はSceneMainに任せる
			m_pMain->AddShot(pShot);
			//m_pSecond->AddShot(pShot);

			m_pSoundManager->SoudndAttack();
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
			if (PlayerAnim >= DefFrameCycle)
			{
				PlayerAnim = 0;
			}
		}
		else if (isMove == true)
		{
			// 左右移動アニメーション
			PlayerAnim++;
			if (PlayerAnim >= DefFrameCycle)
			{
				PlayerAnim = 0;
			}
		}
		else if (isMove == true && m_dir == kDirDown)
		{
			// しゃがみアニメーション
			PlayerAnim++;
			if (PlayerAnim >= DefFrameCycle)
			{
				PlayerAnim = 0;
			}
		}
		else if (isJumpFlag == true)
		{
			// ジャンプアニメーション
			PlayerAnim++;
			if (PlayerAnim >= DefFrameCycle)
			{
				PlayerAnim = 0;
			}
		}
		else if (isAttack == true)
		{
			// 攻撃アニメーション
			PlayerAnim++;
			if (PlayerAnim >= AttackFrameCycle)
			{
				PlayerAnim = 0;
			}
		}
	}
}

void Player::Draw()
{
	SetFontSize(16);
	// プレイヤーの現在体力表示
	DrawFormatString(80, 0, GetColor(255, 255, 255),
		"PlayerHP:%d", HP);

	SetFontSize(64);
	DrawFormatString(kScreenWidth*0.45f, kScreenHeight*0.15f, GetColor(255, 255, 255),
		"Score:%d", m_Score);

	if (!PlayerDeath()) {
		// ダメージ演出 2フレーム間隔で表示非表示切り替え
		// 0: 表示される
		// 1:表示される
		// 2:非表示
		// 3:非表示
		// 4:表示される	...
		// %4することで012301230123...に変換する
		if (m_damageFrame % 4 >= 2) return;

		// プレイヤーアニメーション
		int DefPlayerFrame = PlayerAnim / DefAnimFrameNum;
		int AttackPlayerFrame = PlayerAnim / AttackAnimFrameNum;
		int srcX = DefFrame[DefPlayerFrame] * 16;
		int srcX2 = AttackFrame[AttackPlayerFrame] * 32;

		// プレイヤーの通常立ち絵(画像の中から切り抜いて拡大する)
		if (isMove == false && m_dir == kDirFront || m_dir == kDirUp && isJumpFlag == false && isAttack == false && isDeath == false)
		{
			// 右向き
			if (isTurn == false)
			{
				DrawRectExtendGraph(m_pos.x, m_pos.y,
					m_pos.x + kWidth, m_pos.y + kHeight,
					srcX + 2, 64, 13, 16,
					Graph, true);
			}
			// 左向き
			else if (isTurn == true)
			{
				DrawRectExtendGraph(m_pos.x + kWidth, m_pos.y,
					m_pos.x, m_pos.y + kHeight,
					srcX + 2, 64, 13, 16,
					Graph, true);
			}
		}
		// プレイヤー移動
		if (isMove == true && isJumpFlag == false && isAttack == false && isDeath == false)
		{
			// 右向き
			if (m_dir == kDirRight)
			{
				DrawRectExtendGraph(m_pos.x, m_pos.y,
					m_pos.x + kWidth, m_pos.y + kHeight,
					srcX + 2, 80, 13, 17,
					Graph, true);
			}
			// 左向き
			else if (m_dir == kDirLeft)
			{
				DrawRectExtendGraph(m_pos.x + kWidth, m_pos.y,
					m_pos.x, m_pos.y + kHeight,
					srcX + 2, 80, 13, 17,
					Graph, true);
			}
		}
		// プレイヤーしゃがみ
		if (isMove == true && m_dir == kDirDown && isAttack == false && isDeath == false)
		{
			// 右向き
			if (isTurn == false)
			{
				DrawRectExtendGraph(m_pos.x, m_pos.y,
					m_pos.x + kWidth, m_pos.y + kHeight,
					srcX + 2, 32, 13, 16,
					Graph, true);
			}
			// 左向き
			else if (isTurn == true)
			{
				DrawRectExtendGraph(m_pos.x + kWidth, m_pos.y,
					m_pos.x, m_pos.y + kHeight,
					srcX + 2, 32, 13, 16,
					Graph, true);
			}
		}
		// プレイヤージャンプ
		if (isJumpFlag == true && isAttack == false && isDeath == false)
		{
			// 右向き
			if (isTurn == false)
			{
				DrawRectExtendGraph(m_pos.x, m_pos.y,
					m_pos.x + kWidth, m_pos.y + kHeight,
					srcX + 97, 64, 13, 16,
					Graph, true);
			}
			// 左向き
			else if (isTurn == true)
			{
				DrawRectExtendGraph(m_pos.x + kWidth, m_pos.y,
					m_pos.x, m_pos.y + kHeight,
					srcX + 97, 64, 13, 16,
					Graph, true);
			}
		}
		// プレイヤー攻撃
		if (isAttack == true && isDeath == false)
		{
			// 右向き
			if (isTurn == false)
			{
				DrawRectExtendGraph(m_pos.x, m_pos.y - kWidth * 1.1,
					m_pos.x + kWidth, m_pos.y + kHeight,
					srcX2 + 3, 0, 26, 32,
					Graph, true);
			}
			// 左向き
			else if (isTurn == true)
			{
				DrawRectExtendGraph(m_pos.x + kWidth, m_pos.y - kWidth * 1.1,
					m_pos.x, m_pos.y + kHeight,
					srcX2 + 3, 0, 26, 32,
					Graph, true);
			}

			// 攻撃ボタンをIsTriggerにしている為、isAttackが一瞬しか反応していない。
			// 　なので恐らく、一瞬描画した後にデフォルトの描画に戻っている模様。
			// 　最終的には、1ループ分のアニメーションは動いてほしい
		}
	}
#ifdef _DEBUG
	int y = 19;

	SetFontSize(16);
	// プレイヤーの現在座標表示
	DrawFormatString(80, y*1, GetColor(255, 255, 255),
		"現在座標:(%.2f,%.2f)", m_pos.x, m_pos.y);
	DrawFormatString(80, y*2, GetColor(255, 255, 255),
		"isMove:(%d)", isMove);
	DrawFormatString(80, y*3, GetColor(255, 255, 255),
		"isAttack:(%d)", isAttack);
	DrawFormatString(80, y*4, GetColor(255, 255, 255),
		"m_dir:(%d)", m_dir);
	DrawFormatString(80, y*5, GetColor(255, 255, 255),
		"isTurn:(%d)", isTurn);

	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

void Player::Death()
{
	// SEを止める
	StopSoundMem(m_pSoundManager->m_soundAttack);
	StopSoundMem(m_pSoundManager->m_soundJump);
	StopSoundMem(m_pSoundManager->m_soundDamage);

	if (isDeath == true)
	{
		// 死亡時アニメーション
		PlayerAnim++;
		if (PlayerAnim >= DeathFrameCycle)
		{
			PlayerAnim = 300;
		}

		// プレイヤーアニメーション
		int DeathPlayerFrame = PlayerAnim / DefAnimFrameNum;
		int srcX2 = DefFrame[DeathPlayerFrame] * 16;

		// ↑詰まる所、一度最終フレーム(6)まで来たらそれ以降は計算しないようにしたい
		// 　そうしたら、死にモーションの最後のコマで止まり続ける。
		// boolで一回回ったら止まるようにするのもあり

		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX2, 48, 15, 17,
			Graph, true);
	}
}

void Player::End()
{
	// 背景をメモリから削除
	DeleteGraph(Graph);

	m_pSoundManager->End();
}

void Player::OnDamage_Mozu()
{
	// 被ダメージSE
	m_pSoundManager->SoundDamage();

	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0)	return;

	// プレイヤーのHPを、敵の攻撃力分減らす
	HP -= m_pMozueyeEnemy->GetEnemyAtk();

	// HPが0以下になった場合、プレイヤーの死亡フラグをtrueにする
	if (HP <= 0)
	{
		isDeath = true;
	}

	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;

#ifdef _DEBUG
	// 敵とプレイヤーの当たり判定が反応したか
	printfDx("当たった\n");
#endif
}

void Player::OnDamage_Death()
{
	// 被ダメージSE
	m_pSoundManager->SoundDamage();

	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0) return;

	// プレイヤーのHPを、敵の攻撃力分減らす
	HP -= m_pDeathYourEnemy->GetEnemyAtk();

	// HPが0以下になった場合、プレイヤーの死亡フラグをtrueにする
	if (HP <= 0)
	{
		isDeath = true;
	}

	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;

#ifdef _DEBUG
	// 敵とプレイヤーの当たり判定が反応したか
	printfDx("当たった\n");
#endif
}

void Player::OnDamage_Pump()
{
	// 被ダメージSE
	m_pSoundManager->SoundDamage();

	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0)	return;

	// プレイヤーのHPを、敵の攻撃力分減らす
	HP -= m_pPumpkinEnemy->GetEnemyAtk();

	// HPが0以下になった場合、プレイヤーの死亡フラグをtrueにする
	if (HP <= 0)
	{
		isDeath = true;
	}

	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;

#ifdef _DEBUG
	// 敵とプレイヤーの当たり判定が反応したか
	printfDx("当たった\n");
#endif
}
