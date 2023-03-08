//-----------------------------
//
// [mode.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _MODE_H_
#define _MODE_H_

//---------------------------
//インクルード
//---------------------------
#include "object.h"

//---------------------------
//前方宣言
//---------------------------
class CTitle;
class CGame;
class CResult;

//---------------------------
//モードクラス
//---------------------------
class CMode : public CObject
{
public:
	CMode();			//コンストラクタ
	~CMode() override;	//デストラクタ

	virtual HRESULT Init() override { return S_OK; }	//初期化処理
	virtual void Uninit() override {};					//終了処理
	virtual void Update() override {};					//更新処理
	virtual void Draw() override {};					//描画処理

	void SetPos(const D3DXVECTOR3 pos)override {};				//Posの値を設定

	const D3DXVECTOR3 GetPos() override {return D3DXVECTOR3();}			//posの値を取得する
	const D3DXVECTOR3 GetSize() override { return D3DXVECTOR3(); }		//サイズの情報取得
	const D3DXCOLOR GetCol() override { return D3DXCOLOR(); }			//colの情報取得
	
private:
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
};

#endif