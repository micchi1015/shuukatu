//-------------------------
//
//弾の処理[bullet.cpp]
//Author:梶田大夢
//
//-------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>

#include "application.h"
#include "bullet.h"
#include "collision.h"
#include "enemy.h"
#include "explosion.h"
#include "fade.h"
#include "game.h"
#include "life.h"
#include "object.h"
#include "object2D.h"
#include "renderer.h"
#include "result.h"
#include "score.h"
#include "sound.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = nullptr;				//テクスチャへのポインタ
CPolygon *CBullet::m_pPolygon = nullptr;						//地面の体力ポリゴンのポインタ変数
CPlayerLifePolygon *CBullet::m_pPlayerLifePolygon = nullptr;	//プレイヤーの体力ポリゴンのポインタ変数
int CBullet::m_Polygon = 0;										//地面用変数
int CBullet::m_PlayerLifePolygon = 0;							//プレイヤー用変数

//コンストラクタ
CBullet::CBullet(int nPriority) : CObject2D(nPriority)
{
}

//デストラクタ
CBullet::~CBullet()
{
}

//初期化処理
HRESULT CBullet::Init()
{
	//オブジェクト2Dの初期化処理
	CObject2D::Init();

	//テクスチャ分け
	switch (m_type)
	{
	case BULLET_PLAYER:
		BindTexture(m_pTexture);
		break;

	case BULLET_ENEMY:
		BindTexture(m_pTexture);
		break;

	default:
		break;
	}

	//bulletの情報初期化
	m_nLife = 150;
	
	return S_OK;
}

//更新処理
void CBullet::Update()
{
	//pos,size,moveを格納
	D3DXVECTOR3 BulletPos = CObject2D::GetPos();
	D3DXVECTOR3 BulletSize = GetSize();
	D3DXVECTOR3 BulletMove = CObject::GetMove();

	//弾の位置の更新
	BulletPos += BulletMove;

	//弾の寿命のカウントダウン
	m_nLife--;

	//弾の位置を更新
	CObject2D::SetPos(BulletPos);

	//更新処理
	CObject2D::Update();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_3,nCnt);

		if (pObj != nullptr)
		{
			//-------------------------
			//弾と敵の当たり判定
			//-------------------------
			if (pObj->GetType() == CObject::OBJTYPE_ENEMY && m_type == BULLET_PLAYER && (pObj->GetEnemyType() == CEnemy::ENEMY_SKYSPACEMAN || pObj->GetEnemyType() == CEnemy::ENEMY_SKY))
			{//タイプが敵かつプレイヤーの弾だったら
				//敵の位置取得
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//敵のサイズ取得
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				//敵のライフ取得
				int ObjectLife = pObj->GetLife();

				//敵と弾の当たり判定
				if (ObjectPos.y - ObjectSize.y / 2 <= BulletPos.y + BulletSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= BulletPos.y - BulletSize.y / 2
					&& ObjectPos.x + ObjectSize.x / 2 >= BulletPos.x - BulletSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= BulletPos.x + BulletSize.x / 2)
				{
					//敵に当たったら弾のライフを0にする
					m_nLife = 0;

					//敵のライフを1減らす
					ObjectLife--;

					//敵のライフを更新設定する
					pObj->SetLife(ObjectLife);

					//敵のライフが0以下になったら
					if (ObjectLife <= 0)
					{
						//scoreを10追加
						CGame::GetScore()->AddScore(1000);

						//敵の終了処理
						pObj->Uninit();
					}
				}
			}

			//-------------------------
			//弾と敵の当たり判定
			//-------------------------
			if (pObj->GetType() == CObject::OBJTYPE_ENEMY && m_type == BULLET_PLAYER && (pObj->GetEnemyType() == CEnemy::ENEMY_GROUNDSPACEMANR || pObj->GetEnemyType() == CEnemy::ENEMY_GROUNDSPACEMANL))
			{//タイプが敵かつプレイヤーの弾だったら
			 //敵の位置取得
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//敵のサイズ取得
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				//敵のライフ取得
				int ObjectLife = pObj->GetLife();

				//敵と弾の当たり判定
				if (ObjectPos.y - ObjectSize.y / 2 <= BulletPos.y + BulletSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= BulletPos.y - BulletSize.y / 2
					&& ObjectPos.x + ObjectSize.x / 2 - 15.0f>= BulletPos.x - BulletSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 + 15.0f <= BulletPos.x + BulletSize.x / 2)
				{
					//敵に当たったら弾のライフを0にする
					m_nLife = 0;

					//敵のライフを1減らす
					ObjectLife--;

					//敵のライフを更新設定する
					pObj->SetLife(ObjectLife);

					//敵のライフが0以下になったら
					if (ObjectLife <= 0)
					{
						//scoreを10追加
						CGame::GetScore()->AddScore(1000);

						//敵の終了処理
						pObj->Uninit();
					}
				}
			}

			//-------------------------
			//弾とプレイヤーの当たり判定
			//-------------------------
			if (pObj->GetType() == CObject::OBJTYPE_PLAYER && m_type == BULLET_ENEMY)
			{//タイプがプレイヤーかつ敵の弾だったら
				//プレイヤーの位置取得
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//プレイヤーのサイズ取得
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				//プレイヤーのライフ取得
				int ObjectLife = pObj->GetLife();

				//プレイヤーと弾の当たり判定
				if (ObjectPos.y - ObjectSize.y / 2 <= BulletPos.y + BulletSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= BulletPos.y - BulletSize.y / 2
					&& ObjectPos.x + ObjectSize.x / 2 >= BulletPos.x - BulletSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= BulletPos.x + BulletSize.x / 2)
				{
					//弾のライフを0にする
					m_nLife = 0;

					//プレイヤーのライフを1減らす
					ObjectLife--;

					//プレイヤーのライフを更新設定する
					pObj->SetLife(ObjectLife);

					//プレイヤーの体力ポリゴンを減らす
					SubPlayerLife();

					//プレイヤーのライフが0以下になったら
					if (ObjectLife <= 0)
					{
						//プレイヤーの終了処理
						pObj->Uninit();
						CResult::SetState(CResult::STATE_GAMEOVER);
						CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);		
					}
				}
			}

			//-------------------------
			//弾と地面の当たり判定
			//-------------------------
			if (pObj->GetType() == CObject::OBJTYPE_GROUND && m_type == BULLET_ENEMY)
			{//タイプが地面かつ敵の弾だったら
				//地面の位置取得
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//地面のサイズ取得
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				//地面のライフ取得
				int ObjectLife = pObj->GetLife();

				//地面と弾の当たり判定
				if (ObjectPos.y - ObjectSize.y / 2 <= BulletPos.y + BulletSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= BulletPos.y - BulletSize.y / 2
					&& ObjectPos.x + ObjectSize.x / 2 >= BulletPos.x - BulletSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= BulletPos.x + BulletSize.x / 2)
				{
					//弾のライフを0にする
					m_nLife = 0;

					//地面のライフを1減らす
					ObjectLife--;

					//地面のライフを更新設定する
					pObj->SetLife(ObjectLife);

					//地面の体力7でテクスチャ画像変更
					if (ObjectLife == 7)
					{
						pObj->UpdateTex();
					}
					//地面の体力3でテクスチャ画像変更
					if (ObjectLife == 3)
					{
						pObj->UpdateTex();
					}

					//地面の体力ポリゴンを減らす
					SubLife();

					if (ObjectLife <= 0)
					{//地面のライフが0以下になったら
					 //地面の終了処理
						pObj->Uninit();
						CResult::SetState(CResult::STATE_GAMEOVER);
						CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);
					}
				}
			}
		}
	}

	if (m_nLife <= 0)
	{//弾のライフが0以下になったら
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_EXP);

		//爆発生成
   		CExplosion::Create(D3DXVECTOR3(BulletPos.x, BulletPos.y, 0),D3DXVECTOR3(50.0f,50.0f,0.0f));

		//終了処理
		Uninit();
	}
	else
	{	
		if (BulletPos.y <= 0)
		{//弾の位置が画面外になったら
			//終了処理
			Uninit();
		}
		else if (BulletPos.x <= 0 || BulletPos.x >= CRenderer::SCREEN_WIDTH)
		{//弾の位置が画面外になったら
			//終了処理
 			Uninit();
		}
	}
}

