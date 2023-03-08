//=============================================================================
//
// trampoline.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "trampoline.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "camera.h"

//�R���X�g���N�^
CTrampoline::CTrampoline()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;				//�q�b�g�{�b�N�X�𐶐�����
}

//�f�X�g���N�^
CTrampoline::~CTrampoline()
{

}

//����������
HRESULT CTrampoline::Init(void)
{
	//����������
	if (FAILED(CModel::Init()))
	{//����������
		return -1;
	}

	m_pHitbox = nullptr;			//�q�b�g�{�b�N�X

	return S_OK;
}

//�I������
void CTrampoline::Uninit(void)
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
void CTrampoline::Update(void)
{
	//��{�N���X�̍X�V����
	CModel::Update();

	if (GetPos().z < CApplication::GetCamera()->GetPos().z - 100.0f)
	{//�����Ȃ��Ȃ�����A����
		Release();
	}
}

//�`�揈��
void CTrampoline::Draw(void)
{
	if (GetPos().z < CApplication::GetCamera()->GetPos().z + 650.0f)
	{//����������A�`�悵�Ȃ�
		CModel::Draw();				//��{�N���X�̕`�揈��
	}
}




//=============================================================================
//								�ÓI�֐�
//=============================================================================



//��������
CTrampoline* CTrampoline::Create(const D3DXVECTOR3 pos)
{
	CTrampoline* pModel = new CTrampoline;			//�C���X�^���X�𐶐�����

	if (FAILED(pModel->Init()))
	{//����������
		return nullptr;
	}

	pModel->SetModel(CModel::MODEL_TRAMPOLINE);				//���f���̐ݒ�
	pModel->SetPos(pos);									//�ʒu�̐ݒ�
	pModel->SetShadowDraw(false);							//�e��`�悵�Ȃ��悤�ɐݒ肷��

	//�q�b�g�{�b�N�X�̐���
	pModel->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(20.0f, 3.0f, 20.0f), CHitbox::TYPE_OBSTACLE, 0, nullptr, CHitbox::EFFECT_JUMP);

	return pModel;											//���������C���X�^���X��Ԃ�
}