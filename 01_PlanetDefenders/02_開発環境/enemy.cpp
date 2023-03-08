//------------------------------
//
// 敵の処理[enemy.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include <assert.h>
#include <time.h>

#include "application.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "game.h"
#include "ground.h"
#include "input.h"
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "player.h"
#include"renderer.h"
#include "result.h"
#include "score.h"
#include "sound.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
LPDIRECT3DTEXTURE9	CEnemy::m_pTexture[MAX_TEXTURE] = {};		//テクスチャへのポインタ
int					CEnemy::m_SkyEnemy = 7;
int					CEnemy::m_Sky = 3;
int					CEnemy::m_GroundEnemy = 3;
int					CEnemy::m_GroundEnemyL = 1;
int					CEnemy::m_DamageCount = 0;
int					CEnemy::m_SoundCount = 0;
int					CEnemy::m_SoundCount2 = 0;
int					CEnemy::m_SoundCount3 = 0;

//コンストラクタ
CEnemy::CEnemy()
{
	
}

//デストラクタ
CEnemy::~CEnemy()
{
}

//初期化処理
HRESULT CEnemy::Init()
{
	CObject2D::Init();

	srand((unsigned int)time(NULL));

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//敵のテクスチャ分別
	switch (m_type)
	{
	case ENEMY_SKYSPACEMAN:
		BindTexture(m_pTexture[0]);
		SetLifeTexPos(7.0, 0.0f, 4.0f, 0.0f);
		break;

	case ENEMY_SKY:
		BindTexture(m_pTexture[3]);
		SetLifeTexPos(1.0, 0.0f, 1.0f, 0.0f);
		break;

	case ENEMY_GROUNDSPACEMANR:
		BindTexture(m_pTexture[1]);
		SetLifeTexPos(4.0f, 0.0f, 2.0f, 0.0f);
		break;

	case ENEMY_GROUNDSPACEMANL:
		BindTexture(m_pTexture[2]);
		SetLifeTexPos(4.0f, 0.0f, 2.0f, 0.0f);
		break;

	default:
		break;
	}

	switch (m_state)
	{
	case CEnemy::STATE_NORMAL:	
		break;
	case CEnemy::STATE_ATTACK:
		break;
	case CEnemy::STATE_MAX:
		break;
	case CEnemy::STATE_NONE:
		break;
	default:
		break;
	}

	if (CGame::GetWave() == CGame::WAVE_1)
	{
		m_SkyEnemy = 7;
		m_GroundEnemy = 3;
	}
	else if (CGame::GetWave() == CGame::WAVE_2)
	{
		m_SkyEnemy = 5;
		m_GroundEnemy = 2;
		m_Sky = 3;
	}
	else if (CGame::GetWave() == CGame::WAVE_3)
	{
		m_SkyEnemy = 3;
		m_GroundEnemy = 1;
		m_Sky = 2;
		m_GroundEnemyL = 1;
	}

	return S_OK;
}

void CEnemy::Uninit()
{
	if (m_type == ENEMY_SKYSPACEMAN)
	{
		m_SkyEnemy--;
	}

	if (m_type == ENEMY_GROUNDSPACEMANR)
	{
		m_GroundEnemy--;
	}

	if (m_type == ENEMY_SKY)
	{
		m_Sky--;
	}

	if (m_type == ENEMY_GROUNDSPACEMANL)
	{
		m_GroundEnemyL--;
	}

	if (m_SkyEnemy == 0 && m_GroundEnemy == 0 && m_GroundEnemyL == 0 && m_Sky == 0)
	{
		int GroundLife = CGround::GetGroundLife();
		int PlayerLife = CPlayer::GetPlayerLife();

		//scoreを10 * Life分追加
		CGame::GetScore()->AddScore(10000 * (GroundLife * 2));
		CGame::GetScore()->AddScore(10000 * (PlayerLife * 2));

		CResult::SetState(CResult::STATE_GAMECLEAR);
		 
		if (m_pFade->GetFade() == CFade::FADE_NONE)
		{
			CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);
		}	
	}

	CObject2D::Uninit();
}

