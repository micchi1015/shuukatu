//------------------------------
//
//ポリゴン処理[polygon.cpp]
//Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include "application.h"
#include "bullet.h"
#include "game.h"
#include "renderer.h"
#include "polygon.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture;				//テクスチャへのポインタ
CPolygon *CPolygon::m_Polygon;
int CPolygon::m_Life = 1;

//コンストラクタ
CPolygon::CPolygon(int nPriority) : CObject2D(nPriority)
{
	SetType(OBJTYPE_LIFEBER);
}

//デストラクタ
CPolygon::~CPolygon()
{
}

//スコアの初期化処理 
HRESULT CPolygon::Init()
{
	CObject2D::Init();
	BindTexture(m_pTexture);
	SetColer(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	return S_OK;
}

//スコアの更新処理
void CPolygon::Update()
{
	CObject2D::Update();
}

CPolygon * CPolygon::Create(const D3DXVECTOR3 pos)
{
	CPolygon *pPolygon = new CPolygon;

	if (pPolygon != nullptr)
	{
		pPolygon->Init();
		pPolygon->SetPos(pos);
		pPolygon->SetSize(D3DXVECTOR3(20.0f,33.0f,0.0f));
		pPolygon->SetType(OBJTYPE_LIFEBER);
		pPolygon->SetLife(1);
	}

	return pPolygon;
}

//ライフの設定
void CPolygon::SetLife(int nLife)
{
	m_Life = nLife;
}

//ライフの値を返す
int CPolygon::GetLife()
{
	return m_Life;
}

//テクスチャの更新
void CPolygon::UpdateLife(int nCnt)
{
	m_Polygon = CGame::GetPolygon(nCnt);
	m_Polygon->Uninit();
}

//テクスチャ読み込み
HRESULT CPolygon::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\polygon.png",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CPolygon::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}