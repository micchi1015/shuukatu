//-----------------------------
//
// [umbrella.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _UMBRELLA_H_
#define _UMBRELLA_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "player.h"

//---------------------------
//�P�N���X
//---------------------------
class CUmbrella : public CPlayer
{
public:
	CUmbrella();				//�R���X�g���N�^
	~CUmbrella() override;		//�f�X�g���N�^

	HRESULT Init() override;	//����������
	void Update() override;		//�X�V����
	static CUmbrella *Create(D3DXVECTOR3 pos);	//�|���S���̐���

	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//�e�N�X�`���ւ̃|�C���^
};
#endif