//更新処理
void CEnemy::Update()
{
	D3DXVECTOR3 EnemyPos = GetPos();
	ENEMYTYPE EnemyType = GetEnemy();
	D3DXVECTOR3 EnemySize = CObject2D::GetSize();
	D3DXVECTOR3 EnemyMove = GetMove();

	//-------------------------
	//空中敵(1)
	//-------------------------
	if (EnemyType == ENEMY_SKYSPACEMAN)
	{
		m_SoundCount++;

		m_nCounterAnim++;	//カウンターを加算

		if ((m_nCounterAnim % 5) == 0)
		{//一定時間経過
		 //テクスチャの座標変更
			SetLifeTexPos(7.0f, (float)m_nPatternAnim, 4.0f, 0.0f);

			//パターンNo.を更新する
			m_nPatternAnim++;
		}

		if (m_nPatternAnim >= 7)
		{
			m_nCntAnim++;	//カウンターを加算
			m_nCounterAnim = 0;

			if ((m_nCntAnim % 8) == 0)
			{//一定時間経過
				//移動量の最大値
				if (EnemyMove.x <= -3.0f)
				{
					EnemyMove.x = -3.0f;
				}
				else if (EnemyMove.x >= 3.0f)
				{
					EnemyMove.x = 3.0f;
				}

				int nTime = (rand() % 6000) + 1;

				if (nTime <= 6000 && nTime > 2000)
				{
					EnemyMove.x += (D3DX_PI * 0.5f) * 0.1f;
					nTime = 0;
				}
				else if (nTime < 2000 && nTime >= 0)
				{
					EnemyMove.x -= (D3DX_PI * 0.5f) * 0.1f;

					nTime = 0;
				}

				if (EnemyMove.x >= 0.03f)
				{
					SetLifeTexPos(8.0f, (float)m_nPtnAnim, 4.0f, 1.0f);
				}
				else
				{
					SetLifeTexPos(8.0f, (float)m_nPtnAnim, 4.0f, 3.0f);
				}

				//移動制限
				if (EnemyPos.x + (EnemySize.x / 2) >= CRenderer::SCREEN_WIDTH)
				{
					EnemyPos.x = CRenderer::SCREEN_WIDTH - (EnemySize.x / 2);
					EnemyMove.x *= -1;
				}
				else if (EnemyPos.x - (EnemySize.x / 2) <= 0)
				{
					EnemyPos.x = 0 + (EnemySize.x / 2);
					EnemyMove.x *= -1;
				}

				//パターンNo.を更新する
				m_nPtnAnim++;

				if (m_SoundCount >= 50)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_WING);

					m_SoundCount = 0;
				}
			}

			m_AttackTime = (rand() % 1000) + 1;
			SetAttackCount(m_AttackTime);

			m_AttackTime++;

			if (m_AttackTime >= 1000)
			{
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_ENEMYSHOOT);
				
				CBullet::Create(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + GetSize().y / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CBullet::BULLET_ENEMY);
				m_AttackTime = 0;
			}
		}
	}

	//-------------------------
	//空中敵(2)
	//-------------------------
	if (EnemyType == ENEMY_SKY)
	{
		m_AttackTime = (rand() % 1000) + 1;
		SetAttackCount(m_AttackTime);

		m_AttackTime++;

		if (m_AttackTime >= 1000)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_ENEMYSHOOT);

			CBullet::Create(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + GetSize().y / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CBullet::BULLET_ENEMY);
			m_AttackTime = 0;
		}
	}

	//-------------------------
	//地面敵(1)
	//-------------------------
	if (EnemyType == ENEMY_GROUNDSPACEMANR)
	{
		m_SoundCount2++;

		//移動量の最大値
		if (EnemyMove.x <= -1.0f)
		{
			EnemyMove.x = -1.0f;
		}
		else if (EnemyMove.x >= 1.0f)
		{
			EnemyMove.x = 1.0f;
		}

		//右から来て、途中で止まる
		if (EnemyPos.x <= (CRenderer::SCREEN_WIDTH + 100.0f) && EnemyPos.x >= CRenderer::SCREEN_WIDTH - 200.0f)
		{
			if (m_SoundCount2 >= 20)
			{
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_MOTION);
				m_SoundCount2 = 0;
			}

			//移動
			EnemyMove.x -= (D3DX_PI * 0.5f) * 0.05f;
		}
		else if (EnemyPos.x >= 1000.0f && EnemyPos.x <= 1001.0f)
		{
			EnemyMove.x = 0.0f;
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

					//地面の色取得
					D3DXCOLOR ObjectColer = pObj->GetCol();

					m_AttackTime = (rand() % 200) + 1;
					SetAttackCount(m_AttackTime);

					m_AttackTime++;

					//敵と地面の当たり判定
					if (ObjectPos.x + ObjectSize.x / 2 >= EnemyPos.x - EnemySize.x / 2
						&& ObjectPos.x - ObjectSize.x / 2 <= EnemyPos.x + EnemySize.x / 2
						&& ObjectPos.y - ObjectSize.y / 2 <= EnemyPos.y + EnemySize.y / 2 - 5.0f
						&& ObjectPos.y + ObjectSize.y / 2 >= EnemyPos.y - EnemySize.y / 2 + 5.0f)
					{
						if (m_AttackTime >= 200 && EnemyMove.x == 0)
						{
							m_state = STATE_ATTACK;
						}
						else
						{
							EnemyMove.y = 0;
						}
					}
					else
					{
						//重力分加算
						EnemyMove.y += MAX_GRAVITY;
					}
				}
			}
		}

		EnemyAction();
	}

	//-------------------------
	//地面敵(2)
	//-------------------------
	if (EnemyType == ENEMY_GROUNDSPACEMANL)
	{
		m_SoundCount3 ++;

		//移動量の最大値
		if (EnemyMove.x <= -1.0f)
		{
			EnemyMove.x = -1.0f;
		}
		else if (EnemyMove.x >= 1.0f)
		{
			EnemyMove.x = 1.0f;
		}

		//左から来て、途中で止まる
		if (EnemyPos.x <= 200.0f && EnemyPos.x >= -100.0f)
		{
			if (m_SoundCount3 >= 20)
			{
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_MOTION);
				m_SoundCount3 = 0;
			}

			//移動
			EnemyMove.x += (D3DX_PI * 0.5f) * 0.05f;
		}
		else if (EnemyPos.x >= 201.0f && EnemyPos.x <= 202.0f)
		{
			EnemyMove.x = 0.0f;
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

					//地面の色取得
					D3DXCOLOR ObjectColer = pObj->GetCol();

					m_AttackTime = (rand() % 200) + 1;
					SetAttackCount(m_AttackTime);

					m_AttackTime++;

					//敵と地面の当たり判定
					if (ObjectPos.x + ObjectSize.x / 2 >= EnemyPos.x - EnemySize.x / 2
						&& ObjectPos.x - ObjectSize.x / 2 <= EnemyPos.x + EnemySize.x / 2
						&& ObjectPos.y - ObjectSize.y / 2 <= EnemyPos.y + EnemySize.y / 2 - 10.0f
						&& ObjectPos.y + ObjectSize.y / 2 >= EnemyPos.y - EnemySize.y / 2 + 10.0f)
					{
						if (m_AttackTime >= 200 && EnemyMove.x == 0)
						{
							m_state = STATE_ATTACK;
						}
						else
						{
							EnemyMove.y = 0;
						}
					}
					else
					{
						//重力分加算
						EnemyMove.y += MAX_GRAVITY;
					}
				}
			}
		}

		EnemyAction();
	}

	//位置を更新
	EnemyPos.x += EnemyMove.x;
	EnemyPos.y += EnemyMove.y;
	EnemyPos.z += EnemyMove.z;

	SetMove(EnemyMove);
	SetPos(EnemyPos);
	CObject2D::Update();
}

