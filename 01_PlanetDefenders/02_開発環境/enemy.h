//-----------------------------
//
// [enemy.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object2D.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_TEXTURE	(4)			//�摜��

//---------------------------
//�O���錾
//---------------------------
class CPolygon;
class CFade;

//---------------------------
//�G�N���X
//---------------------------
class CEnemy : public CObject2D
{
public:
	enum ENEMYTYPE				//�G�̃^�C�v
	{
		ENEMY_SKYSPACEMAN,
		ENEMY_SKY,
		ENEMY_GROUNDSPACEMANR,
		ENEMY_GROUNDSPACEMANL,
		ENEMY_MAX,
		ENEMY_NONE
	};

	enum ENEMYSTATE			//�G�̏��
	{
		STATE_NORMAL,
		STATE_ATTACK,
		STATE_MAX,
		STATE_NONE
	};

	CEnemy();				//�R���X�g���N�^
	~CEnemy() override;		//�f�X�g���N�^

	HRESULT Init() override;	//����������
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	static CEnemy *Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,ENEMYTYPE type, int life);	//�G�̐���

	static void SetSkyEnemy(int nSkyEnemy);
	static void SetSky(int nSky);
	static void SetGroundEnemy(int nGroundEnemy);
	static void SetGroundEnemyL(int nGroundEnemyL);

	void EnemyAction();					//�U�������֐�
	void SetAttackCount(int nAttack);	//�U���^�C�~���O��ݒ�
	void SetEnemyType(ENEMYTYPE type);	//�^�C�v�̐ݒ�
	void SetLife(int nLife) override;	//�G�̗̑͐ݒ�
	void DamageCout();

	static int GetCount();
	int GetSkyEnemyCnt();				//�󒆓G�̑�����Ԃ�
	int GetSky();
	int GetGroundEnemyCnt();			//�n�ʓG�̑�����Ԃ�
	int GetGroundEnemyLCnt();
	int GetLife() override;				//�G�̗̑͏��擾
	int GetEnemyType() override;		//�^�C�v�̏��擾
	ENEMYTYPE GetEnemy();				//�^�C�v�̏��擾

	static HRESULT Load();				//�e�N�X�`���̓ǂݍ���
	static void Unload();				//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[ENEMY_MAX];	//�e�N�X�`���ւ̃|�C���^								

	ENEMYTYPE					m_type;					//�^�C�v
	ENEMYSTATE					m_state;				//���
	CFade *m_pFade;
	static int					m_SkyEnemy;				//�󒆓G
	static int					m_Sky;
	static int					m_GroundEnemy;			//�n�ʓG
	static int					m_GroundEnemyL;
	static int					m_DamageCount;			//�_���[�W����
	static int					m_SoundCount;			//�T�E���h����
	static int					m_SoundCount2;			//�T�E���h����2
	static int					m_SoundCount3;			//�T�E���h����3

	int							m_Life;					//�̗�
	int							m_AttackTime;			//�U���^�C�~���O
	int							m_nAttackCounter;		//�U�����̃e�N�X�`���ύX�p�ϐ�
	int							m_nAttackPattern;		//�U�����̃e�N�X�`���ύX�p�ϐ�
	int							m_nNormalPattern;		//�ʏ펞�̃e�N�X�`���ύX�p�ϐ�
	int							m_nNormalCounter;		//�ʏ펞�̃e�N�X�`���ύX�p�ϐ�
	int							m_nCounterAnim;			//�ʏ펞�̃e�N�X�`���ύX�p�ϐ�
	int							m_nPatternAnim;			//�ʏ펞�̃e�N�X�`���ύX�p�ϐ�
	int							m_nCntAnim;				//�ʏ펞�̃e�N�X�`���ύX�p�ϐ�
	int							m_nPtnAnim;				//�ʏ펞�̃e�N�X�`���ύX�p�ϐ�
};
#endif
