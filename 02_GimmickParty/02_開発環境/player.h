//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CModelPart;
class CAnimator;
class CCylinderHitbox;
class CScore;
class CUIString;
class CBoxHitbox;

class CPlayer : public CObject
{
public:

	enum Parts
	{
		BODY = 0,								//��
		HEAD,									//��
		LEFT_ARM,								//���r
		LEFT_HAND,								//����
		RIGHT_ARM,								//�E�r
		RIGHT_HAND,								//�E��
		LEFT_LEG,								//����
		LEFT_FOOT,								//������
		RIGHT_LEG,								//�E��
		RIGHT_FOOT,								//�E����
		PARTS_MAX
	};

	enum STATE
	{
		STATE_NEUTRAL = 0,						//�j���[�g����
		STATE_RUNNING,							//����
		STATE_JUMP,								//�W�����v
		STATE_PUNCH,							//�p���`
		STATE_DAMAGE,							//�_���[�W
		STATE_MAX								
	};

	enum PlayerColor
	{
		PLAYER_RED = 0,							//��
		PLAYER_GREEN,							//��
		PLAYER_BLUE,							//��
		PLAYER_YELLOW,							//��
		PLAYER_MAGENTA,							//�}�[���^
		PLAYER_CYAN,							//�V�A��
		PLAYER_BLACK,							//��
		PLAYER_WHITE,							//��

		PLAYER_COLOR_MAX
	};

	CPlayer();															//�R���X�g���N�^
	~CPlayer() override;												//�f�X�g���N�^

	HRESULT Init(void) override;										//����������
	void Uninit(void) override;											//�I������
	void Update(void) override;											//�X�V����
	void Draw(void) override;											//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override { m_pos = pos; }		//�ʒu�̐ݒ菈��
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }					//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override { return Vec2Null; }		//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override { return m_pos; }			//�ʒu�̎擾����

	D3DXVECTOR3 GetDestRot(void) { return m_DestRot; }					//�ړI�̊p�x�̎擾����

	static CPlayer* Create(const D3DXVECTOR3 pos,int nCntPlayer);		//��������
	static D3DXCOLOR* GetPlayerColors(void);							//�v���C���[�̐F�̎擾����

	void PlayerController(int nCntPlayer);								//�v���C���[�̃L�[����
	void SetPlayerIdx(int nCntPlayer);									//�v���C���[�ԍ��̐ݒ�
	void SetFriction(const float fFriction);

	void MoveWinner();													//���҂̈ړ�����
	void SetWinner(bool bWinner);										//���҂̐ݒ菈��
	void WinnerAnim();													//���҂̃A�j���[�V����
	void LoserAnim();													//�s�҂̃A�j���[�V����
	void PlayerRespawn();												//�v���C���[��������

	bool GetGoal() { return m_bGoal; }									//�S�[���̏�Ԏ擾
	bool GetRotCmp();													//�S�[����̉�]���̎擾

private:
	void GoalMove();													//�S�[����̓���

	static D3DXCOLOR m_playerColor[PLAYER_COLOR_MAX];					//�v���C���[�̐F
	static const float m_MaxWalkingSpeed;								//�ő�̕����X�s�[�h
	static const float m_AccelerationCoeff;								//�����W��
	static int m_nRanking;												//����

	D3DXVECTOR3 m_pos;													//�ʒu
	D3DXVECTOR3 m_move;													//���x
	D3DXVECTOR3 m_rot;													//����
	D3DXVECTOR3 m_DestRot;												//�ړI�̊p�x
	D3DXMATRIX  m_mtxWorld;												//���[���h�}�g���b�N�X
	int			m_nInvincibilityCnt;									//���G��Ԃ̃J�E���^�[
	int			m_nCntAttack;											//�U���J�E���^�[
	int			m_nPlayerRanking;										//�v���C���[�̏���
	int			m_nIdxPlayer;											//�v���C���[�ԍ�
	int			m_nFrame;												//�t���[����
	float		m_fFrictionCoeff;										//���C�W��
	float		m_fAngle;														
	bool		m_bJump;												//�W�����v���Ă��邩�ǂ���
	bool		m_bGoal;												//�S�[���������ǂ���
	bool		m_bMove;												//�����؂������ǂ���
	bool		m_bWinner;												//�����������ǂ���
	bool		m_bPos;													//�ʒu�ɂ������ǂ���
	bool		m_bRot;													//��]�������ǂ���
	bool		m_bHit;													//�����������ǂ���
	bool		m_bPunch;												//�p���`�������ǂ���
	bool		m_bAttacking;											//�A�^�b�N�������ǂ���
	bool		m_bDebug;												//�f�o�b�O����

	D3DXVECTOR3 m_TargetPos;											//�ڕW�̈ʒu
	D3DXVECTOR3 GoalPos;												//�S�[������̈ʒu
	STATE m_State;														//�v���C���[�̏��

	CModelPart* m_pModel[PARTS_MAX];									//���f���ւ̃|�C���^
	CAnimator* m_pAnimator;												//�A�j���[�^�[�ւ̃|�C���^
	CCylinderHitbox* m_pHitbox;											//�q�b�g�{�b�N�X
	CCylinderHitbox* m_pHeadHitbox;										//���̃q�b�g�{�b�N�X
	CBoxHitbox* m_pAttackHitbox;										//�U���q�b�g�{�b�N�X
	CScore* m_pScore;													//�X�R�A�̃|�C���^
	CUIString* m_pScoreUI;												//�X�R�AUI�̃|�C���^
};

#endif