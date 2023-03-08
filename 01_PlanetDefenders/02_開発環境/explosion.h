//-----------------------------
//
// [explosion.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_EXPLOSION			(128)	//�����̍ő吔
#define MAX_EXPLOSIONSIZE		(50.0f)	//�傫���̍ő吔

//---------------------------
//�����N���X
//---------------------------
class CExplosion : public CObject2D
{
public:
	CExplosion();				//�R���X�g���N�^
	~CExplosion() override;		//�f�X�g���N�^

	HRESULT Init() override;							//����������
	void Update() override;								//�X�V����
	static CExplosion *Create(const D3DXVECTOR3 pos,D3DXVECTOR3 size);	//�|���S���̐���

	static HRESULT Load();								//�e�N�X�`���̓ǂݍ���
	static void Unload();								//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^

	D3DXCOLOR m_col;	//�F
	int m_nCounterAnim;	//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	//�A�j���[�V�����p�^�[��
};
#endif