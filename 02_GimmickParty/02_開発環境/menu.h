//=============================================================================
//
// menu.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _MENU_H_
#define _MENU_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fontString.h"

//---------------------------
// �O���錾
//---------------------------
class CFontString;

//---------------------------
//�N���X�錾
//---------------------------
class CMenu
{
public:
	CMenu();
	~CMenu();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void ModeType(void);						// ���[�h���̏���
	void Input(void);							// ���͏���

	static void PauseChange(bool bPause);		// �|�[�Y�̕ύX����
	static void SetResult(void);				// ���U���g�̐ݒ菈��

	static CMenu* Create(void);
private:
	static const int MaxChoice = 10;			// �I������

	static int m_nNumAll;						// �I�����̑S�̐�
	static int m_nSelectNum;					// ���ݑI������Ă���ԍ�
	static bool m_bResult;						// ���U���g����
	static CFontString* m_pChoice[MaxChoice];	// �I����������
	static CFontString* m_pPause;				// �|�[�Y������
	static CObject_2D* m_pObj2D;				// �������|���S��
};

#endif // !_MENU_H_
