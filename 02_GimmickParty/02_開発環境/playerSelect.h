//=============================================================================
//
// palyerSelect.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _PLAYERSELECT_H_
#define _PLAYERSELECT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"
#include "fontString.h"

//---------------------------
// �O���錾
//---------------------------
class CFontString;
class CPlayerModel;

//---------------------------
//�N���X�錾
//---------------------------
class CPlayerSelect : public CMode
{
public:

	CPlayerSelect();
	~CPlayerSelect() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Input(void);

	static CPlayerSelect* Create(void);
	
	void AddPlayerCounnt(int nCount);
private:
	static CFontString* m_pStr;			// ������
	int m_nPlayerCount;
};

#endif // !_TITLE_H_
