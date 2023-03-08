//-------------------------
//
//ゲームの処理[game.cpp]
//Author:梶田大夢
//
//-------------------------
//---------------------------
//インクルード
//---------------------------
#include "application.h"
#include "background.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "fade.h"
#include "game.h"
#include "gravity.h"
#include "ground.h"
#include "input.h"
#include "life.h"
#include "main.h"
#include "number.h"
#include "player.h"
#include "playerlife.h"
#include "playerlifepolygon.h"
#include "polygon.h"
#include "renderer.h"
#include "result.h"
#include "score.h"
#include "sound.h"
#include "umbrella.h"

CScore *CGame::m_pScore = nullptr;
CPolygon *CGame::m_pPolygon[MAX_LIFE] = {};
CPlayerLifePolygon *CGame::m_pLifePolygon[MAX_PLAYERLIFEPOLYGON] = {};
CWaveCount *CGame::m_WaveCount = nullptr;

CEnemy *CGame::m_pSkyEnemy[MAX_SKYENEMY] = {};
CEnemy *CGame::m_pSky[MAX_SKY2] = {};
CEnemy *CGame::m_pGroundEnemy[MAX_GROUNDENEMY] = {};

CGame::WAVE CGame::m_Wave = CGame::WAVE_1;		//ウェーブ変数
CGame::GAMESTATE CGame::m_State = STATE_INIT;

LPDIRECT3DTEXTURE9 CGame::m_pTexture[MAX_WAVECOUNT] = {};	//テクスチャへのポインタ
CObject2D *CGame::m_pObject2D[MAX_WAVECOUNT] = {};			//Object2Dのポインタ変数

int CGame::m_nTime = 0;

//コンストラクタ
CGame::CGame()
{
	m_Wave = WAVE_1;
}

//デストラクタ
CGame::~CGame()
{
}

