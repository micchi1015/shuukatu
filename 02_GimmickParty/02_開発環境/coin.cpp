//=============================================================================
//
// coin.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "coin.h"
#include "BoxHitbox.h"
#include "meshfield.h"
#include "application.h"
#include "effect.h"
#include "camera.h"

//=============================================================================
//
//							�ÓI�ϐ��̏�����
//
//=============================================================================

//�R�C���̓����蔻��̃T�C�Y
const D3DXVECTOR3 CCoin::m_hitboxSize[COIN_MAX] =
{
	{15.0f, 20.0f, 15.0f},
	{15.0f, 20.0f, 15.0f},
	{15.0f, 20.0f, 15.0f},
	{15.0f, 20.0f, 15.0f},
	{15.0f, 20.0f, 15.0f}
};

//�R���X�g���N�^
CCoin::CCoin()
{
	//�����o�[�ϐ����N���A����
	m_move = Vec3Null;			//�ړ���
	m_nLife = 0;				//���C�t
	m_pHitbox = nullptr;		//�q�b�g�{�b�N�X
}

//�f�X�g���N�^
CCoin::~CCoin()
{

}

//����������
HRESULT CCoin::Init(void)
{
	//����������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_move = Vec3Null;				//�ړ��ʂ̐ݒ�
	m_nLife = -1;					//���C�t�̐ݒ�
									
	m_pHitbox = nullptr;			//�q�b�g�{�b�N�X

	return S_OK;
}

//�I������
void CCoin::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CCoin::Update(void)
{
	//��{�N���X�̍X�V����
	CModel::Update();

	if (m_pHitbox != nullptr)
	{//�����蔻�肪null�ł͂Ȃ�������
		if (m_pHitbox->GetCollisionState())
		{//�v���C���[�Ɠ��������ꍇ
			m_pHitbox->Release();		//�q�b�g�{�b�N�X������
			Release();					//�R�C��������
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN_GET);			//�T�E���h���Đ�����

			//�G�t�F�N�g�𐶐�����
			for (int nCnt = 0; nCnt < 50; nCnt++)
			{
				CEffect::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * ((float)CObject::random(-100, 100) * 0.001f)), D3DXVECTOR3((float)CObject::random(-50, 50) * 0.05f, (float)CObject::random(-50, 50) * 0.05f, (float)CObject::random(-50, 50) * 0.05f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.25f), D3DXCOLOR(-0.005f, -0.005f, 0.001f, 0.0f), 1.0f, -0.03f, 30);
			
			}

			return;		
		}
	}

	if (m_nLife > 0)
	{//���C�t��0���傫����������
		m_nLife--;			//���C�t���f�N�������g����

		if (m_nLife <= 0)
		{//���C�t��0�ɂȂ�����
			m_pHitbox->Release();		//�q�b�g�{�b�N�X������
			Release();					//�R�C��������
			return;
		}
	}

	if (D3DXVec3Length(&m_move) > 0.0f)
	{//�ړ��ʂ�0�ł͂Ȃ�������

		//�d�͂𑫂�
		if (m_move.y >= -10.0f)
		{
			m_move.y += -0.7f;
		}

		D3DXVECTOR3 newPos = GetPos() + m_move;			//�V�����ʒu�̌v�Z
		SetPos(newPos);									//�ʒu�̐ݒ�
		m_pHitbox->SetPos(newPos);						//�q�b�g�{�b�N�X�̈ʒu�̐ݒ�

		m_move.x += (0.0f - m_move.x) * 0.05f;			//����
		m_move.z += (0.0f - m_move.z) * 0.05f;			//����

		CMeshfield::FieldInteraction(this);				//���b�V���t�B�[���h�Ƃ̓����蔻��
	}

	if (GetPos().z < CApplication::GetCamera()->GetPos().z - 100.0f)
	{//�����Ȃ��Ȃ�����A����

		Release();
	}
}

//�`�揈��
void CCoin::Draw(void)
{
	if (GetPos().z < CApplication::GetCamera()->GetPos().z + 650.0f)
	{//����������A�`�悵�Ȃ�

		if ((m_nLife % 30) <= 15)
		{//���Ƃ����R�C����������A�_�ł�����
			CModel::Draw();
		}
	}
}

//�ړ��ʂ̐ݒ菈��
void CCoin::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//�ړ��ʂ̎擾����
const D3DXVECTOR3 CCoin::GetMove(void)
{
	return m_move;
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CCoin* CCoin::Create(const D3DXVECTOR3 pos, const COIN_TYPE type)
{
	CCoin* pCoin = new CCoin;			//�R�C���𐶐�����

	if (FAILED(pCoin->Init()))
	{//����������
		return nullptr;
	}

	int nType = (int)CModel::MODEL_COIN_0 + (int)type;					//���f���ԍ����v�Z����

	pCoin->SetModel((CModel::ModelType)nType);							//���f���̐ݒ菈��
	pCoin->SetPos(pos);													//�ʒu�̐ݒ菈��
	pCoin->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.01f, 0.0f));		//��]���x�̐ݒ�

	int nAddScore = 0;

	//��ނɂ���ăX�R�A��ݒ肷��
	switch (type)
	{
	case COIN_0:
	{
		nAddScore = 10;
	}
	break;
	case COIN_1:
	{
		nAddScore = 20;
	}
	break;
	case COIN_2:
	{
		nAddScore = 30;
	}
	break;
	case COIN_3:
	{
		nAddScore = 50;
	}
	break;
	default:
		break;
	}

	pCoin->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, m_hitboxSize[type], CHitbox::TYPE_VANISHING, pCoin, nAddScore);		//�q�b�g�{�b�N�X�𐶐�����

	return pCoin;				//���������C���X�^���X��Ԃ�

}

//��������
CCoin* CCoin::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const COIN_TYPE type)
{
	CCoin* pCoin = new CCoin;			//�R�C���𐶐�����

	if (FAILED(pCoin->Init()))
	{//����������
		return nullptr;
	}

	int nType = (int)CModel::MODEL_COIN_0 + (int)type;					//���f���ԍ����v�Z����

	pCoin->SetModel((CModel::ModelType)nType);							//���f���̐ݒ菈��
	pCoin->SetPos(pos);													//�ʒu�̐ݒ菈��
	pCoin->m_move = move;												//�ړ��ʂ̐ݒ菈��
	pCoin->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.01f, 0.0f));		//��]���x�̐ݒ�
	pCoin->m_nLife = nLife;												//���C�t�̐ݒ�

	pCoin->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, m_hitboxSize[type], CHitbox::TYPE_VANISHING, pCoin, 10);		//�q�b�g�{�b�N�X�𐶐�����

	return pCoin;				//���������C���X�^���X��Ԃ�
}