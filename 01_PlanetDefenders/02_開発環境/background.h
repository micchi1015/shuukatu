//-----------------------------
//
// [background.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//背景クラス
//---------------------------
class CBg : public CObject2D
{
public:
	explicit CBg(int nPriority = PRIORITY_1);				//コンストラクタ
	~CBg() override;	//デストラクタ

	HRESULT Init() override;	//初期化処理
	static CBg *Create();		//ポリゴンの生成

	static HRESULT Load();		//テクスチャの読み込み
	static void Unload();		//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//テクスチャ
};
#endif
