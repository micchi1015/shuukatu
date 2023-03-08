//-----------------------------------------
//
//タイトル画面の処理[title.cpp]
//Author:梶田大夢
//
//-----------------------------------------
#include "application.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "result.h"
#include "sound.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
CResult::STATE CResult::m_State = STATE_NONE;

//コンストラクタ
CResult::CResult()
{
}

//デストラクタ
CResult::~CResult()
{
}

//初期化処理
HRESULT CResult::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\utyu50-1536x864.jpg",
		&m_pTexture[0]);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\崩壊した都市の背景.jpg",
		&m_pTexture[1]);

	m_pObject2D = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2,CRenderer::SCREEN_HEIGHT / 2,0.0f),PRIORITY_3);
	m_pObject2D->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));

	switch (m_State)
	{
	case STATE_GAMECLEAR:
		m_pObject2D->BindTexture(m_pTexture[0]);
		break;
	case STATE_GAMEOVER:
		m_pObject2D->BindTexture(m_pTexture[1]);
		break;
	default:
		break;
	}

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);

	return S_OK;
}

//終了処理
void CResult::Uninit(void)
{
	//サウンドの停止
	StopSound();

	CObject::Release();
}

//更新処理
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();

	//決定キー(ENTERキー)が押されたかどうか
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
	{
		//モード設定
		CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RANKING);
	}
}

//生成処理
CResult * CResult::Create()
{
	CResult *pGame = new CResult;

	if (pGame != nullptr)
	{
		pGame->Init();
	}

	return pGame;
}

void CResult::SetState(STATE state)
{
	m_State = state;
}