//初期化処理
HRESULT CGame::Init()
{
	//テクスチャ読み込み
	CGravity::Load();
	CExplosion::Load();
	CBullet::Load();
	CUmbrella::Load();
	CPlayer::Load();
	CPlayerLife::Load();
	CEnemy::Load();
	CGround::Load();
	CLife::Load();
	CNumber::Load();
	CBg::Load();

	InitTexture();

	//生成
	CBg::Create();

	CGravity::Create(D3DXVECTOR3(120.0f, 440.0f, 0.0f), D3DXVECTOR3(330.0f, 330.0f, 0.0f), CGravity::GRAVITY_RIGHT, 0.3f);
	CGravity::Create(D3DXVECTOR3(380.0f, 440.0f, 0.0f), D3DXVECTOR3(330.0f, 330.0f, 0.0f), CGravity::GRAVITY_LEFT, 0.3f);
	CGravity::Create(D3DXVECTOR3(635.0f, 440.0f, 0.0f), D3DXVECTOR3(330.0f, 330.0f, 0.0f), CGravity::GRAVITY_MID, 0.3f);
	CGravity::Create(D3DXVECTOR3(890.0f, 440.0f, 0.0f), D3DXVECTOR3(330.0f, 330.0f, 0.0f), CGravity::GRAVITY_RIGHT, 0.3f);
	CGravity::Create(D3DXVECTOR3(1145.0f, 440.0f, 0.0f), D3DXVECTOR3(330.0f, 330.0f, 0.0f), CGravity::GRAVITY_LEFT, 0.3f);

	CGround::Create();

	m_State = STATE_INIT;
	m_nTime = 0;

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

//終了処理
void CGame::Uninit()
{
	//テクスチャの破棄
	CGravity::Unload();
	CExplosion::Unload();
	CBullet::Unload();
	CUmbrella::Unload();
	CPlayerLife::Unload();
	CPlayer::Unload();
	CEnemy::Unload();
	CGround::Unload();
	CLife::Unload();
	CNumber::Unload();
	CBg::Unload();

	CObject::Release();

	//サウンドの停止
	StopSound();
}

//更新処理
void CGame::Update()
{
	switch (m_State)
	{
	case STATE_INIT:
		NextWave();
		break;

	case STATE_WAVEINIT:
		WaveInit();
		m_State = STATE_EXE;
		break;

	case STATE_EXE:
		WaveExe();
		break;

	default:
		break;
	}
}

//描画処理
void CGame::Draw()
{
}

void CGame::WaveInit()
{
	if (m_Wave == WAVE_1)
	{
		for (int nCnt = 0; nCnt < MAX_SKYENEMY; nCnt++)
		{
			m_pSkyEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(600.0f + (nCnt * 100), 140.0f + (nCnt * 50), 0.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f), CEnemy::ENEMY_SKYSPACEMAN, 5);
		}

		for (int nCnt = 0; nCnt < MAX_GROUNDENEMY; nCnt++)
		{
			m_pGroundEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(1300.0f, 590.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemy::ENEMY_GROUNDSPACEMANR, 5);
		}
	}
	else if (m_Wave == WAVE_2)
	{
		for (int nCnt = 0; nCnt < MAX_SKYENEMY2; nCnt++)
		{
			m_pSkyEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(600.0f + (nCnt * 100), 140.0f + (nCnt * 50), 0.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f), CEnemy::ENEMY_SKYSPACEMAN, 5);
		}

		for (int nCnt = 0; nCnt < MAX_SKY2; nCnt++)
		{
			m_pSkyEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(300.0f, 250.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), CEnemy::ENEMY_SKY, 5);
		}

		for (int nCnt = 0; nCnt < MAX_GROUNDENEMY2; nCnt++)
		{
			m_pGroundEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(1300.0f, 610.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemy::ENEMY_GROUNDSPACEMANR, 5);
		}
	}
	else if (m_Wave == WAVE_3)
	{
		for (int nCnt = 0; nCnt < MAX_SKYENEMY3; nCnt++)
		{
			m_pSkyEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(600.0f + (nCnt * 100), 140.0f + (nCnt * 50), 0.0f), D3DXVECTOR3(80.0f, 80.0f, 0.0f), CEnemy::ENEMY_SKYSPACEMAN, 5);
		}

		for (int nCnt = 0; nCnt < MAX_SKY3; nCnt++)
		{
			m_pSkyEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(300.0f + (nCnt * 600), 200.0f - (nCnt * 50), 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), CEnemy::ENEMY_SKY, 5);
		}

		for (int nCnt = 0; nCnt < MAX_GROUNDENEMY3; nCnt++)
		{
			m_pGroundEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(1300.0f, 610.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemy::ENEMY_GROUNDSPACEMANR, 5);
		}

		for (int nCnt = 0; nCnt < MAX_GROUNDENEMYL3; nCnt++)
		{
			m_pGroundEnemy[nCnt] = CEnemy::Create(D3DXVECTOR3(0.0f, 610.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CEnemy::ENEMY_GROUNDSPACEMANL, 5);
		}
	}
}

