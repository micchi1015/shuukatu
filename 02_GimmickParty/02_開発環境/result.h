//=============================================================================
//
// result.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//---------------------------
//クラス宣言
//---------------------------
class CResult : public CMode
{
public:
	CResult();
	~CResult() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static CResult* Create(void);			//生成処理
private:
};

#endif // !_RESULT_H_