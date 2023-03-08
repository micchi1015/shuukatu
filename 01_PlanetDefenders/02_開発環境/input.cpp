//-------------------------
//
//入力の処理[input.cpp]
//Author:梶田大夢
//
//-------------------------
//---------------------------
//インクルード
//---------------------------
#include "input.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//コンストラクタ
CInput::CInput()
{
	m_pInput = nullptr;			//Directlnputオブジェクトへのポインタ
	m_pDevice= nullptr;			//入力デバイスへのポインタ
}

//デストラクタ
CInput::~CInput()
{
}

//コンストラクタ
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = {};
		m_aKeyStateTrigger[nCnt] = {};
		m_aKeyStateRelease[nCnt] = {};
	}
}

//デストラクタ
CInputKeyboard::~CInputKeyboard()
{

}

//初期化処理
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Directinputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイス（キーボード）の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットのを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権
	m_pDevice->Acquire();

	return S_OK;
}

//終了処理
void CInputKeyboard::Uninit()
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();		//キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if (m_pInput != NULL)
	{	
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//更新処理
void CInputKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];			//キーボードの入力情報

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyStateTrigger[nCntKey] ^ 0);
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//Press処理
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//Trigger処理
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//Release処理
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}