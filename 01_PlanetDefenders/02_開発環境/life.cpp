//-------------------------
//
//���C�t�̏���[life.cpp]
//Author:���c�喲
//
//-------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "life.h"
#include "renderer.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CLife::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^

													//�R���X�g���N�^
CLife::CLife(int nPriortiy) : CObject2D(nPriortiy)
{
	SetType(OBJTYPE_LIFE);
}

//�f�X�g���N�^
CLife::~CLife()
{
}

//����������
HRESULT CLife::Init()
{
	CObject2D::Init();
	BindTexture(m_pTexture);

	return S_OK;
}
//�X�V����
void CLife::Update()
{
	CObject2D::Update();
}

//�����̐���
CLife *CLife::Create(const D3DXVECTOR3 pos)
{
	CLife *pLife = new CLife;

	if (pLife != nullptr)
	{
		pLife->Init();
		pLife->SetPos(pos);
		pLife->SetSize(D3DXVECTOR3(300.0f, 50.0f, 0.0f));
		pLife->SetType(OBJTYPE_LIFE);
	}
	else
	{
		assert(false);
	}

	return pLife;
}

//�e�N�X�`���ǂݍ���
HRESULT CLife::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\hVxD8UlgFHKJ9eQ1662005850_1662005861.png",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CLife::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}