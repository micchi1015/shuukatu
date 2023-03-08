//--------------------------------
//
//タイトルヘッダー[title.h]
//Author:梶田大夢
//
//--------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

//---------------------------
//インクルード
//---------------------------
#include "mode.h"

//---------------------------
//前方宣言
//---------------------------
class CObject2D;
class CFade;

//---------------------------
//マクロ定義
//---------------------------
#define MAX_TITLE		(5)			//タイトルで使うポリゴン数

//---------------------------
//タイトルクラス
//---------------------------
class CTitle : public CMode
{
public:
	CTitle();	//コンストラクタ
	~CTitle();	//デストラクタ
	
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	static CTitle *Create();	//タイトルの生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TITLE];	//テクスチャへのポインタ
	CObject2D *m_pObject2D[MAX_TITLE];			//Object2Dのポインタ変数
	CFade *m_pFade;

	D3DXVECTOR3	m_BgMove;					//移動量を初期化する
	D3DXVECTOR3	m_BgPos;					//移動量を初期化する
	int m_Menu;
};
#endif