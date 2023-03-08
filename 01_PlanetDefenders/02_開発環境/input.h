//-----------------------------
//
// [input.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//---------------------------
//インクルード
//---------------------------
#define DIRECTINPUT_VERSION			(0x0800)		//ビルド時の警告対処用マクロ
#include "dinput.h"									//入力処理に必要
#pragma comment(lib,"dinput8.lib")					//入力処理に必要
#pragma comment(lib,"dxguid.lib")					// DirectXコンポーネントに使用

//---------------------------
//マクロ定義
//---------------------------
#define NUM_KEY_MAX		(256)		//キーの最大数

//---------------------------
//インプットクラス
//---------------------------
class CInput
{
public:
	CInput();					//コンストラクタ
	virtual ~CInput() = 0;		//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd) = 0;	//初期化処理
	virtual void Uninit() = 0;									//終了処理
	virtual void Update() = 0;									//更新処理

protected:
	static LPDIRECTINPUT8 m_pInput;					//Directlnputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevice;					//入力デバイスへのポインタ
};

//---------------------------
//インプットキーボードクラス
//---------------------------
class CInputKeyboard: public CInput
{
public:
	CInputKeyboard();				//コンストラクタ
	~CInputKeyboard()override;		//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;	//初期化処理
	void Uninit()override;									//終了処理
	void Update()override;									//更新処理
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];						//キーボードのプレス情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];				//キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];				//キーボードのリリース情報
};
#endif