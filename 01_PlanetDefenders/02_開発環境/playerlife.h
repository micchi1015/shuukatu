//-----------------------------
//
// [playerlife.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _PLAYERLIFE_H_
#define _PLAYERLIFE_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//プレイヤーライフクラス
//---------------------------
class CPlayerLife : public CObject2D
{
public:
	explicit CPlayerLife(int nPriortiy = PRIORITY_4);	//コンストラクタ
	~CPlayerLife() override;							//デストラクタ

	HRESULT Init() override;							//初期化処理
	void Update() override;								//更新処理
	static CPlayerLife *Create(const D3DXVECTOR3 pos);	//ポリゴンの生成

	static HRESULT Load();								//テクスチャの読み込み
	static void Unload();								//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャへのポインタ
};
#endif
