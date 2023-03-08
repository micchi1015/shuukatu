//------------------------------
//
// 背景の処理[background.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "background.h"
#include"renderer.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CBg::m_pTexture = nullptr;		//テクスチャへのポインタ

//コンストラクタ
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
}

//デストラクタ
CBg::~CBg()
{
}

//初期化処理
HRESULT CBg::Init()
{
	CObject2D::Init();

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	BindTexture(m_pTexture);

	return S_OK;
}

//生成
CBg *CBg::Create()
{
	CBg *pObject2D = new CBg;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
		pObject2D->SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//テクスチャ読み込み
HRESULT CBg::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Bg.jpg",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CBg::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}