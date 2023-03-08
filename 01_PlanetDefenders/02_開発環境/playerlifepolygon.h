//-----------------------------
//
// [playerlifepolygon.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _PLAYERLIFEPOLYGON_H_
#define _PLAYERLIFEPOLYGON_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_PLAYERLIFEPOLYGON	(7)		

//---------------------------
//プレイヤーライフポリゴンクラス
//---------------------------
class CPlayerLifePolygon : public CObject2D
{
public:
	explicit CPlayerLifePolygon(int nPriortiy = PRIORITY_2);	//コンストラクタ
	~CPlayerLifePolygon() override;								//デストラクタ

	HRESULT Init() override;									//初期化処理
	void Update() override;										//更新処理
	static CPlayerLifePolygon *Create(const D3DXVECTOR3 pos);	//ポリゴンの生成

	void UpdateLife(int nCnt);				//テクスチャの更新

	void SetLife(int nLife) override;		//体力を設定
	static int GetPlayerLife();				//体力情報を取得

	static HRESULT Load();		//テクスチャの読み込み
	static void Unload();		//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャへのポインタ
	static CPlayerLifePolygon *m_Polygon;

	static int	m_Life;						//体力
};
#endif


