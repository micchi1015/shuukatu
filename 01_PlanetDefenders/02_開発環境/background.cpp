//------------------------------
//
// �w�i�̏���[background.cpp]
// Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "background.h"
#include"renderer.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CBg::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^

//�R���X�g���N�^
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
}

//�f�X�g���N�^
CBg::~CBg()
{
}

//����������
HRESULT CBg::Init()
{
	CObject2D::Init();

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	BindTexture(m_pTexture);

	return S_OK;
}

//����
CBg *CBg::Create()
{
	CBg *pObject2D = new CBg;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
		pObject2D->SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//�e�N�X�`���ǂݍ���
HRESULT CBg::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bg.jpg",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CBg::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}