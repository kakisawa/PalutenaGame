#pragma once
class SoundManager
{
public:
	void Init();
	void Update(){}
	void Draw(){}
	void End();

public:
	void SoundSelect();
	void SoundButton();
	void SoundDamage();
	void SoundJump();
	void SoudndAttack();

public:
	int m_soundJump;
	int m_soundAttack;
	int m_soundDamage;

	int m_soundSelect;
	int m_soundButton;
};
