//=============================================================================
//
// game.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "game.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "application.h"
#include "menu.h"
#include "fade.h"

bool CGame::m_bEndGame = false;		//�Q�[���I������

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CGame::CGame()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CGame::~CGame()
{

}

//=====================================
// ����������
//=====================================
HRESULT CGame::Init(void)
{
	return S_OK;
}

//=====================================
// �I������
//=====================================
void CGame::Uninit(void)
{
	m_bEndGame = false;	// �Q�[���I������̏�����
}

//=====================================
// �X�V����
//=====================================
void CGame::Update(void)
{
	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//�Q�[�����̏���
		if (m_bEndGame == false)
		{
			//P�Ń|�[�Y�؂�ւ�
			if (CInputKeyboard::GetKeyboardTrigger(DIK_P)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 0)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 1)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 2)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 3))
			{
				bool bPause = !CApplication::GetPause();	// �|�[�Y�̐؂�ւ�����
				CApplication::SetPause(bPause);				// �|�[�Y�̐ݒ�
				CMenu::PauseChange(bPause);					// �|�[�Y�̕ύX����
			}
		}
	}
}

//=====================================
// �X�V����
//=====================================
void CGame::SetEndGame(void)
{
	m_bEndGame = true;
}