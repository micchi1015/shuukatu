//=============================================================================
//
// player.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "player.h"
#include "inputKeyboard.h"
#include "inputPad.h"
#include "camera.h"
#include "application.h"
#include "debugProc.h"
#include "meshfield.h"
#include "modelPart.h"
#include "animator.h"
#include "CylinderHitbox.h"
#include "score.h"
#include "UIString.h"
#include "gamerace.h"
#include "stage.h"
#include "rendering.h"
#include "coin.h"
#include "playerModel.h"
#include "message.h"
#include "BoxHitbox.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================

int CPlayer::m_nRanking;								//�����L���O�ւ̃|�C���^
const float CPlayer::m_MaxWalkingSpeed = 7.0f;			//�ő�����X�s�[�h
const float CPlayer::m_AccelerationCoeff = 2.0f;		//�����W��

//�v���C���[�̐F

D3DXCOLOR CPlayer::m_playerColor[PLAYER_COLOR_MAX]
{

	{ 1.0f, 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f, 1.0f },
	{ 0.0f, 0.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f, 1.0f },
	{ 0.0f, 1.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f }
};

//�R���X�g���N�^
CPlayer::CPlayer() : CObject::CObject(1)
{
	//�����o�[�ϐ����N���A����
	m_move = Vec3Null;								//���x�̏���������
	m_DestRot = Vec3Null;							//�ړI�̊p�x�̏���������
	m_pAnimator = nullptr;							//�A�j���[�^�[�ւ̃|�C���^
	m_pHitbox = nullptr;							//�q�b�g�{�b�N�X�ւ̃|�C���^
	m_pScore = nullptr;								//�X�R�A�ւ̃|�C���^
	m_pScoreUI = nullptr;							//�X�R�AUI�ւ̃|�C���^
	m_rot = Vec3Null;								//����
	m_bGoal = false;								//�S�[���ɒ��������ǂ���
	m_bMove = false;								//�����Ă��邩�ǂ���
	m_bWinner = false;								//�������ǂ���
	m_bPos = false;									//�ʒu�ɂ������ǂ���
	m_bRot = false;									//��]�������ǂ���
	m_pAnimator = nullptr;							//�A�j���[�^�[�ւ̃|�C���^
	m_pHitbox = nullptr;							//�q�b�g�{�b�N�X�ւ̃|�C���^
	m_pScore = nullptr;								//�X�R�A�ւ̃|�C���^
	m_State = (STATE)0;								//�A�j���[�V�������
	m_pScoreUI = nullptr;							//�X�R�A��UI�ւ̃|�C���^
	m_bJump = false;								//�W�����v���Ă��邩�ǂ���
	m_nInvincibilityCnt = 0;						//���G��Ԃ̃J�E���^�[
	m_nFrame = 0;									//�t���[��
	m_pAttackHitbox = nullptr;						//�U���̃q�b�g�{�b�N�X
	m_pHeadHitbox = nullptr;						//���̃q�b�g�{�b�N�X
	m_bAttacking = false;							//�U�����Ă��邩�ǂ���
	m_nCntAttack = 0;								//�U���J�E���^�[
	m_fFrictionCoeff = 0.0f;						//���C�W��
	m_nPlayerRanking = 0;							//�v���C���[�̃����L���O
	m_nRanking = 0;									//�����L���O
	m_bDebug = false;								//�f�o�b�O����̏�����

#ifdef _DEBUG
	m_bDebug = true;								//�f�o�b�O���ɂ���
#endif // !DEBUG

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(void)
{
	//�����o�[�ϐ��̏���������
	m_move = Vec3Null;								//���x�̏���������
	m_DestRot = Vec3Null;							//�ړI�̊p�x�̏���������
	m_pAnimator = nullptr;							//�A�j���[�^�[�ւ̃|�C���^
	m_pHitbox = nullptr;							//�q�b�g�{�b�N�X�ւ̃|�C���^
	m_pScore = nullptr;								//�X�R�A�ւ̃|�C���^
	m_pScoreUI = nullptr;							//�X�R�AUI�ւ̃|�C���^
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);		//����
	m_bGoal = false;								//�S�[���ɒ��������ǂ���
	m_bMove = false;								//�����Ă��邩�ǂ���
	m_bWinner = false;								//�������ǂ���
	m_bPos = false;									//�ʒu�ɂ������ǂ���
	m_bRot = false;									//��]�������ǂ���
	m_pAnimator = nullptr;							//�A�j���[�^�[�ւ̃|�C���^
	m_pHitbox = nullptr;							//�q�b�g�{�b�N�X�ւ̃|�C���^
	m_pScore = nullptr;								//�X�R�A�ւ̃|�C���^
	m_State = STATE_NEUTRAL;						//�A�j���[�V�������
	m_pScoreUI = nullptr;							//�X�R�A��UI�ւ̃|�C���^
	m_bJump = false;								//�W�����v���Ă��邩�ǂ���
	m_nInvincibilityCnt = 0;						//���G��Ԃ̃J�E���^�[
	m_nFrame = 0;									//�t���[��
	m_pAttackHitbox = nullptr;						//�U���̃q�b�g�{�b�N�X
	m_pHeadHitbox = nullptr;						//���̃q�b�g�{�b�N�X
	m_bAttacking = false;							//�U�����Ă��邩�ǂ���
	m_nCntAttack = 0;								//�U���J�E���^�[
	m_fFrictionCoeff = 0.1f;						//���C�W��
	m_nPlayerRanking = 0;							//�v���C���[�̃����L���O
	m_nRanking = 0;									//�����L���O

	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CPlayer::Uninit(void)
{
	//���f���p�[�c�̏I������
	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Uninit();
			delete m_pModel[nCnt];
			m_pModel[nCnt] = nullptr;
		}
	}

	//�A�j���[�^�[�̔j������
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Uninit();
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	//�X�R�A�̔j������
	if (m_pScore != nullptr)
	{
		m_pScore->Clear();
		m_pScore = nullptr;
	}
	//�X�R�A��UI�̔j������
	if (m_pScoreUI != nullptr)
	{
		m_pScoreUI->Uninit();
		m_pScoreUI = nullptr;
	}
	//���̃q�b�g�{�b�N�X�̔j������
	if (m_pHeadHitbox != nullptr)
	{
		m_pHeadHitbox->Release();
		m_pHeadHitbox = nullptr;
	}
	//�U���̃q�b�g�{�b�N�X�̔j������
	if (m_pAttackHitbox != nullptr)
	{
		m_pAttackHitbox->Release();
		m_pAttackHitbox = nullptr;
	}
}

