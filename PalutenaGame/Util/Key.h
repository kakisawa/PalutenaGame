#pragma once
// �L�[�{�[�h�̏�Ԃ��擾����
namespace Key
{
	// �p�b�h�̍X�V���� 1�t���[����1��s��
	void Update();

	// ������Ă��邩���擾
	bool IsPress(int key);
	// �����ꂽ�u�Ԃ��擾
	bool IsTrigger(int key);
	// �������u�Ԃ��擾
	bool IsRelase(int key);
}