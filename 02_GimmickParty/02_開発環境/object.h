//=============================================================================
//
// object.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef OBJECT_H
#define OBJECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�O���錾
//=============================================================================
class CPlayer;

//=============================================================================
// �I�u�W�F�N�g�N���X
//=============================================================================
class CObject
{
public:

	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;			//xyz���W
		float rhw;					//rhw
		D3DCOLOR col;				//�J�[���[
		D3DXVECTOR2 tex;			//�e�N�X�`�����W
	};

	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;			//xyz���W
		D3DXVECTOR3 nor;			//�@��
		D3DCOLOR col;				//�J�[���[
		D3DXVECTOR2 tex;			//�e�N�X�`�����W
	};

	struct VERTEX_LINE
	{
		D3DXVECTOR3 pos;			//xyz���W
		D3DCOLOR col;				//�J�[���[
	};

	//�e�N�X�`���̎��
	enum TextType
	{
		TEXTURE_NULL = 0,

		TEXTURE_BLOCK,
		TEXTURE_SKY,
		TEXTURE_GRASS,
		TEXTURE_ROCK,
		TEXTURE_MAGMA,
		TEXTURE_SNOW,
		TEXTURE_SNOW_AREA,
		TEXTURE_CHARACTERS,
		TEXTURE_LETTERS,
		TEXTURE_NUMBERS,
		TEXTURE_JAPANESE,
		TEXTURE_CHARASET_FRAM,
		TEXTURE_MESSAGE_START,
		TEXTURE_MESSAGE_GOAL,
		TEXTURE_1P_WIN,
		TEXTURE_2P_WIN,
		TEXTURE_3P_WIN,
		TEXTURE_4P_WIN,
		TEXTURE_WINNER,
		TEXTURE_DRAW,
		TEXTURE_SELECT_FRAME,
		TEXTURE_LAVA,
		TEXTURE_ICE,
		TEXTURE_BACKGROUND,
		TEXTURE_PARTICLE_EFFECT,
		TEXTURE_STAGESEL01,
		TEXTURE_STAGESEL02,
		TEXTURE_STAGESEL03,
		TEXTURE_STAGESELR,
		TEXTURE_OK_UI,
		TEXTURE_TITLE_UI,
		TEXTURE_STAGE_SELECT_BG,
		TEXTURE_BUTTON_SELECT_UI,
		TEXTURE_TUTORIAL_MOVE,
		TEXTURE_TUTORIAL_BUTTON,
		TEXTURE_PLAYER_SEL_CTRL,

		TEXTURE_TYPE_MAX
	};

	static const int MaxObject = 5000;					//�I�u�W�F�N�g�̍ő吔

	CObject();											//�R���X�g���N�^
	CObject(int nPriority);								//�R���X�g���N�^ (1 <= priority <= 5)
	virtual~CObject();									//�f�X�g���N�^
														
	virtual HRESULT Init(void) = 0;						//����������
	virtual void Uninit(void) = 0;						//�I������
	virtual void Update(void) = 0;						//�X�V����
	virtual void Draw(void) = 0;						//�`�揈��
														
	virtual void SetPos(const D3DXVECTOR3 pos) = 0;		//�ʒu�̐ݒ菈��
	
	void Release(void);									//�C���X�^���X��̏I������
	virtual const D3DXVECTOR2 GetSize(void) = 0;		//�T�C�Y�̎擾����
	virtual const D3DXVECTOR3 GetPos(void) = 0;			//�ʒu�̎擾����
	void SetPriority(int nPriority);					//�v���C�I���e�B�̐ݒ菈��
														
	//�ÓI�֐�
	static void ReleaseAll(void);						//�S���̏I������
	static void UpdateAll(void);						//�S���̍X�V����
	static void DrawAll(void);							//�S���̕`�揈��
	static CObject** GetObj(void);						//�I�u�W�F�N�g�̎擾����

	static int random(const int low, const int high);				//������Ԃ�����

private:								

	static const int Max_Priority = 5;					//�v���C�I���e�B�̍ő�l
	int m_nIdx;											//���̃C���X�^���X�̔z��̃C���f�b�N�X
	int m_nPriority;									//�`�揇
	bool m_bDeath;										//���S�t���O

	static CObject* m_pTop[Max_Priority];				//�擪�̃I�u�W�F�N�g�ւ̃|�C��
	static CObject* m_pCurrent[Max_Priority];			//����(��Ԍ��)�̃I�u�W�F�N�g�ւ̃|���^
	CObject* m_pPrev;									//�O�̃I�u�W�F�N�g�ւ̃|���^
	CObject* m_pNext;									//���̃I�u�W�F�N�g�ւ̃|���^
};

#endif