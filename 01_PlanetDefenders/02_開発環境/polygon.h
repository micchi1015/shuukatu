//-----------------------------
//
// [life.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _POLYGON_H_
#define _POLYGON_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_LIFE	(12)		

//---------------------------
//ポリゴンクラス
//---------------------------
class CPolygon : public CObject2D
{
public:
	explicit CPolygon(int nPriortiy = PRIORITY_2);	//コンストラクタ
	~CPolygon() override;							//デストラクタ

	HRESULT Init() override;						//初期化処理
	void Update() override;							//更新処理
	static CPolygon *Create(const D3DXVECTOR3 pos);	//ポリゴンの生成

	void UpdateLife(int nCnt);						//テクスチャの更新

	void SetLife(int nLife) override;				//体力を設定
	static int GetLife();							//体力情報を取得

	static HRESULT Load();							//テクスチャの読み込み
	static void Unload();							//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	static CPolygon *m_Polygon;						

	static int	m_Life;								//体力
};
#endif

