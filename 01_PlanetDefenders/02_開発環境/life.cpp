//-------------------------
//
//ライフの処理[life.cpp]
//Author:梶田大夢
//
//-------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "life.h"
#include "renderer.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CLife::m_pTexture = nullptr;		//テクスチャへのポインタ

													//コンストラクタ
CLife::CLife(int nPriortiy) : CObject2D(nPriortiy)
{
	SetType(OBJTYPE_LIFE);
}

//デストラクタ
CLife::~CLife()
{
}

//初期化処理
HRESULT CLife::Init()
{
	CObject2D::Init();
	BindTexture(m_pTexture);

	return S_OK;
}
//更新処理
void CLife::Update()
{
	CObject2D::Update();
}

//爆発の生成
CLife *CLife::Create(const D3DXVECTOR3 pos)
{
	CLife *pLife = new CLife;

	if (pLife != nullptr)
	{
		pLife->Init();
		pLife->SetPos(pos);
		pLife->SetSize(D3DXVECTOR3(300.0f, 50.0f, 0.0f));
		pLife->SetType(OBJTYPE_LIFE);
	}
	else
	{
		assert(false);
	}

	return pLife;
}

//テクスチャ読み込み
HRESULT CLife::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\hVxD8UlgFHKJ9eQ1662005850_1662005861.png",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CLife::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}