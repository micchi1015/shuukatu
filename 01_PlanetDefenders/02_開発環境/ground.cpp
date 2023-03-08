//------------------------------
//
// �n�ʂ̏���[ground.cpp]
// Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "fade.h"
#include "ground.h"
#include "object2D.h"
#include"renderer.h"

//---------------------------
//�}�N����`
//---------------------------
#define		NUM_SPLIT		(3.0f)		//�摜�̕�����

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CGround::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^
int				   CGround::m_Life = 0;

//�R���X�g���N�^
CGround::CGround()
{
	
}

//�f�X�g���N�^
CGround::~CGround()
{
}

//����������
HRESULT CGround::Init()
{
	CObject2D::Init();

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	BindTexture(m_pTexture);

	//�e�N�X�`���̍��W
	SetLifeTexPos(1.0f,0.0f,NUM_SPLIT, (float)m_nPatternAnim);

	return S_OK;
}

//�X�V����
void CGround::Update()
{
	D3DXVECTOR3 GroundPos = CObject2D::GetPos();
	D3DXVECTOR3 GroundSize = GetSize();

	SetPos(GroundPos);
	CObject2D::Update();
}

//����
CGround * CGround::Create()
{
	CGround *pGround = new CGround;

	if (pGround != nullptr)
	{
		pGround->Init();
		pGround->SetPos(D3DXVECTOR3(640.0f, 720.0f, 0.0f));
		pGround->SetType(OBJTYPE_GROUND);
		pGround->SetSize(D3DXVECTOR3(2560.0f, 100.0f, 0.0f));
		pGround->SetLife(12);
	}
	else
	{
		assert(false);
	}

	return pGround;
}

//���C�t�̐ݒ�
void CGround::SetLife(int nLife)
{
	m_Life = nLife;
}

//���C�t�̒l��Ԃ�
int CGround::GetLife()
{
	return m_Life;
}

int CGround::GetGroundLife()
{
	return m_Life;
}

//�e�N�X�`���̍X�V
void CGround::UpdateTex()
{
	m_nPatternAnim++;
	SetLifeTexPos(1.0f,0.0f,NUM_SPLIT, (float)m_nPatternAnim);
}

//�e�N�X�`���ǂݍ���
HRESULT CGround::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.jpg",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CGround::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}