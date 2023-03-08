//=============================================================================
//
// stageSelect.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "stageSelect.h"
#include "Application.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "fade.h"
#include <random>
#include <iostream>//�p����w�b�_�t�@�C�����ς��܂��B

CFontString* CStageSelect::m_pStr = nullptr;
CObject_2D* CStageSelect::m_pFrame = nullptr;
//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CStageSelect::CStageSelect()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CStageSelect::~CStageSelect()
{

}

//=====================================
// ����������
//=====================================
HRESULT CStageSelect::Init(void)
{
	m_pStr = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), "�X�e�[�W�Z���N�g");

	// �X�e�[�W�Z���N�g�w�i�̐���
	CObject_2D* pObj = CObject_2D::Create();
	pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	pObj->SetSize(D3DXVECTOR2(6400.0, (float)SCREEN_HEIGHT * 0.5f));
	pObj->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pObj->SetTexture(CObject::TEXTURE_STAGE_SELECT_BG);
	pObj->MoveTexCoordinates(D3DXVECTOR2(0.00002f, 0.0f));
	pObj->SetPriority(3);

	if (m_pFrame == nullptr)
	{// �I��g�����g�p�̏ꍇ����
		m_pFrame = CObject_2D::Create();
		m_pFrame->SetPos(D3DXVECTOR3((SCREEN_WIDTH / 5), SCREEN_HEIGHT / 2, 0.0f));
		m_pFrame->SetSize(D3DXVECTOR2(125, 125));
		m_pFrame->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pFrame->SetTexture(CObject::TEXTURE_SELECT_FRAME);
		m_pFrame->SetPriority(4);
	}

	m_nNumAll = 4;	// �I�����̑S�̐�

	for(int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		CObject_2D *pObj2D = CObject_2D::Create();
		
		// �����𒆉��ɔz�u���Astring�^����*char�^��1���������o��
		pObj2D->SetPos(D3DXVECTOR3(((float)SCREEN_WIDTH * 0.2f) * (float)(nCnt + 1), (float)SCREEN_HEIGHT * 0.5f, 0.0f));
		pObj2D->SetSize(D3DXVECTOR2(120, 120));
		pObj2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pObj2D->SetPriority(4);

		// �ԍ����Ƀe�N�X�`����\��t����
		if (nCnt == 0)
		{
			pObj2D->SetTexture(CObject::TEXTURE_STAGESEL01);
		}
		else if (nCnt == 1)
		{
			pObj2D->SetTexture(CObject::TEXTURE_STAGESEL02);
		}
		else if (nCnt == 2)
		{
			pObj2D->SetTexture(CObject::TEXTURE_STAGESEL03);
		}
		else if (nCnt == 3)
		{
			pObj2D->SetTexture(CObject::TEXTURE_STAGESELR);
		}
	}

	m_nSelectNum = 0;	// ���ݑI������Ă���I�����̏�����

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CStageSelect::Uninit(void)
{
	if (m_pStr != nullptr)
	{// ������̏I������
		m_pStr->Uninit();
		m_pStr = nullptr;
	}

	if (m_pFrame != nullptr)
	{// �I��g�̏I������
		m_pFrame->Release();
		m_pFrame = nullptr;
	}
	m_nSelectNum = 0;
}

//=====================================
// �X�V����
//=====================================
void CStageSelect::Update(void)
{
	if (m_pStr != nullptr)
	{// ������̍X�V����
		m_pStr->Update();
	}

	if (m_pFrame != nullptr)
	{// �I��g�̍X�V����
		m_pFrame->Update();
	}
	Input();	// ���͏���
}

//=====================================
// ���͏���
//=====================================
void CStageSelect::Input(void)
{
	CSound *pSound = CApplication::GetSound();

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{// �t�F�[�h���ł͂Ȃ��ꍇ
		if (CInputKeyboard::GetKeyboardTrigger(DIK_A)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_LEFT, 0)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_LEFT, 1)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_LEFT, 2)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_LEFT, 3))
		{// W�L�[�������ꂽ�ꍇ
			m_nSelectNum--;

			if (m_nSelectNum < 0)
			{// ���݈ʒu��0��艺�̏ꍇ
				m_nSelectNum = m_nNumAll - 1;
			}
			m_pFrame->SetPos(D3DXVECTOR3(((float)SCREEN_WIDTH * 0.2f) * (float)(m_nSelectNum + 1), (float)SCREEN_HEIGHT * 0.5f, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_D)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT, 0)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT, 1)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT, 2)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT, 3))
		{// S�L�[�������ꂽ�ꍇ
			m_nSelectNum++;

			if (m_nSelectNum >= m_nNumAll)
			{// ���݈ʒu���ő吔���傫���ꍇ
				m_nSelectNum = 0;
			}
			m_pFrame->SetPos(D3DXVECTOR3(((float)SCREEN_WIDTH * 0.2f) * (float)(m_nSelectNum + 1), (float)SCREEN_HEIGHT * 0.5f, 0.0f));
			pSound->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_BACK, 0)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_BACK, 1)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_BACK, 2)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_BACK, 3))
		{// BACKSPACE�L�[����������
			CApplication::SetMode(CApplication::Mode_PlayerSelect);
			pSound->Play(CSound::SOUND_LABEL_SE_NO);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 1)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 2)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 3)
			
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 0)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 1)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 2)
			|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_START, 3))
		{// Enter�L�[����������

			if (m_nSelectNum == m_nNumAll - 1)
			{// �����_�����I�΂ꂽ�ꍇ
				std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
				std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
				std::uniform_int_distribution<> rand100(0, m_nNumAll - 2);   // [0, 99] �͈͂̈�l����
				m_nSelectNum = rand100(mt);
			}

			CApplication::SetStageSelect(m_nSelectNum);				// �I��ԍ���Ԃ�����
			CApplication::SetMode(CApplication::Mode_Game_Race);	// �Q�[��_�������[�h�ɕύX
			pSound->Play(CSound::SOUND_LABEL_SE_YES_STAGE);
		}
	}
}

//=====================================
// ��������
//=====================================
CStageSelect* CStageSelect::Create(void)
{
	CStageSelect* pStaeSelect = new CStageSelect;

	if (FAILED(pStaeSelect->Init()))
	{
		return nullptr;
	}

	return pStaeSelect;
}