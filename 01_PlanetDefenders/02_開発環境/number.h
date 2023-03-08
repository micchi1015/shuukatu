//-----------------------------
//
// [number.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object2D.h"

//---------------------------
//ナンバークラス
//---------------------------
class CNumber : public CObject2D
{
public:
	explicit CNumber(int nPriority = PRIORITY_4);	//コンストラクタ
	~CNumber();										//デストラクタ

	HRESULT Init() override;	//初期化処理
	static CNumber *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	//生成

	static HRESULT Load();		//テクスチャの読み込み
	static void Unload();		//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//テクスチャへのポインタ
};
#endif
