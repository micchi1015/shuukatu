//--------------------------------
//
//フェードヘッダー[fade.h]
//Author:梶田大夢
//
//--------------------------------
#ifndef _FADE_H_
#define _FADE_H_

//---------------------------
//インクルード
//---------------------------
#include "main.h"
#include "mode.h"
#include "object2D.h"

//---------------------------
//フェードクラス
//---------------------------
class CFade : public CObject2D
{
public:
	enum FADE			//フェードの状態
	{
		FADE_NONE = 0,	//何もしてない状態
		FADE_IN,		//フェードイン状態
		FADE_OUT,		//フェードアウト状態
		FADE_COUNTIN,
		FADE_COUNTOUT,
		FADE_SETMODE,
		FADE_MAX
	};

	explicit CFade(int nPriority = PRIORITY_5);
	~CFade();

	void Init(CApplication::MODE modeNext);		//フェードの初期化処理
	void Uninit(void) override;					//フェードの終了処理
	void Update(void) override;					//フェードの更新処理

	static void SetFade(FADE m_pFade,CApplication::MODE modeNext);	//フェードの設定処理
	FADE GetFade(void);

	static CFade *Create(CApplication::MODE modeNext);

private:
	static CApplication::MODE m_ModeNext;	//次の画面(モード)
	static FADE m_pfade;					//フェードの状態	
	static D3DXCOLOR m_color;				//カラー
};
#endif