//-----------------------------
//
// [umbrella.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _UMBRELLA_H_
#define _UMBRELLA_H_

//---------------------------
//インクルード
//---------------------------
#include "player.h"

//---------------------------
//傘クラス
//---------------------------
class CUmbrella : public CPlayer
{
public:
	CUmbrella();				//コンストラクタ
	~CUmbrella() override;		//デストラクタ

	HRESULT Init() override;	//初期化処理
	void Update() override;		//更新処理
	static CUmbrella *Create(D3DXVECTOR3 pos);	//ポリゴンの生成

	static HRESULT Load();		//テクスチャの読み込み
	static void Unload();		//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//テクスチャへのポインタ
};
#endif
