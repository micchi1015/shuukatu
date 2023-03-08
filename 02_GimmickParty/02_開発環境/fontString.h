//=============================================================================
//
// fontString.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _FONTSTRING_H_
#define _FONTSTRING_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "font.h"

//---------------------------
//�N���X�錾
//---------------------------
class CFontString
{
public:
	CFontString();
	~CFontString();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SizeScale(void);			// �����̊g�又��
	void SizeReset(void);			// �����̑傫������������
	void SetSellect(void);			// ���ݔԍ��̐ݒ菈��
	void SetColor(D3DXCOLOR col);	// �F�̐ݒ菈��

	static CFontString* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const std::string letter);
private:
	static const int MaxWordLenght = 24;	// ������̍ő啶����

	int m_nNum;						// ������
	float m_fScale;					// �����̑傫��
	bool m_bScale;					// �����̊g�唻��
	bool m_bSellect;				// �����̑I�𔻒�
	D3DXVECTOR2 m_sizeYuan;			// �����̌��̑傫��
	CFont* m_pFont[MaxWordLenght];	// �����̃|�C���^
};

#endif // !_FONTSTRING_H_
