//=============================================================================
//
// model.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _LAVA_FLOOR_H
#define _LAVA_FLOOR_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;

class CLavaFloor : public CModel

{
public:
	CLavaFloor();										//�R���X�g���N�^
	~CLavaFloor();										//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��
														
	static CLavaFloor* Create(const D3DXVECTOR3 pos);	//��������

private:

	CBoxHitbox* m_pHitbox;								//�q�b�g�{�b�N�X
};





#endif