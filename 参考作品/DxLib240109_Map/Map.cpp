#include "Map.h"
#include "Player.h"
#include "DxLib.h"

namespace
{
	// �X�N���[���T�C�Y		// �{�������ɏ����̂͂悭�Ȃ�(�Q�[���w�b�_�[����낤)
	constexpr int kScreenWidth = 640;
	constexpr int kScreenHeight = 480;

	// �`�b�v1�̃T�C�Y
	constexpr int kChipW = 32;
	constexpr int kChipH = 32;

	// �c���̃`�b�v�̐�
	// �X�N���[�����������̂ŉ�ʃT�C�Y640*480���L��
	constexpr int kChipNumX = 40;
	constexpr int kChipNumY = 30;

	// �`�b�v�̃T�C�Y�A������}�b�v�̍L�����v�Z
	constexpr int kMapWidth = kChipW * kChipNumX;
	constexpr int kMapHeight = kChipH * kChipNumY;

	// �`�b�v�̔z�u���
	// 0:�`�b�v�Ȃ�		1:��
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

}


void Map::Update()
{
}

void Map::Draw()
{
	// �v���C���[�̈ʒu�ɉ������X�N���[���ʂ�����
	int scrollX = GetScrollX();
	int scrollY = GetScrollY();


	for (int x = 0; x < kChipNumX; x++)
	{
		// ��ʊO��`�悵�Ȃ������́A�����Œe���ƁA�����Ə������������ł���

		for (int y = 0; y < kChipNumY; y++)
		{
			int posX = kChipW * x - scrollX;
			int posY = kChipH * y - scrollY;

			// ��ʊO��`�悵�Ȃ�
			if (posX < 0 - kChipW)		continue;
			if (posX > kScreenWidth)	continue;
			if (posY < 0 - kChipH)		continue;
			if (posY > kScreenHeight)	continue;



			if (kChipData[y][x] == 1)
			{
				DrawBox(posX, posY, posX + kChipW, posY + kChipH, 0xffffff, true);
			}
			DrawBox(posX, posY, posX + kChipW, posY + kChipH, 0x808080, false);

		}
	}
}

int Map::GetScrollX()
{
	int result = static_cast<int>(m_pPlayer->GetX() - kScreenWidth / 2);
	result = max(0, result);						// �ŏ��l
	result = min(kMapWidth - kScreenWidth, result);	// �ő�l

	return result;
}

int Map::GetScrollY()
{
	int result = static_cast<int>(m_pPlayer->GetY() - kScreenHeight / 2);
	if (result < 0) 
	{
		result = 0; 
	}

	if (result >kMapHeight-kScreenHeight)
	{
		result = kMapHeight - kScreenHeight; 
	}
		return result;
}

bool Map::IsColPlayer()
{
	// m_pPlayer
	float playerLeft = m_pPlayer->GetLeft();
	float playerRight = m_pPlayer->GetRight();
	float playerTop = m_pPlayer->GetTop();
	float playerBottom = m_pPlayer->GetBottom();

	for (int x = 0; x < kChipNumX; x++)
	{
		// �����̏������H�v���Ă����Ə����𑁂��ł���
		for (int y = 0; y < kChipNumY; y++)
		{
			// �ǈȊO�Ƃ͓�����Ȃ�
			if (kChipData[y][x] == 0)continue;

			int chipLeft = kChipW * x;
			int chipRight = chipLeft + kChipW;
			int chipTop = kChipH * y;
			int chipBottom = chipTop + kChipH;

			// ��Γ�����Ȃ��ꍇ�͎���
			if (chipLeft > playerRight)continue;
			if (chipTop > playerBottom)continue;
			if (chipRight < playerLeft)continue;
			if (chipBottom < playerTop)continue;

			// ���ꂩ�̃`�b�v�Ɠ������Ă�����I��
			return true;
		}
	}
	// �S�Ẵ`�b�v���`�F�b�N���ĂP���������Ă��Ȃ���Γ������Ă��Ȃ�

	return false;
}

bool Map::IsCol(Rect rect, Rect& chipRect)
{
	for (int x = 0; x < kChipNumX; x++)
	{
		// �����̏������H�v���Ă����Ə����𑁂��ł���
		for (int y = 0; y < kChipNumY; y++)
		{
			// �ǈȊO�Ƃ͓�����Ȃ�
			if (kChipData[y][x] == 0)continue;

			int chipLeft = kChipW * x;
			int chipRight = chipLeft + kChipW;
			int chipTop = kChipH * y;
			int chipBottom = chipTop + kChipH;
			 
			// ��Γ�����Ȃ��ꍇ�͎���
			if (chipLeft > rect.right)continue;
			if (chipTop > rect.bottom)continue;
			if (chipRight < rect.left)continue;
			if (chipBottom < rect.top)continue;

			// �Ԃ������}�b�v�`�b�v�̋�`��ݒ肷��
			chipRect.left = chipLeft;
			chipRect.right = chipRight;
			chipRect.top = chipTop;
			chipRect.bottom = chipBottom;

			// ���ꂩ�̃`�b�v�Ɠ������Ă�����I��
			return true;
		}
	}
	// �S�Ẵ`�b�v���`�F�b�N���ĂP���������Ă��Ȃ���Γ������Ă��Ȃ�

	return false;
}
