#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Bg;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player(SceneMain* pMain);
	~Player();

	// マップのポインタを設定する
	void SetBg(Bg* pBg) { m_pBg = pBg; }

	void Init();
	void Update();
	void Draw();

	// マップチップとの当たり判定の処理
	void CheckHitMap();

	// プレイヤーがダメージを受けた時の処理
	void OnDamage();
	// プレイヤーがE缶取得処理
	void GetHpFullRecovery();
	// プレイヤーの回復処理
	void HpSmallRecovery();		// HP小回復
	void HpGreatRecovery();		// HP大回復
	void ShotSmallRecovery();	// 弾小回復
	void ShotGreatRecovery();	// 弾大回復
	void LifeRecovery();		// 残機回復
	void HpFullRecovery();		// HP全回復

	// アイテム2号に乗った際の処理
	void RideLineMove(Rect shotRect);

	// 現在の武器選択状態を更新する
	void ChangeShot(bool isBuster, bool isMetal, bool isFire, bool isLineMove);

public:
	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	// 現在位置を更新する
	void SetPos(Vec2 pos) { m_pos = pos; }
	// プレイヤーの現在の向きを取得する
	bool GetDir() const { return m_isRight; }
	// プレイヤーの現在座標を取得する
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

	// 現在のHPを取得する
	float GetHp() const { return m_hp; }
	// 現在の残機数を取得する
	int GetLife() const { return m_life; }
	// 現在のE缶数を取得
	int GetFullHpRecovery() const { return m_fullHpRecovery; }

	// 現在の弾エネルギー数を取得する
	float GetMetalEnergy() const { return m_metalEnergy; }
	float GetFireEnergy() const { return m_fireEnergy; }
	float GetLineEnergy() const { return m_lineEnergy; }

	// ボタンを押して離すまでの時間を取得する
	int GetPressTime() const { return m_nowPressTime; }

public:
	// 武器が選択中か取得する
	bool IstBuster() const { return m_isBuster; }	// バスター
	bool IsMetal() const { return m_isMetal; }		// メタル
	bool IsFire() const { return m_isFire; }		// ファイア
	bool IsLineMove() const { return m_isLineMove; }// 2号

private:
	SceneMain* m_pMain;
	Bg* m_pBg;

	// 表示位置
	Vec2 m_pos;
	// 移動量
	Vec2 m_move;
	// 当たり判定用の矩形
	Rect m_colRect;

	// グラフィックのハンドル
	int m_handle;

	// 向いている方向
	bool m_isRight;
	// 地面と接しているか
	bool m_isGround;	// true:接している
	// ジャンプ中のフレーム数
	int m_jumpFrame;

	// HP
	int m_hp;
	// 残機
	int m_life;
	// E缶
	int m_fullHpRecovery;

	// ダメージを受けてからのフレーム数
	int m_damageFrame;

	// メタルの弾エネルギー数
	float m_metalEnergy;
	// ファイヤーの弾エネルギー数
	float m_fireEnergy;
	// アイテム2号の弾エネルギー数
	float m_lineEnergy;

	// 武器を装備しているか
	bool m_isBuster; // バスター
	bool m_isMetal;	 // メタル
	bool m_isFire;	 // ファイア
	bool m_isLineMove; // 2号(直線移動する足場)

	// ボタンの状態を取得する
	int m_keyState;
	// ボタンが長押しされた時間
	int m_pressTime;
	// ボタンを押して離すまでの時間
	int m_nowPressTime;
};

