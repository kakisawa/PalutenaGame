#pragma once

class Player;

namespace
{
	// プレイヤーのサイズ
	constexpr int kPlayerWidth = 32;
	constexpr int kPlayerHeight = 32;

	// 正直ここのプレイヤーサイズはRectクラスとか活用した方がいい
	// 要改善

	// 弾のサイズ
	constexpr int kShotWidth = 16;
	constexpr int kShotHeight = 16;

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

	void RightShot();
	void LeftShot();
	void UpShot();

	bool IsExist() const { return m_isExist; }

	// プレイヤーの向いている方向を取得する為
//	void SetPlayer(Player* pPlayer) { m_Player = pPlayer; }

protected:
	int Se;

	int x;
	int y;

	bool m_isExist;	// 存在するかフラグ(使用中かどうか)

public:
	// プレイヤー
	Player* m_Player;
};

