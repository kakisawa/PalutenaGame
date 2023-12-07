#include "KeyProcess.h"
#include "Dxlib.h"

namespace
{
	// �O�̃t���[���̃p�b�h�����������
	int lastPad = 0;
	// ���̃t���[���̃p�b�h�����������
	int nowPad = 0;
}

void KeyProcess::Update()
{
	// �O�̃t���[���Ɏ擾�����p�b�h������Â����ɂ���
	lastPad = nowPad;
	// ���݂̃p�b�h�̏����擾����
	nowPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

bool KeyProcess::IsPress(int key)
{
	return (nowPad & key);
}

bool KeyProcess::IsTrigger(int key)
{
	bool isNow = (nowPad & key);	// ���̃t���[��
	bool isLast = (lastPad & key);	// �O�̃t���[��
	// return !isLast && isNow;	// ����ł������Ǘ������ɂ����̂Ł��ɕ�����₷��

	if (isNow &&	// ���̃t���[���ɉ�����Ă���
		!isLast)	// �O��̃t���[���ɉ�����Ă��Ȃ�
	{
		return true;
	}
	return false;
}

bool KeyProcess::IsRelase(int key)
{
	bool isNow = (nowPad & key);	// ���̃t���[��
	bool isLast = (lastPad & key);	// �O�̃t���[��
	// return !isLast && isNow;	// ����ł������Ǘ������ɂ����̂Ł��ɕ�����₷��

	if (!isNow &&	// ���̃t���[���͉�����Ă��Ȃ���
		isLast)		// �O��̃t���[���͉�����Ă���
	{
		return true;
	}
	return false;
}