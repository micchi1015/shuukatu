//=============================================================================
//
// pointLight.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "light.h"

class CPointLight : public CLight
{
public:

	CPointLight();							//�R���X�g���N�^
	~CPointLight() override;				//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CPointLight* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 attenuation, float fRange);			//the x component of attenuation is the attenuation 0 of D3DLIGHT9; the y component is attenuation 1 and the z component is attenuation 2

private:

	D3DLIGHT9 m_pPointLight;				//���C�g
};

#endif // !_DIRECTIONAL_LIGHT_H_