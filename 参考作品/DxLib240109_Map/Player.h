#pragma once
#include <memory>

class Map;
class Player
{
public:
	Player();
	virtual ~Player();

	// マップのポインタを設定する
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }

	void Update();
	void Draw();

	// プレイヤーの位置を取得		// プライベートのままだと他のクラスで使用できない為
	float GetX() const { return m_x; }
	float GetY() const { return m_y; }

	// プレイヤーの上下左右座標を取得
	float GetLeft();
	float GetRight(); 
	float GetTop();
	float GetBottom();

private:
	// Mapで決定したスクロール量を取得するためにMapクラスの情報が必要
	std::shared_ptr<Map>	m_pMap;

	// ジャンプしているかどうかのフラグを持つ
	// 空中にいる場合はtrue,地面に立っている場合はfalse
	bool m_isJump;

	// プレイヤーの足元中央を基準とした座標
	float m_x;
	float m_y;

	// プレイヤーの加速度	1フレーム当たりの移動量
	float m_moveX;
	float m_moveY;

};

