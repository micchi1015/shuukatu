//-------------------------
//
//���C�t�̏���[playerlife.cpp]
//Author:���c�喲
//
//-------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "playerlife.h"
#include "renderer.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CPlayerLife::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^

//�R���X�g���N�^
CPlayerLife::CPlayerLife(int nPriortiy) : CObject2D(nPriortiy)
{
	SetType(OBJTYPE_LIFE);
}

//�f�X�g���N�^
CPlayerLife::~CPlayerLife()
{
}

//����������
HRESULT CPlayerLife::Init()
{
	CObject2D::Init();
	BindTexture(m_pTexture);

	return S_OK;
}
//�X�V����
void CPlayerLife::Update()
{
	CObject2D::Update();
}

//�����̐���
CPlayerLife *CPlayerLife::Create(const D3DXVECTOR3 pos)
{
	CPlayerLife *pLife = new CPlayerLife;

	if (pLife != nullptr)
	{
		pLife->Init();
		pLife->SetPos(pos);
		pLife->SetSize(D3DXVECTOR3(200.0f, 45.0f, 0.0f));
		pLife->SetType(OBJTYPE_LIFE);
	}
	else
	{
		assert(false);
	}

	return pLife;
}

//�e�N�X�`���ǂݍ���
HRESULT CPlayerLife::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\hMxuY0UREkaJw7Y1662186290_1662186348.png",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CPlayerLife::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}