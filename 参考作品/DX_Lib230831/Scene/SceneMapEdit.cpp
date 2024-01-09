#include "SceneMapEdit.h"
#include "DxLib.h"
#include <cassert>
#include "Pad.h"

// �t�@�C���̏o�͂Ɏg�p����
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>	// �����̏o��
using namespace std;

namespace
{
	// �J�[�\���ړ����s�[�g�t���[��
	constexpr int kCursorRepeatFrame = 5;
}

SceneMapEdit::SceneMapEdit() :
	m_cursorX(0),
	m_cursorY(0),
	m_upRepeatFrame(0),
	m_downRepeatFrame(0),
	m_leftRepeatFrame(0),
	m_rightRepeatFrame(0)
{
	// �O���t�B�b�N�̃��[�h
	m_bgHandle = LoadGraph("data/image/bg.png");
	assert(m_bgHandle != -1);

	// �}�b�v�`�b�v�̐��𐔂���
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_bgHandle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;


	// �`�b�v�̔z�u���̐���
	for (int x = 0; x < kChipNumX; x++)
	{
		for (int y = 0; y < kChipNumY; y++)
		{
			m_chipData[y][x] = 0;
		}
	}
}

SceneMapEdit::~SceneMapEdit()
{
	// �O���t�B�b�N�̉��
	DeleteGraph(m_bgHandle);
}

void SceneMapEdit::Init()
{
}

void SceneMapEdit::End()
{
}

void SceneMapEdit::Update()
{
	// �J�[�\���̈ړ�
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		m_upRepeatFrame++;
		if ((m_upRepeatFrame >= kCursorRepeatFrame) ||
			Pad::IsTrigger(PAD_INPUT_UP))
		{
			m_upRepeatFrame = 0;
			// �J�[�\���̈ړ�����
			CursorUp(Pad::IsTrigger(PAD_INPUT_UP));
		}
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		m_downRepeatFrame++;
		if ((m_downRepeatFrame >= kCursorRepeatFrame) ||
			Pad::IsTrigger(PAD_INPUT_DOWN))
		{
			m_downRepeatFrame = 0;
			CursorDown(Pad::IsTrigger(PAD_INPUT_DOWN));
		}
	}
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_leftRepeatFrame++;
		if ((m_leftRepeatFrame >= kCursorRepeatFrame) ||
			Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			m_leftRepeatFrame = 0;
			CursorLeft(Pad::IsTrigger(PAD_INPUT_LEFT));
		}
	}
	// �E�����ւ̃J�[�\���ړ�
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_rightRepeatFrame++;
		if ((m_rightRepeatFrame >= kCursorRepeatFrame) ||
			Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			m_rightRepeatFrame = 0;
			// �J�[�\���̈ړ�����
			CursorRight(Pad::IsTrigger(PAD_INPUT_RIGHT));
		}
	}

	if (Pad::IsPress(PAD_INPUT_1))
	{
		// �z��͈̔͊O�A�N�Z�X�����m���邽�߂�assert
		assert(m_cursorX >= 0 && m_cursorX < kChipNumX);
		assert(m_cursorY >= 0 && m_cursorY < kChipNumY);

		// m_cursorX	�����̒��ɃJ�[�\���̍��W�������Ă���

		// �I�����Ă���}�b�v�`�b�v�̔ԍ���+1
		m_chipData[m_cursorY][m_cursorX]++;

		// �O���t�B�b�N���ɑ��݂���}�b�v�`�b�v�̐�
		int chipNum = GetGraphChipNum();
		
		// chip�̔ԍ���0�Ԃ���̒ʂ��ԍ��ŊǗ����Ă���
		// chip��10���ƁA�ʂ��ԍ���0~9
		// ���[�v����
		if (m_chipData[m_cursorY][m_cursorX] > chipNum-1)
		{
			m_chipData[m_cursorY][m_cursorX] = 0;
		}
	}

	if (Pad::IsPress(PAD_INPUT_2))
	{
		// �z��͈̔͊O�A�N�Z�X�����m���邽�߂�assert
		assert(m_cursorX >= 0 && m_cursorX < kChipNumX);
		assert(m_cursorY >= 0 && m_cursorY < kChipNumY);

		// �I�����Ă���}�b�v�`�b�v�̔ԍ���+2
		m_chipData[m_cursorY][m_cursorX]--;

		// �O���t�B�b�N���ɑ��݂���}�b�v�`�b�v�̐�
		int chipNum = GetGraphChipNum();

		// ���[�v����
		if (m_chipData[m_cursorY][m_cursorX] < 0)
		{
			m_chipData[m_cursorY][m_cursorX] = chipNum - 1;
		}
	}

	// �t�@�C���o�̓e�X�g
	if (Pad::IsTrigger(PAD_INPUT_3))	// �R���g���[���[����X �L�[�{�[�h����"C"
	{
		OutputBainary();
	}

	// �t�@�C���ǂݍ��݃e�X�g
	if (Pad::IsTrigger(PAD_INPUT_4))	// �R���g���[���[����Y �L�[�{�[�h����"V"
	{
		InputBainary();
	}
