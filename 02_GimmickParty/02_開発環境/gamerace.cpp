//=============================================================================
//
// gamerace.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "gamerace.h"
#include "input.h"
#include "application.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "fade.h"
#include "stage.h"
#include "message.h"

CStage* CGameRace::m_pStage = nullptr;

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CGameRace::CGameRace()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CGameRace::~CGameRace()
{

}

//=====================================
// ����������
//=====================================
HRESULT CGameRace::Init(void)
{
    CGame::Init();

	// �J�E���g�_�E�����b�Z�[�W�\��
	CApplication::GetMsg()->SetCountDown(3);

	m_pStage = CStage::Create();	// �X�e�[�W��������

    return S_OK;
}

//=====================================
// �I������
//=====================================
void CGameRace::Uninit(void)
{
    CGame::Uninit();

	if (m_pStage != nullptr)
	{// �X�e�[�W�̏I������
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = nullptr;
	}
}

//=====================================
// �X�V����
//=====================================
void CGameRace::Update(void)
{
    CGame::Update();

	if (m_pStage != nullptr)
	{// �X�e�[�W�̍X�V����
		m_pStage->Update();
	}

#ifdef _DEBUG

    CDebugProc::Print("\n[F2] : �f�o�b�O���[�h�ֈړ�\n");

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{// �t�F�[�h���ł͂Ȃ��ꍇ
		if (CInputKeyboard::GetKeyboardTrigger(DIK_BACK))
		{// Enter�L�[����������
			SetEndGame();
		}
	}

#endif // _DEBUG
}

//=====================================
// ��������
//=====================================
CGameRace* CGameRace::Create(void)
{
    CGameRace* pGameRace = new CGameRace;

    if (FAILED(pGameRace->Init()))
    {
        return nullptr;
    }

    return pGameRace;
}