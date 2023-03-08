//=============================================================================
//
// line.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef LINE_H
#define LINE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

class CLine : public CObject
{
public:
	CLine();											//�R���X�g���N�^
	~CLine();											//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	//��������
	static CLine* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 start, const D3DXVECTOR3 end, D3DXCOLOR col);
	static CLine* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 start, const D3DXVECTOR3 end);

private:

	void SetLine(void);

	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_rot;						//��]
	D3DXCOLOR   m_col;						//�J���[
	D3DXVECTOR3 m_start;					//�n�_
	D3DXVECTOR3 m_finish;					//�I�_
	D3DXMATRIX  m_mtxWorld;					//���[���h�}�g���b�N�X

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

};

#endif