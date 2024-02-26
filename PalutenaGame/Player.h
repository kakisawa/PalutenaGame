#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneExplanation;
class SceneMain;
class SceneSecond;
class MozueyeEnemy;
class DeathYourEnemy;
class PumpkinEnemy;
class Shot;
class SoundManager;
class FontManager;
class ColorManager;

// プレイヤーが向いている方向
enum Dir
{
	kDirFront,	// 正面
	kDirDown,	// 下
	kDirLeft,	// 左
	kDirRight,	// 右
	kDirUp,		// 上
};

// プレイヤーが弾を撃つ方向
enum ShotDir
{
	kShotDirLeft,	// 左
	kShotDirRight,	// 右
	kShotDirUp,		// 上
};

class Player
{
public:
	Player();
	Player(SceneMain* pMain);
	Player(SceneSecond* pSceneSecond);
	~Player();

	void Init();
	void Update();
	void Draw();
	void End();

	void OnDamage_Mozu();	// プレイヤー被ダメ処理(敵_モズアイ)
	void OnDamage_Death();	// プレイヤー被ダメ処理(敵_死)
	void OnDamage_Pump();	// プレイヤー被ダメ処理(敵_パンプキン)
	void Death();			// プレイヤー死亡時処理
	void HpDraw();			// プレイヤーのHP描画

public:
	void SetHandle(int handle) { m_graph = handle; }	// メンバー変数にアクセスする
	void AddScore(int Score) { m_score += Score; }		// スコアを追加する
	// 敵の攻撃力を獲得する
	void SetMozu(MozueyeEnemy* pMozu) { m_pMozueyeEnemy = pMozu; }
	void SetDeath(DeathYourEnemy* pDeath) { m_pDeathYourEnemy = pDeath; }
	void SetPump(PumpkinEnemy* pPump) { m_pPumpkinEnemy = pPump; }
	int GetAtk() const { return m_atk; }				// プレイヤーの攻撃力を取得する
	int GetScore() const { return m_score; }			// スコアを取得する
	bool GetPlayerDeath() const { return m_isDeath; }		// プレイヤーの生死状態を取得する
	Rect GetColRect() const { return m_colRect; }		// プレイヤーの当たり判定を取得する
	Vec2 GetPos() const { return m_pos; }				// プレイヤーの座標を取得する 	
	ShotDir GetShotDir() const { return m_shotDir; }	// プレイヤーがどの方向を向いているかを取得する

private:
	SceneExplanation* m_pOption;
	SceneMain* m_pMain;
	SceneSecond* m_pSecond;
	MozueyeEnemy* m_pMozueyeEnemy;
	DeathYourEnemy* m_pDeathYourEnemy;
	PumpkinEnemy* m_pPumpkinEnemy;
	Shot* m_pShot;
	SoundManager* m_pSoundManager;
	FontManager* m_pFontManager;
	ColorManager* m_pColorManager;

	int m_hp;			// プレイヤーの体力
	int m_atk;			// プレイヤーの攻撃力
	int m_score;		// プレイヤーの獲得スコア
	int m_graph;		// プレイヤーの画像
	int m_damageFrame;	// ダメージを受けてからのフレーム数
	int m_playerAnim;	// プレイヤーアニメーション
	float m_gravity;	// プレイヤーの重力
	float m_jumpPower;	// プレイヤーのジャンプ移動量
	
	bool m_isMove;		// プレイヤーが移動中かどうかのフラグ
	bool m_isTurn;		// プレイヤーの左右反転状況についてのフラグ
	bool m_isJump;		// プレイヤーがジャンプ中かどうかのフラグ
	bool m_isAttack;	// プレイヤーが攻撃したかどうかのフラグ
	bool m_isDeath;		// プレイヤーが死亡したかどうかのフラグ

	Vec2 m_pos;			// 表示位置
	Dir m_dir;			// 向いている方向
	ShotDir m_shotDir;	// 弾を打つ方向
	Rect m_colRect;		// 当たり判定用の矩形
};