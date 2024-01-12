#include "EnemyBase.h"

EnemyBase::EnemyBase():
	EGraph(-1),
	W(0),
	H(0),
	HP(0),
	Atk(0), 
	EnemyAnim(0),
	Gravity(0),
	isTurn(false),	// �G�l�~�[�̌����t���O,�E�������Ă����false��}��
	isDeath(false)	// ���S�t���O,����ł��Ȃ���false��}��
{
}