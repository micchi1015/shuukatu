//------------------------------
//
// �i���o�[�̏���[number.cpp]
// Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "number.h"
#include "renderer.h"

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9	CNumber::m_pTexture;		//�e�N�X�`���ւ̃|�C���^

//�R���X�g���N�^
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{
	
}

//�f�X�g���N�^
CNumber::~CNumber()
{
}

HRESULT CNumber::Init()
{
	CObject2D::Init();

	BindTexture(m_pTexture);

	//�e�N�X�`���̏�����
	SetTexPos(10,0);

	return S_OK;
}

CNumber * CNumber::Create(const D3DXVECTOR3 pos,const D3DXVECTOR3 size)
{
	CNumber *pObject2D = new CNumber;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(pos);
		pObject2D->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//�e�N�X�`���ǂݍ���
HRESULT CNumber::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CNumber::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}