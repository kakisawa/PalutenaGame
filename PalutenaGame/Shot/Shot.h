#pragma once
#include "Rect.h"
#include "Vec2.h"

class Player;
class SceneMain;
class SceneSecond;

namespace
{
	// プレイヤーのサイズ
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 32;

	// 弾のサイズ
	constexpr int kShotWidth = 20;
	constexpr int kShotHeight = 20;

	// 弾の移動速度
	constexpr float kShotSpeed = 8.0f;
}

class Shot
{
public:
	Shot();
	virtual ~Shot();

	virtual void init();
	virtual void Update();
	virtual void Draw();

	void Start(Vec2 pos);

	void colShot();		// 弾が敵とぶつかったときの処理

	Rect GetColRect() const { return m_colRect; }	// 当たり判定の矩形を取得する
	bool IsExist() const { return m_isExist; }
	
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetSecond(SceneSecond* pSecond) { m_pSecond = pSecond; }
	// プレイヤーの向いている方向を取得する為
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
private:
	int Se;

	int x;	// 弾の座標
	int y;

	int dir;	// 弾の方向

	bool m_isExist;	// 存在するかフラグ(使用中かどうか)

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;

public:
	// ショットを打ったプレイヤーのポインタを覚えておく
	Player* m_pPlayer;
	// SceneMainの関数を呼び出すためにポインタを覚えておく
	SceneMain* m_pMain;
	SceneSecond* m_pSecond;
};