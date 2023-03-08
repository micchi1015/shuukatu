//--------------------------------
//
//ランキングヘッダー[ranking.h]
//Author:梶田大夢
//
//--------------------------------
#ifndef _RANKING_H_						//このマクロ定義がされてなかったら
#define _RANKING_H_						//二重インクルード防止のマクロ定義

//---------------------------
//インクルード
//---------------------------
#include "mode.h"

//---------------------------
//前方宣言
//---------------------------
class CObject2D;
class CFade;
class CNumber;

//---------------------------
//マクロ定義
//---------------------------
#define MAX_RANKING		(8)		//ランキングの桁数
#define MAX_RANKINGRANK	(5)		//ランキングの順位分
#define MAX_TEXTURE		(3)		//テクスチャの数

//---------------------------
//ランキングクラス
//---------------------------
class CRanking : public CMode	
{
public:
	CRanking();		//コンストラクタ
	~CRanking();	//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理
	void Load(void);	//ファイル読み込み処理
	void Save(void);	//ファイル書き出し処理
	static void SetRankingScore();			//スコアの設定処理
	static void GetRanking(int Ranking);	//ランキング情報の取得

	static CRanking *Create();	//ランキングの生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE] = {};			//テクスチャへのポインタ
	CObject2D *m_pObject2D[3];									//Object2Dのポインタ配列
	CFade *m_pFade;												//フェードのポインタ変数

	static CNumber *m_apNumber[MAX_RANKINGRANK][MAX_RANKING];	//Number型の配列
	static int m_nRanking;
	static int aData[MAX_RANKINGRANK];
};
#endif