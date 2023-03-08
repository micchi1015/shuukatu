//-----------------------------
//
// [ground.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _GROUND_H_
#define _GROUND_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//�n�ʃN���X
//---------------------------
class CGround : public CObject2D
{
public:
	CGround();				//�R���X�g���N�^
	~CGround() override;	//�f�X�g���N�^

	HRESULT Init() override;	//����������
	void Update() override;		//�X�V����
	static CGround *Create();	//�|���S���̐���

	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̔j��

	void SetLife(int nLife) override;	//�̗͂�ݒ�
	int GetLife() override;				//�̗͏����擾

	static int GetGroundLife();

	void UpdateTex() override;			//�e�N�X�`���̍X�V

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	static int					m_Life;			//�̗�
	int							m_ColorNumber;
	int m_nCounterAnim;	//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	//�A�j���[�V�����p�^�[��
};
#endif