void CGame::WaveExe()
{
	if (m_Wave == WAVE_1)
	{
		for (int nCnt = 0; nCnt < MAX_SKYENEMY; nCnt++)
		{
			m_MaxSkyEnemy = m_pSkyEnemy[nCnt]->GetSkyEnemyCnt();
		}

		for (int nCnt = 0; nCnt < MAX_GROUNDENEMY; nCnt++)
		{
			m_MaxGroundEnemy = m_pGroundEnemy[nCnt]->GetGroundEnemyCnt();
		}

		if (m_MaxSkyEnemy == 5 && m_MaxGroundEnemy == 2)
		{
			if (m_Wave == WAVE_1)
			{
				if (CApplication::GetMode() == CApplication::MODE_GAME)
				{
					m_Wave = WAVE_2;
					InitTexture();
					m_State = STATE_INIT;
				}
			}
		}
	}
	else if (m_Wave == WAVE_2)
	{
		for (int nCnt = 0; nCnt < MAX_SKYENEMY2; nCnt++)
		{
			m_MaxSkyEnemy = m_pSkyEnemy[nCnt]->GetSkyEnemyCnt();
		}

		for (int nCnt = 0; nCnt < MAX_GROUNDENEMY2; nCnt++)
		{
			m_MaxGroundEnemy = m_pGroundEnemy[nCnt]->GetGroundEnemyCnt();
		}

		for (int nCnt = 0; nCnt < MAX_SKY2; nCnt++)
		{
			m_MaxSky = m_pSky[nCnt]->GetSky();
		}

		if (m_MaxSkyEnemy == 3 && m_MaxGroundEnemy == 1 && m_MaxSky == 2)
		{
			if (m_Wave == WAVE_2)
			{
				if (CApplication::GetMode() == CApplication::MODE_GAME)
				{
					m_Wave = WAVE_3;
					InitTexture();
					m_State = STATE_INIT;
				}
			}
		}
	}
	else if (m_Wave == WAVE_3)
	{
		for (int nCnt = 0; nCnt < MAX_SKYENEMY2; nCnt++)
		{
			m_MaxSkyEnemy = m_pSkyEnemy[nCnt]->GetSkyEnemyCnt();
		}

		for (int nCnt = 0; nCnt < MAX_GROUNDENEMY2; nCnt++)
		{
			m_MaxGroundEnemy = m_pGroundEnemy[nCnt]->GetGroundEnemyCnt();
		}

		for (int nCnt = 0; nCnt < MAX_SKY3; nCnt++)
		{
			m_MaxSky = m_pSky[nCnt]->GetSky();
		}
	}
}

CGame * CGame::Create()
{
	CGame *pGame = new CGame;

	if (pGame != nullptr)
	{
		pGame->Init();
	}

	return pGame;
}

//Scoreの情報取得
CScore *CGame::GetScore()
{
	return m_pScore;
}

//地面の体力ポリゴンを返す
CPolygon * CGame::GetPolygon(int nCnt)
{
	return m_pPolygon[nCnt];
}

//プレイヤーの体力ポリゴンを返す
CPlayerLifePolygon * CGame::GetPlayerLifePolygon(int nCnt)
{
	return m_pLifePolygon[nCnt];
}

void CGame::NextWave()
{
	m_nTime++;

	if (m_Wave == WAVE_1)
	{
		if (m_nTime == 1)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
			m_pObject2D[1]->SetLifeTexPos(3.0f, 0.0f, 1.0f, 0.0f);
		}
		else if (m_nTime == 60)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
			m_pObject2D[1]->SetLifeTexPos(3.0f, 1.0f, 1.0f, 0.0f);
		}
		else if (m_nTime == 120)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
			m_pObject2D[1]->SetLifeTexPos(3.0f, 2.0f, 1.0f, 0.0f);
		}
		else if (m_nTime == 180)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_START);

			CLife::Create(D3DXVECTOR3(150.0f, 30.0f, 0.0f));
			CPlayerLife::Create(D3DXVECTOR3(190.0f, 75.0f, 0.0f));

			m_pScore = CScore::Create();

			for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
			{
				m_pPolygon[nCnt] = CPolygon::Create(D3DXVECTOR3(260.0f - (nCnt * 20.0f), 30.0f, 0.0f));
			}

			for (int nCnt = 0; nCnt < MAX_PLAYERLIFEPOLYGON; nCnt++)
			{
				m_pLifePolygon[nCnt] = CPlayerLifePolygon::Create(D3DXVECTOR3(264.0f - (nCnt * 20.0f), 75.0f, 0.0f));
			}

			CPlayer::Create();

			m_pObject2D[0]->Uninit();
			m_pObject2D[1]->Uninit();

			m_State = STATE_WAVEINIT;
			m_nTime = 0;
		}
	}
	else if (m_Wave == WAVE_2)
	{
		if (m_nTime == 1)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
			m_pObject2D[3]->SetLifeTexPos(3.0f, 0.0f, 1.0f, 0.0f);
		}
		else if (m_nTime == 60)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
			m_pObject2D[3]->SetLifeTexPos(3.0f, 1.0f, 1.0f, 0.0f);
		}
		else if (m_nTime == 120)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
			m_pObject2D[3]->SetLifeTexPos(3.0f, 2.0f, 1.0f, 0.0f);
		}
		else if (m_nTime == 180)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_START);

			m_pObject2D[2]->Uninit();
			m_pObject2D[3]->Uninit();

			m_State = STATE_WAVEINIT;
			m_nTime = 0;
		}
	}
	else if (m_Wave == WAVE_3)
	{
		if (m_nTime == 1)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
			m_pObject2D[5]->SetLifeTexPos(3.0f, 0.0f, 1.0f, 0.0f);
		}
		else if (m_nTime == 60)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
			m_pObject2D[5]->SetLifeTexPos(3.0f, 1.0f, 1.0f, 0.0f);
		}
		else if (m_nTime == 120)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
			m_pObject2D[5]->SetLifeTexPos(3.0f, 2.0f, 1.0f, 0.0f);
		}
		else if (m_nTime == 180)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_START);

			m_pObject2D[4]->Uninit();
			m_pObject2D[5]->Uninit();

			m_State = STATE_WAVEINIT;
			m_nTime = 0;
		}
	}
}