//�X�V����
void CPlayer::Update(void)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//�J�����̌����̎擾����

	//�v���C���[�̖ړI�p�x�̐��K������
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
	float fA = acosf(cR.x);

	if (cR.z < 0.0f)
	{
		fA *= -1.0f;
	}

	//�Q�[�����n�܂�����ƃS�[�����ĂȂ��Ƃ�
	if (!m_bGoal && CMessage::GetStart())
	{
		//�v���C���[�̑���
		PlayerController(m_nIdxPlayer);
	}

	//�ʒu�̍X�V
	m_pos += m_move;				
	CDebugProc::Print("\n%f %f %f", m_move.x, m_move.y, m_move.z);
	
	m_move.x += (0.0f - m_move.x) * m_fFrictionCoeff;		//�ړ��ʂ�X�R���|�l���g�̍X�V
	m_move.y += (0.0f - m_move.y) * 0.1f;					//�ړ��ʂ�Y�R���|�l���g�̍X�V
	m_move.z += (0.0f - m_move.z) * m_fFrictionCoeff;		//�ړ��ʂ�Z�R���|�l���g�̍X�V

	//���X�|�[������
	PlayerRespawn();

	//�ړI�̊p�x�̐��K������
	if (m_DestRot.y - (m_pModel[BODY]->GetRot().y) > D3DX_PI)
	{
		m_DestRot.y -= 2 * D3DX_PI;
	}
	else if (m_DestRot.y - (m_pModel[BODY]->GetRot().y) < -D3DX_PI)
	{
		m_DestRot.y += 2 * D3DX_PI;
	}

	//��]�p�x�̌v�Z
	D3DXVECTOR3 rot = m_pModel[BODY]->GetRot() + ((m_DestRot - m_pModel[BODY]->GetRot()) * 0.1f);		

	//��]�p�x�̐ݒ菈��
	m_pModel[BODY]->SetRot(rot);		

	//��]�p�x�̐��K������
	float fRot = m_pModel[BODY]->GetRot().y;

	if (fRot > D3DX_PI)
	{
		fRot = -D3DX_PI + (fRot - D3DX_PI);
	}
	else if (fRot < -D3DX_PI)
	{
		fRot = D3DX_PI - (D3DX_PI + fRot);
	}

	if (fRot < D3DX_PI * -2.0f)
	{
		fRot += D3DX_PI * 2.0f;
	}
	else if (fRot > D3DX_PI * 2.0f)
	{
		fRot += D3DX_PI * -2.0f;
	}

	//��]�̐ݒ菈��
	m_pModel[BODY]->SetRot(D3DXVECTOR3(m_pModel[BODY]->GetRot().x, fRot, m_pModel[BODY]->GetRot().z));

	//�d�ʂ�ǉ�����
	if (m_move.y >= -10.0f)
	{
		m_move.y -= 0.65f;
	}

	float fHeight = 0.0f;

	//���b�V���t�B�[���h�Ƃ̓����蔻��
	CMeshfield* pField = CMeshfield::FieldInteraction(this, &fHeight);

	//�n�ʂƂ̓����蔻��
	if (pField != nullptr)
	{
		m_bJump = false;		//���n���Ă����Ԃɂ���
		m_bHit = false;			//�������ĂȂ���Ԃɂ���
		//���C�W���̎擾
		m_fFrictionCoeff = pField->GetFriction();

		//�e�̍����̐ݒ�
		for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
		{
			if (m_pModel[nCnt] != nullptr)
			{
				m_pModel[nCnt]->SetShadowHeight(fHeight);		
			}
		}
	}
	else if (m_pos.x < -135.0f || m_pos.x > 125.0f)
	{//���b�V���t�B�[���h���痣�ꂽ��
		//�e�̍��������Ȃ��悤�ɐݒ肷��
		for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
		{
			if (m_pModel[nCnt] != nullptr)
			{
				m_pModel[nCnt]->SetShadowHeight(-5000.0f);
			}
		}
	}

	if (m_pAnimator != nullptr)
	{
		//�A�j���[�V�����̍X�V
		m_pAnimator->Update();
	}

	//�J�����̏��̎擾
	CCamera* pCamera = CApplication::GetCamera();

	if (pCamera != nullptr)
	{
		//�J������Pos�̎擾
		D3DXVECTOR3 wallPos = pCamera->GetPos();
		wallPos.z += 160.0f;

		if (m_pos.z <= wallPos.z)
		{//�J�����̑O�ɉ����o��
			m_pos.z = wallPos.z;
		}
		else if (m_pos.z >= wallPos.z + 250.0f)
		{//�J�����̈����O�ɏo�Ȃ�
			m_pos.z = wallPos.z + 250.0f;
		}

		// �v���C���[�ő吔���̃C���X�^���X���쐬
		CPlayer* pPlayer[PLAYER_MAX];

		// �e�v���C���[�̃|�C���^���擾���A�e�C���X�^���X�ɑ��
		for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
		{
			pPlayer[nCnt] = CStage::GetPlayer(nCnt);
		}

		//�S�[��������
		if (m_pos.z >= 900.0f && m_bGoal == false)
		{
			m_bGoal = true;
			//���ʕt��
			m_nRanking++;
			m_nPlayerRanking = m_nRanking;
			//���ʂɂ���ăX�R�A�̉��Z
			if (m_pScore != nullptr)
			{
				if (m_nPlayerRanking == 1)
				{
					m_pScore->AddScore(100);
				}
				else if (m_nPlayerRanking == 2)
				{
					m_pScore->AddScore(50);
				}
				else if (m_nPlayerRanking == 3)
				{
					m_pScore->AddScore(15);
				}
				else if (m_nPlayerRanking == 4)
				{
					m_pScore->AddScore(5);
				}
			}
		}

		//�S�[����̓���
		GoalMove();

		//���G����
		if (m_nInvincibilityCnt > 0)
		{
			m_nInvincibilityCnt--;			//�J�E���^�[�̍X�V

			if (m_nInvincibilityCnt <= 0)
			{//0�ɂȂ�����A
				if (m_pHitbox != nullptr)
				{//�q�b�g�{�b�N�X��null�ł͂Ȃ�������
					m_pHitbox->SetInvincibility(false);			//���G��Ԃ��I���悤�ɐݒ肷��
				}
			}
		}

		if (m_pHitbox != nullptr)
		{
			//�X�R�A�̎擾
			int nScore = m_pScore->GetScore();

			//�����蔻��̍X�V
			m_pHitbox->SetPos(m_pos);
			m_pHitbox->Update();

			//�����蔻��̃G�t�F�N�g���擾
			CHitbox::INTERACTION_EFFECT effect = m_pHitbox->GetEffect();

			switch (effect)
			{

			case CHitbox::EFFECT_DAMAGE:
			
			{//���ʂ̃_���[�W���󂯂��ꍇ

				int spawnCoin = (int)((nScore - m_pScore->GetScore()) * 0.1f);			//�X�|�[���R�C�������v�Z����

				for (int nCnt = 0; nCnt < spawnCoin; nCnt++)
				{//�R�C���𗎂Ƃ�����
					CCoin::Create(GetPos(), D3DXVECTOR3((float)random(-5, 5), 10.0f, (float)random(-5, 5)), 180, CCoin::COIN_0);
				}

				m_nInvincibilityCnt = 60;												//���G��ԃJ�E���^�[��ݒ肷��
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);			//�_���[�W�T�E���h���Đ�����

				if (m_pHitbox != nullptr)
				{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);		//�G�t�F�N�g��߂�
					m_pHitbox->SetInvincibility(true);				//���G��Ԃ�ݒ肷��
				}
			}

			break;

			case CHitbox::EFFECT_LAUNCH:

			{//�m�b�N�o�b�N
				m_bHit = true;								//�_���[�W�t���O��true�ɂ���
				m_pAnimator->SetPresentAnim(4);				//���݂̃A�j���[�V�������_���[�W�A�j���[�V�����ɂ���

				int spawnCoin = (int)((nScore - m_pScore->GetScore()) * 0.1f);		//�X�|�[���R�C�������v�Z����

				for (int nCnt = 0; nCnt < spawnCoin; nCnt++)
				{//�R�C���𗎂Ƃ�����
					CCoin::Create(GetPos(), D3DXVECTOR3((float)random(-5, 5), 10.0f, (float)random(-5, 5)), 180, CCoin::COIN_0);
				}

				//�m�b�N�o�b�N�̏���(�V�������x�̐ݒ�)
				D3DXVec3Normalize(&m_move, &m_move);
				m_move.x *= -50.0f;
				m_move.y = 10.0f;
				m_move.z *= -50.f;
						
				m_nInvincibilityCnt = 60;												//���G��ԃJ�E���^�[��ݒ肷��
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);			//�_���[�W�T�E���h���Đ�����

				if (m_pHitbox != nullptr)
				{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);				//�G�t�F�N�g��߂�
					m_pHitbox->SetInvincibility(true);						//���G��Ԃ�ݒ肷��
				}
			}

			break;

			case CHitbox::EFFECT_PUSH:

			{//�����ꂽ�G�t�F�N�g
				m_bHit = true;								//�_���[�W�t���O��true�ɂ���
				m_pAnimator->SetPresentAnim(4);				//���݂̃A�j���[�V�������_���[�W�A�j���[�V�����ɂ���

				//�m�b�N�o�b�N�̏���(�V�������x�̐ݒ�)
				m_move = m_pHitbox->GetDirection();
				D3DXVec3Normalize(&m_move, &m_move);
				m_move.x *= 5.0f;
				m_move.y = 10.0f;
				m_move.z *= 5.f;

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE_PUNCH);		//�_���[�W�T�E���h���Đ�����

				if (m_pHitbox != nullptr)
				{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);					//�G�t�F�N�g��߂�
					m_pHitbox->SetDirection(Vec3Null);							//���G��Ԃ�ݒ肷��
				}
			}

				break;

			case CHitbox::EFFECT_BOUNCE:

			{//���˕Ԃ�G�t�F�N�g
				m_bHit = true;								//�_���[�W�t���O��true�ɂ���
				m_pAnimator->SetPresentAnim(4);				//���݂̃A�j���[�V�������_���[�W�A�j���[�V�����ɂ���

				//�m�b�N�o�b�N�̏���(�V�������x�̐ݒ�)
				D3DXVec3Normalize(&m_move, &m_move);
				m_move.x *= -50.0f;
				m_move.y = 10.0f;
				m_move.z *= -50.f;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE_PUNCH);			//�_���[�W�T�E���h���Đ�����

				if (m_pHitbox != nullptr)
				{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);					//�G�t�F�N�g��߂�
					m_pHitbox->SetDirection(Vec3Null);							//���G��Ԃ�ݒ肷��
				}
			}

			break;

			case CHitbox::EFFECT_JUMP:

			{//�W�����v�G�t�F�N�g
				m_bHit = true;							//�_���[�W�t���O��true�ɂ���
				m_bJump = true;							//�W�����v�t���O��true�ɂ���
				m_pAnimator->SetPresentAnim(4);			//���݂̃A�j���[�V�������_���[�W�A�j���[�V�����ɂ���

														//�m�b�N�o�b�N�̏���(�V�������x�̐ݒ�)
				D3DXVec3Normalize(&m_move, &m_move);
				m_move.y = 30.0f;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);			//�_���[�W�T�E���h���Đ�����

				if (m_pHitbox != nullptr)
				{//�q�b�g�{�b�N�X�̃|�C���^��null�ł͂Ȃ�������
					m_pHitbox->SetEffect(CHitbox::EFFECT_MAX);					//�G�t�F�N�g��߂�
					m_pHitbox->SetDirection(Vec3Null);							//���G��Ԃ�ݒ肷��
				}
			}

			break;

			default:
				break;
			}
		}
		if (m_nCntAttack > 0)
		{//�U������������A
			m_nCntAttack--;				//�U���J�E���^�[���X�V����

			if (m_nCntAttack == 15 && m_pAttackHitbox == nullptr)
			{//�U���A�j���V�������n�܂�����A�U���̃q�b�g�{�b�N�X��null��������A

				//�X�|�[���̈ʒu���v�Z����
				D3DXVECTOR3 Rot = Vec3Null;

				if (m_pModel[0] != nullptr)
				{
					Rot = m_pModel[0]->GetRot();
				}
				D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 20.0f, 20.0f);
				D3DXMATRIX mtxOut ,mtxTrans ,mtxRot;
				D3DXMatrixIdentity(&mtxOut);
				D3DXMatrixRotationYawPitchRoll(&mtxRot, Rot.y, 0.0f, 0.0f);
				D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);
				D3DXVec3TransformCoord(&dir, &dir, &mtxOut);

				//�q�b�g�{�b�N�X�̐���
				m_pAttackHitbox = CBoxHitbox::Create(dir + m_pos, Vec3Null, D3DXVECTOR3(17.0f, 14.0f, 17.0f), CHitbox::TYPE_OBSTACLE, this, 0, CHitbox::EFFECT_PUSH);
				
				if (m_pAttackHitbox != nullptr)
				{//�����o������
					dir.y = 0.0f;
					D3DXVec3Normalize(&dir, &dir);
					m_pAttackHitbox->SetDirection(dir);		//�����̐ݒ�
				}
			}

			if (m_nCntAttack <= 0)
			{//�J�E���^�[��0�ȉ��ɂȂ�����
				m_pAttackHitbox->Release();			//�q�b�g�{�b�N�X��j������
				m_pAttackHitbox = nullptr;			//�|�C���^��null�ɂ���
				m_nCntAttack = 0;					//�J�E���^�[��0�ɖ߂�
				m_bAttacking = false;				//�U���t���O��false�ɂ���
			}
		}
		if (m_pHeadHitbox != nullptr)
		{//���̃q�b�g�{�b�N�X��null�ł͂Ȃ�������
			m_pHeadHitbox->SetPos(m_pos);			//�ʒu�̍X�V
			m_pHeadHitbox->Update();				//�X�V����
		}
		
		CPlayer *m_pPlayer[PLAYER_MAX] = {};

		for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
		{
			m_pPlayer[nCnt] = CStage::GetPlayer(nCnt);
		}

		//�S�����U������I�������
		if (m_pPlayer[0]->m_bRot &&m_pPlayer[1]->m_bRot &&m_pPlayer[2]->m_bRot &&m_pPlayer[3]->m_bRot)
		{
			//�J�������ړ�����
			pCamera->SetPos(D3DXVECTOR3(pCamera->GetPos().x, -80.0f, 800.0f), pCamera->GetPos());

			m_nFrame++;

			if (m_nFrame >= 60)
			{
				//���҂��O�ɏo��
				MoveWinner();
			}
		}

		if (m_pScoreUI != nullptr && m_pScore != nullptr)
		{//�X�R�AUI�̍X�V����

			//�X�R�A���擾���āA4���̕�����ɕϊ�����
			int nScore = m_pScore->GetScore();
			std::string str = std::to_string(nScore);
			std::string begin = {};

			if (str.size() < 4)
			{
				for (int nCnt = 0; nCnt < 4 - (int)str.size(); nCnt++)
				{
					begin += '0';
				}

				begin += str;
			}
			else
			{
				begin = str;
			}

			const char* pStr = begin.c_str();
			m_pScoreUI->ChangeString(pStr);				//UI�̕�����̐ݒ�
		}
	}

	//�f�o�b�O�p�̕�����
	CDebugProc::Print("\nRot: %f\nRot Dest: %f\n\nPos: %f, %f, %f", m_pModel[BODY]->GetRot().y, m_DestRot.y, m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("\nPlayer %d score: %d", m_nIdxPlayer, m_pScore->GetScore());
}