//弾の生成
CBullet *CBullet::Create(const D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,BULLETTYPE type)
{
	CBullet *pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		pBullet->Init();
		pBullet->SetPos(pos);
		pBullet->SetType(OBJTYPE_BULLET);
		pBullet->SetBulletType(type);
		pBullet->SetSize(D3DXVECTOR3(10.0f,10.0f,0.0f));
		pBullet->SetMove(move);
		pBullet->SetColer(col);
	}
	else
	{
		assert(false);
	}

	return pBullet;
}

//タイプの取得
CBullet::BULLETTYPE CBullet::GetType()
{
	return m_type;
}

//タイプの設定
void CBullet::SetBulletType(BULLETTYPE type)
{
	m_type = type;
}

//弾の種類
int CBullet::GetBulletType()
{
	return m_type;
}

//地面の体力を減らす
void CBullet::SubLife()
{
	//ライフのライフ取得
	int ObjectLife = CPolygon::GetLife();

	//ライフのライフを1減らす
	ObjectLife--;

	//ライフが0以下になったら
	if (ObjectLife <= 0)
	{
		//ライフの画像変更
		m_pPolygon->UpdateLife(m_Polygon);
		m_Polygon++;
	}
}

//プレイヤーの体力を減らす
void CBullet::SubPlayerLife()
{
	//ライフのライフ取得
	int ObjectLife = CPlayerLifePolygon::GetPlayerLife();

	//ライフのライフを1減らす
	ObjectLife--;

	//ライフが0以下になったら
	if (ObjectLife <= 0)
	{
		//ライフの画像変更
		m_pPlayerLifePolygon->UpdateLife(m_PlayerLifePolygon);
		m_PlayerLifePolygon++;
	}
}

void CBullet::SetPolygon(int m_polygon)
{
	m_Polygon = m_polygon;
}

void CBullet::SetLifePolygon(int m_PlayerLife)
{
	m_PlayerLifePolygon = m_PlayerLife;
}

//テクスチャ読み込み
HRESULT CBullet::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&m_pTexture);

	return S_OK;
}

//テクスチャの破棄
void CBullet::Unload()
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}