//--------------------------------
//
//チュートリアルヘッダー[tutorial.h]
//Author:梶田大夢
//
//--------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

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
#define MAX_TUTORIAL		(1)			//チュートリアルで使うポリゴン数

//---------------------------
//タイトルクラス
//---------------------------
class CTutorial : public CMode
{
public:
	CTutorial();	//コンストラクタ
	~CTutorial();	//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	static CTutorial *Create();	//タイトルの生成

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TUTORIAL];	//テクスチャへのポインタ
	CObject2D *m_pObject2D[MAX_TUTORIAL];			//Object2Dのポインタ変数
	CFade *m_pFade;
};
#endif
