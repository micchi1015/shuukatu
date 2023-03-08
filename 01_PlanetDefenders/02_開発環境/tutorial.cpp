//-----------------------------------------
//
//チュートリアル画面の処理[tutorial.cpp]
//Author:梶田大夢
//
//-----------------------------------------
//---------------------------
//インクルード
//---------------------------
#include "application.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "tutorial.h"
#include "sound.h"

//コンストラクタ
CTutorial::CTutorial()
{
}

//デストラクタ
CTutorial::~CTutorial()
{
}

//初期化処理
HRESULT CTutorial::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\チューと.jpg",
		&m_pTexture[0]);

	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), PRIORITY_3);
	m_pObject2D[0]->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D[0]->BindTexture(m_pTexture[0]);

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM004);

	return S_OK;
}

//終了処理
void CTutorial::Uninit(void)
{
	//サウンドの停止
	StopSound();
	CObject::Release();
}

//更新処理
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
	{
		//モードのセット処理
		CFade::SetFade(CFade::FADE_OUT,CApplication::MODE_TITLE);
	}
}

//描画処理
void CTutorial::Draw(void)
{
}

//チュートリアルの生成
CTutorial * CTutorial::Create()
{
	CTutorial *pTutorial = new CTutorial;

	if (pTutorial != nullptr)
	{
		pTutorial->Init();
	}

	return pTutorial;
}