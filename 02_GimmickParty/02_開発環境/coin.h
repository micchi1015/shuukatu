//=============================================================================
//
// coin.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _COIN_H
#define _COIN_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;

class CCoin : public CModel
{
public:

	//�R�C���̎��
	enum COIN_TYPE
	{
		COIN_0 = 0,					//10�_�̃R�C��
		COIN_1,						//20�_�̃R�C��
		COIN_2,						//30�_�̃R�C��
		COIN_3,						//50�_�̃R�C��
									
		COIN_DROPPED,				//���Ƃ����R�C��

		COIN_MAX
	};

	CCoin();									//�R���X�g���N�^
	~CCoin() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	void SetMove(const D3DXVECTOR3 move);		//�ړ��ʂ̐ݒ菈��

	const D3DXVECTOR3 GetMove(void);			//�ړ��ʂ̎擾����


	static CCoin* Create(const D3DXVECTOR3 pos, const COIN_TYPE type);						//��������
	static CCoin* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const COIN_TYPE type);		//��������

private:

	static const D3DXVECTOR3 m_hitboxSize[COIN_MAX];		//�q�b�g�{�b�N�X�̑傫��

	D3DXVECTOR3 m_move;				//�ړ���
	int m_nLife;					//���C�t

	CBoxHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^

};





#endif