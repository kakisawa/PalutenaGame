#pragma once
class EnemyBase
{
public:

	EnemyBase();			// コンストラクタ
	virtual ~EnemyBase();	// デストラクタ

protected:		// 派生クラスからアクセスできるように
	int HP;
	int Atk;
	int Def;
	int Item;

};