#pragma once
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();
	// グラフィックの設定、幅と高さの取得を行う
	void SetGraphHandle(int handle);

	// 矩形の当たり判定をとるのに必要な情報を取得する関数
	float GetLeft() const;	// 左のX座標
	float GetTop() const;	// 上のY座標
	float GetRight() const;	// 右のX座標
	float GetBottom() const;// 下のY座標

private:
	int m_handle;
	// グラフィックのサイズ
	int m_width;
	int m_height;

	float m_posX;
	float m_posY;

	// 左右反転表示
	bool m_isTurn;
};

