#include "Pad_Key.h"
#include "Dxlib.h"

namespace
{
	// �O�̃t���[���̃p�b�h�����������
	int lastPad = 0;
	// ���̃t���[���̃p�b�h�����������
	int nowPad = 0;

	// �O�̃t���[���̃L�[�{�[�h�����������
	int lastKey = 0;
	// ���̃t���[���̃L�[�{�[�h�����������
	int nowKey = 0;
}

namespace Pad
{
	void Update()
	{
		// �O�̃t���[���Ɏ擾�����p�b�h������Â����ɂ���
		lastPad = nowPad;
		// ���݂̃p�b�h�̏����擾����
		nowPad = GetJoypadInputState(DX_CHECKINPUT_PAD);

		// �W���C�p�b�h�̓��͏�Ԃ��擾����
		// CheckHitKeyAll�Œ��ׂ���̓^�C�v// �p�b�h���͂𒲂ׂ�
	}

	bool IsPress(int pad)
	{
		return (nowPad & pad);
	}
	bool IsTrigger(int pad)
	{
		bool isNow = (nowPad & pad);	// ���̃t���[��
		bool isLast = (lastPad & pad);	// �O�̃t���[��
		// return !isLast && isNow;	// ����ł������Ǘ������ɂ����̂Ł��ɕ�����₷��

		if (isNow &&	// ���̃t���[���ɉ�����Ă���
			!isLast)	// �O��̃t���[���ɉ�����Ă��Ȃ�
		{
			return true;
		}
		return false;
	}
	bool IsRelase(int pad)
	{
		bool isNow = (nowPad & pad);	// ���̃t���[��
		bool isLast = (lastPad & pad);	// �O�̃t���[��
		// return !isLast && isNow;	// ����ł������Ǘ������ɂ����̂Ł��ɕ�����₷��

		if (!isNow &&	// ���̃t���[���͉�����Ă��Ȃ���
			isLast)		// �O��̃t���[���͉�����Ă���
		{
			return true;
		}
		return false;
	}

	namespace Key
	{
		void Update()
		{
			// �O�̃t���[���Ɏ擾�����L�[�{�[�h������Â����ɂ���
			lastKey = nowKey;
			// ���݂̃L�[�{�[�h�L�[�{�[�h�̏����擾����
			nowKey = CheckHitKey(DX_CHECKINPUT_KEY);

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
}