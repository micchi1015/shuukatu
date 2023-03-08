//--------------------------------
//
//�^�C�g���w�b�_�[[title.h]
//Author:���c�喲
//
//--------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

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
#define MAX_TITLE		(5)			//�^�C�g���Ŏg���|���S����

//---------------------------
//�^�C�g���N���X
//---------------------------
class CTitle : public CMode
{
public:
	CTitle();	//�R���X�g���N�^
	~CTitle();	//�f�X�g���N�^
	
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	static CTitle *Create();	//�^�C�g���̐���

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TITLE];	//�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject2D[MAX_TITLE];			//Object2D�̃|�C���^�ϐ�
	CFade *m_pFade;

	D3DXVECTOR3	m_BgMove;					//�ړ��ʂ�����������
	D3DXVECTOR3	m_BgPos;					//�ړ��ʂ�����������
	int m_Menu;
};
#endif