//-------------------------
//
//ライフの処理[playerlife.cpp]
//Author:梶田大夢
//
//-------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "playerlife.h"
#include "renderer.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CPlayerLife::m_pTexture = nullptr;		//テクスチャへのポインタ

//コンストラクタ
CPlayerLife::CPlayerLife(int nPriortiy) : CObject2D(nPriortiy)
{
	SetType(OBJTYPE_LIFE);
}

//デストラクタ
CPlayerLife::~CPlayerLife()
{
}

//初期化処理
HRESULT CPlayerLife::Init()
{
	CObject2D::Init();
	BindTexture(m_pTexture);

	return S_OK;
}
//更新処理
void CPlayerLife::Update()
{
	CObject2D::Update();
}

//爆発の生成
CPlayerLife *CPlayerLife::Create(const D3DXVECTOR3 pos)
{
	CPlayerLife *pLife = new CPlayerLife;

	if (pLife != nullptr)
	{
		pLife->Init();
		pLife->SetPos(pos);
		pLife->SetSize(D3DXVECTOR3(200.0f, 45.0f, 0.0f));
		pLife->SetType(OBJTYPE_LIFE);
	}
	else
	{
		assert(false);
	}

	return pLife;
}

//テクスチャ読み込み
HRESULT CPlayerLife::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\hMxuY0UREkaJw7Y1662186290_1662186348.png",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CPlayerLife::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}