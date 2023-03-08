//--------------------------------
//
//���U���g�w�b�_�[[result.h]
//Author:���c�喲
//
//--------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "mode.h"

//---------------------------
//�O���錾
//---------------------------
class CObject2D;
class CFade;

//---------------------------
//�}�N����`
//---------------------------
#define MAX_RESULT		(2)			//���U���g�Ŏg���|���S����

//---------------------------
//���U���g�N���X
//---------------------------
class CResult : public CMode
{
public:
	enum STATE
	{
		STATE_GAMECLEAR,
		STATE_GAMEOVER,
		STATE_NONE,
		STATE_MAX
	};

	CResult();		//�R���X�g���N�^
	~CResult();		//�f�X�g���N�^
	
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����

	static CResult *Create();	//�|���S���̐���

	static void SetState(STATE state);

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_RESULT];			//�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject2D;
	CFade *m_pFade;

	static STATE m_State;
};
#endif