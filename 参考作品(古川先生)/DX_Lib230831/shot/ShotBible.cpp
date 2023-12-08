#include "ShotBible.h"
#include "Player.h"
#include <DxLib.h>
#include <cassert>

namespace
{
	// �V���b�g�̑傫��
	constexpr int kWidth = 16;
	constexpr int kHeight = 24;
	// �������Ă��������܂ł̃t���[����
	constexpr int kExistFrame = 60 * 5;
	// �v���C���[�̎����1��]�����ɂ�����t���[����
	constexpr int kRotFrame = 60;

	// �v���C���[�̎�����܂��Ƃ��̔��a
	constexpr float kRadius = 100.0f;

	// �v���C���[���猩�����Έʒu���f�[�^�Ƃ��Ď���
	const Vec2 k0ffset[] =
	{
		Vec2{kRadius,	0.0f},		// �E
		Vec2{0.0f,		kRadius},	// ��
		Vec2{-kRadius,	0.0f},		// ��
		Vec2{0.0f,		-kRadius},	// ��
	};
}

ShotBible::ShotBible():
	m_frameCount(0),
	m_angle(0)
{
}

ShotBible::~ShotBible()
{
}

void ShotBible::Init()
{
}

void ShotBible::Update()
{
	if (!m_isExist)	return;
	// �v���C���[�̃|�C���^���ݒ肳��Ă��Ȃ�
	assert(m_pPlayer);

	// ��莞�Ԍo�߂����������
	m_frameCount++;
	if (m_frameCount > kExistFrame)
	{
		m_isExist = false;
		return;	//  �I�����m�肵���ȍ~�̏����͍s��Ȃ�
	}


	// �ړ�����
	// �v���C���[�̈ʒu�ɂ���ĕ\������ꏊ���ς��
	// �v���C���[�̈ʒu��񂪗~�����I

	//// ������܂ł̐i�s�x�������ɕϊ�����
	//float progress = static_cast<float>(m_frameCount) / static_cast<float>(kExistFrame);
	//// �i�s�x*�v�f���ŉ��Ԗڂ̗v�f���g�p���邩���߂�
	//int index = progress * _countof(k0ffset);

	// �v���C���[���猩���p�x�̍X�V
	// kRotFrame(60) ������1��]����
	m_angle += DX_TWO_PI / kRotFrame;

	// k0ffset[index]�ƃv���C���[�̈ʒu����ŏI�I�ȃV���b�g�̈ʒu�����肷��
//	m_pos = m_pPlayer->GetPos() + k0ffset[index];
// 	m_pos : �V���b�g�̈ʒu	����͂����cos,sin�Ő�������
	// m_pos : ��]�̒��S�ʒu
	// m_angle : �^����0�Ƃ����ꍇ�̉�]�p�x
	// kRadius : ��]���a

	Vec2 offset;	// �v���C���[���猩���ʒu
	offset.x = cosf(m_angle) * kRadius;
	offset.y = sinf(m_angle) * kRadius;

	m_pos = m_pPlayer->GetPos() + offset;


	/*������Ȃ�������if���ł�ok
	if (m_frameCount < 15)
	{
		index = 0;
	}
	else if (m_frameCount < 30)
	{
		index = 1;
	}
	*/


//	// index:k0ffset�̉��Ԗڂ̃f�[�^���g����
//	// _countof():�z��̗v�f�����擾����
//	int index = m_frameCount % _countof(k0ffset);
}

void ShotBible::Draw()
{
	if (!m_isExist) return;		// ���݂��邩

	// �e�̎���
	DrawBox(m_pos.x - kWidth / 2, m_pos.y - kHeight / 2,
		m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, 
		GetColor(32, 32, 255), true);
}

void ShotBible::Start(Vec2 pos)
{
	m_isExist = true;

	m_pos = pos;
	m_frameCount = 0;
}
