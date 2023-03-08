//-----------------------------
//
// [number.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object2D.h"

//---------------------------
//�i���o�[�N���X
//---------------------------
class CNumber : public CObject2D
{
public:
	explicit CNumber(int nPriority = PRIORITY_4);	//�R���X�g���N�^
	~CNumber();										//�f�X�g���N�^

	HRESULT Init() override;	//����������
	static CNumber *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	//����

	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;		//�e�N�X�`���ւ̃|�C���^
};
#endif
