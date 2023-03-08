//-----------------------------
//
// [game.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _GAME_H_
#define _GAME_H_
//---------------------------
//�C���N���[�h
//---------------------------
#include "mode.h"
#include "polygon.h"
#include "playerlifepolygon.h"

//---------------------------
//�}�N����`
//---------------------------
#define MAX_SKYENEMY	(2)			//wave1���̓G�̐�
#define MAX_GROUNDENEMY	(1)			//wave1���̓G�̐�

#define MAX_SKYENEMY2		(2)		//wave2���̓G�̐�
#define MAX_GROUNDENEMY2	(1)		//wave2���̓G�̐�
#define MAX_SKY2			(1)

#define MAX_SKYENEMY3		(3)
#define MAX_GROUNDENEMY3	(1)
#define MAX_GROUNDENEMYL3	(1)
#define MAX_SKY3			(2)

#define MAX_WAVECOUNT		(6)			//�^�C�g���Ŏg���|���S����
//---------------------------
//�O���錾
//---------------------------
class CScore;
class CEnemy;
class CPolygon;
class CPlayerLifePolygon;
class CWaveCount;

//---------------------------
//�Q�[���N���X
//---------------------------
class CGame : public CMode
{
public:
	enum GAMESTATE		//�Q�[���̏��
	{
		STATE_INIT,
		STATE_WAVEINIT,
		STATE_EXE,
		STATE_UNINIT,
		STATE_MAX
	};

	enum WAVE			//�E�F�[�u
	{
		WAVE_NONE = 0,
		WAVE_1,
		WAVE_2,
		WAVE_3,
		WAVE_MAX
	};

	CGame();	//�R���X�g���N�^
	~CGame();	//�f�X�g���N�^

	HRESULT Init();		//����������
	void Uninit();		//�I������
	void Update();		//�X�V����
	void Draw();		//�`�揈��

	void WaveInit();	//Wave�̏���������
	void WaveExe();		//Wave���s���̏���

	static CGame *Create();										//�|���S���̐���
	static CScore *GetScore();									//�X�R�A�̎擾
	static CPolygon *GetPolygon(int nCnt);						//�n�ʂ̗̑̓|���S����Ԃ�
	static CPlayerLifePolygon *GetPlayerLifePolygon(int nCnt);	//�v���C���[�̗̑̓|���S����Ԃ�

	void NextWave();
	void InitTexture();

	static GAMESTATE GetState();
	static WAVE GetWave();
private:
	static CScore *m_pScore;											//�X�R�A�̃|�C���^�ϐ�
	static CPolygon *m_pPolygon[MAX_LIFE];								//�n�ʂ̗̑̓|���S���|�C���^�z��
	static CPlayerLifePolygon *m_pLifePolygon[MAX_PLAYERLIFEPOLYGON];	//�v���C���[�̗̑̓|���S���|�C���^�z��
	static CWaveCount *m_WaveCount;

	static CEnemy *m_pSkyEnemy[MAX_SKYENEMY];			//�󒆓G�|�C���^�z��
	static CEnemy *m_pSky[MAX_SKY2];					//�󒆓G�|�C���^�z��
	static CEnemy *m_pGroundEnemy[MAX_GROUNDENEMY];		//�n�ʓG�|�C���^�z��

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_WAVECOUNT];	//�e�N�X�`���ւ̃|�C���^
	static CObject2D *m_pObject2D[MAX_WAVECOUNT];			//Object2D�̃|�C���^�ϐ�

	static GAMESTATE m_State;	//��ԕϐ�
	static WAVE m_Wave;			//�E�F�[�u�ϐ�

	int m_MaxSkyEnemy;		//�󒆓G����
	int m_MaxSky;
	int m_MaxGroundEnemy;	//�n�ʓG����

	static int m_nTime;
};
#endif