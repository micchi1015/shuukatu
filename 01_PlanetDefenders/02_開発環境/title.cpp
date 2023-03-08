//-----------------------------------------
//
//タイトル画面の処理[title.cpp]
//Author:梶田大夢
//
//-----------------------------------------
//---------------------------
//インクルード
//---------------------------
#include "application.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "object2D.h"
#include "renderer.h"
#include "result.h"
#include "title.h"
#include "sound.h"

//コンストラクタ
CTitle::CTitle()
{
}

//デストラクタ
CTitle::~CTitle()
{
}

//初期化処理
HRESULT CTitle::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\background.jpg",
		&m_pTexture[0]);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Start.png",
		&m_pTexture[1]);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Tutorial.png",
		&m_pTexture[2]);


	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2,CRenderer::SCREEN_HEIGHT / 2,0.0f),PRIORITY_3);
	m_pObject2D[0]->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D[0]->BindTexture(m_pTexture[0]);

	m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2 - 250.0f, CRenderer::SCREEN_HEIGHT / 2 + 250.0f, 0.0f), PRIORITY_3);
	m_pObject2D[1]->SetSize(D3DXVECTOR3(380.0f, 180.0f, 0.0f));
	m_pObject2D[1]->BindTexture(m_pTexture[1]);

	m_pObject2D[2] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2 + 250.0f, CRenderer::SCREEN_HEIGHT / 2 + 250.0f, 0.0f), PRIORITY_3);
	m_pObject2D[2]->SetSize(D3DXVECTOR3(430.0f, 330.0f, 0.0f));
	m_pObject2D[2]->BindTexture(m_pTexture[2]);

	m_Menu = 0;

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

//終了処理
void CTitle::Uninit(void)
{
	//サウンドの停止
	StopSound();
	CObject::Release();
}

//更新処理
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();

	//頂点カラーの更新
	if (m_Menu == 0)
	{
		m_pObject2D[1]->SetColer(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		m_pObject2D[2]->SetColer(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
	else if (m_Menu == 1)
	{
		m_pObject2D[1]->SetColer(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		m_pObject2D[2]->SetColer(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (m_pFade->GetFade() == CFade::FADE_NONE)
	{
		if (pInputKeyboard->GetTrigger(DIK_LEFT) || pInputKeyboard->GetTrigger(DIK_A))
		{//←が入力されたとき
		 //サウンドの再生
			PlaySound(SOUND_LABEL_SE_SEL);
			m_Menu--;
			if (m_Menu < 0)
			{
				m_Menu = 0;
			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_RIGHT) || pInputKeyboard->GetTrigger(DIK_D))
		{//→が入力されたとき
		 //サウンドの再生
			PlaySound(SOUND_LABEL_SE_SEL);
			m_Menu++;
			if (m_Menu >= 2)
			{
				m_Menu = 1;
			}
		}
	}

	//メニュー選択でフェード移行
	switch (m_Menu)
	{
	case 0:
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_DEC);

			//モードのセット処理
			CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_GAME);
			break;
		}
	case 1:
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_DEC);

			//モードのセット処理
			CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_TUTORIAL);
			break;
		}
	}
}

//描画処理
void CTitle::Draw(void)
{
}

//タイトルの生成
CTitle * CTitle::Create()
{
	CTitle *pTitle = new CTitle;

	if (pTitle != nullptr)
	{
		pTitle->Init();
		CBullet::SetPolygon(0);
		CBullet::SetLifePolygon(0);
		CEnemy::SetSkyEnemy(5);
		CEnemy::SetGroundEnemy(2);
	}

	return pTitle;
}
