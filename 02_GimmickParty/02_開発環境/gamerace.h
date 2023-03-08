//=============================================================================
//
// gamerace.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _GAMERACE_H_
#define _GAMERACE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "game.h"

//---------------------------
//�O���錾
//---------------------------
class CStage;

//---------------------------
//�N���X�錾
//---------------------------
class CGameRace : public CGame
{
public:
	CGameRace();
	~CGameRace();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static CStage* GetStage(void) { return m_pStage; }	// �X�e�[�W�̎擾����

	static CGameRace* Create(void);			//��������
private:
	static CStage* m_pStage;
};

#endif // !_GAMERACE_H_

