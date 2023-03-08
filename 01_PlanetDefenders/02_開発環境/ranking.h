//--------------------------------
//
//�����L���O�w�b�_�[[ranking.h]
//Author:���c�喲
//
//--------------------------------
#ifndef _RANKING_H_						//���̃}�N����`������ĂȂ�������
#define _RANKING_H_						//��d�C���N���[�h�h�~�̃}�N����`

//---------------------------
//�C���N���[�h
//---------------------------
#include "mode.h"

//---------------------------
//�O���錾
//---------------------------
class CObject2D;
class CFade;
class CNumber;

//---------------------------
//�}�N����`
//---------------------------
#define MAX_RANKING		(8)		//�����L���O�̌���
#define MAX_RANKINGRANK	(5)		//�����L���O�̏��ʕ�
#define MAX_TEXTURE		(3)		//�e�N�X�`���̐�

//---------------------------
//�����L���O�N���X
//---------------------------
class CRanking : public CMode	
{
public:
	CRanking();		//�R���X�g���N�^
	~CRanking();	//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
	void Load(void);	//�t�@�C���ǂݍ��ݏ���
	void Save(void);	//�t�@�C�������o������
	static void SetRankingScore();			//�X�R�A�̐ݒ菈��
	static void GetRanking(int Ranking);	//�����L���O���̎擾

	static CRanking *Create();	//�����L���O�̐���

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE] = {};			//�e�N�X�`���ւ̃|�C���^
	CObject2D *m_pObject2D[3];									//Object2D�̃|�C���^�z��
	CFade *m_pFade;												//�t�F�[�h�̃|�C���^�ϐ�

	static CNumber *m_apNumber[MAX_RANKINGRANK][MAX_RANKING];	//Number�^�̔z��
	static int m_nRanking;
	static int aData[MAX_RANKINGRANK];
};
#endif