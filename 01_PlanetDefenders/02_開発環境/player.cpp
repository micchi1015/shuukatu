//------------------------------
//
// プレイヤーの処理[player.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include "input.h"
#include "object2D.h"
#include "player.h"
#include "renderer.h"
#include "sound.h"
#include "umbrella.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = nullptr;		//テクスチャへのポインタ
int				   CPlayer::m_ColorTime = 0;
int				   CPlayer::m_Life = 0;

//コンストラクタ
CPlayer::CPlayer()
{
}

//デストラクタ
CPlayer::~CPlayer()
{
}

//初期化処理
HRESULT CPlayer::Init()
{
	CObject2D::Init();

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//プレイヤー情報の初期化
	m_nDirectionMove = 0;
	mIndex = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	BindTexture(m_pTexture);
	
	SetLifeTexPos(8.0f, (float)m_nPatternAnim, 2.0f, 1.0f);

	return S_OK;
}

//更新処理
void CPlayer::Update()
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();
	D3DXVECTOR3 PlayerPos = GetPos();
	D3DXVECTOR3 PlayerSize = CObject2D::GetSize();

	//移動量の最大値
	if (m_playermove.x <= -25.0f)
	{
		m_playermove.x = -25.0f;
	}
	else if (m_playermove.x >= 25.0f)
	{
		m_playermove.x = 25.0f;
	}

	if (CGame::GetState() == CGame::STATE_EXE)
	{
		//移動
		m_nCounterAnim++;

		if ((m_nCounterAnim % 8) == 0)
		{
			if (pInputKeyboard->GetPress(DIK_A))
			{//Aキーが押された
			 //移動量を更新(増加させる)
				m_nDirectionMove = 0;
				m_playermove.x -= (D3DX_PI * 0.5f) * 3.5f;

				m_nPatternAnim = (m_nPatternAnim + 1) % 8;		//パターンNO.を更新する
				SetLifeTexPos(8.0f, (float)m_nPatternAnim, 2.0f, 1.0f);
			}
			else if (pInputKeyboard->GetPress(DIK_D))
			{//Dキーが押された
			 //移動量を更新(増加させる)
				m_nDirectionMove = 1;
				m_playermove.x += (D3DX_PI * 0.5f) *3.5f;

				m_nPatternAnim = (m_nPatternAnim + 1) % 8;		//パターンNO.を更新する
				SetLifeTexPos(8.0f, (float)m_nPatternAnim, 2.0f, 0.0f);
			}
		}

		//傘
		if (pInputKeyboard->GetTrigger(DIK_C) == true)
		{
			CUmbrella::Create(D3DXVECTOR3(PlayerPos.x + 10.0f, PlayerPos.y - 30.0f, 0.0f));
			mIndex = 1;
		}
		else if (pInputKeyboard->GetPress(DIK_C) == false)
		{
			//空中弾
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
			{
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_SHOOT);
				CBullet::Create(D3DXVECTOR3(PlayerPos.x, PlayerPos.y - GetSize().y / 2.0f, 0.0f), D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), CBullet::BULLET_PLAYER);
			}

			//地上弾
			if (m_nDirectionMove == 0)
			{
				if (pInputKeyboard->GetTrigger(DIK_LSHIFT) == true)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_SHOOT);
					CBullet::Create(D3DXVECTOR3(PlayerPos.x - (GetSize().x / 2), PlayerPos.y, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CBullet::BULLET_PLAYER);
				}
			}
			else if (m_nDirectionMove == 1)
			{
				if (pInputKeyboard->GetTrigger(DIK_LSHIFT) == true)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_SHOOT);
					CBullet::Create(D3DXVECTOR3(PlayerPos.x + (GetSize().x / 2), PlayerPos.y, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CBullet::BULLET_PLAYER);
				}
			}

			for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
			{
				CObject *pObj = CObject::GetMyObject(PRIORITY_3, nCnt);

				if (pObj != nullptr)
				{//タイプが傘だったら
					if (pObj->GetType() == CObject::OBJTYPE_UMBRELLA)
					{
						if (mIndex == 1)
						{
							pObj->Uninit();
						}
					}
				}
			}

			mIndex = 0;
		}
	}

	SetPos(PlayerPos);
	SetMove(m_playermove);
	CObject2D::Update();

	//位置を更新
	PlayerPos.x += m_playermove.x;
	PlayerPos.y += m_playermove.y;
	PlayerPos.z += m_playermove.z;

	//移動量を更新(減衰させる)
	m_playermove.x += (0.0f - m_playermove.x) * 0.1f;
	m_playermove.y += (0.0f - m_playermove.y) * 0.1f;
	m_playermove.z += (0.0f - m_playermove.z) * 0.1f;

	//移動制限
	if (PlayerPos.x + (PlayerSize.x / 2) >= CRenderer::SCREEN_WIDTH)
	{
		PlayerPos.x = CRenderer::SCREEN_WIDTH - (PlayerSize.x / 2);
		m_playermove.x = 0.0f;
		SetMove(m_playermove);
		SetPos(PlayerPos);
	}
	else if (PlayerPos.x - (PlayerSize.x / 2) <= 0)
	{
		PlayerPos.x = 0 + (PlayerSize.x / 2);
		m_playermove.x = 0.0f;
		SetMove(m_playermove);
		SetPos(PlayerPos);
	}

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_3,nCnt);

		if (pObj != nullptr)
		{//タイプが地面だったら
			if (pObj->GetType() == CObject::OBJTYPE_GROUND)
			{
				//地面の位置取得
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//地面のサイズ取得
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				//プレイヤーと地面の当たり判定
				if (ObjectPos.x + ObjectSize.x / 2 >= PlayerPos.x - PlayerSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= PlayerPos.x + PlayerSize.x / 2
					&& ObjectPos.y - ObjectSize.y / 2 <= PlayerPos.y + PlayerSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= PlayerPos.y - PlayerSize.y / 2)
				{
					m_playermove.y = 0;
				}
				else
				{
					//重力分加算
					m_playermove.y += MAX_GRAVITY;
				}
			}
		}
	}
}

//生成
CPlayer * CPlayer::Create()
{
	CPlayer *pObject2D = new CPlayer;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(D3DXVECTOR3(640.0f,600.0f,0.0f));
		pObject2D->SetType(OBJTYPE_PLAYER);
		pObject2D->SetSize(D3DXVECTOR3(50.0f, 80.0f, 0.0f));
		pObject2D->SetLife(7);
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//ライフの設定
void CPlayer::SetLife(int nLife)
{
	m_Life = nLife;
}

//ライフの情報取得
int CPlayer::GetLife()
{
	return m_Life;
}

int CPlayer::GetPlayerLife()
{
	return m_Life;
}

//テクスチャ読み込み
HRESULT CPlayer::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\E.png",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CPlayer::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}