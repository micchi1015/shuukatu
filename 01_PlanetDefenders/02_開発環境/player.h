//-----------------------------
//
// [player.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_GRAVITY		(0.6f)			//重力の大きさ

//---------------------------
//プレイヤークラス
//---------------------------
class CPlayer : public CObject2D
{
public:
	CPlayer();				//コンストラクタ
	~CPlayer() override;	//デストラクタ

	HRESULT Init() override;	//初期化処理
	void Update() override;		//更新処理
	static CPlayer *Create();	//ポリゴンの生成

	void SetLife(int nLife) override;	//体力の設定
	int GetLife() override;				//体力情報取得

	static int GetPlayerLife();

	static HRESULT Load();		//テクスチャの読み込み
	static void Unload();		//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;			//テクスチャへのポインタ	
	static int m_ColorTime;

	D3DXVECTOR3					m_playermove;		//移動量を初期化する
	D3DXCOLOR					m_coler;
	static int					m_Life;				//体力
	int							m_nDirectionMove;	//向き
	int							mIndex;				//傘の状態番号
	int							m_nCounterAnim;
	int							m_nPatternAnim;
};
#endif