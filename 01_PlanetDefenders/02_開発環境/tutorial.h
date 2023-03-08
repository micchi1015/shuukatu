//--------------------------------
//
//�`���[�g���A���w�b�_�[[tutorial.h]
//Author:���c�喲
//
//--------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

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
#define MAX_TUTORIAL		(1)			//�`���[�g���A���Ŏg���|���S����

//---------------------------
//�^�C�g���N���X
//---------------------------
class CTutorial : public CMode
{
public:
	CTutorial();	//�R���X�g���N�^
	~CTutorial();	//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	static CTutorial *Create();	//�^�C�g���̐���

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TUTORIAL];	//�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject2D[MAX_TUTORIAL];			//Object2D�̃|�C���^�ϐ�
	CFade *m_pFade;
};
#endif
