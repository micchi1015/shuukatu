//=============================================================================
//
// directionalLight.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "directionalLight.h"
#include "application.h"
#include "rendering.h"

//=============================================================================
//
//							�ÓI�ϐ��̏�����
//
//=============================================================================
D3DXVECTOR3 CDirectionalLight::m_PrincipalLightDir = Vec3Null;					//��ԋ������C�g

//�R���X�g���N�^
CDirectionalLight::CDirectionalLight()
{
	//�����o�[�ϐ����N���A����
	ZeroMemory(&m_pDirLight, sizeof(D3DLIGHT9));			//���������N���A����
}

//�f�X�g���N�^
CDirectionalLight::~CDirectionalLight()
{

}

//����������
HRESULT CDirectionalLight::Init(void)
{
	//����������
	ZeroMemory(&m_pDirLight, sizeof(m_pDirLight));

	return S_OK;
}

//�I������
void CDirectionalLight::Uninit(void)
{

}

//�X�V����
void CDirectionalLight::Update(void)
{

}

//��ԋ������C�g�̌����̐ݒ�
void CDirectionalLight::SetPrincipalLightDir(const D3DXVECTOR3 dir)
{
	m_PrincipalLightDir = dir;			//��ԋ������C�g�̌����̐ݒ�
}

//��ԋ������C�g�̌����̎擾
const D3DXVECTOR3 CDirectionalLight::GetPrincipalLightDir(void)
{
	return m_PrincipalLightDir;
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CDirectionalLight* CDirectionalLight::Create(D3DXCOLOR col, D3DXVECTOR3 dir)
{
	CDirectionalLight* pLight = new CDirectionalLight;			//���C�g�𐶐�����

	if (FAILED(pLight->Init()))
	{//����������
		return nullptr;
	}

	pLight->m_pDirLight.Type = D3DLIGHT_DIRECTIONAL;					//���C�g�̎�ނ̐ݒ�
	pLight->m_pDirLight.Diffuse = col;									//���C�g�̐F�̐ݒ�
	pLight->m_pDirLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	

	//�����̐ݒ�
	D3DXVECTOR3 newDir;													
	D3DXVec3Normalize(&newDir, &dir);									
	pLight->m_pDirLight.Direction = dir;								

	if (m_PrincipalLightDir == Vec3Null)
	{
		m_PrincipalLightDir = dir;
	}

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();			//�f�o�C�X�̎擾

	pDevice->SetLight(pLight->GetLightIdx(), &pLight->m_pDirLight);					//���C�g�̐ݒ�
	pDevice->LightEnable(pLight->GetLightIdx(), TRUE);								//���C�g��L���ɂ���

	return pLight;					//�����������C�g��Ԃ�
}