//=============================================================================
//
// application.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "application.h"
#include "rendering.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "inputPad.h"
#include "directionalLight.h"
#include "camera.h"
#include "model.h"
#include "debugProc.h"
#include "animator.h"
#include "title.h"
#include "playerSelect.h"
#include "stageSelect.h"
#include "gamerace.h"
#include "fade.h"
#include "menu.h"
#include "hitbox.h"
#include "score.h"
#include "tutorial.h"
#include "message.h"

//�ÓI�����o�[�ϐ��̐錾
HWND CApplication::m_hWnd;													//�E�C���h�E
CRenderer* CApplication::m_pRenderer = nullptr;								//�����f�B���O�C���X�^���X�ւ̃|�C���^
CInput* CApplication::m_pInput[2] = {};										//�C���v�b�g�C���X�^���X�ւ̃|�C���^
CInputMouse* CApplication::m_pMouse = nullptr;								//�}�E�X�C���X�^���X�ւ̃|�C���^
CInputPad* CApplication::m_pPad = nullptr;									//�p�b�h�̃C���X�^���X
CSound* CApplication::m_pSound = nullptr;									//�T�E���h�̃C���X�^���X
CFade* CApplication::m_pFade = nullptr;										//�t�F�[�h�̃C���X�^���X
CCamera* CApplication::m_pCamera = nullptr;									//�J�����̃C���X�^���X
CMode* CApplication::m_pMode = nullptr;										// ���[�h�ւ̃|�C���^
CMenu* CApplication::m_pMenu = nullptr;										// ���j���[�ւ̃|�C���^
CMessage* CApplication::m_pMessage = nullptr;								// ���b�Z�[�W�ւ̃|�C���^
CDebugProc* CApplication::m_pDebug = nullptr;								//�f�o�b�O�\��
CApplication::Mode CApplication::m_mode = CApplication::Mode_Title;			//���[�h
CApplication::Mode CApplication::m_modeNext = CApplication::Mode_Title;		//���̃��[�h
bool CApplication::m_bPause = false;										//�|�[�Y��Ԃł��邩�ǂ���
int CApplication::m_nStageSelect = 0;										// �X�e�[�W�I��ԍ�

//�R���X�g���N�^
CApplication::CApplication()
{
	
}

//�f�X�g���N�^
CApplication::~CApplication()
{
	
}

//����������
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;				//�E�C���h�E�̐ݒ菈��

	//�����f�B���O�C���X�^���X�̐�������
	if (m_pRenderer == nullptr)
	{//�|�C���^��null�ł͂Ȃ�������
		m_pRenderer = new CRenderer;
	}

	//�����f�B���O�C���X�^���X�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, FALSE)))
	{//��2������FALSE��������A�t���X�N���[���ɂȂ�܂��B
		return -1;
	}

	m_pDebug = CDebugProc::Create();			//�f�o�b�O�e�L�X�g�̐�������

	//�e�N�X�`���S�������[�h����
	CObject_2D::LoadTextures();

	//���f���S�������[�h����
	CModel::LoadAllModels();

	//�S���̃A�j���[�V�����̓ǂݍ���
	CAnimator::LoadAllAnimation();		

	//�T�E���h�̐���
	m_pSound = CSound::Create(hWnd);

	CLight::ReleaseAll();																						//�S���̃��C�g�̃����[�X����
	CDirectionalLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(2, -5, 2));						//���C�����C�g�̐���
	CDirectionalLight::Create(D3DXCOLOR(0.75f, 0.75f, 0.75f, 0.75f), D3DXVECTOR3(-0.2f, 0.2f, 1.0f));			//���C�g�̐���

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, -200.0f, 100.0f));			//�J�����̐���

	// ���[�h�C���X�^���X�̐�������
	m_pMode = CTitle::Create();
	m_mode = Mode_Title;
	m_modeNext = Mode_Title;
	m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	// �t�F�[�h����
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create();
		m_pFade->SetFade();
	}

	//�L�[�{�[�h�C���X�^���X�̐������� 
	m_pInput[0] = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInput[0]->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	//�}�E�X�̐���
	m_pMouse = new CInputMouse;			

	if (m_pMouse != nullptr)
	{//�}�E�X�̏���������
		m_pMouse->Init(hInstance, hWnd, GUID_SysMouse);
	}

	//�p�b�h�̐���
	m_pPad = new CInputPad;

	if (m_pPad != nullptr)
	{//�p�b�h�̏���������
		m_pPad->Init(hInstance, hWnd, GUID_SysMouse);
	}

	// ���j���[����
	if (m_pMenu == nullptr)
	{
		m_pMenu = CMenu::Create();
	}

	// ���b�Z�[�W����
	if (m_pMessage == nullptr)
	{
		m_pMessage = CMessage::Create();
	}

	m_bPause = false;	//�|�[�Y�𖢎g�p�ɂ���

	m_nStageSelect = 0;	// �X�e�[�W�ԍ�������

	return S_OK;
}

