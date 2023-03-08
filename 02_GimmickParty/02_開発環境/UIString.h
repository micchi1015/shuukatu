//=============================================================================
//
// UIString.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _UI_STRING_H_
#define _UI_STRING_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CLetter;

class CUIString : public CObject
{
public:
	CUIString();									//�R���X�g���N�^
	CUIString(const int nPriority);					//�R���X�g���N�^
	~CUIString() override;							//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void ChangeString(const char* pString);
	void ChangeColor(const D3DXCOLOR col);
	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��
	const D3DXVECTOR2 GetSize(void) override;		//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;		//�ʒu�̎擾����

	void ReleaseLetters(void);						//�j������

	static CUIString* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const char* pString);								//��������
	static CUIString* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const char* pString, const int nPriority);			//��������

private:

	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR2 m_size;			//�T�C�Y
								
	CLetter* m_pTop;			//�ŏ��̕����̃A�h���X
};

#endif