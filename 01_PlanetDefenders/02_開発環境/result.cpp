//-----------------------------------------
//
//�^�C�g����ʂ̏���[title.cpp]
//Author:���c�喲
//
//-----------------------------------------
#include "application.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "result.h"
#include "sound.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
CResult::STATE CResult::m_State = STATE_NONE;

//�R���X�g���N�^
CResult::CResult()
{
}

//�f�X�g���N�^
CResult::~CResult()
{
}

//����������
HRESULT CResult::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\utyu50-1536x864.jpg",
		&m_pTexture[0]);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\���󂵂��s�s�̔w�i.jpg",
		&m_pTexture[1]);

	m_pObject2D = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2,CRenderer::SCREEN_HEIGHT / 2,0.0f),PRIORITY_3);
	m_pObject2D->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));

	switch (m_State)
	{
	case STATE_GAMECLEAR:
		m_pObject2D->BindTexture(m_pTexture[0]);
		break;
	case STATE_GAMEOVER:
		m_pObject2D->BindTexture(m_pTexture[1]);
		break;
	default:
		break;
	}

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM002);

	return S_OK;
}

//�I������
void CResult::Uninit(void)
{
	//�T�E���h�̒�~
	StopSound();

	CObject::Release();
}

//�X�V����
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();

	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
	{
		//���[�h�ݒ�
		CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RANKING);
	}
}

//��������
CResult * CResult::Create()
{
	CResult *pGame = new CResult;

	if (pGame != nullptr)
	{
		pGame->Init();
	}

	return pGame;
}

void CResult::SetState(STATE state)
{
	m_State = state;
}