//�I������
void CApplication::Uninit(void)
{
	CScore::Clear();		//�X�R�A�̃N���A����

	//Renderer�C���X�^���X�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();			//�I������
		delete m_pRenderer;				//�j������
		m_pRenderer = nullptr;			//null�ɂ���
	}

	// ���[�h�̔j������
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();				//�I������
		delete m_pMode;					//�j������
		m_pMode = nullptr;				//null�ɂ���
	}

	//�C���v�b�g�f�o�C�X�̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Uninit();	//�I������
			delete m_pInput[nCnt];		//�j������
			m_pInput[nCnt] = nullptr;	//null�ɂ���
		}
	}

	//�}�E�X�̔j������
	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();				//�I������
		delete m_pMouse;				//�j������
		m_pMouse = nullptr;				//null�ɂ���
	}

	//�p�b�h�̔j������
	if (m_pPad != nullptr)
	{
		m_pPad->Uninit();				//�I������
		delete m_pPad;					//�j������
		m_pPad = nullptr;				//null�ɂ���
	}

	//�T�E���h�̔j������
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();				//�I������
		delete m_pSound;				//�j������
		m_pSound = nullptr;				//null�ɂ���
	}

	//�t�F�[�h�̔j������
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();				//�I������
		delete m_pFade;					//�j������
		m_pFade = nullptr;				//null�ɂ���
	}

	//���j���[�̔j������
	if (m_pMenu != nullptr)
	{
		m_pMenu->Uninit();				//�I������
		delete m_pMenu;					//�j������
		m_pMenu = nullptr;				//null�ɂ���
	}

	//���b�Z�[�W�̔j������
	if (m_pMessage != nullptr)
	{
		m_pMessage->Uninit();			//�I������
		delete m_pMessage;				//�j������
		m_pMessage = nullptr;			//null�ɂ���
	}

	//�J�����̔j������
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();			//�I������
		delete m_pCamera;				//�j������
		m_pCamera = nullptr;			//null�ɂ���
	}

	//�f�o�b�O�e�L�X�g�̔j������
	if (m_pDebug != nullptr)
	{
		delete m_pDebug;				//�j������
		m_pDebug = nullptr;				//null�ɂ���
	}

	//�I�u�W�F�N�g�S�̂̏I������
	CObject::ReleaseAll();

	//�q�b�g�{�b�N�X�̔j������
	CHitbox::ReleaseAll();

	//���C�g�̔j������
	CLight::ReleaseAll();

	//�e�N�X�`���S���̔j��
	CObject_2D::DestroyLoadedTextures();

	//�S���̃A�j���[�V�����̔j������
	CAnimator::DestroyLoadedAnimation();

	//���f���S���j���̔j������
	CModel::DestroyAllModels();
}

//�X�V����
void CApplication::Update(void)
{
	//�C���v�b�g�f�o�C�X�̍X�V����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Update();
		}
	}

	//Renderer�̍X�V����
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	//�t�F�[�h�̍X�V����
	if (m_pFade != nullptr)
	{
		//�t�F�[�h���ǂݍ��܂�Ă��Ȃ��ꍇ
		if (m_pFade->GetFade() != CFade::FADE_NONE)
		{
			m_pFade->Update();

			if (m_pFade->GetFade() == CFade::FADE_CHANGE)
			{// �t�F�[�h�؂�ւ���Ԃ̏ꍇ
				ChangeMode();
			}
		}
	}

	//���݂̃��[�h�̍X�V����
	if (m_pMode != nullptr)
	{
		m_pMode->Update();
	}

	//���j���[�̍X�V����
	if (m_pMenu != nullptr)
	{
		m_pMenu->Update();
	}

	//���b�Z�[�W�̍X�V����
	if (m_pMessage != nullptr)
	{
		m_pMessage->Update();
	}

	//�}�E�X�̍X�V����
	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}

	//�p�b�h�̍X�V����
	if (m_pPad != nullptr)
	{
		m_pPad->Update();
	}

	// �|�[�Y���łȂ��ꍇ�̂ݍX�V
	if (m_bPause == false)
	{
		//�J�����̍X�V����
		if (m_pCamera != nullptr)
		{
			m_pCamera->Update();
		}
	}
}

