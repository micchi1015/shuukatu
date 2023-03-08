//-----------------------------
//
// [explosion.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_EXPLOSION			(128)	//爆発の最大数
#define MAX_EXPLOSIONSIZE		(50.0f)	//大きさの最大数

//---------------------------
//爆発クラス
//---------------------------
class CExplosion : public CObject2D
{
public:
	CExplosion();				//コンストラクタ
	~CExplosion() override;		//デストラクタ

	HRESULT Init() override;							//初期化処理
	void Update() override;								//更新処理
	static CExplosion *Create(const D3DXVECTOR3 pos,D3DXVECTOR3 size);	//ポリゴンの生成

	static HRESULT Load();								//テクスチャの読み込み
	static void Unload();								//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャへのポインタ

	D3DXCOLOR m_col;	//色
	int m_nCounterAnim;	//アニメーションカウンター
	int m_nPatternAnim;	//アニメーションパターン
};
#endif