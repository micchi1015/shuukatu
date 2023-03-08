//=============================================================================
//
// bouncePole.h
// Author : KAJITA HIROMU
//
//=============================================================================
#ifndef _BOUNCEPOLE_H
#define _BOUNCEPOLE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;

class CBouncePole : public CModel
{
public:

	CBouncePole();											//�R���X�g���N�^
	~CBouncePole() override;									//�f�X�g���N�^

	HRESULT Init(void) override;							//����������
	void Uninit(void) override;								//�I������
	void Update(void) override;								//�X�V����
	void Draw(void) override;								//�`�揈��

	static CBouncePole* Create(const D3DXVECTOR3 pos);		//��������

private:

	CCylinderHitbox* m_pHitbox;
	D3DXVECTOR3 m_move;
	float m_Height;
};


#endif
#pragma once