//�`�揈��
void CApplication::Draw(void)
{
	//Renderer�̕`�揈��
	if (m_pRenderer != nullptr)
	{//null�ł͂Ȃ�������
		m_pRenderer->Draw();
	}
}

//Renderer�̎擾����
CRenderer* CApplication::GetRenderer(void)
{
	return m_pRenderer;
}

//�}�E�X�̎擾����
CInputMouse* CApplication::GetMouse(void)
{
	return m_pMouse;
}

//�p�b�h�̎擾����
CInputPad * CApplication::GetPad(void)
{
	return m_pPad;
}

//�E�C���h�E�̎擾����
HWND CApplication::GetWindow(void)
{
	return m_hWnd;
}

//�T�E���h�̎擾����
CSound* CApplication::GetSound(void)
{
	return m_pSound;
}

//�J�����̎擾����
CCamera* CApplication::GetCamera(void)
{
	return m_pCamera;
}

//�t�F�[�h�̎擾����
CFade* CApplication::GetFade(void)
{
	return m_pFade;
}

//=====================================
// ���[�h�擾����
//=====================================
CApplication::Mode CApplication::GetMode(void)
{
	return m_mode;
}

//=====================================
// ���[�h�ݒ菈��
//=====================================
void CApplication::SetMode(Mode mode)
{
	// �t�F�[�h�؂�ւ���Ԃł͂Ȃ��ꍇ
	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		m_modeNext = mode;
		m_pFade->SetFade();
	}
}

//=====================================
// ���[�h�؂�ւ�����
//=====================================
void CApplication::ChangeMode()
{
	// ���݃��[�h�̏I��
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	m_pMenu->Uninit();		// ���j���[�̏I��
	m_pMessage->Uninit();	// ���b�Z�[�W�̏I��

	CObject::ReleaseAll();	// �S�ẴI�u�W�F�N�g�̏I��
	CHitbox::ReleaseAll();	// �S�Ă̓����蔻��̏I��

	m_bPause = false;		// �|�[�Y�𖢎g�p�ɂ���

	// ���̃��[�h���X�e�[�W�I���łȂ����
	if (m_modeNext != Mode_StageSelect)
	{
		if (m_pSound != nullptr)
		{// �g�p���̃T�E���h��~
			m_pSound->Stop();
		}
	}

	// ���[�h�𐶐�����
	switch (m_modeNext)
	{
	case CApplication::Mode_Title:
		m_pMode = CTitle::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		break;
	case CApplication::Mode_PlayerSelect:
		m_pMode = CPlayerSelect ::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_SELECT);
		break;
	case CApplication::Mode_StageSelect:
		m_pMode = CStageSelect::Create();
		break;
	case CApplication::Mode_Game_Race:
		m_pMode = CGameRace::Create();

		// �I���X�e�[�W�ԍ��ʂ̏���
		if (m_nStageSelect == 0)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME01);
		}
		else if (m_nStageSelect == 1)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME02);
		}
		else if (m_nStageSelect == 2)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME03);
		}
		break;
	case CApplication::Mode_Tutorial:
		m_pMode = CTutorial::Create();
		m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME01);
		break;
	default:
		break;
	}
	m_mode = m_modeNext;	// ���̃��[�h�ɕύX

	m_pMenu->Init();		// ���j���[�̏���������
}

//=====================================
// �|�[�Y�擾����
//=====================================
bool CApplication::GetPause()
{
	return m_bPause;
}

//=====================================
// �|�[�Y�ݒ菈��
//=====================================
void CApplication::SetPause(const bool bPause)
{
	m_bPause = bPause;
}