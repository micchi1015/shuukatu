//=============================================================================
//
// result.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//---------------------------
//�N���X�錾
//---------------------------
class CResult : public CMode
{
public:
	CResult();
	~CResult() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static CResult* Create(void);			//��������
private:
};

#endif // !_RESULT_H_