//�`�揈��
void CPlayer::Draw(void)
{
	if (m_nInvincibilityCnt % 10 <= 5)
	{//���G��Ԃ�������A�_�ł�����

		D3DXMATRIX mtxTrans, mtxRot;												//�v�Z�p�̃}�g���b�N�X
		D3DXMatrixIdentity(&m_mtxWorld);											//���[���h�}�g���b�N�X�̏���������

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		m_pModel[BODY]->Draw(m_mtxWorld);											//�ŏ��̃��f���̕`�揈��

		for (int nCnt = 1; nCnt < PARTS_MAX; nCnt++)
		{//���̃��f���̕`�揈��
			if (m_pModel[nCnt] != nullptr)
			{
				m_pModel[nCnt]->Draw();
			}
		}
	}
}

//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================

//��������
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, int nCntPlayer)
{
	CPlayer* pModel = new CPlayer;		//�C���X�^���X�𐶐�����

	//�v���C���[�̏���������
	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	CModel::ModelType pType = CPlayerModel::GetHeadType(nCntPlayer);			//�I�����ꂽ���̎�ނ̎擾

	pModel->m_pos = pos;																									//�ʒu�̐ݒ�
	pModel->m_pModel[BODY] = CModelPart::Create(CModel::MODEL_BODY, D3DXVECTOR3(0.0f, 17.0f, 0.0f), Vec3Null);				//�̂̃��f���𐶐�����

	pModel->m_pModel[HEAD] = CModelPart::Create(pType, D3DXVECTOR3(0.0f, 7.0f, 0.0f), Vec3Null);							//���̃��f���𐶐�����
	pModel->m_pModel[HEAD]->SetParent(pModel->m_pModel[BODY]);																//���̐e��ݒ肷��

	pModel->m_pModel[LEFT_ARM] = CModelPart::Create(CModel::MODEL_LEFT_ARM, D3DXVECTOR3(8.0f, 3.0f, 0.0f), Vec3Null);		//���r�̃��f���𐶐�����
	pModel->m_pModel[LEFT_ARM]->SetParent(pModel->m_pModel[BODY]);															//���r�̐e��ݒ肷��

	pModel->m_pModel[LEFT_HAND] = CModelPart::Create(CModel::MODEL_LEFT_HAND, D3DXVECTOR3(9.0f, 0.0f, 0.0f), Vec3Null);		//����̃��f���𐶐�����
	pModel->m_pModel[LEFT_HAND]->SetParent(pModel->m_pModel[LEFT_ARM]);														//����̐e��ݒ肷��

	pModel->m_pModel[RIGHT_ARM] = CModelPart::Create(CModel::MODEL_RIGHT_ARM, D3DXVECTOR3(-8.0f, 3.0f, 0.0f), Vec3Null);	//�E�r�̃��f���𐶐�����
	pModel->m_pModel[RIGHT_ARM]->SetParent(pModel->m_pModel[BODY]);															//�E�r�̐e��ݒ肷��

	pModel->m_pModel[RIGHT_HAND] = CModelPart::Create(CModel::MODEL_RIGHT_HAND, D3DXVECTOR3(-9.0f, 0.0f, 0.0f), Vec3Null);	//�E��̃��f���𐶐�����
	pModel->m_pModel[RIGHT_HAND]->SetParent(pModel->m_pModel[RIGHT_ARM]);													//�E��̐e��ݒ肷��

	pModel->m_pModel[LEFT_LEG] = CModelPart::Create(CModel::MODEL_LEFT_LEG, D3DXVECTOR3(3.0f, -9.0f, 0.0f), Vec3Null);		//�����ڂ̃��f���𐶐�����
	pModel->m_pModel[LEFT_LEG]->SetParent(pModel->m_pModel[BODY]);															//�����ڂ̐e��ݒ肷��

	pModel->m_pModel[LEFT_FOOT] = CModelPart::Create(CModel::MODEL_LEFT_FOOT, D3DXVECTOR3(0.1f, -5.0f, 0.0f), Vec3Null);	//�����̃��f���𐶐�����
	pModel->m_pModel[LEFT_FOOT]->SetParent(pModel->m_pModel[LEFT_LEG]);														//�����̐e��ݒ肷��

	pModel->m_pModel[RIGHT_LEG] = CModelPart::Create(CModel::MODEL_RIGHT_LEG, D3DXVECTOR3(-3.0f, -9.0f, 0.0f), Vec3Null);	//�E���ڂ̃��f���𐶐�����
	pModel->m_pModel[RIGHT_LEG]->SetParent(pModel->m_pModel[BODY]);															//�E���ڂ̐e��ݒ肷��

	pModel->m_pModel[RIGHT_FOOT] = CModelPart::Create(CModel::MODEL_RIGHT_FOOT, D3DXVECTOR3(-0.1f, -5.0f, 0.0f), Vec3Null);//�E���̃��f���𐶐�����
	pModel->m_pModel[RIGHT_FOOT]->SetParent(pModel->m_pModel[RIGHT_LEG]);													//�E���̐e��ݒ肷��

	//�����������f�����A�j���[�^�[�ɑ������
	std::vector <CModelPart*> vParts;
	vParts.clear();
	vParts.push_back(pModel->m_pModel[BODY]);
	vParts.push_back(pModel->m_pModel[HEAD]);
	vParts.push_back(pModel->m_pModel[LEFT_ARM]);
	vParts.push_back(pModel->m_pModel[LEFT_HAND]);
	vParts.push_back(pModel->m_pModel[RIGHT_ARM]);
	vParts.push_back(pModel->m_pModel[RIGHT_HAND]);
	vParts.push_back(pModel->m_pModel[LEFT_LEG]);
	vParts.push_back(pModel->m_pModel[LEFT_FOOT]);
	vParts.push_back(pModel->m_pModel[RIGHT_LEG]);
	vParts.push_back(pModel->m_pModel[RIGHT_FOOT]);

	pModel->m_pAnimator = CAnimator::Create(&vParts, CAnimator::ANIM_TYPE_PLAYER);

	//�q�b�g�{�b�N�X�̐���
	pModel->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(10.0f, 35.0f, 10.0f), CHitbox::TYPE_PLAYER, pModel, nCntPlayer);
	pModel->m_pHeadHitbox = CCylinderHitbox::Create(pos, D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXVECTOR3(1.0f, 2.0f, 1.0f), CHitbox::TYPE_PLAYER, pModel);

	//�v���C���[�̃C���f�b�N�X
	pModel->SetPlayerIdx(nCntPlayer);

	//�X�R�A�̐���
	pModel->m_pScore = CScore::Create(nCntPlayer);

	D3DXCOLOR UIcol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);				//UI�F�̐ݒ�

	//�I�����ꂽ�F�̎擾�Ɛݒ�
	D3DXCOLOR col = CPlayerModel::GetPlayerColors()[nCntPlayer];		

	pModel->m_pModel[BODY]->SetModelColor(2, col);
	UIcol = col;

	D3DXVECTOR3 fieldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���[�h�Ŏ擾���郁�b�V���t�B�[���h�𕪂���
	fieldPos = CGameRace::GetStage()->GetField()->GetPos();

	pModel->m_TargetPos = D3DXVECTOR3(-75.0f + (50.0f * (nCntPlayer)), -150.0f, fieldPos.z - 100.0f);

	//UI�̐���
	pModel->m_pScoreUI = CUIString::Create(D3DXVECTOR3(100.0f + (320.0f * nCntPlayer), SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR2(150.0f, 50.0f), UIcol, "0000", 5);
	
	return pModel;					//���������C���X�^���X��Ԃ�
}

//�v���C���[�̐F�̎擾����
D3DXCOLOR* CPlayer::GetPlayerColors(void)
{
	return m_playerColor;
}

//�v���C���[�̃L�[����
void CPlayer::PlayerController(int nCntPlayer)
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();					//�J�����̌����̎擾����
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
	float fA = acosf(cR.x);

	if (!m_bDebug && m_nIdxPlayer == 0)
	{// �f�o�b�O���ł͂Ȃ��ꍇ & �v���C���[�ԍ���0�̏ꍇ
		if (!m_bAttacking)
		{
			//�ړ��ʂƖړI�̊p�x�̌v�Z
			if (CInputKeyboard::GetKeyboardPress(DIK_W))
			{//W�L�[�������ꂽ�ꍇ
				if (CInputKeyboard::GetKeyboardPress(DIK_A))
				{//A�L�[�������ꂽ�ꍇ
					if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
					{
						m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
					}
					if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
					{
						m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
					}

					m_DestRot.y = -D3DX_PI * 0.75f + fA;
				}
				else if (CInputKeyboard::GetKeyboardPress(DIK_D))
				{//D�L�[�������ꂽ�ꍇ
					if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
					{
						m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
					}
					if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
					{
						m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
					}

					m_DestRot.y = -D3DX_PI * 0.25f + fA;
				}
				else
				{//W�L�[�����������ꂽ�ꍇ
					if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
					{
						m_move.x += m_AccelerationCoeff * cosf(cameraRot.y) * (m_fFrictionCoeff);
					}
					if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
					{
						m_move.z += m_AccelerationCoeff * sinf(cameraRot.y) * (m_fFrictionCoeff);
					}

					m_DestRot.y = -D3DX_PI * 0.5f + fA;
				}
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_S))
			{//S�L�[�������ꂽ�ꍇ
				if (CInputKeyboard::GetKeyboardPress(DIK_A))
				{//A�L�[�������ꂽ�ꍇ
					if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
					{
						m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
					}
					if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
					{
						m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
					}

					m_DestRot.y = D3DX_PI * 0.75f + fA;
				}
				else if (CInputKeyboard::GetKeyboardPress(DIK_D))
				{//D�L�[�������ꂽ�ꍇ
					if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
					{
						m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
					}
					if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
					{
						m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
					}

					m_DestRot.y = D3DX_PI * 0.25f + fA;
				}
				else
				{//S�L�[�����������ꂽ�ꍇ
					if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
					{
						m_move.x += m_AccelerationCoeff * cosf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
					}
					if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
					{
						m_move.z += m_AccelerationCoeff * sinf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
					}

					m_DestRot.y = D3DX_PI * 0.5f + fA;
				}
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_D))
			{//D�L�[���������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = fA;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_A))
			{//A�L�[���������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
				}
				m_DestRot.y = D3DX_PI + fA;
			}
		}

		//SPACE�L�[�������ꂽ�ꍇ
		if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) && !m_bJump && !m_bAttacking && m_move.y < 0.0f)
		{//�W�����v
			m_move.y = 18.0f;
			m_bJump = true;
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
			m_pAnimator->SetPresentAnim(2);
		}

		//�ړ��L�[��������Ă��鎞
		if (CInputKeyboard::GetKeyboardPress(DIK_W) || CInputKeyboard::GetKeyboardPress(DIK_S) || CInputKeyboard::GetKeyboardPress(DIK_A) || CInputKeyboard::GetKeyboardPress(DIK_D))
		{
			if (!m_bJump && !m_bHit && !m_bAttacking)
			{
				m_pAnimator->SetLoopingAnim(1);
			}
		}

		//�U���L�[��������Ă��鎞
		if (CInputKeyboard::GetKeyboardTrigger(DIK_V) && !m_bJump && !m_bHit && !m_bAttacking)
		{
			m_pAnimator->SetPresentAnim(3);

			m_bAttacking = true;
			m_nCntAttack = 19;

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_PUNCH);
		}
	}

