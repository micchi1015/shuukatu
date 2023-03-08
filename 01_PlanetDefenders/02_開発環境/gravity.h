//-----------------------------
//
// [gravity.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _GRAVITY_H_
#define _GRAVITY_H_

//---------------------------
//インクルード
//---------------------------
#include "object2D.h"
#include "bullet.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_GRAVITYTEXTURE	(3)		//重力画像の数

//---------------------------
//重力クラス
//---------------------------
class CGravity : public CObject2D
{
public:
	enum GRAVITYTYPE		//重力のタイプ
	{
		GRAVITY_AROUND,
		GRAVITY_MID,
		GRAVITY_LEFT,
		GRAVITY_RIGHT,
		GRAVITY_MAX,
		GRAVITY_NONE
	};
	explicit CGravity(int nPriority = PRIORITY_2);				//コンストラクタ
	~CGravity() override;	//デストラクタ

	HRESULT Init() override;	//初期化処理
	void Update() override;		//更新処理
	static CGravity *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, GRAVITYTYPE type,float power);	//ポリゴンの生成

	GRAVITYTYPE GetGravityType();			//重力のタイプ情報取得
	void SetGravityType(GRAVITYTYPE type);	//タイプの設定
	static HRESULT Load();					//テクスチャの読み込み
	static void Unload();					//テクスチャの破棄

private:
	GRAVITYTYPE					m_type;								//タイプ
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_GRAVITYTEXTURE];		//テクスチャへのポインタ
	float				m_power;									//強さ
};
#endif
