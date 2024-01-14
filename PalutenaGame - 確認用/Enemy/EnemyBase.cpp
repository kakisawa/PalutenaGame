#include "EnemyBase.h"

EnemyBase::EnemyBase():
	EGraph(-1),
	W(0),
	H(0),
	HP(0),
	Atk(0), 
	EnemyAnim(0),
	Gravity(0),
	isTurn(false),	// エネミーの向きフラグ,右を向いているのfalseを挿入
	isDeath(false)	// 死亡フラグ,死んでいないのfalseを挿入
{
}