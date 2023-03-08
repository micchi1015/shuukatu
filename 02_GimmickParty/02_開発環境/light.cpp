//=============================================================================
//
// light.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "light.h"
#include "application.h"
#include "rendering.h"

//���C�g�̃A�h���X�z��
CLight* CLight::m_pLight[CLight::MaxLight] = {};

//�R���X�g���N�^
CLight::CLight()
{
	for (int nCnt = 0; nCnt < CLight::MaxLight; nCnt++)
	{
		if (m_pLight[nCnt] == nullptr)
		{//�X�y�[�X����������A���C�g�̃A�h���X��ۑ�����
			m_pLight[nCnt] = this;
			m_nIdx = nCnt;
			break;
		}
	}
}

//�f�X�g���N�^
CLight::~CLight()
{

}

//���C�g�̏���������
HRESULT CLight::Init(void)
{
	return S_OK;
}

//���C�g�̏I������
void CLight::Uninit(void)
{

}

//���C�g�̍X�V����
void CLight::Update(void)
{

}

//�C���X�^���X�̔j������
void CLight::Release(void)
{
	int nIdx = m_nIdx;			//�C���f�b�N�X��ۑ�����

	delete m_pLight[nIdx];		//���������������
	m_pLight[nIdx] = nullptr;	//�|�C���^��null�ɂ���
}

//�C���f�b�N�X�̎擾����
const int CLight::GetLightIdx(void)
{
	return m_nIdx;
}



//�S���̃��C�g�̔j������
void CLight::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < CLight::MaxLight; nCnt++)
	{
		if (m_pLight[nCnt] != nullptr)
		{
			m_pLight[nCnt]->Release();
		}
	}
}