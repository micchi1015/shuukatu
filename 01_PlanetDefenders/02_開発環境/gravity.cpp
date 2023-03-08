//------------------------------
//
// 重力の処理[gravity.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "collision.h"
#include "gravity.h"
#include "object2D.h"
#include"renderer.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CGravity::m_pTexture[MAX_GRAVITYTEXTURE] = {};	//テクスチャへのポインタ

//コンストラクタ
CGravity::CGravity(int nPriority) : CObject2D(nPriority)
{
}

//デストラクタ
CGravity::~CGravity()
{
}

//初期化処理
HRESULT CGravity::Init()
{
	CObject2D::Init();

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	m_power = 0;

	switch (m_type)
	{
	case GRAVITY_MID:
		BindTexture(m_pTexture[0]);
		break;

	case GRAVITY_LEFT:
		BindTexture(m_pTexture[1]);
		break;

	case GRAVITY_RIGHT:
		BindTexture(m_pTexture[2]);
		break;

	default:
		break;
	}

	return S_OK;
}

//更新処理
void CGravity::Update()
{
	D3DXVECTOR3 GravityPos = CObject2D::GetPos();
 	GRAVITYTYPE GravityType =GetGravityType();
	D3DXVECTOR3 GravitySize = CObject2D::GetSize();
	D3DXCOLOR GravityCol = CObject2D::GetCol();

	CObject2D::SetPos(GravityPos);
	CObject2D::Update();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_2,nCnt);

		if (pObj != nullptr)
		{
			if (pObj->GetType() == CObject::OBJTYPE_BULLET && pObj->GetBulletType() == CBullet::BULLET_PLAYER)
			{
				D3DXVECTOR3 ObjectPos = pObj->GetPos();
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				if (CColision::CollisionCircle(GravityPos, 5.0f, ObjectPos, 165.0f))
				{
					GravityCol = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
					SetColer(GravityCol);

					if (GravityType == GRAVITY_MID)
					{
						D3DXVECTOR3 vector = GravityPos - ObjectPos;
						D3DXVec3Normalize(&vector, &vector);
						vector *= m_power;
						pObj->AddMove(vector);
					}
					else if (GravityType == GRAVITY_LEFT)
					{
						D3DXVECTOR3 vector = (GravityPos - (GravitySize / 2)) - ObjectPos; 
						D3DXVec3Normalize(&vector, &vector);
						vector *= m_power;
						pObj->AddMove(vector);
					}
					else if (GravityType == GRAVITY_RIGHT)
					{
						D3DXVECTOR3 vector = (GravityPos + (GravitySize / 2)) - ObjectPos;
						D3DXVec3Normalize(&vector, &vector);
						vector *= m_power;
						pObj->AddMove(vector);
					}
				}
				else
				{
					GravityCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					SetColer(GravityCol);
				}
			}
		}
	}
}

//生成
CGravity * CGravity::Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,GRAVITYTYPE type,float power)
{
	CGravity *pObject2D = new CGravity;

	if (pObject2D != nullptr)
	{
		pObject2D->SetGravityType(type);
		pObject2D->Init();	
		pObject2D->SetType(OBJTYPE_GRAVITY);
		pObject2D->SetPos(pos);
		pObject2D->SetSize(size);
		pObject2D->SetColer(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		pObject2D->m_power = power;
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//重力タイプ情報取得
CGravity::GRAVITYTYPE CGravity::GetGravityType()
{
	return m_type;
}

//タイプ設定
void CGravity::SetGravityType(GRAVITYTYPE type)
{
	m_type = type;
}

//テクスチャ読み込み
HRESULT CGravity::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Gravity.png",
		&m_pTexture[0]);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LeftGrabity.png",
		&m_pTexture[1]);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RightGravity.png",
		&m_pTexture[2]);
	return S_OK;
}

//テクスチャの破棄
void CGravity::Unload()
{
	for (int nCnt = 0; nCnt < MAX_GRAVITYTEXTURE; nCnt++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}