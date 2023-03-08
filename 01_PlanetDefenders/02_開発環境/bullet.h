//-----------------------------
//
// [bullet.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_SIZE		(15.0f)	//大きさの最大数

//---------------------------
//前方宣言
//---------------------------
class CPolygon;
class CPlayerLifePolygon;

//---------------------------
//弾クラス
//---------------------------
class CBullet : public CObject2D
{
public:
	enum BULLETTYPE			//弾の種類
	{
		BULLET_PLAYER,
		BULLET_ENEMY,
		BULLET_MAX,
		BULLET_NONE
	};

	explicit CBullet(int nPriority = PRIORITY_2);	//コンストラクタ
	~CBullet() override;							//デストラクタ

	HRESULT Init() override;						//初期化処理
	void Update() override;							//更新処理
	static CBullet *Create(const D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col, BULLETTYPE type);	//弾の生成

	BULLETTYPE GetType();							//タイプの取得
	void SetBulletType(BULLETTYPE type);			//タイプの設定

	int GetBulletType() override;					//弾の種類情報取得

	static void SubLife();							//地面の体力を減らす
	static void SubPlayerLife();					//プレイヤーの体力を減らす

	static void SetPolygon(int m_polygon);
	static void SetLifePolygon(int m_PlayerLife);

	static HRESULT Load();							//テクスチャの読み込み
	static void Unload();							//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	BULLETTYPE m_type;								//弾のタイプ型変数

	static CPolygon *m_pPolygon;						//地面の体力ポリゴンのポインタ変数
	static CPlayerLifePolygon *m_pPlayerLifePolygon;	//プレイヤーの体力ポリゴンのポインタ変数
	static int m_Polygon;								//地面用変数
	static int m_PlayerLifePolygon;						//プレイヤー用変数

	int m_nLife;			//体力
};
#endif