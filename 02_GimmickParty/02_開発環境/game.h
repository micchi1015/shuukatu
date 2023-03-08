//=============================================================================
//
// game.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "mode.h"

//---------------------------
//�N���X�錾
//---------------------------
class CGame : public CMode
{
public:
	CGame();
	~CGame();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static void SetEndGame();							// �Q�[���I���̐ݒ菈��
	static bool GetEndGame() { return m_bEndGame; }		// �Q�[���I���̎擾����

private:
	static bool m_bEndGame;	// �Q�[���I������
};

#endif // !_GAME_H_
