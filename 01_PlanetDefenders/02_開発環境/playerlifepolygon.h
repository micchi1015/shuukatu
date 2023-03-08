//-----------------------------
//
// [playerlifepolygon.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _PLAYERLIFEPOLYGON_H_
#define _PLAYERLIFEPOLYGON_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_PLAYERLIFEPOLYGON	(7)		

//---------------------------
//�v���C���[���C�t�|���S���N���X
//---------------------------
class CPlayerLifePolygon : public CObject2D
{
public:
	explicit CPlayerLifePolygon(int nPriortiy = PRIORITY_2);	//�R���X�g���N�^
	~CPlayerLifePolygon() override;								//�f�X�g���N�^

	HRESULT Init() override;									//����������
	void Update() override;										//�X�V����
	static CPlayerLifePolygon *Create(const D3DXVECTOR3 pos);	//�|���S���̐���

	void UpdateLife(int nCnt);				//�e�N�X�`���̍X�V

	void SetLife(int nLife) override;		//�̗͂�ݒ�
	static int GetPlayerLife();				//�̗͏����擾

	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	static CPlayerLifePolygon *m_Polygon;

	static int	m_Life;						//�̗�
};
#endif


