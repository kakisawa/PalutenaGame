#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Bg;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player(SceneMain* pMain);
	~Player();

	// �}�b�v�̃|�C���^��ݒ肷��
	void SetBg(Bg* pBg) { m_pBg = pBg; }

	void Init();
	void Update();
	void Draw();

	// �}�b�v�`�b�v�Ƃ̓����蔻��̏���
	void CheckHitMap();

	// �v���C���[���_���[�W���󂯂����̏���
	void OnDamage();
	// �v���C���[��E�ʎ擾����
	void GetHpFullRecovery();
	// �v���C���[�̉񕜏���
	void HpSmallRecovery();		// HP����
	void HpGreatRecovery();		// HP���
	void ShotSmallRecovery();	// �e����
	void ShotGreatRecovery();	// �e���
	void LifeRecovery();		// �c�@��
	void HpFullRecovery();		// HP�S��

	// �A�C�e��2���ɏ�����ۂ̏���
	void RideLineMove(Rect shotRect);

	// ���݂̕���I����Ԃ��X�V����
	void ChangeShot(bool isBuster, bool isMetal, bool isFire, bool isLineMove);

public:
	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	// ���݈ʒu���X�V����
	void SetPos(Vec2 pos) { m_pos = pos; }
	// �v���C���[�̌��݂̌������擾����
	bool GetDir() const { return m_isRight; }
	// �v���C���[�̌��ݍ��W���擾����
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

	// ���݂�HP���擾����
	float GetHp() const { return m_hp; }
	// ���݂̎c�@�����擾����
	int GetLife() const { return m_life; }
	// ���݂�E�ʐ����擾
	int GetFullHpRecovery() const { return m_fullHpRecovery; }

	// ���݂̒e�G�l���M�[�����擾����
	float GetMetalEnergy() const { return m_metalEnergy; }
	float GetFireEnergy() const { return m_fireEnergy; }
	float GetLineEnergy() const { return m_lineEnergy; }

	// �{�^���������ė����܂ł̎��Ԃ��擾����
	int GetPressTime() const { return m_nowPressTime; }

public:
	// ���킪�I�𒆂��擾����
	bool IstBuster() const { return m_isBuster; }	// �o�X�^�[
	bool IsMetal() const { return m_isMetal; }		// ���^��
	bool IsFire() const { return m_isFire; }		// �t�@�C�A
	bool IsLineMove() const { return m_isLineMove; }// 2��

private:
	SceneMain* m_pMain;
	Bg* m_pBg;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ���
	Vec2 m_move;
	// �����蔻��p�̋�`
	Rect m_colRect;

	// �O���t�B�b�N�̃n���h��
	int m_handle;

	// �����Ă������
	bool m_isRight;
	// �n�ʂƐڂ��Ă��邩
	bool m_isGround;	// true:�ڂ��Ă���
	// �W�����v���̃t���[����
	int m_jumpFrame;

	// HP
	int m_hp;
	// �c�@
	int m_life;
	// E��
	int m_fullHpRecovery;

	// �_���[�W���󂯂Ă���̃t���[����
	int m_damageFrame;

	// ���^���̒e�G�l���M�[��
	float m_metalEnergy;
	// �t�@�C���[�̒e�G�l���M�[��
	float m_fireEnergy;
	// �A�C�e��2���̒e�G�l���M�[��
	float m_lineEnergy;

	// ����𑕔����Ă��邩
	bool m_isBuster; // �o�X�^�[
	bool m_isMetal;	 // ���^��
	bool m_isFire;	 // �t�@�C�A
	bool m_isLineMove; // 2��(�����ړ����鑫��)

	// �{�^���̏�Ԃ��擾����
	int m_keyState;
	// �{�^�������������ꂽ����
	int m_pressTime;
	// �{�^���������ė����܂ł̎���
	int m_nowPressTime;
};

