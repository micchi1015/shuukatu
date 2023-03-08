//=============================================================================
//
// stageSelect.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"
#include "fontString.h"

//---------------------------
// �O���錾
//---------------------------
class CFontString;

//---------------------------
//�N���X�錾
//---------------------------
class CStageSelect : public CMode
{
public:
	CStageSelect();
	~CStageSelect() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	void Input(void);	// ���͏���

	static CStageSelect* Create(void);
private:
	int m_nNumAll;						// �I�����̑S�̐�
	int m_nSelectNum;					// ���ݑI������Ă���I����
	static CFontString* m_pStr;			// ������
	static CObject_2D* m_pFrame;		// �I��g
};

#endif // !_STAGESELECT_H_
