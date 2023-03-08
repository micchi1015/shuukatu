//-----------------------------------------
//
//ランキング処理[ranking.cpp]
//Author:梶田大夢
//
//-----------------------------------------
#include <stdio.h>
#include "application.h"
#include "fade.h"
#include "input.h"
#include "number.h"
#include "score.h"
#include "sound.h"
#include "ranking.h"
#include "renderer.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
CNumber *CRanking::m_apNumber[MAX_RANKINGRANK][MAX_RANKING] = {};
int CRanking::aData[MAX_RANKINGRANK] = {};
int CRanking::m_nRanking = 0;

//コンストラクタ
CRanking::CRanking()
{
}

//デストラクタ
CRanking::~CRanking()
{
}

//初期化処理
HRESULT CRanking::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\02-1.jpg",
		&m_pTexture[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\vnB0FGfi6u2lpsh1663908208_1663908211.png",
		&m_pTexture[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_pTexture[2]);

	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), PRIORITY_3);
	m_pObject2D[0]->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D[0]->BindTexture(m_pTexture[0]);

	m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), PRIORITY_3);
	m_pObject2D[1]->SetSize(D3DXVECTOR3(1200.0f, 800.0f, 0.0f));
	m_pObject2D[1]->BindTexture(m_pTexture[1]);

	//テクスチャ座標の設定
	for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCnt][nCntRanking] = CNumber::Create(D3DXVECTOR3(50.0f *nCntRanking + 525.0f, 72.5f *nCnt + 230.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
			m_apNumber[nCnt][nCntRanking]->BindTexture(m_pTexture[2]);
		}
	}

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM003);

	//ファイル読み込み処理
	Load();

	return S_OK;
}

//終了処理
void CRanking::Uninit(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャ座標の設定
	for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			if (m_apNumber[nCnt][nCntRanking] != nullptr)
			{
				m_apNumber[nCnt][nCntRanking]->Uninit();
			}
		}
	}

	CObject::Release();
}

//更新処理
void CRanking::Update(void)
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
	{//ENTERキーが押された
		//ファイル書き出し処理
		Save();
		//モード設定
		CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_TITLE);
	}
}

//描画処理
void CRanking::Draw(void)
{
}

//ファイル読み込み処理
void CRanking::Load(void)
{
	//ファイルポインタ宣言
	FILE*pFile;

	//ファイルを開く
	pFile = fopen("data\\save\\ranking.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCntData = 0; nCntData < MAX_RANKINGRANK; nCntData++)
		{
			//ファイルに数値を書き出す
			fscanf(pFile, "%d\n", &aData[nCntData]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}
}

//ファイル書き出し処理
void CRanking::Save(void)
{
	//ファイルポインタ宣言
	FILE*pFile;

	//ファイルを開く
	pFile = fopen("data\\save\\ranking.txt", "w");

	if (pFile != NULL)
	{//ファイルが開けた場合
		for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
		{
			//ファイルに数値を書き出す
			fprintf(pFile, "%d\n", aData[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開かなかった場合
		printf("***ファイルが開けませんでした***");
	}
}

//スコアの設定処理
void CRanking::SetRankingScore()
{
	int aPosTexU[MAX_RANKINGRANK][MAX_RANKING];

	if (m_nRanking > aData[MAX_RANKINGRANK - 1])
	{
		aData[MAX_RANKINGRANK - 1] = m_nRanking;
	}
	
	for (int nCount = 0; nCount < MAX_RANKINGRANK - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < MAX_RANKINGRANK; nCount2++)
		{
			if (aData[nCount] < aData[nCount2])
			{
				int nMin = aData[nCount];
				aData[nCount] = aData[nCount2];
				aData[nCount2] = nMin;
			}
		}
	}

	for (int nCntScore = 0; nCntScore < MAX_RANKINGRANK; nCntScore++)
	{
		aPosTexU[nCntScore][0] = aData[nCntScore] % 100000000 / 1000000;
		aPosTexU[nCntScore][1] = aData[nCntScore] % 10000000 / 1000000;
		aPosTexU[nCntScore][2] = aData[nCntScore] % 1000000 / 100000;
		aPosTexU[nCntScore][3] = aData[nCntScore] % 100000 / 10000;
		aPosTexU[nCntScore][4] = aData[nCntScore] % 10000 / 1000;
		aPosTexU[nCntScore][5] = aData[nCntScore] % 1000 / 100;
		aPosTexU[nCntScore][6] = aData[nCntScore] % 100 / 10;
		aPosTexU[nCntScore][7] = aData[nCntScore] % 10 / 1;
	}

	//テクスチャ座標の設定
	for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
	{
		for (int nCntScore = 0; nCntScore < MAX_RANKING; nCntScore++)
		{
			m_apNumber[nCnt][nCntScore]->SetTexPos(10.0f, (float)aPosTexU[nCnt][nCntScore]);
		}
	}
}

//ランキング情報の取得
void CRanking::GetRanking(int Ranking)
{
	m_nRanking = Ranking;
}

//生成
CRanking * CRanking::Create()
{
	CRanking *pRanking= new CRanking;

	if (pRanking != nullptr)
	{
		pRanking->Init();
	}

	return pRanking;
}
