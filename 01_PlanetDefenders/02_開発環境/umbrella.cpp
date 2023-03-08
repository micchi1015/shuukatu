//------------------------------
//
// 傘の処理[umbrella.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "bullet.h"
#include "explosion.h"
#include "object2D.h"
#include"renderer.h"
#include "sound.h"
#include "umbrella.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CUmbrella::m_pTexture = nullptr;		//テクスチャへのポインタ

//コンストラクタ
CUmbrella::CUmbrella()
{
	
}

//デストラクタ
CUmbrella::~CUmbrella()
{
}

//初期化処理
HRESULT CUmbrella::Init()
{
	CObject2D::Init();

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	BindTexture(m_pTexture);
	SetLifeTexPos(3.0, 2.0f, 3.0f, 1.0f);

	return S_OK;
}

//更新処理
void CUmbrella::Update()
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();
	D3DXVECTOR3 UmbrellaPos = GetPos();
	D3DXVECTOR3 UmbrellaSize = CObject2D::GetSize();
	D3DXVECTOR3 UmbrellaMove = CObject2D::GetMove();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_3,nCnt);

		if (pObj != nullptr)
		{//タイプがプレイヤーだったら
			if (pObj->GetType() == CObject::OBJTYPE_PLAYER)
			{
				D3DXVECTOR3 PlayerMove = pObj->GetMove();

				UmbrellaPos += PlayerMove;

				SetPos(UmbrellaPos);
			}
		}
	}

	CObject2D::Update();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_2,nCnt);

		if (pObj != nullptr)
		{//タイプが弾だったら
			if (pObj->GetType() == CObject::OBJTYPE_BULLET && pObj->GetBulletType() == CBullet::BULLET_ENEMY)
			{
				//弾の位置取得
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//弾のサイズ取得
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				int ObjectLife = pObj->GetLife();

				//傘と弾の当たり判定
				if (UmbrellaPos.y - UmbrellaSize.y / 2 <= ObjectPos.y + ObjectSize.y / 2
					&& UmbrellaPos.y + UmbrellaSize.y / 2 >= ObjectPos.y - ObjectSize.y / 2
					&& UmbrellaPos.x + UmbrellaSize.x / 2 >= ObjectPos.x - ObjectSize.x / 2
					&& UmbrellaPos.x - UmbrellaSize.x / 2 <= ObjectPos.x + ObjectSize.x / 2)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_EXP);

					CExplosion::Create(ObjectPos,D3DXVECTOR3(50.0f,50.0f,0.0f));
					pObj->Uninit();
				}
			}
		}
	}
}

//生成
CUmbrella * CUmbrella::Create(D3DXVECTOR3 pos)
{
	CUmbrella *pObject2D = new CUmbrella;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(pos);
		pObject2D->SetType(OBJTYPE_UMBRELLA);
		pObject2D->SetSize(D3DXVECTOR3(60.0f, 60.0f, 0.0f));
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//テクスチャ読み込み
HRESULT CUmbrella::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\umbrella-520x520.png",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CUmbrella::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}