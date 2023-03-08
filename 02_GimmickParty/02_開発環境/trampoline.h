//=============================================================================
//
// trampoline.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;

class CTrampoline : public CModel
{
public:
	CTrampoline();										//�R���X�g���N�^
	~CTrampoline();										//�f�X�g���N�^
														
	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��
														
	static CTrampoline* Create(const D3DXVECTOR3 pos);	//��������

private:

	CCylinderHitbox* m_pHitbox;							//�q�b�g�{�b�N�X

};






#endif