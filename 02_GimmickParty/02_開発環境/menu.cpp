//=============================================================================
//
// menu.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "menu.h"
#include "Application.h"
#include "mode.h"
#include "fontString.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "game.h"
#include "fade.h"
#include "tutorial.h"

int CMenu::m_nNumAll = 0;
int CMenu::m_nSelectNum = 0;
bool CMenu::m_bResult = false;
CFontString* CMenu::m_pChoice[MaxChoice] = {};
CFontString* CMenu::m_pPause = nullptr;
CObject_2D* CMenu::m_pObj2D = nullptr;

//-----------------------------------------
//�v���g�^�C�v�錾
//-----------------------------------------
void ExitExe(void);		// �E�C���h�E�I������

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CMenu::CMenu()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CMenu::~CMenu()
{

}

//=====================================
// ����������
//=====================================
HRESULT CMenu::Init(void)
{
	switch (CApplication::GetMode())
	{
	case CApplication::Mode_Title :

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 450.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�X�^�[�g");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�`���[�g���A��");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�����");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
		break;
	case CApplication::Mode_Game_Race:
		break;
	default:
		break;
	}

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CMenu::Uninit(void)
{
	for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
	{// �I����������̏I������
		if (m_pChoice[nCnt] != nullptr)
		{
			m_pChoice[nCnt]->Uninit();
			m_pChoice[nCnt] = nullptr;
		}
	}

	if (m_pPause != nullptr)
	{// �|�[�Y������̏I������
		m_pPause->Uninit();
		m_pPause = nullptr;
	}

	if (m_pObj2D != nullptr)
	{// �I�u�W�F�N�g2D�̏I������
		m_pObj2D->Release();
		m_pObj2D = nullptr;
	}

	m_nSelectNum = 0;		// ���ݑI������Ă���ԍ��̏I������
	m_nNumAll = 0;			// �I�����̑S�̐��̏I������
	m_bResult = false;		// ���U���g����̏I������
}

//=====================================
// �X�V����
//=====================================
void CMenu::Update(void)
{
	ModeType();		//���[�h���̏���
}

//=====================================
// ���[�h���̏���
//=====================================
void CMenu::ModeType(void)
{
	switch (CApplication::GetMode())
	{// �擾�������[�h���̏���
	case CApplication::Mode_Title:
	{
		for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
		{// �e�I�����̍X�V����
			if (m_pChoice[nCnt] != nullptr)
			{
				m_pChoice[nCnt]->Update();
			}
		}
		Input();	// ���͏���
	}
	break;
	case CApplication::Mode_Game_Race:
	{
		if (CGame::GetEndGame() == false)
		{// �Q�[�����I�����Ă��Ȃ��ꍇ
			if (CApplication::GetPause() == true)
			{// �|�[�Y���łȂ��ꍇ�̂ݍX�V
				for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
				{// �e�I�����̍X�V����
					if (m_pChoice[nCnt] != nullptr)
					{
						m_pChoice[nCnt]->Update();
					}

				}
				if (m_pPause != nullptr)
				{// �|�[�Y������̍X�V����
					m_pPause->Update();
				}
				Input();	// ���͏���
			}
		}
		else
		{// �Q�[�����I�����Ă���ꍇ
			for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
			{// �e�I�����̍X�V����
				if (m_pChoice[nCnt] != nullptr)
				{
					m_pChoice[nCnt]->Update();
				}
			}
			Input();	// ���͏���
		}
	}
	break;
	case CApplication::Mode_Tutorial:
	{
		if (CGame::GetEndGame() == false)
		{// �Q�[�����I�����Ă��Ȃ��ꍇ
			if (CApplication::GetPause() == true)
			{// �|�[�Y���łȂ��ꍇ�̂ݍX�V
				for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
				{// �e�I�����̍X�V����
					if (m_pChoice[nCnt] != nullptr)
					{
						m_pChoice[nCnt]->Update();
					}

				}
				if (m_pPause != nullptr)
				{// �|�[�Y������̍X�V����
					m_pPause->Update();
				}
				Input();	// ���͏���
			}
		}
		else
		{// �Q�[�����I�����Ă���ꍇ
			for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
			{// �e�I�����̍X�V����
				if (m_pChoice[nCnt] != nullptr)
				{
					m_pChoice[nCnt]->Update();
				}
			}
			Input();	// ���͏���
		}
	}
	break;
	default:
		break;
	}
}

//=====================================
// ���͏���
//=====================================
void CMenu::Input(void)
{
	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{// �t�F�[�h���ł͂Ȃ��ꍇ
		switch (CApplication::GetMode())
		{// �擾�������[�h���̏���
		case CApplication::Mode_Title:
		{
			if (CInputKeyboard::GetKeyboardTrigger(DIK_W)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 0)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 1)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 2)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 3))
			{// W�L�[�������ꂽ�ꍇ
				m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
				m_nSelectNum--;								// ���ݑI������Ă���ԍ���������

				if (m_nSelectNum < 0)
				{// ���݈ʒu��0��艺�̏ꍇ
					m_nSelectNum = m_nNumAll - 1;
				}
				m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
			}
			else if (CInputKeyboard::GetKeyboardTrigger(DIK_S)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 0)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 1)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 2)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 3))
			{// S�L�[�������ꂽ�ꍇ
				m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
				m_nSelectNum++;								// ���ݑI������Ă���ԍ�

				if (m_nSelectNum >= m_nNumAll)
				{// ���݈ʒu���ő吔���傫���ꍇ
					m_nSelectNum = 0;
				}
				m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
			}
			if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 1)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 2)
				|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 3))
			{// Enter�L�[�������ꂽ�ꍇ
				if (m_nSelectNum == 0)
				{// �I������0�Ԗڂ̏ꍇ
					CApplication::SetMode(CApplication::Mode_PlayerSelect);
				}
				else if (m_nSelectNum == 1)
				{// �I������1�Ԗڂ̏ꍇ
					CApplication::SetStageSelect(3);
					CApplication::SetMode(CApplication::Mode_Tutorial);
				}
				else if (m_nSelectNum == 2)
				{// �I������2�Ԗڂ̏ꍇ
					ExitExe();
				}
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_YES);
			}
		}
		break;
		case CApplication::Mode_Game_Race:
		{
			if (CGame::GetEndGame() == false)
			{// �Q�[�����̏ꍇ
				if (CInputKeyboard::GetKeyboardTrigger(DIK_W) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 0))
				{// W�L�[�������ꂽ�ꍇ
					m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
					m_nSelectNum--;								// ���ݑI������Ă���ԍ���������

					// ���݈ʒu��0��艺�̏ꍇ
					if (m_nSelectNum < 0)
					{
						m_nSelectNum = m_nNumAll - 1;
					}
					m_pChoice[m_nSelectNum]->SetSellect();	// ���ݑI�����̐ݒ菈��
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
				}
				else if (CInputKeyboard::GetKeyboardTrigger(DIK_S) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 0))
				{// S�L�[�������ꂽ�ꍇ
					m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
					m_nSelectNum++;								// ���ݑI������Ă���ԍ����グ��

					// ���݈ʒu���ő吔���傫���ꍇ
					if (m_nSelectNum >= m_nNumAll)
					{
						m_nSelectNum = 0;
					}
					m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
				}
				if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0))
				{// Enter�L�[�������ꂽ�ꍇ
					if (m_nSelectNum == 0)
					{// �I������0�Ԗڂ̏ꍇ
						CApplication::SetPause(false);
						PauseChange(false);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_START);
					}
					else if (m_nSelectNum == 1)
					{// �I������1�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_Game_Race);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_FINISH);
					}
					else if (m_nSelectNum == 2)
					{// �I������2�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_PlayerSelect);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_FINISH);
					}
					else if (m_nSelectNum == 3)
					{// �I������3�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_Title);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_FINISH);
					}
				}
			}
			else if (m_bResult)
			{// �Q�[�����I�����Ă��� & ���U���g���̏ꍇ
				if (CInputKeyboard::GetKeyboardTrigger(DIK_W)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 0)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 1)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 2)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 3))
				{// W�L�[�������ꂽ�ꍇ
					m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
					m_nSelectNum--;								// ���ݑI������Ă���ԍ���������

					if (m_nSelectNum < 0)
					{// ���݈ʒu��0��艺�̏ꍇ
						m_nSelectNum = m_nNumAll - 1;
					}
					m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
				}
				else if (CInputKeyboard::GetKeyboardTrigger(DIK_S)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 0)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 1)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 2)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 3))
				{// S�L�[�������ꂽ�ꍇ
					m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
					m_nSelectNum++;								// ���ݑI������Ă���ԍ����グ��

					if (m_nSelectNum >= m_nNumAll)
					{// ���݈ʒu���ő吔���傫���ꍇ
						m_nSelectNum = 0;
					}
					m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
				}
				if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 1)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 2)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 3))
				{// Enter�L�[�������ꂽ�ꍇ
					if (m_nSelectNum == 0)
					{// �I������0�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_Game_Race);
					}
					else if (m_nSelectNum == 1)
					{// �I������1�Ԗڂ̏ꍇ
						CApplication::GetSound()->Stop();
						CApplication::SetMode(CApplication::Mode_StageSelect);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_SELECT);
					}
					if (m_nSelectNum == 2)
					{// �I������2�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_PlayerSelect);
					}
					else if (m_nSelectNum == 3)
					{// �I������3�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_Title);
					}
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_YES);
				}
			}
		}
		break;
		case CApplication::Mode_Tutorial:
		{
			if (CGame::GetEndGame() == false)
			{// �Q�[�����̏ꍇ
				if (CInputKeyboard::GetKeyboardTrigger(DIK_W) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 0))
				{// W�L�[�������ꂽ�ꍇ
					m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
					m_nSelectNum--;								// ���ݑI������Ă���ԍ���������

					if (m_nSelectNum < 0)
					{// ���݈ʒu��0��艺�̏ꍇ
						m_nSelectNum = m_nNumAll - 1;
					}
					m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
				}
				else if (CInputKeyboard::GetKeyboardTrigger(DIK_S) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 0))
				{// S�L�[�������ꂽ�ꍇ
					m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
					m_nSelectNum++;

					if (m_nSelectNum >= m_nNumAll)
					{// ���݈ʒu���ő吔���傫���ꍇ
						m_nSelectNum = 0;
					}
					m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
				}
				if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0))
				{// Enter�L�[�������ꂽ�ꍇ
					if (m_nSelectNum == 0)
					{// �I������0�Ԗڂ̏ꍇ
						CApplication::SetPause(false);
						PauseChange(false);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_START);
					}
					else if (m_nSelectNum == 1)
					{// �I������1�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_Tutorial);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_FINISH);
					}
					else if (m_nSelectNum == 2)
					{// �I������2�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_PlayerSelect);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_FINISH);
					}
					else if (m_nSelectNum == 3)
					{// �I������3�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_Title);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_FINISH);
					}
				}
			}
			else if (m_bResult)
			{// �Q�[�����I�����Ă��� & ���U���g���̏ꍇ
				if (CInputKeyboard::GetKeyboardTrigger(DIK_W)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 0)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 1)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 2)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, 3))
				{// W�L�[�������ꂽ�ꍇ
					m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
					m_nSelectNum--;								// ���ݑI������Ă���ԍ���������

					if (m_nSelectNum < 0)
					{// ���݈ʒu��0��艺�̏ꍇ
						m_nSelectNum = m_nNumAll - 1;
					}
					m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
				}
				else if (CInputKeyboard::GetKeyboardTrigger(DIK_S)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 0)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 1)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 2)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, 3))
				{// S�L�[�������ꂽ�ꍇ
					m_pChoice[m_nSelectNum]->SizeReset();		// �����̑傫������������
					m_nSelectNum++;								// ���ݑI������Ă���ԍ����グ��

					if (m_nSelectNum >= m_nNumAll)
					{// ���݈ʒu���ő吔���傫���ꍇ
						m_nSelectNum = 0;
					}
					m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
				}
				if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 0)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 1)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 2)
					|| CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, 3))
				{// Enter�L�[�������ꂽ�ꍇ
					if (m_nSelectNum == 0)
					{// �I������0�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_Tutorial);
					}
					else if (m_nSelectNum == 1)
					{// �I������1�Ԗڂ̏ꍇ
						CApplication::GetSound()->Stop();
						CApplication::SetMode(CApplication::Mode_StageSelect);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_SELECT);
					}
					else if (m_nSelectNum == 2)
					{// �I������2�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_PlayerSelect);
					}
					else if (m_nSelectNum == 3)
					{// �I������3�Ԗڂ̏ꍇ
						CApplication::SetMode(CApplication::Mode_Title);
					}
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_YES);
				}
			}
		}
		break;
		default:
			break;
		}
	}
}

