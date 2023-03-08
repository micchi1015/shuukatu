//-----------------------------
//
// [background.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//�w�i�N���X
//---------------------------
class CBg : public CObject2D
{
public:
	explicit CBg(int nPriority = PRIORITY_1);				//�R���X�g���N�^
	~CBg() override;	//�f�X�g���N�^

	HRESULT Init() override;	//����������
	static CBg *Create();		//�|���S���̐���

	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//�e�N�X�`��
};
#endif
