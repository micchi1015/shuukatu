//=============================================================================
//
// SpikeBall.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "SpikeBall.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "camera.h"


//�R���X�g���N�^
CSpikeBall::CSpikeBall()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;			//�q�b�g�{�b�N�X
}

//�f�X�g���N�^
CSpikeBall::~CSpikeBall()
{

}

//����������
HRESULT CSpikeBall::Init(void)
{
	//����������
	if (FAILED(CModel::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	m_pHitbox = nullptr;			//�q�b�g�{�b�N�X

	return S_OK;
}

//�I������
void CSpikeBall::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CSpikeBall::Update(void)
{
	if (m_pHitbox != nullptr)
	{//�q�b�g�{�b�N�X��null�ł͂Ȃ�������
		//�ʒu���X�V����
		D3DXVECTOR3 newPos = GetPos() +  m_pHitbox->GetRelativePos();	
		m_pHitbox->SetPos(newPos);
	}

	//��{�N���X�̍X�V����
	CModel::Update();

	if (GetPos().z < CApplication::GetCamera()->GetPos().z - 100.0f)
	{//�����Ȃ��Ȃ�����A����
		Release();
	}
}

//�`�揈��
void CSpikeBall::Draw(void)
{
	if (GetPos().z < CApplication::GetCamera()->GetPos().z + 650.0f)
	{//����������A�`�悵�Ȃ�
		CModel::Draw();
	}
}




//=============================================================================
//								�ÓI�֐�
//=============================================================================




//��������
CSpikeBall* CSpikeBall::Create(const D3DXVECTOR3 pos)
{
	CSpikeBall* pObs = new CSpikeBall;				//�C���X�^���X�𐶐�����

	if (FAILED(pObs->Init()))
	{//����������
		return nullptr;
	}

	pObs->SetModel(CModel::MODEL_SPIKE_BALL);			//���f���̐ݒ�

	pObs->SetPos(pos);		//�ʒu�̐ݒ�

	//�����_���ŉ�]��ݒ肷��
	D3DXVECTOR3 rotation = D3DXVECTOR3((float)random(-100, 100), (float)random(-100, 100), (float)random(-100, 100));
	D3DXVec3Normalize(&rotation, &rotation);
	rotation.x *= 0.1f;
	rotation.y *= 0.1f;
	rotation.z *= 0.1f;
	pObs->StartRotation(rotation);

	//�q�b�g�{�b�N�X�𐶐�����
	pObs->m_pHitbox = CCylinderHitbox::Create(D3DXVECTOR3(pos.x, pos.y - 10.0f, pos.z), Vec3Null, D3DXVECTOR3(8.0f, 20.0f, 8.0f), CHitbox::TYPE_OBSTACLE, -30, pObs, CHitbox::EFFECT_LAUNCH);

	return pObs;									//���������C���X�^���X��Ԃ�
}