//生成
CEnemy * CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,ENEMYTYPE type,int life)
{
		CEnemy *pEnemy = new CEnemy;
		
		if (pEnemy != nullptr)
		{
			pEnemy->SetEnemyType(type);
			pEnemy->Init();
			pEnemy->SetPos(pos);
			pEnemy->SetSize(size);
			pEnemy->SetLife(life);
			pEnemy->SetType(OBJTYPE_ENEMY);
		}
		else
		{
			assert(false);
		}

	return pEnemy;
}

void CEnemy::SetSkyEnemy(int nSkyEnemy)
{
	m_SkyEnemy = nSkyEnemy;
}

void CEnemy::SetSky(int nSky)
{
	m_Sky = nSky;
}

void CEnemy::SetGroundEnemy(int nGroundEnemy)
{
	m_GroundEnemy = nGroundEnemy;
}

void CEnemy::SetGroundEnemyL(int nGroundEnemyL)
{
	m_GroundEnemyL = nGroundEnemyL;
}

//攻撃処理関数
void CEnemy::EnemyAction()
{
	D3DXVECTOR3 EnemyPos = GetPos();
	ENEMYTYPE EnemyType = GetEnemy();
	D3DXVECTOR3 EnemySize = CObject2D::GetSize();
	D3DXVECTOR3 EnemyMove = GetMove();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_3, nCnt);

		if (pObj != nullptr)
		{//タイプがプレイヤーだったら
			if (pObj->GetType() == CObject::OBJTYPE_PLAYER)
			{
				//プレイヤーの位置取得
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//プレイヤーのサイズ取得
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				int nLife = pObj->GetLife();

				//プレイヤーと敵の当たり判定
				if (ObjectPos.x + ObjectSize.x / 2 >= EnemyPos.x - EnemySize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= EnemyPos.x + EnemySize.x / 2
					&& ObjectPos.y - ObjectSize.y / 2 <= EnemyPos.y + EnemySize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= EnemyPos.y - EnemySize.y / 2)
				{
					DamageCout();
				}

				//プレイヤーのライフが0以下になったら
				if (nLife <= 0)
				{
					//プレイヤーの終了処理
					pObj->Uninit();
					CResult::SetState(CResult::STATE_GAMEOVER);
					CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);
				}
			}
		}
	}

	if (m_state == STATE_NORMAL)
	{
		m_nNormalCounter++;	//カウンターを加算

		if ((m_nNormalCounter % 8) == 0)
		{
			SetLifeTexPos(4.0f, (float)m_nNormalPattern, 2.0f, 0.0f);

			//パターンNo.を更新する
			m_nNormalPattern++;
		}

		if (EnemyMove.x == 0)
		{
			SetLifeTexPos(4.0f, 0.0f, 2.0f, 0.0f);
		}
	}

	if (m_state == STATE_ATTACK)
	{
		m_nAttackCounter++;	//カウンターを加算

		if ((m_nAttackCounter % 12) == 0)
		{
			SetLifeTexPos(4.0f, (float)m_nAttackPattern, 2.0f, 1.0f);

			//パターンNo.を更新する
			m_nAttackPattern++;

			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_ATTACK);		
		}

		if (m_nAttackPattern >= 4)
		{
			for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
			{
				CObject *pObj = CObject::GetMyObject(PRIORITY_3,nCnt);

				if (pObj != nullptr)
				{//タイプが地面だったら
					if (pObj->GetType() == CObject::OBJTYPE_GROUND)
					{
						//攻撃処理
						int nLife = pObj->GetLife();
						nLife--;

						pObj->SetLife(nLife);

						if (nLife == 7)
						{
							pObj->UpdateTex();
						}

						if (nLife == 3)
						{
							pObj->UpdateTex();
						}

						if (nLife <= 0)
						{
							pObj->Uninit();
							CResult::SetState(CResult::STATE_GAMEOVER);
							CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);
						}
					}
				}
			}

			CBullet::SubLife();

			m_nAttackPattern = 0;
			m_state = STATE_NORMAL;
		}
	}

	SetMove(EnemyMove);
	SetPos(EnemyPos);
}

