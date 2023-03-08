//=============================================================================
//
// gamedebug.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _GAMEDEBUG_H_
#define _GAMEDEBUG_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "game.h"
#include "input.h"

//---------------------------
//�O���錾
//---------------------------
class CMeshfield;
class CPlayer;

//---------------------------
//�N���X�錾
//---------------------------
class CGameDebug : public CGame
{
public:
	CGameDebug();
	~CGameDebug();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static CMeshfield* GetField(void) { return m_pField; }		// ���b�V���t�B�[���h�̎擾����
	static CPlayer* GetPlayer(void) { return m_pPlayer[0]; }	// �v���C���[�̎擾����

	static CGameDebug* Create(void);			//��������
private:
	static CMeshfield* m_pField;
	static CPlayer* m_pPlayer[PLAYER_MAX];							//�v���C���[�̃C���X�^���X�ւ̃|�C���^
};

#endif // !_GAMEDEBUG_H_
