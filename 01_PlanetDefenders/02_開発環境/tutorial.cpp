//-----------------------------------------
//
//�`���[�g���A����ʂ̏���[tutorial.cpp]
//Author:���c�喲
//
//-----------------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include "application.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "tutorial.h"
#include "sound.h"

//�R���X�g���N�^
CTutorial::CTutorial()
{
}

//�f�X�g���N�^
CTutorial::~CTutorial()
{
}

//����������
HRESULT CTutorial::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\�`���[��.jpg",
		&m_pTexture[0]);

	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), PRIORITY_3);
	m_pObject2D[0]->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D[0]->BindTexture(m_pTexture[0]);

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM004);

	return S_OK;
}

//�I������
void CTutorial::Uninit(void)
{
	//�T�E���h�̒�~
	StopSound();
	CObject::Release();
}

//�X�V����
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
	{
		//���[�h�̃Z�b�g����
		CFade::SetFade(CFade::FADE_OUT,CApplication::MODE_TITLE);
	}
}

//�`�揈��
void CTutorial::Draw(void)
{
}

//�`���[�g���A���̐���
CTutorial * CTutorial::Create()
{
	CTutorial *pTutorial = new CTutorial;

	if (pTutorial != nullptr)
	{
		pTutorial->Init();
	}

	return pTutorial;
}