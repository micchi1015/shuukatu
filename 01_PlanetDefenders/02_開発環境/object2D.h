//-----------------------------
//
// [object2D.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//---------------------------
//インクルード
//---------------------------
#include "object.h"

//--------------------------
//マクロ定義
//--------------------------
//頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//--------------------------
// 構造体定義
//--------------------------
// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

//---------------------------
//オブジェクト2Dクラス
//---------------------------
class CObject2D : public CObject
{
public:
	explicit CObject2D(int nPriority = PRIORITY_3);			//コンストラクタ
	~CObject2D() override;	//デストラクタ

	virtual HRESULT Init() override;						//初期化処理
	virtual void Uninit() override;							//終了処理
	virtual void Update() override;							//更新処理
	virtual void Draw() override;							//描画処理
	virtual void SetPos(const D3DXVECTOR3 pos) override;	//Posの値を設定

	void SetColer(const D3DXCOLOR col);						//colerの設定
	void SetSize(const D3DXVECTOR3 size);					//sizeの値を設定
	void SetTexPos(float BesideSplit, float nNumIndex);		//Texの設定
	void SetLifeTexPos(float BesideSplit, float nNumIndexX, float Split, float nNumIndexY);		//Texの設定
	const D3DXVECTOR3 GetPos() override;					//posの値を取得する
	const D3DXVECTOR3 GetSize() override;					//サイズの情報取得
	const D3DXCOLOR GetCol() override;						//colの情報取得

	static CObject2D *Create(const D3DXVECTOR3 pos,int nPriority);		//ポリゴンの生成
	void BindTexture(LPDIRECT3DTEXTURE9	pTexture);						//テクスチャを代入	

private:
	LPDIRECT3DTEXTURE9			m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3					m_pos;			//座標位置
	D3DXVECTOR3					m_rot;			//回転量	
	D3DXVECTOR3					m_size;			//サイズ
	D3DXCOLOR					m_col;			//カラー

	float m_nTimer;		//時間
};

#endif