//攻撃タイミングを設定
void CEnemy::SetAttackCount(int nAttack)
{
	m_AttackTime = nAttack;
}

//タイプの設定
void CEnemy::SetEnemyType(ENEMYTYPE type)
{
	m_type = type;
}

//敵の体力設定
void CEnemy::SetLife(int nLife)
{
	m_Life = nLife;
}

void CEnemy::DamageCout()
{
	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_3, nCnt);

		if (pObj != nullptr)
		{//タイプがプレイヤーだったら
			if (pObj->GetType() == CObject::OBJTYPE_PLAYER)
			{
				int nLife = pObj->GetLife();

				m_DamageCount++;

				if (m_DamageCount == 1)
				{
					//プレイヤーのライフを1減らす
					nLife--;

					//プレイヤーのライフを更新設定する
					pObj->SetLife(nLife);

					//プレイヤーの体力ポリゴンを減らす
					CBullet::SubPlayerLife();
				}
				else if (m_DamageCount == 120)
				{
					m_DamageCount = 0;
				}
			}
		}
	}
}

int CEnemy::GetCount()
{
	return m_DamageCount;
}

//空中敵の総数を返す
int CEnemy::GetSkyEnemyCnt()
{
	return m_SkyEnemy;
}

int CEnemy::GetSky()
{
	return m_Sky;
}

//地面敵の総数を返す
int CEnemy::GetGroundEnemyCnt()
{
	return m_GroundEnemy;
}

int CEnemy::GetGroundEnemyLCnt()
{
	return m_GroundEnemyL;
}

//敵の体力情報取得
int CEnemy::GetLife()
{
	return m_Life;
}

//タイプの情報取得
int CEnemy::GetEnemyType()
{
	return m_type;
}

//タイプの情報取得
CEnemy::ENEMYTYPE CEnemy::GetEnemy()
{
	return m_type;
}

//テクスチャ読み込み処理
HRESULT CEnemy::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TfTOTBkUoWq2Kha1661127459_1661127461.png",
		&m_pTexture[0]);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rXtd1zTfrhyYYxT1658972170_1658972221.png",
		&m_pTexture[1]);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gVBTlx8SI84VJTW1658972670_1658972767.png",
		&m_pTexture[2]);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Head.png",
		&m_pTexture[3]);

	return S_OK;
}

//テクスチャの破棄
void CEnemy::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}