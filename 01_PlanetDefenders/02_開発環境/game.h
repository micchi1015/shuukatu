//-----------------------------
//
// [game.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _GAME_H_
#define _GAME_H_
//---------------------------
//インクルード
//---------------------------
#include "mode.h"
#include "polygon.h"
#include "playerlifepolygon.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_SKYENEMY	(2)			//wave1時の敵の数
#define MAX_GROUNDENEMY	(1)			//wave1時の敵の数

#define MAX_SKYENEMY2		(2)		//wave2時の敵の数
#define MAX_GROUNDENEMY2	(1)		//wave2時の敵の数
#define MAX_SKY2			(1)

#define MAX_SKYENEMY3		(3)
#define MAX_GROUNDENEMY3	(1)
#define MAX_GROUNDENEMYL3	(1)
#define MAX_SKY3			(2)

#define MAX_WAVECOUNT		(6)			//タイトルで使うポリゴン数
//---------------------------
//前方宣言
//---------------------------
class CScore;
class CEnemy;
class CPolygon;
class CPlayerLifePolygon;
class CWaveCount;

//---------------------------
//ゲームクラス
//---------------------------
class CGame : public CMode
{
public:
	enum GAMESTATE		//ゲームの状態
	{
		STATE_INIT,
		STATE_WAVEINIT,
		STATE_EXE,
		STATE_UNINIT,
		STATE_MAX
	};

	enum WAVE			//ウェーブ
	{
		WAVE_NONE = 0,
		WAVE_1,
		WAVE_2,
		WAVE_3,
		WAVE_MAX
	};

	CGame();	//コンストラクタ
	~CGame();	//デストラクタ

	HRESULT Init();		//初期化処理
	void Uninit();		//終了処理
	void Update();		//更新処理
	void Draw();		//描画処理

	void WaveInit();	//Waveの初期化処理
	void WaveExe();		//Wave実行中の処理

	static CGame *Create();										//ポリゴンの生成
	static CScore *GetScore();									//スコアの取得
	static CPolygon *GetPolygon(int nCnt);						//地面の体力ポリゴンを返す
	static CPlayerLifePolygon *GetPlayerLifePolygon(int nCnt);	//プレイヤーの体力ポリゴンを返す

	void NextWave();
	void InitTexture();

	static GAMESTATE GetState();
	static WAVE GetWave();
private:
	static CScore *m_pScore;											//スコアのポインタ変数
	static CPolygon *m_pPolygon[MAX_LIFE];								//地面の体力ポリゴンポインタ配列
	static CPlayerLifePolygon *m_pLifePolygon[MAX_PLAYERLIFEPOLYGON];	//プレイヤーの体力ポリゴンポインタ配列
	static CWaveCount *m_WaveCount;

	static CEnemy *m_pSkyEnemy[MAX_SKYENEMY];			//空中敵ポインタ配列
	static CEnemy *m_pSky[MAX_SKY2];					//空中敵ポインタ配列
	static CEnemy *m_pGroundEnemy[MAX_GROUNDENEMY];		//地面敵ポインタ配列

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_WAVECOUNT];	//テクスチャへのポインタ
	static CObject2D *m_pObject2D[MAX_WAVECOUNT];			//Object2Dのポインタ変数

	static GAMESTATE m_State;	//状態変数
	static WAVE m_Wave;			//ウェーブ変数

	int m_MaxSkyEnemy;		//空中敵総数
	int m_MaxSky;
	int m_MaxGroundEnemy;	//地面敵総数

	static int m_nTime;
};
#endif