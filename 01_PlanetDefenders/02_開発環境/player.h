//-----------------------------
//
// [player.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_GRAVITY		(0.6f)			//�d�͂̑傫��

//---------------------------
//�v���C���[�N���X
//---------------------------
class CPlayer : public CObject2D
{
public:
	CPlayer();				//�R���X�g���N�^
	~CPlayer() override;	//�f�X�g���N�^

	HRESULT Init() override;	//����������
	void Update() override;		//�X�V����
	static CPlayer *Create();	//�|���S���̐���

	void SetLife(int nLife) override;	//�̗͂̐ݒ�
	int GetLife() override;				//�̗͏��擾

	static int GetPlayerLife();

	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;			//�e�N�X�`���ւ̃|�C���^	
	static int m_ColorTime;

	D3DXVECTOR3					m_playermove;		//�ړ��ʂ�����������
	D3DXCOLOR					m_coler;
	static int					m_Life;				//�̗�
	int							m_nDirectionMove;	//����
	int							mIndex;				//�P�̏�Ԕԍ�
	int							m_nCounterAnim;
	int							m_nPatternAnim;
};
#endif