//-----------------------------
//
// [ground.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _GROUND_H_
#define _GROUND_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//地面クラス
//---------------------------
class CGround : public CObject2D
{
public:
	CGround();				//コンストラクタ
	~CGround() override;	//デストラクタ

	HRESULT Init() override;	//初期化処理
	void Update() override;		//更新処理
	static CGround *Create();	//ポリゴンの生成

	static HRESULT Load();		//テクスチャの読み込み
	static void Unload();		//テクスチャの破棄

	void SetLife(int nLife) override;	//体力を設定
	int GetLife() override;				//体力情報を取得

	static int GetGroundLife();

	void UpdateTex() override;			//テクスチャの更新

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//テクスチャへのポインタ
	static int					m_Life;			//体力
	int							m_ColorNumber;
	int m_nCounterAnim;	//アニメーションカウンター
	int m_nPatternAnim;	//アニメーションパターン
};
#endif