//=============================================================================
//
// environment.cpp
// Author : Tanimoto Kosuke
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "environment.h"
#include "application.h"
#include "rendering.h"

//�R���X�g���N�^
CEnvironment::CEnvironment()
{

}

//�f�X�g���N�^
CEnvironment::~CEnvironment()
{

}

//������
HRESULT CEnvironment::Init(void)
{
	//����������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	return S_OK;
}

//�I��
void CEnvironment::Uninit(void)
{
	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V
void CEnvironment::Update(void)
{
	//��{�N���X�̍X�V����
	CModel::Update();
}

//�`��
void CEnvironment::Draw(void)
{
	CModel::Draw();
}

//����
CEnvironment * CEnvironment::Create(D3DXVECTOR3 pos, EnvironmentType type)
{
	//�C���X�^���X�𐶐�����
	CEnvironment* pEnvironment = new CEnvironment;

	//�v���C���[�̏���������
	if (FAILED(pEnvironment->Init()))
	{
		return nullptr;
	}

	switch (type)
	{
	case CEnvironment::ENVIRONMENT_MOUNT:
	{
		pEnvironment->SetModel(MODEL_MOUNT_FUJI);	//���f���̐ݒ菈��
	}
	break;
	case CEnvironment::ENVIRONMENT_MOUNT_YUKI:
	{
		pEnvironment->SetModel(MODEL_MOUNT_FUJI_YUKI);	//���f���̐ݒ菈��
	}
	break;
	case CEnvironment::ENVIRONMENT_BALLOON:
	{
		pEnvironment->SetModel(MODEL_BALLOON);	//���f���̐ݒ菈��
	}
	break;
	case CEnvironment::ENVIRONMENT_TREE1:
	{
		pEnvironment->SetModel(MODEL_TREE1);	//���f���̐ݒ菈��
	}
	break;
	case CEnvironment::ENVIRONMENT_TREE2:
	{
		pEnvironment->SetModel(MODEL_TREE2);	//���f���̐ݒ菈��
	}
	break;
	case CEnvironment::ENVIRONMENT_WINDMILL:
	{
		pEnvironment->SetModel(MODEL_WINDMILL);	//���f���̐ݒ菈��
	}
	break;
	case CEnvironment::ENVIRONMENT_AIRSHIP:
	{
		pEnvironment->SetModel(MODEL_AIRSHIP);	//���f���̐ݒ菈��
	}
	break;
	case CEnvironment::ENVIRONMENT_STONE:
	{
		pEnvironment->SetModel(MODEL_STONE);	//���f���̐ݒ菈��
	}
	break;

	default:
		break;
	}
	pEnvironment->SetPos(pos);				//�ʒu�̐ݒ菈��
	pEnvironment->SetShadowDraw(false);

	return pEnvironment;
}
