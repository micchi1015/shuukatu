//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM1
	SOUND_LABEL_BGM001,			// BGM2
	SOUND_LABEL_BGM002,			// BGM3
	SOUND_LABEL_BGM003,			// BGM4
	SOUND_LABEL_BGM004,			// BGM5
	SOUND_LABEL_SE_EXP,			// ������
	SOUND_LABEL_SE_SHOOT,		// ���ˉ�
	SOUND_LABEL_SE_ENEMYSHOOT,	// �G���ˉ�
	SOUND_LABEL_SE_ATTACK,		// �U����
	SOUND_LABEL_SE_DEC,			// ���艹
	SOUND_LABEL_SE_SEL,			// �I����
	SOUND_LABEL_SE_COUNTDOWN,	// �J�E���g�_�E��
	SOUND_LABEL_SE_START,		// �X�^�[�g
	SOUND_LABEL_SE_WING,		// �H�΂�����
	SOUND_LABEL_SE_MOTION,		// ������
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
