//-----------------------------
//
// [gravity.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _GRAVITY_H_
#define _GRAVITY_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"
#include "bullet.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_GRAVITYTEXTURE	(3)		//�d�͉摜�̐�

//---------------------------
//�d�̓N���X
//---------------------------
class CGravity : public CObject2D
{
public:
	enum GRAVITYTYPE		//�d�͂̃^�C�v
	{
		GRAVITY_AROUND,
		GRAVITY_MID,
		GRAVITY_LEFT,
		GRAVITY_RIGHT,
		GRAVITY_MAX,
		GRAVITY_NONE
	};
	explicit CGravity(int nPriority = PRIORITY_2);				//�R���X�g���N�^
	~CGravity() override;	//�f�X�g���N�^

	HRESULT Init() override;	//����������
	void Update() override;		//�X�V����
	static CGravity *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, GRAVITYTYPE type,float power);	//�|���S���̐���

	GRAVITYTYPE GetGravityType();			//�d�͂̃^�C�v���擾
	void SetGravityType(GRAVITYTYPE type);	//�^�C�v�̐ݒ�
	static HRESULT Load();					//�e�N�X�`���̓ǂݍ���
	static void Unload();					//�e�N�X�`���̔j��

private:
	GRAVITYTYPE					m_type;								//�^�C�v
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_GRAVITYTEXTURE];		//�e�N�X�`���ւ̃|�C���^
	float				m_power;									//����
};
#endif
