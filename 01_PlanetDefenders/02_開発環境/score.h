//--------------------------------
//
//[score.h]
//Author:梶田大夢
//
//--------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

//---------------------------
//インクルード
//---------------------------
#include "object.h"

//---------------------------
//前方宣言
//---------------------------
class CNumber;

//---------------------------
//マクロ定義
//---------------------------
#define MAX_SCORE	(8)		//スコアの桁数

//---------------------------
//スコアクラス
//---------------------------
class CScore : public CObject
{
public:
	explicit CScore(int nPriority = PRIORITY_4);	//コンストラクタ
	~CScore() override;		//デストラクタ

	HRESULT Init() override;	//初期化処理
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理
	static CScore *Create();	//ポリゴンの生成

	void SetScore(int nScore);	//スコアの設定処理
	void AddScore(int nValue);	//スコアの加算処理
	int GetScore();				//スコア情報の取得処理

	void SetPos(const D3DXVECTOR3 pos) override {};	//Posの値を設定
	const D3DXVECTOR3 GetPos() override { return D3DXVECTOR3(); }		//posの値を取得する
	const D3DXVECTOR3 GetSize() override { return D3DXVECTOR3(); };		//サイズの情報取得
	const D3DXCOLOR GetCol() override { return D3DXCOLOR(); };			//カラーの情報取得

private:
	CNumber *m_apNumber[MAX_SCORE];		//Number型の配列
	int m_nScore;						//スコアの値
};
#endif