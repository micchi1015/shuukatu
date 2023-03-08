//=============================================================================
//
// BoxHitbox.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BOX_HITBOX_H
#define BOX_HITBOX_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "hitbox.h"

//=============================================================================
//�O���錾
//=============================================================================
class CLine;

class CBoxHitbox : public CHitbox
{
public:
	CBoxHitbox();										//�R���X�g���N�^
	~CBoxHitbox() override;								//�f�X�g���N�^
														
	HRESULT Init(void) override;						//����������
	void    Uninit(void) override;						//�I������
	void    Update(void) override;						//�X�V����

	//==============================================================================================================
	//												�ÓI�֐�
	//==============================================================================================================


	//��������
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore);
	static CBoxHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nScore, INTERACTION_EFFECT effect);

private:

	bool BoxBoxHit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);					//�����蔻��

	CLine* m_pLine[12];					//�f�o�b�O�悤�̐�
};


#endif