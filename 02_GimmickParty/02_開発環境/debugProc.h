//=============================================================================
//
// debugProc.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include <stdarg.h>
#include <string>

class CDebugProc
{
public:
	CDebugProc();										//�R���X�g���N�^
	~CDebugProc();										//�f�X�g���N�^
														
	void Init(void);									//����������
	void Uninit(void);									//�I������
														
	static void Print(const char *pFormat, ...);		//������̐ݒ菈��
	static void Draw(void);								//�`�揈��

	static CDebugProc* Create(void);					//��������

private:

	static LPD3DXFONT m_pFont;							//�t�H���g
	static std::string m_str;							//������
};


#endif