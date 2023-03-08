//------------------------------
//
//スコア処理[score.cpp]
//Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include "application.h"
#include "number.h"
#include "ranking.h"
#include "renderer.h"
#include "score.h"

//コンストラクタ
CScore::CScore(int nPriority) : CObject(nPriority)
{
	m_nScore = 0;
}

//デストラクタ
CScore::~CScore()
{
}
//スコアの初期化処理 
HRESULT CScore::Init()
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(60.0f *nCnt + 800.0f, 70.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f));
	}

	m_nScore = 0;

	return S_OK;
}

void CScore::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{ 
			m_apNumber[nCnt]->Uninit();
		}
	}

	CObject::Release();
}
	
//スコアの更新処理
void CScore::Update()
{
}

//スコアの描画処理
void CScore::Draw()
{
}

CScore *CScore::Create()
{
	CScore *pScore = new CScore;

	if (pScore != nullptr)
	{
		pScore->Init();
	}
	
	return pScore;
}

//スコアの設定処理
void CScore::SetScore(int nScore)
{
	int aPosTexU[8];	//各桁の数字を格納

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	m_nScore = nScore;

	aPosTexU[0] = m_nScore % 100000000 / 10000000;
	aPosTexU[1] = m_nScore % 10000000 / 1000000;
	aPosTexU[2] = m_nScore % 1000000 / 100000;
	aPosTexU[3] = m_nScore % 100000 / 10000;
	aPosTexU[4] = m_nScore % 10000 / 1000;
	aPosTexU[5] = m_nScore % 1000 / 100;
	aPosTexU[6] = m_nScore % 100 / 10;
	aPosTexU[7] = m_nScore % 10 / 1;

	//テクスチャ座標の設定
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore]->SetTexPos(10.0f, (float)aPosTexU[nCntScore]);
	}

	CRanking::GetRanking(m_nScore);
}

//スコアの加算処理
void CScore::AddScore(int nValue)
{
	SetScore(m_nScore + nValue);
}

//スコアの情報の取得
int CScore::GetScore(void)
{
	return m_nScore;
}