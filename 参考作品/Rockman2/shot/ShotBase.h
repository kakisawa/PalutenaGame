#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player;

// �e�̎�ނ̒�`
enum ShotType
{
	kShotBase,
	kShotBuster, // �o�X�^�[
	kShotFire,	 // �t�@�C�A
	kShotMetal,	 // ���^��
	kShotLineMove // 2��
};

/// <summary>
/// �e�̊��N���X
/// </summary>
class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �e���X�^�[�g������
	// ���ˈʒu�������Ƃ��Ďw�肷��
	virtual void Start(Vec2 pos) = 0;

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// �e�����݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// �����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

	// �e�̎�ނ��擾����
	virtual ShotType GetShotType() const { return ShotType::kShotBase; }

protected:
	// SceneMain�̃|�C���^
	SceneMain* m_pMain;
	// �V���b�g���������v���C���[�̃|�C���^
	Player* m_pPlayer;

	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// �e�����݂��邩�t���O(�g�p�����ǂ���)
	bool m_isExist;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���
	Vec2 m_vec;
};

