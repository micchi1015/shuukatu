//------------------------------
//
// 地面の処理[ground.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "fade.h"
#include "ground.h"
#include "object2D.h"
#include"renderer.h"

//---------------------------
//マクロ定義
//---------------------------
#define		NUM_SPLIT		(3.0f)		//画像の分割数

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CGround::m_pTexture = nullptr;		//テクスチャへのポインタ
int				   CGround::m_Life = 0;

//コンストラクタ
CGround::CGround()
{
	
}

//デストラクタ
CGround::~CGround()
{
}

//初期化処理
HRESULT CGround::Init()
{
	CObject2D::Init();

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	BindTexture(m_pTexture);

	//テクスチャの座標
	SetLifeTexPos(1.0f,0.0f,NUM_SPLIT, (float)m_nPatternAnim);

	return S_OK;
}

//更新処理
void CGround::Update()
{
	D3DXVECTOR3 GroundPos = CObject2D::GetPos();
	D3DXVECTOR3 GroundSize = GetSize();

	SetPos(GroundPos);
	CObject2D::Update();
}

//生成
CGround * CGround::Create()
{
	CGround *pGround = new CGround;

	if (pGround != nullptr)
	{
		pGround->Init();
		pGround->SetPos(D3DXVECTOR3(640.0f, 720.0f, 0.0f));
		pGround->SetType(OBJTYPE_GROUND);
		pGround->SetSize(D3DXVECTOR3(2560.0f, 100.0f, 0.0f));
		pGround->SetLife(12);
	}
	else
	{
		assert(false);
	}

	return pGround;
}

//ライフの設定
void CGround::SetLife(int nLife)
{
	m_Life = nLife;
}

//ライフの値を返す
int CGround::GetLife()
{
	return m_Life;
}

int CGround::GetGroundLife()
{
	return m_Life;
}

//テクスチャの更新
void CGround::UpdateTex()
{
	m_nPatternAnim++;
	SetLifeTexPos(1.0f,0.0f,NUM_SPLIT, (float)m_nPatternAnim);
}

//テクスチャ読み込み
HRESULT CGround::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ground.jpg",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CGround::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}