//=====================================
// �|�[�Y�I��������
//=====================================
void CMenu::PauseChange(bool bPause)
{
	if (bPause == true)
	{// �|�[�Y���̏ꍇ
		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�Â���");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "���g���C");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�L�����Z���N�g");
		m_nNumAll++;

		m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�^�C�g���ɂ��ǂ�");
		m_nNumAll++;

		m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��

		m_pPause = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), "�|�[�Y");

		// �I�u�W�F�N�g2D����
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		m_pObj2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.1f));
		m_pObj2D->SetTexture(CObject::TEXTURE_NULL);
		m_pObj2D->SetPriority(4);
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_STOP);
	}
	else
	{// �|�[�Y���ł͂Ȃ��ꍇ
		for (int nCnt = 0; nCnt < MaxChoice; nCnt++)
		{
			if (m_pChoice[nCnt] != nullptr)
			{// �I����������g�p���̏ꍇ������
				m_pChoice[nCnt]->Uninit();
				m_pChoice[nCnt] = nullptr;
			}
		}

		if (m_pPause != nullptr)
		{// �|�[�Y������g�p���̏ꍇ������
			m_pPause->Uninit();
			m_pPause = nullptr;
		}

		if (m_pObj2D != nullptr)
		{// �I�u�W�F�N�g2D�g�p���̏ꍇ������
			m_pObj2D->Release();
			m_pObj2D = nullptr;
		}

		m_nSelectNum = 0;	// ���ݑI������Ă���ԍ��̏�����
		m_nNumAll = 0;		// �I�����̑S�̐��̏�����
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_START);
	}
}

//=====================================
// ���U���g�̐ݒ菈��
//=====================================
void CMenu::SetResult(void)
{
	m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 250.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "���g���C");
	m_nNumAll++;

	m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�X�e�[�W�Z���N�g");
	m_nNumAll++;

	m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 450.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�L�����Z���N�g");
	m_nNumAll++;

	m_pChoice[m_nNumAll] = CFontString::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), "�^�C�g���ɂ��ǂ�");
	m_nNumAll++;

	m_pChoice[m_nSelectNum]->SetSellect();		// ���ݑI�����̐ݒ菈��

	m_bResult = true;		// ���U���g���ɂ���
}

//=====================================
// ��������
//=====================================
CMenu* CMenu::Create(void)
{
	CMenu* pMenu = new CMenu;

	if (FAILED(pMenu->Init()))
	{
		return nullptr;
	}

	return pMenu;
}