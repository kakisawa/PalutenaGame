#pragma once
class EnemyBase
{
public:

	EnemyBase();			// �R���X�g���N�^
	virtual ~EnemyBase();	// �f�X�g���N�^

protected:		// �h���N���X����A�N�Z�X�ł���悤��
	int HP;
	int Atk;
	int Def;
	int Item;

};