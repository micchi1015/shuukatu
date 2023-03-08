//-----------------------------
//
// [enemy.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_TEXTURE	(4)			//画像数

//---------------------------
//前方宣言
//---------------------------
class CPolygon;
class CFade;

//---------------------------
//敵クラス
//---------------------------
class CEnemy : public CObject2D
{
public:
	enum ENEMYTYPE				//敵のタイプ
	{
		ENEMY_SKYSPACEMAN,
		ENEMY_SKY,
		ENEMY_GROUNDSPACEMANR,
		ENEMY_GROUNDSPACEMANL,
		ENEMY_MAX,
		ENEMY_NONE
	};

	enum ENEMYSTATE			//敵の状態
	{
		STATE_NORMAL,
		STATE_ATTACK,
		STATE_MAX,
		STATE_NONE
	};

	CEnemy();				//コンストラクタ
	~CEnemy() override;		//デストラクタ

	HRESULT Init() override;	//初期化処理
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	static CEnemy *Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,ENEMYTYPE type, int life);	//敵の生成

	static void SetSkyEnemy(int nSkyEnemy);
	static void SetSky(int nSky);
	static void SetGroundEnemy(int nGroundEnemy);
	static void SetGroundEnemyL(int nGroundEnemyL);

	void EnemyAction();					//攻撃処理関数
	void SetAttackCount(int nAttack);	//攻撃タイミングを設定
	void SetEnemyType(ENEMYTYPE type);	//タイプの設定
	void SetLife(int nLife) override;	//敵の体力設定
	void DamageCout();

	static int GetCount();
	int GetSkyEnemyCnt();				//空中敵の総数を返す
	int GetSky();
	int GetGroundEnemyCnt();			//地面敵の総数を返す
	int GetGroundEnemyLCnt();
	int GetLife() override;				//敵の体力情報取得
	int GetEnemyType() override;		//タイプの情報取得
	ENEMYTYPE GetEnemy();				//タイプの情報取得

	static HRESULT Load();				//テクスチャの読み込み
	static void Unload();				//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[ENEMY_MAX];	//テクスチャへのポインタ								

	ENEMYTYPE					m_type;					//タイプ
	ENEMYSTATE					m_state;				//状態
	CFade *m_pFade;
	static int					m_SkyEnemy;				//空中敵
	static int					m_Sky;
	static int					m_GroundEnemy;			//地面敵
	static int					m_GroundEnemyL;
	static int					m_DamageCount;			//ダメージ時間
	static int					m_SoundCount;			//サウンド時間
	static int					m_SoundCount2;			//サウンド時間2
	static int					m_SoundCount3;			//サウンド時間3

	int							m_Life;					//体力
	int							m_AttackTime;			//攻撃タイミング
	int							m_nAttackCounter;		//攻撃時のテクスチャ変更用変数
	int							m_nAttackPattern;		//攻撃時のテクスチャ変更用変数
	int							m_nNormalPattern;		//通常時のテクスチャ変更用変数
	int							m_nNormalCounter;		//通常時のテクスチャ変更用変数
	int							m_nCounterAnim;			//通常時のテクスチャ変更用変数
	int							m_nPatternAnim;			//通常時のテクスチャ変更用変数
	int							m_nCntAnim;				//通常時のテクスチャ変更用変数
	int							m_nPtnAnim;				//通常時のテクスチャ変更用変数
};
#endif
