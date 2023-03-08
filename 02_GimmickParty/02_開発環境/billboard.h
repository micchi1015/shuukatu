//=============================================================================
//
// billboard.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

class CBillboard : public CObject
{
public:
	CBillboard();										//�R���X�g���N�^
	CBillboard(const int nPriority);					//�R���X�g���N�^
	virtual ~CBillboard() override;						//�f�X�g���N�^

	virtual HRESULT Init(void) override;				//����������
	virtual void Uninit(void) override;					//�I������
	virtual void Update(void) override;					//�X�V����
	virtual void Draw(void) override;					//�`�揈��

	void SetSize(const D3DXVECTOR2 size);				//�T�C�Y�̐ݒ菈��
	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	void SetRot(const D3DXVECTOR3 rot);					//�����̐ݒ菈��
	const D3DXVECTOR3 GetRot(void);						//�����̎擾����
														
	void SetColor(const D3DXCOLOR col);					//�J�[���[�̐ݒ菈��
	const D3DXCOLOR GetColor(void);						//�J�[���[�̎擾����
		
	void SetTexture(TextType textType);					//�e�N�X�`���̎�ނ̐ݒ菈��

	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);							//��������
	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, const int nPriority);		//��������
		
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;						//�e�N�X�`�����ւ̃|�C���^

	D3DXVECTOR3 m_pos;									//�|���S���̈ʒu
	D3DXVECTOR3 m_rot;									//�|���S���̉�]�p�x
	D3DXCOLOR	m_col;									//�J�[���[
	D3DXVECTOR2 m_size;									//�|���S���̕��ƍ���
	D3DXMATRIX m_mtxWorld;								//���[���h�}�g���b�N�X
};

#endif