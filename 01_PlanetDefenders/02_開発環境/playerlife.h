//-----------------------------
//
// [playerlife.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _PLAYERLIFE_H_
#define _PLAYERLIFE_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//�v���C���[���C�t�N���X
//---------------------------
class CPlayerLife : public CObject2D
{
public:
	explicit CPlayerLife(int nPriortiy = PRIORITY_4);	//�R���X�g���N�^
	~CPlayerLife() override;							//�f�X�g���N�^

	HRESULT Init() override;							//����������
	void Update() override;								//�X�V����
	static CPlayerLife *Create(const D3DXVECTOR3 pos);	//�|���S���̐���

	static HRESULT Load();								//�e�N�X�`���̓ǂݍ���
	static void Unload();								//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^
};
#endif
