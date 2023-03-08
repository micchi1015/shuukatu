//=============================================================================
//
// SpikeBall.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _SPIKE_BALL_H
#define _SPIKE_BALL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;

class CSpikeBall : public CModel
{
public:

	CSpikeBall();											//�R���X�g���N�^
	~CSpikeBall() override;									//�f�X�g���N�^
															
	HRESULT Init(void) override;							//����������
	void Uninit(void) override;								//�I������
	void Update(void) override;								//�X�V����
	void Draw(void) override;								//�`�揈��
															
	static CSpikeBall* Create(const D3DXVECTOR3 pos);		//��������

private:

	CCylinderHitbox* m_pHitbox;								//�q�b�g�{�b�N�X
};


#endif
#pragma once
