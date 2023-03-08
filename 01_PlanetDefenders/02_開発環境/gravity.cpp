//------------------------------
//
// �d�͂̏���[gravity.cpp]
// Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "collision.h"
#include "gravity.h"
#include "object2D.h"
#include"renderer.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CGravity::m_pTexture[MAX_GRAVITYTEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^

//�R���X�g���N�^
CGravity::CGravity(int nPriority) : CObject2D(nPriority)
{
}

//�f�X�g���N�^
CGravity::~CGravity()
{
}

//����������
HRESULT CGravity::Init()
{
	CObject2D::Init();

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	m_power = 0;

	switch (m_type)
	{
	case GRAVITY_MID:
		BindTexture(m_pTexture[0]);
		break;

	case GRAVITY_LEFT:
		BindTexture(m_pTexture[1]);
		break;

	case GRAVITY_RIGHT:
		BindTexture(m_pTexture[2]);
		break;

	default:
		break;
	}

	return S_OK;
}

//�X�V����
void CGravity::Update()
{
	D3DXVECTOR3 GravityPos = CObject2D::GetPos();
 	GRAVITYTYPE GravityType =GetGravityType();
	D3DXVECTOR3 GravitySize = CObject2D::GetSize();
	D3DXCOLOR GravityCol = CObject2D::GetCol();

	CObject2D::SetPos(GravityPos);
	CObject2D::Update();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_2,nCnt);

		if (pObj != nullptr)
		{
			if (pObj->GetType() == CObject::OBJTYPE_BULLET && pObj->GetBulletType() == CBullet::BULLET_PLAYER)
			{
				D3DXVECTOR3 ObjectPos = pObj->GetPos();
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				if (CColision::CollisionCircle(GravityPos, 5.0f, ObjectPos, 165.0f))
				{
					GravityCol = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
					SetColer(GravityCol);

					if (GravityType == GRAVITY_MID)
					{
						D3DXVECTOR3 vector = GravityPos - ObjectPos;
						D3DXVec3Normalize(&vector, &vector);
						vector *= m_power;
						pObj->AddMove(vector);
					}
					else if (GravityType == GRAVITY_LEFT)
					{
						D3DXVECTOR3 vector = (GravityPos - (GravitySize / 2)) - ObjectPos; 
						D3DXVec3Normalize(&vector, &vector);
						vector *= m_power;
						pObj->AddMove(vector);
					}
					else if (GravityType == GRAVITY_RIGHT)
					{
						D3DXVECTOR3 vector = (GravityPos + (GravitySize / 2)) - ObjectPos;
						D3DXVec3Normalize(&vector, &vector);
						vector *= m_power;
						pObj->AddMove(vector);
					}
				}
				else
				{
					GravityCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					SetColer(GravityCol);
				}
			}
		}
	}
}

//����
CGravity * CGravity::Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,GRAVITYTYPE type,float power)
{
	CGravity *pObject2D = new CGravity;

	if (pObject2D != nullptr)
	{
		pObject2D->SetGravityType(type);
		pObject2D->Init();	
		pObject2D->SetType(OBJTYPE_GRAVITY);
		pObject2D->SetPos(pos);
		pObject2D->SetSize(size);
		pObject2D->SetColer(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		pObject2D->m_power = power;
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//�d�̓^�C�v���擾
CGravity::GRAVITYTYPE CGravity::GetGravityType()
{
	return m_type;
}

//�^�C�v�ݒ�
void CGravity::SetGravityType(GRAVITYTYPE type)
{
	m_type = type;
}

//�e�N�X�`���ǂݍ���
HRESULT CGravity::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Gravity.png",
		&m_pTexture[0]);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LeftGrabity.png",
		&m_pTexture[1]);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RightGravity.png",
		&m_pTexture[2]);
	return S_OK;
}

//�e�N�X�`���̔j��
void CGravity::Unload()
{
	for (int nCnt = 0; nCnt < MAX_GRAVITYTEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}