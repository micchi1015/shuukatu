//-------------------------
//
//爆発の処理[explosion.cpp]
//Author:梶田大夢
//
//-------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "explosion.h"
#include "renderer.h"

//---------------------------
//マクロ定義
//---------------------------
#define		NUM_BESIDESPLIT	(8.0f)		//画像の分割数

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = nullptr;		//テクスチャへのポインタ

//コンストラクタ
CExplosion::CExplosion()
{
}

//デストラクタ
CExplosion::~CExplosion()
{
}

//初期化処理
HRESULT CExplosion::Init()
{
	CObject2D::Init();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	BindTexture(m_pTexture);

	//爆発の初期
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	//テクスチャの座標
	SetTexPos(NUM_BESIDESPLIT, (float)m_nPatternAnim);

	return S_OK;
}
//更新処理
void CExplosion::Update()
{
	D3DXVECTOR3 pos = CObject2D::GetPos();

	m_nCounterAnim++;	//カウンターを加算

	if ((m_nCounterAnim % 3) == 0)
	{//一定時間経過
		//テクスチャの座標変更
		SetTexPos(NUM_BESIDESPLIT, (float)m_nPatternAnim);

		//パターンNo.を更新する
		m_nPatternAnim++;
	}

	CObject2D::Update();

	if (m_nPatternAnim >= 8)
	{
		Uninit();
	}
}

//爆発の生成
CExplosion *CExplosion::Create(const D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	CExplosion *pExplosion = new CExplosion;

	if (pExplosion != nullptr)
	{
		pExplosion->Init();
		pExplosion->SetPos(pos);
		pExplosion->SetSize(size);
	}
	else
	{
		assert(false);
	}

	return pExplosion;
}

//テクスチャ読み込み
HRESULT CExplosion::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CExplosion::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}