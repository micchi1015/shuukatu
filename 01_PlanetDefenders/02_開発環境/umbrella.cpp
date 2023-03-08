//------------------------------
//
// �P�̏���[umbrella.cpp]
// Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "bullet.h"
#include "explosion.h"
#include "object2D.h"
#include"renderer.h"
#include "sound.h"
#include "umbrella.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CUmbrella::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^

//�R���X�g���N�^
CUmbrella::CUmbrella()
{
	
}

//�f�X�g���N�^
CUmbrella::~CUmbrella()
{
}

//����������
HRESULT CUmbrella::Init()
{
	CObject2D::Init();

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	BindTexture(m_pTexture);
	SetLifeTexPos(3.0, 2.0f, 3.0f, 1.0f);

	return S_OK;
}

//�X�V����
void CUmbrella::Update()
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();
	D3DXVECTOR3 UmbrellaPos = GetPos();
	D3DXVECTOR3 UmbrellaSize = CObject2D::GetSize();
	D3DXVECTOR3 UmbrellaMove = CObject2D::GetMove();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_3,nCnt);

		if (pObj != nullptr)
		{//�^�C�v���v���C���[��������
			if (pObj->GetType() == CObject::OBJTYPE_PLAYER)
			{
				D3DXVECTOR3 PlayerMove = pObj->GetMove();

				UmbrellaPos += PlayerMove;

				SetPos(UmbrellaPos);
			}
		}
	}

	CObject2D::Update();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_2,nCnt);

		if (pObj != nullptr)
		{//�^�C�v���e��������
			if (pObj->GetType() == CObject::OBJTYPE_BULLET && pObj->GetBulletType() == CBullet::BULLET_ENEMY)
			{
				//�e�̈ʒu�擾
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//�e�̃T�C�Y�擾
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				int ObjectLife = pObj->GetLife();

				//�P�ƒe�̓����蔻��
				if (UmbrellaPos.y - UmbrellaSize.y / 2 <= ObjectPos.y + ObjectSize.y / 2
					&& UmbrellaPos.y + UmbrellaSize.y / 2 >= ObjectPos.y - ObjectSize.y / 2
					&& UmbrellaPos.x + UmbrellaSize.x / 2 >= ObjectPos.x - ObjectSize.x / 2
					&& UmbrellaPos.x - UmbrellaSize.x / 2 <= ObjectPos.x + ObjectSize.x / 2)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_EXP);

					CExplosion::Create(ObjectPos,D3DXVECTOR3(50.0f,50.0f,0.0f));
					pObj->Uninit();
				}
			}
		}
	}
}

//����
CUmbrella * CUmbrella::Create(D3DXVECTOR3 pos)
{
	CUmbrella *pObject2D = new CUmbrella;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(pos);
		pObject2D->SetType(OBJTYPE_UMBRELLA);
		pObject2D->SetSize(D3DXVECTOR3(60.0f, 60.0f, 0.0f));
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//�e�N�X�`���ǂݍ���
HRESULT CUmbrella::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\umbrella-520x520.png",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CUmbrella::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}