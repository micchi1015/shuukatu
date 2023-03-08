//-------------------------
//
//�����̏���[explosion.cpp]
//Author:���c�喲
//
//-------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "explosion.h"
#include "renderer.h"

//---------------------------
//�}�N����`
//---------------------------
#define		NUM_BESIDESPLIT	(8.0f)		//�摜�̕�����

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^

//�R���X�g���N�^
CExplosion::CExplosion()
{
}

//�f�X�g���N�^
CExplosion::~CExplosion()
{
}

//����������
HRESULT CExplosion::Init()
{
	CObject2D::Init();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	BindTexture(m_pTexture);

	//�����̏���
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//�e�N�X�`���̍��W
	SetTexPos(NUM_BESIDESPLIT, (float)m_nPatternAnim);

	return S_OK;
}
//�X�V����
void CExplosion::Update()
{
	D3DXVECTOR3 pos = CObject2D::GetPos();

	m_nCounterAnim++;	//�J�E���^�[�����Z

	if ((m_nCounterAnim % 3) == 0)
	{//��莞�Ԍo��
		//�e�N�X�`���̍��W�ύX
		SetTexPos(NUM_BESIDESPLIT, (float)m_nPatternAnim);

		//�p�^�[��No.���X�V����
		m_nPatternAnim++;
	}

	CObject2D::Update();

	if (m_nPatternAnim >= 8)
	{
		Uninit();
	}
}

//�����̐���
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	CExplosion *pExplosion = new CExplosion;

	if (pExplosion != nullptr)
	{
		pExplosion->Init();
		pExplosion->SetPos(pos);
		pExplosion->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pExplosion;
}

//�e�N�X�`���ǂݍ���
HRESULT CExplosion::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CExplosion::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}