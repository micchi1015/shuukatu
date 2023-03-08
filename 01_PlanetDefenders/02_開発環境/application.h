//-----------------------------
//
// [application.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
//---------------------------
//インクルード
//---------------------------
#include "main.h"

//---------------------------
//前方宣言
//---------------------------
class CInputKeyboard;
class CScore;
class CMode;

//---------------------------
//アプリケーションクラス
//---------------------------
class CApplication
{
public:
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_RANKING,
		MODE_MAX
	};

	CApplication();		//コンストラクタ
	~CApplication();	//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	//初期化処理
	void Uninit();		//終了処理
	void Update();		//更新処理
	void Draw();		//描画処理

	static CRenderer *GetRendere();				//Rendereの情報取得
	static CInputKeyboard *GetInputKeyboard();	//Keyboardの情報取得

	static void SetMode(MODE mode);
	static MODE GetMode();

private:
	static CRenderer *m_pRenderer;				//Rendereのポインタ変数
	static CInputKeyboard *m_pInputKeyboard;	//Keyboardのポインタ変数
	static CObject *m_pMode;
	static MODE m_mode;

	int m_Index;
	int m_count;
};
#endif