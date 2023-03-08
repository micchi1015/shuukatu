//-----------------------------
//
// [life.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _LIFE_H_
#define _LIFE_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//ライフクラス
//---------------------------
class CLife : public CObject2D
{
public:
	explicit CLife(int nPriortiy = PRIORITY_4);		//コンストラクタ
	~CLife() override;								//デストラクタ

	HRESULT Init() override;						//初期化処理
	void Update() override;							//更新処理
	static CLife *Create(const D3DXVECTOR3 pos);	//ポリゴンの生成

	static HRESULT Load();							//テクスチャの読み込み
	static void Unload();							//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
};
#endif
