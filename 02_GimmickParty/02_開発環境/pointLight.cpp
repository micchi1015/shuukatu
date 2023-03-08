//=============================================================================
//
// pointLight.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "pointLight.h"
#include "application.h"
#include "rendering.h"

//�R���X�g���N�^
CPointLight::CPointLight()
{
	ZeroMemory(&m_pPointLight, sizeof(D3DLIGHT9));
}

//�f�X�g���N�^
CPointLight::~CPointLight()
{

}

//����������
HRESULT CPointLight::Init(void)
{
	ZeroMemory(&m_pPointLight, sizeof(m_pPointLight));

	return S_OK;
}

//�I������
void CPointLight::Uninit(void)
{

}

//�X�V����
void CPointLight::Update(void)
{

}



CPointLight* CPointLight::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 attenuation, float fRange)
{
	CPointLight* pLight = new CPointLight;

	if (FAILED(pLight->Init()))
	{
		return nullptr;
	}

	pLight->m_pPointLight.Type = D3DLIGHT_POINT;
	pLight->m_pPointLight.Position = pos;
	pLight->m_pPointLight.Diffuse = col;
	pLight->m_pPointLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pLight->m_pPointLight.Attenuation0 = attenuation.x;
	pLight->m_pPointLight.Attenuation1 = attenuation.y;
	pLight->m_pPointLight.Attenuation2 = attenuation.z;
	pLight->m_pPointLight.Range = fRange;

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	pDevice->SetLight(pLight->GetLightIdx(), &pLight->m_pPointLight);
	pDevice->LightEnable(pLight->GetLightIdx(), TRUE);

	return pLight;
}