//-----------------------------
//
// [object.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "main.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_DATA	(2048)	//�f�[�^�̍ő吔
#define MAX_PRI		(6)

//---------------------------
//�I�u�W�F�N�g�N���X
//---------------------------
class CObject
{
public:
	enum EObjType			//�I�u�W�F�N�g�̎��
	{
		OBJTYPE_PLAYER,		//�v���C���[
		OBJTYPE_ENEMY,		//�G
		OBJTYPE_BULLET,		//�e
		OBJTYPE_EXPLOSION,	//����
		OBJTYPE_GRAVITY,	//�d��
		OBJTYPE_GROUND,		//�n��
		OBJTYPE_LIFE,		//�̗�
		OBJTYPE_UMBRELLA,	//�P
		OBJTYPE_MODE,		//���[�h
		OBJTYPE_LIFEBER,
		OBJTYPE_MAX,
		OBJTYPE_NONE
	};

	enum EPriority
	{
		PRIORITY_1 = 0,
		PRIORITY_2,
		PRIORITY_3,
		PRIORITY_4,
		PRIORITY_5,
		PRIORITY_MAX
	};

	explicit CObject(int nPriority = PRIORITY_3);
	virtual ~CObject();				//�f�X�g���N�^

	virtual HRESULT Init() = 0;		//����������
	virtual void Uninit() = 0;		//�I������
	virtual void Update() = 0;		//�X�V����
	virtual void Draw() = 0;		//�`�揈��
	virtual void SetPos(const D3DXVECTOR3 pos) = 0;	//Pos�̒l��ݒ�
	virtual const D3DXVECTOR3 GetPos() = 0;			//pos�̒l���擾����
	virtual const D3DXVECTOR3 GetSize() = 0;		//�T�C�Y�̏��擾
	virtual const D3DXCOLOR GetCol() = 0;

	static void ReleaseAll();		//�S�Ẵ|���S���̔j������
	static void UpdateAll();		//�S�Ẵ|���S���̍X�V����
	static void DrawAll();			//�S�Ẵ|���S���̕`�揈��

	static void ReleaseMode();

	void Release();					//�j������

	void SetType(const EObjType type);		//�^�C�v��ݒ肷��
	static CObject *GetMyObject(int nPriority,int nCnt);			//�I�u�W�F�N�g�̏��擾
	EObjType GetType();						//�^�C�v�̏��擾
	void AddMove(D3DXVECTOR3 vec);			//move�̉��Z
	void SubMove(D3DXVECTOR3 vec);			//move�̈����Z

	D3DXVECTOR3 GetMove();					//move�̏��擾
	void SetMove(D3DXVECTOR3 move);			//move�̐ݒ�

	virtual void SetLife(int nLife) {}		//���C�t�̐ݒ�
	virtual int GetLife() { return 0; }		//���C�t�̏��擾

	virtual int GetBulletType() { return 0; }	//�e�̃^�C�v���擾
	virtual int GetEnemyType() { return 0; }	//�G�̃^�C�v���擾

	virtual void UpdateTex() {}					//�e�N�X�`���̍X�V����

private:
	D3DXVECTOR3	m_move;						//�ړ���
	EObjType m_type;						//�^�C�v
	static CObject *m_apObject[MAX_PRI][MAX_DATA];	//Object�̃|�C���^�ϐ�
	static int m_nNumAll;					//�I�u�W�F�N�g�̐�
	int m_nID;								//�I�u�W�F�N�g�ԍ�
	int m_nPriority;
};
#endif
