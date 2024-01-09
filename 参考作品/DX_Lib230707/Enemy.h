#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const;
	// グラフィックの指定
	void SetGrahpHandle(int handle);

	// 敵キャラクター開始処理
	// 画面上から落ち始める
	void Start();

	// 存在するかチェック
	bool isExist() const { return m_isExist; }

	// 敵キャラクターの初期位置設定(グラフィックを設定してから行う)
	void SetStartPos();

	// 矩形の当たり判定をとるのに必要な情報を取得する関数
	float GetLeft() const;	// 左のX座標
	float GetTop() const;	// 上のY座標
	float GetRight() const;	// 右のX座標
	float GetBottom()const;	// 下のY座標

private:
	// 残像用に保存する位置情報の数
	static constexpr int kPosLogFrame = 8;

private:
	int m_handle;
	// グラフィックのサイズ
	int m_width;
	int m_height;

	// 存在するかフラグ
	bool m_isExist;
	
	// 位置情報
	float m_posX[kPosLogFrame];
	float m_posY[kPosLogFrame];

	// 移動量
	float m_moveY;

};