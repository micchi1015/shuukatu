//------------------------------
//
// ナンバーの処理[number.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "number.h"
#include "renderer.h"

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9	CNumber::m_pTexture;		//テクスチャへのポインタ

//コンストラクタ
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{
	
}

//デストラクタ
CNumber::~CNumber()
{
}

HRESULT CNumber::Init()
{
	CObject2D::Init();

	BindTexture(m_pTexture);

	//テクスチャの初期化
	SetTexPos(10,0);

	return S_OK;
}

CNumber * CNumber::Create(const D3DXVECTOR3 pos,const D3DXVECTOR3 size)
{
	CNumber *pObject2D = new CNumber;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(pos);
		pObject2D->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//テクスチャ読み込み
HRESULT CNumber::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CNumber::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}