#pragma once
#include <memory>

class Map;
class Enemy
{
public:
	Enemy();
	virtual ~Enemy(){}

	// マップのポインタを設定する
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }

	void Update();
	void Draw();

private:
	// Mapで決定したスクロール量を取得するためにMapクラスの情報が必要
	std::shared_ptr<Map>	m_pMap;

	// プレイヤーの足元中央を基準とした座標
	float m_x;
	float m_y;

};

