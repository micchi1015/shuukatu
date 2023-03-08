//-----------------------------
//
// [life.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _POLYGON_H_
#define _POLYGON_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_LIFE	(12)		

//---------------------------
//�|���S���N���X
//---------------------------
class CPolygon : public CObject2D
{
public:
	explicit CPolygon(int nPriortiy = PRIORITY_2);	//�R���X�g���N�^
	~CPolygon() override;							//�f�X�g���N�^

	HRESULT Init() override;						//����������
	void Update() override;							//�X�V����
	static CPolygon *Create(const D3DXVECTOR3 pos);	//�|���S���̐���

	void UpdateLife(int nCnt);						//�e�N�X�`���̍X�V

	void SetLife(int nLife) override;				//�̗͂�ݒ�
	static int GetLife();							//�̗͏����擾

	static HRESULT Load();							//�e�N�X�`���̓ǂݍ���
	static void Unload();							//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	static CPolygon *m_Polygon;						

	static int	m_Life;								//�̗�
};
#endif

