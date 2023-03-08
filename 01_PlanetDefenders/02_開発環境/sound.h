//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM1
	SOUND_LABEL_BGM001,			// BGM2
	SOUND_LABEL_BGM002,			// BGM3
	SOUND_LABEL_BGM003,			// BGM4
	SOUND_LABEL_BGM004,			// BGM5
	SOUND_LABEL_SE_EXP,			// 爆発音
	SOUND_LABEL_SE_SHOOT,		// 発射音
	SOUND_LABEL_SE_ENEMYSHOOT,	// 敵発射音
	SOUND_LABEL_SE_ATTACK,		// 攻撃音
	SOUND_LABEL_SE_DEC,			// 決定音
	SOUND_LABEL_SE_SEL,			// 選択音
	SOUND_LABEL_SE_COUNTDOWN,	// カウントダウン
	SOUND_LABEL_SE_START,		// スタート
	SOUND_LABEL_SE_WING,		// 羽ばたき音
	SOUND_LABEL_SE_MOTION,		// 歩き音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
