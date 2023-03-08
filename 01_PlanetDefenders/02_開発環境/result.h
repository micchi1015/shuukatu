//--------------------------------
//
//リザルトヘッダー[result.h]
//Author:梶田大夢
//
//--------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

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
#define MAX_RESULT		(2)			//リザルトで使うポリゴン数

//---------------------------
//リザルトクラス
//---------------------------
class CResult : public CMode
{
public:
	enum STATE
	{
		STATE_GAMECLEAR,
		STATE_GAMEOVER,
		STATE_NONE,
		STATE_MAX
	};

	CResult();		//コンストラクタ
	~CResult();		//デストラクタ
	
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理

	static CResult *Create();	//ポリゴンの生成

	static void SetState(STATE state);

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_RESULT];			//テクスチャへのポインタ
	CObject2D *m_pObject2D;
	CFade *m_pFade;

	static STATE m_State;
};
#endif