#if false
	// test
	if (false)
	{
		fstream file;
		file.open("test.txt", ios::in | ios::out);	// �����̃t���O�𓯎��w��\
	}
#endif
}

void SceneMapEdit::Draw()
{
	for (int y = 0; y < kChipNumY;y++)
	{
		for(int x=0;x<kChipNumX;x++)
		{
			// �}�b�v��񂩂�u���`�b�v������Ă���
			int chipNo = m_chipData[y][x];

			// �}�b�v�`�b�v�̐؂�o�����W
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			DrawRectGraph(x * kChipHeight, y * kChipWidth,
				srcX, srcY, kChipWidth, kChipHeight,
				m_bgHandle, true);
		}
	}

	// �O���b�h�̕\��

	// �c��
	for (int x = 0; x < kChipNumX; x++) 
	{
		DrawLine(x * kChipWidth, 0, x * kChipWidth, 
			Game::kScreenHeight, GetColor(255, 255, 255));
	}
	// ����
	for (int y = 0; y < kChipNumY; y++)
	{
		DrawLine(0, y * kChipHeight, Game::kScreenWidth,
			y * kChipHeight, GetColor(255, 255, 255));
	}

	// ���ݑI�����Ă���`�b�v�ɃJ�[�\����\��
	int cursorPosX = m_cursorX * kChipWidth;
	int cursorPosY = m_cursorY * kChipHeight;

	DrawBox(cursorPosX, cursorPosY,		// ������W
		cursorPosX + kChipWidth, cursorPosY + kChipHeight,	// �E�����W
		GetColor(255, 0, 0), false);
	// ���菬�������i��`�悵�Đ��̑����l�p�ɂ���
	DrawBox(cursorPosX + 1, cursorPosY + 1,
		cursorPosX + kChipWidth - 1, cursorPosY + kChipHeight - 1,
		GetColor(255, 0, 0), false);	
}

void SceneMapEdit::CursorUp(bool isLoop)
{
	m_cursorY--;
	if (m_cursorY < 0)
	{
		if (isLoop)
		{
			// �g���K�[�̎��̓J�[�\�������[�v����
			m_cursorY = kChipNumY - 1;
		}
		else
		{
			// ���s�[�g�̏ꍇ�͒[�Ŏ~�܂�
			m_cursorY = 0;
		}
	}
}

void SceneMapEdit::CursorDown(bool isLoop)
{
	m_cursorY++;
	if (m_cursorY > kChipNumY - 1)
	{
		if (isLoop)
		{
			m_cursorY = 0;
		}
		else
		{
			m_cursorY = kChipNumY - 1;
		}
	}
}

void SceneMapEdit::CursorLeft(bool isLoop)
{
	m_cursorX--;
	if (m_cursorX < 0)
	{
		if (isLoop) 
		{
			m_cursorX = kChipNumX - 1;
		}
		else
		{
			m_cursorX = 0;
		}
	}
}

void SceneMapEdit::CursorRight(bool isLoop)
{
	m_cursorX++;
	if (m_cursorX > kChipNumX - 1)
	{
		if (isLoop)
		{
			m_cursorX = 0;
		}
		else
		{
			m_cursorX = kChipNumX - 1;
		}
	}
}

int SceneMapEdit::GetGraphChipNum()
{
	return m_graphChipNumX * m_graphChipNumY;
}

