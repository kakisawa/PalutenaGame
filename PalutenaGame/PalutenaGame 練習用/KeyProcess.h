#pragma once

// �p�b�h�̏�Ԃ��擾����
class KeyProcess
{
public:
	// �p�b�h�̍X�V���� 1�t���[����1��s��
	void Update();

	// ������Ă��邩���擾
	static bool IsPress(int key);
	// �����ꂽ�u�Ԃ��擾
	static bool IsTrigger(int key);
	// �������u�Ԃ��擾
	bool IsRelase(int key);
};