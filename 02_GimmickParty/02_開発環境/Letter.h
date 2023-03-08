//=============================================================================
//
// Letter.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef LETTER_H
#define LETTER_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

class CLetter : public CObject_2D
{
public:
	CLetter();																//�R���X�g���N�^
	CLetter(const int nPriority);											//�R���X�g���N�^
	~CLetter() override;													//�f�X�g���N�^

	HRESULT Init(void) override;											//����������
	void Uninit(void) override;												//�I������
	void Update(void) override;												//�X�V����
	void Draw(void) override;												//�I������

	bool Convert(const char symbol);										//�����̕ϊ�����

	void SetPrevLetter(CLetter* pPrev);										//�O�̕����̐ݒ菈��
	void SetNextLetter(CLetter* pNext);										//���̕����̐ݒ菈��
																			
	CLetter* GetPrevLetter(void);											//�O�̕����̎擾����
	CLetter* GetNextLetter(void);											//���̕����̎擾����

	static CLetter* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter);			//��������
	static CLetter* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter, const int nPriority);			//��������

private:

	CLetter* m_pPreviousLetter;		//�O�̕���
	CLetter* m_pNextLetter;			//���̕���
};

#endif