#ifdef _DEBUG
	if (!m_bAttacking)
	{
		//�ړ��ʂƖړI�̊p�x�̌v�Z
		if (CInputKeyboard::GetKeyboardPress(DIK_W))
		{//W�L�[�������ꂽ�ꍇ
			if (CInputKeyboard::GetKeyboardPress(DIK_A))
			{//A�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.75f + fA;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_D))
			{//D�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.25f + fA;
			}
			else
			{//W�L�[�����������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.5f + fA;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_S))
		{//S�L�[�������ꂽ�ꍇ
			if (CInputKeyboard::GetKeyboardPress(DIK_A))
			{//A�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.75f + fA;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_D))
			{//D�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.25f + fA;
			}
			else
			{//S�L�[�����������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.5f + fA;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D))
		{//D�L�[���������ꂽ�ꍇ
			if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
			{
				m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
			{
				m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}

			m_DestRot.y = fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_A))
		{//A�L�[���������ꂽ�ꍇ
			if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
			{
				m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
			{
				m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			m_DestRot.y = D3DX_PI + fA;
		}
	}

	//SPACE�L�[�������ꂽ�ꍇ
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) && !m_bJump && !m_bAttacking && m_move.y < 0.0f)
	{//�W�����v
		m_move.y = 18.0f;
 		m_bJump = true;
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		m_pAnimator->SetPresentAnim(2);
	}

	//�ړ��L�[��������Ă��鎞
	if (CInputKeyboard::GetKeyboardPress(DIK_W) || CInputKeyboard::GetKeyboardPress(DIK_S) || CInputKeyboard::GetKeyboardPress(DIK_A) || CInputKeyboard::GetKeyboardPress(DIK_D))
	{
		if (!m_bJump && !m_bHit && !m_bAttacking)
		{
			m_pAnimator->SetLoopingAnim(1);
		}
	}

	//�U���L�[��������Ă��鎞
	if (CInputKeyboard::GetKeyboardTrigger(DIK_V) &&  !m_bJump && !m_bHit && !m_bAttacking)
	{
		m_pAnimator->SetPresentAnim(3);

		m_bAttacking = true;
		m_nCntAttack = 19;

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_PUNCH);
	}
#endif // !DEBUG
	if (!m_bAttacking)
	{
		//�ړ��ʂƖړI�̊p�x�̌v�Z
		if (CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y < -0.3f)
		{//W�L�[�������ꂽ�ꍇ
			if ( CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x < -0.3f)
			{//A�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.75f + fA;
			}
			else if ( CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x > 0.3f)
			{//D�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.25f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.25f + fA;
			}
			else
			{//W�L�[�����������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = -D3DX_PI * 0.5f + fA;
			}
		}
		else if (CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y > 0.3f)
		{//S�L�[�������ꂽ�ꍇ
			if (CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x < -0.3f)
			{//A�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.75f + fA;
			}
			else if (CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x > 0.5f)
			{//D�L�[�������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.75f + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.25f + fA;
			}
			else
			{//S�L�[�����������ꂽ�ꍇ
				if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
				{
					m_move.x += m_AccelerationCoeff * cosf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
				}
				if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
				{
					m_move.z += m_AccelerationCoeff * sinf(D3DX_PI + cameraRot.y) * (m_fFrictionCoeff);
				}

				m_DestRot.y = D3DX_PI * 0.5f + fA;
			}
		}
		else if (CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x > 0.3f)
		{//D�L�[���������ꂽ�ꍇ
			if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
			{
				m_move.x += m_AccelerationCoeff * cosf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
			{
				m_move.z += m_AccelerationCoeff * sinf(-D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}

			m_DestRot.y = fA;
		}
		else if (CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x < -0.3f)
		{//A�L�[���������ꂽ�ꍇ
			if (m_move.x <= m_MaxWalkingSpeed && m_move.x >= -m_MaxWalkingSpeed)
			{
				m_move.x += m_AccelerationCoeff * cosf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			if (m_move.z <= m_MaxWalkingSpeed && m_move.z >= -m_MaxWalkingSpeed)
			{
				m_move.z += m_AccelerationCoeff * sinf(D3DX_PI * 0.5f + cameraRot.y) * (m_fFrictionCoeff);
			}
			m_DestRot.y = D3DX_PI + fA;
		}
	}

	//�p�b�h��A�{�^���������ꂽ��
	if (CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_A, nCntPlayer) && !m_bJump && !m_bAttacking && m_move.y < 0.0f)
	{//�W�����v
		m_move.y = 18.0f;
		m_bJump = true;
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
		m_pAnimator->SetPresentAnim(2);
	}

	//�p�b�h�̃X�e�B�b�N�����͂���Ă��鎞
	if (CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  < -0.3f || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).x  > 0.3f
		|| CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  < -0.3f || CInputPad::GetJoypadStick(CInputPad::JOYKEY_LEFT_STICK, nCntPlayer).y  > 0.3f)
	{
		if (!m_bJump && !m_bHit && !m_bAttacking)
		{
			m_pAnimator->SetLoopingAnim(1);
		}
	}

	//�p�b�h��B�{�^����������Ă��鎞
	if (CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, nCntPlayer) && !m_bJump && !m_bHit && !m_bAttacking)
	{
		m_pAnimator->SetPresentAnim(3);

		m_bAttacking = true;
		m_nCntAttack = 19;

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_PUNCH);
	}
}

//�v���C���[�ԍ��ݒ菈��
void CPlayer::SetPlayerIdx(int nCntPlayer)
{
	m_nIdxPlayer = nCntPlayer;
}

void CPlayer::SetFriction(const float fFriction)
{
	m_fFrictionCoeff = fFriction;
}

//�U������擾����
bool CPlayer::GetRotCmp()
{
	return m_bRot;
}

//=====================================
// ���҂̈ړ�����
//=====================================
void CPlayer::MoveWinner()
{
	if (m_bWinner && GetRotCmp())
	{
		if (!m_bPos)
		{
			GoalPos = m_pos - D3DXVECTOR3(0.0f, 0.0f, 50.0f);
			m_bPos = true;
		}

		m_fAngle = sqrtf((float)(pow(GoalPos.x - m_pos.x, 2) + pow(GoalPos.z - m_pos.z, 2)));
		m_move.x = (GoalPos.x - m_pos.x) / (m_fAngle / 1.0f);
		m_move.z = (GoalPos.z - m_pos.z) / (m_fAngle / 1.0f);

		if (m_pos.z <= GoalPos.z)
		{
			m_move = Vec3Null;
			m_bMove = true;
		}

		WinnerAnim();
	}
	else if(GetRotCmp())
	{
		LoserAnim();
	}
}

//���Ґݒ菈��
void CPlayer::SetWinner(bool bWinner)
{
	m_bWinner = bWinner;
}

//���҃A�j���[�V��������
void CPlayer::WinnerAnim()
{
	m_pAnimator->SetPresentAnim(5);
}

//�s�҃A�j���[�V��������
void CPlayer::LoserAnim()
{
	m_pAnimator->SetPresentAnim(6);
}

//��������
void CPlayer::PlayerRespawn()
{
	if (m_pos.y <= -500.0f)
	{
		D3DXVECTOR3 posCamera = CApplication::GetCamera()->GetPos();
		m_pos = D3DXVECTOR3(posCamera.x, posCamera.y + 100.0f, posCamera.z + 100.0f);
		m_fFrictionCoeff = 0.1f;

		if (m_pHitbox != nullptr)
		{
			m_pHitbox->SetInvincibility(true);
		}

		if (m_pScore != nullptr)
		{
			m_pScore->AddScore(-30);
		}

		m_nInvincibilityCnt = 180;
	}
}

//�S�[����̓�������
void CPlayer::GoalMove()
{
	D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();
	D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
	float fA = acosf(cR.x);

	if (!m_bGoal)
	{
		return;
	}

	// �Ώۂ܂ł̊p�x�̎Z�o
	m_fAngle = sqrtf((float)(pow(m_TargetPos.x - m_pos.x, 2) + pow(m_TargetPos.z - m_pos.z, 2)));
	m_move.x = (m_TargetPos.x - m_pos.x) / (m_fAngle / 1.0f);
	m_move.z = (m_TargetPos.z - m_pos.z) / (m_fAngle / 1.0f);

	if (m_pos.z >= m_TargetPos.z)
	{
		m_move = Vec3Null;
		m_DestRot.y = D3DX_PI * 0.5f + fA;
	}
	
	if(m_rot.y <= m_DestRot.y * 2.0f)
	{
		m_bRot = true;
	}
}