void SceneMapEdit::OutputText()
{
	fstream file;
	file.open("test.txt", ios::out);	// �t�@�C�����J�� �o�͂������̂�ios::out
	// �t�@�C���̓��e���������ꍇ��ios::in�ŊJ��

// �t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
	if (!file.is_open()) {
		// �t�@�C�����J���Ȃ������ꍇ�̏���
		// return EXIT_FAILURE;	// ���ȏ��͊J���Ȃ������炻�̎��_�Ńv���O�����I��
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");	// �t�@�C���͊J���Ȃ������ƕ��͂�\������
	}
	else
	{
		//// �t�@�C�����J�����ꍇ�̏���
		// �쐬�����}�b�v�̃f�[�^���e�L�X�g�ŏo�͂���

		// test�Ń}�b�v�̈�ԏ�̍s�̂ݏo�͂���
		// m_chipData[kChipNumY][kChipNumX];
		// m_chipData[0][~kChipNumX-1]	// ������o�͂���
		for (int y = 0; y < kChipNumY; y++)
		{
			file << "{";
			for (int x = 0; x < kChipNumX; x++)
			{
				if (x == kChipNumX - 1)	// �Ō�̂�","�͏o�͂��Ȃ�
				{
					file << m_chipData[y][x];
				}
				else
				{
					file << m_chipData[y][x] << ",";
				}

			}
			file << "}," << endl;
		}
		file.close();	// �J��������� 

		printfDx("�t�@�C���ɏ������݂��s���܂���\n");
	}
}

void SceneMapEdit::InputText()
{
	fstream file;
	file.open("test.txt", ios::in);	// �ǂݍ��ނƂ���ios::in�ŊJ��

	// �t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
	if (!file.is_open())
	{
		// �t�@�C�����J���Ȃ������ꍇ�̏���
		// return EXIT_FAILURE;	// ���ȏ��͊J���Ȃ������炻�̎��_�Ńv���O�����I��
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");	// �t�@�C���͊J���Ȃ������ƕ��͂�\������
	}
	else
	{
		// �t�@�C���̃I�[�v���ɐ��������̂œǂݍ��݂��s��
		string str;			// ������char�̔z��������Ă���(�悤�Ȃ���)
		getline(file, str);
		file.close();

		printfDx(str.c_str());
	}
}

void SceneMapEdit::OutputBainary()
{
	fstream file;
	// �o�C�i�����[�h�ŊJ��
	// �g���q�͉��ł��悢 �o�C�i���f�[�^��\��bin,�f�[�^��\��dat�������W���[
	file.open("map.bin", ios::out|ios::binary);	

	// �t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
	if (!file.is_open())
	{
		// �t�@�C�����J���Ȃ������ꍇ�̏���
		// return EXIT_FAILURE;	// ���ȏ��͊J���Ȃ������炻�̎��_�Ńv���O�����I��
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");	// �t�@�C���͊J���Ȃ������ƕ��͂�\������
	}
	else
	{
		// �t�@�C���I�[�v���ɐ�������
		// �}�b�v�`�b�v�̔z�u�f�[�^���o�C�i���ŏo��

		// fstream��write�֐����g�p���ďo�͂���
		// ��������̂ǂ��ɒu����Ă��邩(�A�h���X)��
		// �������牽�o�C�g�o�͂��邩�A���w�肷��

		file.write((const char*)&(m_chipData[0][0]), sizeof(int) * kChipNumX * kChipNumY);
		file.close();

		printfDx("�o�C�i���f�[�^�Ƃ��ă}�b�v�f�[�^���o�͂��܂���\n");
	}
}

void SceneMapEdit::InputBainary()
{
	fstream file;
	// �o�C�i�����[�h�ŊJ��
	file.open("map.bin", ios::in | ios::binary);


	// �t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
	if (!file.is_open())
	{
		// �t�@�C�����J���Ȃ������ꍇ�̏���
		// return EXIT_FAILURE;	// ���ȏ��͊J���Ȃ������炻�̎��_�Ńv���O�����I��
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");	// �t�@�C���͊J���Ȃ������ƕ��͂�\������
	}
	else
	{
		// �t�@�C���I�[�v���ɐ�������
		// �ǂݍ��񂾃o�C�i���̓��e����������̃}�b�v�`�b�v���ɏ㏑������
		file.read((char*)&(m_chipData[0][0]), sizeof(int) * kChipNumX * kChipNumY);
		file.close();

		printfDx("�o�C�i���f�[�^��ǂݍ���Ń}�b�v�f�[�^�ɂ��܂���\n");
	}
}
