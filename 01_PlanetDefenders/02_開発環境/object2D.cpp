//------------------------------
//
// オブジェクト2Dの処理[object2D.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "input.h"
#include "object.h"
#include "object2D.h"
#include "main.h"
#include "renderer.h"

//コンストラクタ
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;	//テクスチャへのポインタ
	m_pVtxBuff = nullptr;	//頂点バッファへのポインタ
}

//デストラクタ
CObject2D::~CObject2D()
{
}

//初期化処理
HRESULT CObject2D::Init()
{
	//頂点座標へのポインタ
	VERTEX_2D *pVtx;

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//情報の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);													//回転
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nTimer = 0.0f;																		//時間

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x -  m_size.x / 2, m_pos.y - m_size.y / 2,0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x +  m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x +  m_size.x / 2, m_pos.y + m_size.y / 2, 0);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//終了処理
void CObject2D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//更新処理
void CObject2D::Update()
{
	D3DXVECTOR3 move = GetMove();

	VERTEX_2D *pVtx; //頂点へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0);

	//位置を更新
	m_pos.x += move.x;
	m_pos.y += move.y;
	m_pos.z += move.z;

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//描画処理
void CObject2D::Draw()
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	0,2);										

	//テクスチャの解除
	pDevice->SetTexture(0, NULL);
}

//ポリゴンの生成・設定処理
CObject2D *CObject2D::Create(const D3DXVECTOR3 pos, int nPriority)
{
	CObject2D *pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//posの設定
void CObject2D::SetPos(const D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx; //頂点へのポインタ

	 m_pos = pos;

	 //頂点バッファをロックし頂点情報へのポインタを取得
	 m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	 pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	 pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	 pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0);
	 pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0);

	 //頂点バッファをアンロック
	 m_pVtxBuff->Unlock();
}

//カラーの設定
void CObject2D::SetColer(const D3DXCOLOR col)
{
	m_col = col;
}

//sizeの設定
void CObject2D::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}

//posの情報取得
const D3DXVECTOR3 CObject2D::GetPos()
{
	return m_pos;
}

//sizeの情報取得
const D3DXVECTOR3 CObject2D::GetSize()
{
	return m_size;
}

//colの情報取得
const D3DXCOLOR CObject2D::GetCol()
{
	return m_col;
}

//テクスチャを代入
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//横テクスチャ画像の設定
void CObject2D::SetTexPos(float BesideSplit, float nNumIndex)
{
	//頂点座標へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndex / BesideSplit, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nNumIndex +1) / BesideSplit,0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumIndex / BesideSplit,1.0f);
	pVtx[3].tex = D3DXVECTOR2((nNumIndex + 1) / BesideSplit, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//テクスチャ画像の設定
void CObject2D::SetLifeTexPos(float BesideSplit, float nNumIndexX, float Split, float nNumIndexY)
{
	//頂点座標へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / BesideSplit, (nNumIndexY) / Split);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / BesideSplit, (nNumIndexY) / Split);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / BesideSplit, (nNumIndexY + 1) / Split);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / BesideSplit, (nNumIndexY + 1) / Split);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}