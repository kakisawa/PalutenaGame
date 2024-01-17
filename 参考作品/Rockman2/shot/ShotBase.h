#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player;

// 弾の種類の定義
enum ShotType
{
	kShotBase,
	kShotBuster, // バスター
	kShotFire,	 // ファイア
	kShotMetal,	 // メタル
	kShotLineMove // 2号
};

/// <summary>
/// 弾の基底クラス
/// </summary>
class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// 弾をスタートさせる
	// 発射位置を引数として指定する
	virtual void Start(Vec2 pos) = 0;

	// メンバー変数にアクセスする
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// 弾が存在しているか
	bool IsExist() const { return m_isExist; }
	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

	// 弾の種類を取得する
	virtual ShotType GetShotType() const { return ShotType::kShotBase; }

protected:
	// SceneMainのポインタ
	SceneMain* m_pMain;
	// ショットを撃ったプレイヤーのポインタ
	Player* m_pPlayer;

	// グラフィックのハンドル
	int m_handle;
	// 弾が存在するかフラグ(使用中かどうか)
	bool m_isExist;

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量
	Vec2 m_vec;
};

