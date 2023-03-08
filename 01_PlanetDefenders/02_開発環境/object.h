//-----------------------------
//
// [object.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_

//---------------------------
//インクルード
//---------------------------
#include "main.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_DATA	(2048)	//データの最大数
#define MAX_PRI		(6)

//---------------------------
//オブジェクトクラス
//---------------------------
class CObject
{
public:
	enum EObjType			//オブジェクトの種類
	{
		OBJTYPE_PLAYER,		//プレイヤー
		OBJTYPE_ENEMY,		//敵
		OBJTYPE_BULLET,		//弾
		OBJTYPE_EXPLOSION,	//爆発
		OBJTYPE_GRAVITY,	//重力
		OBJTYPE_GROUND,		//地面
		OBJTYPE_LIFE,		//体力
		OBJTYPE_UMBRELLA,	//傘
		OBJTYPE_MODE,		//モード
		OBJTYPE_LIFEBER,
		OBJTYPE_MAX,
		OBJTYPE_NONE
	};

	enum EPriority
	{
		PRIORITY_1 = 0,
		PRIORITY_2,
		PRIORITY_3,
		PRIORITY_4,
		PRIORITY_5,
		PRIORITY_MAX
	};

	explicit CObject(int nPriority = PRIORITY_3);
	virtual ~CObject();				//デストラクタ

	virtual HRESULT Init() = 0;		//初期化処理
	virtual void Uninit() = 0;		//終了処理
	virtual void Update() = 0;		//更新処理
	virtual void Draw() = 0;		//描画処理
	virtual void SetPos(const D3DXVECTOR3 pos) = 0;	//Posの値を設定
	virtual const D3DXVECTOR3 GetPos() = 0;			//posの値を取得する
	virtual const D3DXVECTOR3 GetSize() = 0;		//サイズの情報取得
	virtual const D3DXCOLOR GetCol() = 0;

	static void ReleaseAll();		//全てのポリゴンの破棄処理
	static void UpdateAll();		//全てのポリゴンの更新処理
	static void DrawAll();			//全てのポリゴンの描画処理

	static void ReleaseMode();

	void Release();					//破棄処理

	void SetType(const EObjType type);		//タイプを設定する
	static CObject *GetMyObject(int nPriority,int nCnt);			//オブジェクトの情報取得
	EObjType GetType();						//タイプの情報取得
	void AddMove(D3DXVECTOR3 vec);			//moveの加算
	void SubMove(D3DXVECTOR3 vec);			//moveの引き算

	D3DXVECTOR3 GetMove();					//moveの情報取得
	void SetMove(D3DXVECTOR3 move);			//moveの設定

	virtual void SetLife(int nLife) {}		//ライフの設定
	virtual int GetLife() { return 0; }		//ライフの情報取得

	virtual int GetBulletType() { return 0; }	//弾のタイプ情報取得
	virtual int GetEnemyType() { return 0; }	//敵のタイプ情報取得

	virtual void UpdateTex() {}					//テクスチャの更新処理

private:
	D3DXVECTOR3	m_move;						//移動量
	EObjType m_type;						//タイプ
	static CObject *m_apObject[MAX_PRI][MAX_DATA];	//Objectのポインタ変数
	static int m_nNumAll;					//オブジェクトの数
	int m_nID;								//オブジェクト番号
	int m_nPriority;
};
#endif
