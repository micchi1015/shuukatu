//=============================================================================
//
// hitbox.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef CYLINDER_HITBOX_H
#define CYLINDER_HITBOX_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "hitbox.h"

class CLine;

class CCylinderHitbox : public CHitbox
{
public:
	CCylinderHitbox();						//�R���X�g���N�^
	~CCylinderHitbox() override;			//�f�X�g���N�^
											
	HRESULT Init(void) override;			//����������
	void    Uninit(void) override;			//�I������
	void    Update(void) override;			//�X�V����

	//��������
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nPlayerIdx);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent);
	static CCylinderHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect);

private:

	bool CylinderCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);							//�V�����_�[�ƃV�����_�[�̓����蔻��
	//bool CylinderBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);			//�V�����_�[����`�̓����蔻��
	bool PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);				//�_�Ƌ�`�̓����蔻��

	CLine* m_pLine[18];					//�f�o�b�O�p�̐�

};


#endif