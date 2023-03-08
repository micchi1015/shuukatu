//-----------------------------
//
// [bullet.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_SIZE		(15.0f)	//�傫���̍ő吔

//---------------------------
//�O���錾
//---------------------------
class CPolygon;
class CPlayerLifePolygon;

//---------------------------
//�e�N���X
//---------------------------
class CBullet : public CObject2D
{
public:
	enum BULLETTYPE			//�e�̎��
	{
		BULLET_PLAYER,
		BULLET_ENEMY,
		BULLET_MAX,
		BULLET_NONE
	};

	explicit CBullet(int nPriority = PRIORITY_2);	//�R���X�g���N�^
	~CBullet() override;							//�f�X�g���N�^

	HRESULT Init() override;						//����������
	void Update() override;							//�X�V����
	static CBullet *Create(const D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col, BULLETTYPE type);	//�e�̐���

	BULLETTYPE GetType();							//�^�C�v�̎擾
	void SetBulletType(BULLETTYPE type);			//�^�C�v�̐ݒ�

	int GetBulletType() override;					//�e�̎�ޏ��擾

	static void SubLife();							//�n�ʂ̗̑͂����炷
	static void SubPlayerLife();					//�v���C���[�̗̑͂����炷

	static void SetPolygon(int m_polygon);
	static void SetLifePolygon(int m_PlayerLife);

	static HRESULT Load();							//�e�N�X�`���̓ǂݍ���
	static void Unload();							//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	BULLETTYPE m_type;								//�e�̃^�C�v�^�ϐ�

	static CPolygon *m_pPolygon;						//�n�ʂ̗̑̓|���S���̃|�C���^�ϐ�
	static CPlayerLifePolygon *m_pPlayerLifePolygon;	//�v���C���[�̗̑̓|���S���̃|�C���^�ϐ�
	static int m_Polygon;								//�n�ʗp�ϐ�
	static int m_PlayerLifePolygon;						//�v���C���[�p�ϐ�

	int m_nLife;			//�̗�
};
#endif