#pragma once
#include "Rect.h"
#include "Vec2.h"
#include <vector>

class Player;
class SceneMain;
class SceneSecond;

namespace
{
	// プレイヤーのサイズ
	constexpr int kPlayerWidth = 72;
	constexpr int kPlayerHeight = 72;

	// 弾のサイズ
	constexpr int kShotWidth = 30;
	constexpr int kShotHeight = 30;

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
	int m_x;	// 弾の座標
	int m_y;

	int m_dir;	// 弾の方向

	bool m_isExist;	// 存在するかフラグ(使用中かどうか)

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量	1フレーム当たりの移動量を入れる
	Vec2 m_vec;
private:
	std::vector<Vec2> m_posLog;

public:
	// ショットを打ったプレイヤーのポインタを覚えておく
	Player* m_pPlayer;
	// SceneMainの関数を呼び出すためにポインタを覚えておく
	SceneMain* m_pMain;
	SceneSecond* m_pSecond;
};