void CGame::InitTexture()
{
	if (m_Wave == WAVE_1)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\Xo39OrW0hNbmgNR1663583523_1663583530.png",
			&m_pTexture[0]);

		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\mwSRo5BWg2gsZeN1663583615_1663583617.png",
			&m_pTexture[1]);

		m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 200, 0.0f), PRIORITY_3);
		m_pObject2D[0]->SetSize(D3DXVECTOR3(800.0f, 400.0f, 0.0f));
		m_pObject2D[0]->BindTexture(m_pTexture[0]);

		m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 500, 0.0f), PRIORITY_3);
		m_pObject2D[1]->SetSize(D3DXVECTOR3(500.0f, 350.0f, 0.0f));
		m_pObject2D[1]->BindTexture(m_pTexture[1]);
		m_pObject2D[1]->SetLifeTexPos(3.0f, 0.0f, 1.0f, 0.0f);
	}
	else if (m_Wave == WAVE_2)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\mkCgPYgtXSz1D6X1663583723_1663583729.png",
			&m_pTexture[2]);

		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\mwSRo5BWg2gsZeN1663583615_1663583617.png",
			&m_pTexture[3]);

		m_pObject2D[2] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 200, 0.0f), PRIORITY_3);
		m_pObject2D[2]->SetSize(D3DXVECTOR3(800.0f, 400.0f, 0.0f));
		m_pObject2D[2]->BindTexture(m_pTexture[2]);

		m_pObject2D[3] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 500, 0.0f), PRIORITY_3);
		m_pObject2D[3]->SetSize(D3DXVECTOR3(500.0f, 350.0f, 0.0f));
		m_pObject2D[3]->BindTexture(m_pTexture[3]);
		m_pObject2D[3]->SetLifeTexPos(3.0f, 0.0f, 1.0f, 0.0f);
	}
	else if (m_Wave == WAVE_3)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gkwSCQOT0FhV2Yr1663668114_1663668119.png",
			&m_pTexture[4]);

		//テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\mwSRo5BWg2gsZeN1663583615_1663583617.png",
			&m_pTexture[5]);

		m_pObject2D[4] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 200, 0.0f), PRIORITY_3);
		m_pObject2D[4]->SetSize(D3DXVECTOR3(800.0f, 400.0f, 0.0f));
		m_pObject2D[4]->BindTexture(m_pTexture[4]);

		m_pObject2D[5] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 500, 0.0f), PRIORITY_3);
		m_pObject2D[5]->SetSize(D3DXVECTOR3(500.0f, 350.0f, 0.0f));
		m_pObject2D[5]->BindTexture(m_pTexture[5]);
		m_pObject2D[5]->SetLifeTexPos(3.0f, 0.0f, 1.0f, 0.0f);
	}
}

CGame::GAMESTATE CGame::GetState()
{
	return m_State;
}

CGame::WAVE CGame::GetWave()
{
	return m_Wave;
}
