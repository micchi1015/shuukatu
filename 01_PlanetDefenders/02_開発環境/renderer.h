//-----------------------------
//
// [rendere.h]
// Author:梶田大夢
//
//-----------------------------
#ifndef _RENDERE_H_
#define _RENDERE_H_

//---------------------------
//レンダラークラス
//---------------------------
class CRenderer
{
public:
	static const int SCREEN_WIDTH = 1280;		// スクリーンの幅
	static const int SCREEN_HEIGHT = 720;		// スクリーンの高さ

public:
	CRenderer();			//コンストラクタ
	~CRenderer();			//デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow);	//初期化処理
	void Uninit();							//終了処理
	void Update();							//更新処理
	void Draw();							//描画処理

	LPDIRECT3DDEVICE9 GetD3DDevice();		//m_pD3DDeviceの値を返す

private:
	void DrawFPS();		//FPSの描画処理
	
	LPDIRECT3D9					m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9			m_pD3DDevice;	// Deviceオブジェクト
	LPD3DXFONT					m_pFont;		// フォント
};
#endif