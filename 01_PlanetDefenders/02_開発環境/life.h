//-----------------------------
//
// [life.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _LIFE_H_
#define _LIFE_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//���C�t�N���X
//---------------------------
class CLife : public CObject2D
{
public:
	explicit CLife(int nPriortiy = PRIORITY_4);		//�R���X�g���N�^
	~CLife() override;								//�f�X�g���N�^

	HRESULT Init() override;						//����������
	void Update() override;							//�X�V����
	static CLife *Create(const D3DXVECTOR3 pos);	//�|���S���̐���

	static HRESULT Load();							//�e�N�X�`���̓ǂݍ���
	static void Unload();							//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
};
#endif
