#include "Key.h"
#include"DxLib.h"

namespace
{
	// �O�̃t���[���̃L�[�{�[�h�����������
	int lastKey = 0;
	// ���̃t���[���̃L�[�{�[�h�����������
	int nowKey = 0;
}

namespace Key
{
	int keyState[256];

	void Update()
	{
		// �O�̃t���[���Ɏ擾�����L�[�{�[�h������Â����ɂ���
		lastKey = nowKey;
		// ���݂̃L�[�{�[�h�L�[�{�[�h�̏����擾����
		nowKey = GetHitKeyStateAllEx(keyState);

		// �L�[�{�[�h�̉�����Ԃ��擾����
		// CheckHitKeyAll �Œ��ׂ���̓^�C�v	// �L�[���͂𒲂ׂ�
	}

	bool IsPress(int key)
	{
		return (nowKey & key);
	}
	bool IsTrigger(int key)
	{
		bool isNow = (nowKey & key);	// ���̃t���[��
		bool isLast = (lastKey & key);	// �O�̃t���[��
		// return !isLast && isNow;	// ����ł������Ǘ������ɂ����̂Ł��ɕ�����₷��

		if (isNow &&	// ���̃t���[���ɉ�����Ă���
			!isLast)	// �O��̃t���[���ɉ�����Ă��Ȃ�
		{
			return true;
		}
		return false;
	}
	bool IsRelase(int key)
	{
		bool isNow = (nowKey & key);	// ���̃t���[��
		bool isLast = (lastKey & key);	// �O�̃t���[��
		// return !isLast && isNow;	// ����ł������Ǘ������ɂ����̂Ł��ɕ�����₷��

		if (!isNow &&	// ���̃t���[���͉�����Ă��Ȃ���
			isLast)		// �O��̃t���[���͉�����Ă���
		{
			return true;
		}
		return false;
	}
}