//------------------------------
//
// [application.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "main.h"
#include "ranking.h"
#include "renderer.h"
#include "result.h"
#include "sound.h"
#include "title.h"
#include "tutorial.h"
#include "ranking.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
CRenderer *CApplication::m_pRenderer = nullptr;
CInputKeyboard *CApplication::m_pInputKeyboard = nullptr;
CObject *CApplication::m_pMode = nullptr;
CApplication::MODE CApplication::m_mode = CApplication::MODE_TITLE;

//コンストラクタ
CApplication::CApplication()
{
}

//デストラクタ
CApplication::~CApplication()
{
}

//初期化処理
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_pRenderer = new CRenderer;

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}
	else
	{
		assert(false);
	}

	m_pInputKeyboard = new CInputKeyboard;

	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Init(hInstance, hWnd);
	}
	else
	{
		assert(false);
	}

	//サウンドの初期化処理
	InitSound(hWnd);
	CFade::Create(MODE_TITLE);

	return S_OK;
}

//終了処理
void CApplication::Uninit()
{
	//サウンドの終了処理
	UninitSound();

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//全てのポリゴンの終了処理
	CObject::ReleaseAll();
}

//更新処理
void CApplication::Update()
{
	m_pRenderer->Update();
	m_pInputKeyboard->Update();
}

//描画処理
void CApplication::Draw()
{
	m_pRenderer->Draw();
}

//Rendererの情報取得
CRenderer * CApplication::GetRendere()
{
	return m_pRenderer;
}

//InputKeyboardの情報取得
CInputKeyboard * CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//モード設定
void CApplication::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		m_pMode = nullptr;
	}

	CObject::ReleaseMode();

	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		m_pMode = CTitle::Create();
		break;
	case MODE_GAME:
		m_pMode = CGame::Create();
		break;
	case MODE_RESULT:
		m_pMode = CResult::Create();
		break;
	case MODE_TUTORIAL:
		m_pMode = CTutorial::Create();
		break;
	case MODE_RANKING:
		m_pMode = CRanking::Create();
		CRanking::SetRankingScore();
	default:
		break;
	}
}

CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}