//------------------------------
//
// �G�̏���[enemy.cpp]
// Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>
#include <time.h>

#include "application.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "game.h"
#include "ground.h"
#include "input.h"
#include "main.h"
#include "object.h"
#include "object2D.h"
#include "player.h"
#include"renderer.h"
#include "result.h"
#include "score.h"
#include "sound.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9	CEnemy::m_pTexture[MAX_TEXTURE] = {};		//�e�N�X�`���ւ̃|�C���^
int					CEnemy::m_SkyEnemy = 7;
int					CEnemy::m_Sky = 3;
int					CEnemy::m_GroundEnemy = 3;
int					CEnemy::m_GroundEnemyL = 1;
int					CEnemy::m_DamageCount = 0;
int					CEnemy::m_SoundCount = 0;
int					CEnemy::m_SoundCount2 = 0;
int					CEnemy::m_SoundCount3 = 0;

//�R���X�g���N�^
CEnemy::CEnemy()
{
	
}

//�f�X�g���N�^
CEnemy::~CEnemy()
{
}

//����������
HRESULT CEnemy::Init()
{
	CObject2D::Init();

	srand((unsigned int)time(NULL));

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�G�̃e�N�X�`������
	switch (m_type)
	{
	case ENEMY_SKYSPACEMAN:
		BindTexture(m_pTexture[0]);
		SetLifeTexPos(7.0, 0.0f, 4.0f, 0.0f);
		break;

	case ENEMY_SKY:
		BindTexture(m_pTexture[3]);
		SetLifeTexPos(1.0, 0.0f, 1.0f, 0.0f);
		break;

	case ENEMY_GROUNDSPACEMANR:
		BindTexture(m_pTexture[1]);
		SetLifeTexPos(4.0f, 0.0f, 2.0f, 0.0f);
		break;

	case ENEMY_GROUNDSPACEMANL:
		BindTexture(m_pTexture[2]);
		SetLifeTexPos(4.0f, 0.0f, 2.0f, 0.0f);
		break;

	default:
		break;
	}

	switch (m_state)
	{
	case CEnemy::STATE_NORMAL:	
		break;
	case CEnemy::STATE_ATTACK:
		break;
	case CEnemy::STATE_MAX:
		break;
	case CEnemy::STATE_NONE:
		break;
	default:
		break;
	}

	if (CGame::GetWave() == CGame::WAVE_1)
	{
		m_SkyEnemy = 7;
		m_GroundEnemy = 3;
	}
	else if (CGame::GetWave() == CGame::WAVE_2)
	{
		m_SkyEnemy = 5;
		m_GroundEnemy = 2;
		m_Sky = 3;
	}
	else if (CGame::GetWave() == CGame::WAVE_3)
	{
		m_SkyEnemy = 3;
		m_GroundEnemy = 1;
		m_Sky = 2;
		m_GroundEnemyL = 1;
	}

	return S_OK;
}

void CEnemy::Uninit()
{
	if (m_type == ENEMY_SKYSPACEMAN)
	{
		m_SkyEnemy--;
	}

	if (m_type == ENEMY_GROUNDSPACEMANR)
	{
		m_GroundEnemy--;
	}

	if (m_type == ENEMY_SKY)
	{
		m_Sky--;
	}

	if (m_type == ENEMY_GROUNDSPACEMANL)
	{
		m_GroundEnemyL--;
	}

	if (m_SkyEnemy == 0 && m_GroundEnemy == 0 && m_GroundEnemyL == 0 && m_Sky == 0)
	{
		int GroundLife = CGround::GetGroundLife();
		int PlayerLife = CPlayer::GetPlayerLife();

		//score��10 * Life���ǉ�
		CGame::GetScore()->AddScore(10000 * (GroundLife * 2));
		CGame::GetScore()->AddScore(10000 * (PlayerLife * 2));

		CResult::SetState(CResult::STATE_GAMECLEAR);
		 
		if (m_pFade->GetFade() == CFade::FADE_NONE)
		{
			CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);
		}	
	}

	CObject2D::Uninit();
}

//�X�V����
void CEnemy::Update()
{
	D3DXVECTOR3 EnemyPos = GetPos();
	ENEMYTYPE EnemyType = GetEnemy();
	D3DXVECTOR3 EnemySize = CObject2D::GetSize();
	D3DXVECTOR3 EnemyMove = GetMove();

	//-------------------------
	//�󒆓G(1)
	//-------------------------
	if (EnemyType == ENEMY_SKYSPACEMAN)
	{
		m_SoundCount++;

		m_nCounterAnim++;	//�J�E���^�[�����Z

		if ((m_nCounterAnim % 5) == 0)
		{//��莞�Ԍo��
		 //�e�N�X�`���̍��W�ύX
			SetLifeTexPos(7.0f, (float)m_nPatternAnim, 4.0f, 0.0f);

			//�p�^�[��No.���X�V����
			m_nPatternAnim++;
		}

		if (m_nPatternAnim >= 7)
		{
			m_nCntAnim++;	//�J�E���^�[�����Z
			m_nCounterAnim = 0;

			if ((m_nCntAnim % 8) == 0)
			{//��莞�Ԍo��
				//�ړ��ʂ̍ő�l
				if (EnemyMove.x <= -3.0f)
				{
					EnemyMove.x = -3.0f;
				}
				else if (EnemyMove.x >= 3.0f)
				{
					EnemyMove.x = 3.0f;
				}

				int nTime = (rand() % 6000) + 1;

				if (nTime <= 6000 && nTime > 2000)
				{
					EnemyMove.x += (D3DX_PI * 0.5f) * 0.1f;
					nTime = 0;
				}
				else if (nTime < 2000 && nTime >= 0)
				{
					EnemyMove.x -= (D3DX_PI * 0.5f) * 0.1f;

					nTime = 0;
				}

				if (EnemyMove.x >= 0.03f)
				{
					SetLifeTexPos(8.0f, (float)m_nPtnAnim, 4.0f, 1.0f);
				}
				else
				{
					SetLifeTexPos(8.0f, (float)m_nPtnAnim, 4.0f, 3.0f);
				}

				//�ړ�����
				if (EnemyPos.x + (EnemySize.x / 2) >= CRenderer::SCREEN_WIDTH)
				{
					EnemyPos.x = CRenderer::SCREEN_WIDTH - (EnemySize.x / 2);
					EnemyMove.x *= -1;
				}
				else if (EnemyPos.x - (EnemySize.x / 2) <= 0)
				{
					EnemyPos.x = 0 + (EnemySize.x / 2);
					EnemyMove.x *= -1;
				}

				//�p�^�[��No.���X�V����
				m_nPtnAnim++;

				if (m_SoundCount >= 50)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_WING);

					m_SoundCount = 0;
				}
			}

			m_AttackTime = (rand() % 1000) + 1;
			SetAttackCount(m_AttackTime);

			m_AttackTime++;

			if (m_AttackTime >= 1000)
			{
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_ENEMYSHOOT);
				
				CBullet::Create(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + GetSize().y / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CBullet::BULLET_ENEMY);
				m_AttackTime = 0;
			}
		}
	}

	//-------------------------
	//�󒆓G(2)
	//-------------------------
	if (EnemyType == ENEMY_SKY)
	{
		m_AttackTime = (rand() % 1000) + 1;
		SetAttackCount(m_AttackTime);

		m_AttackTime++;

		if (m_AttackTime >= 1000)
		{
			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_ENEMYSHOOT);

			CBullet::Create(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + GetSize().y / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CBullet::BULLET_ENEMY);
			m_AttackTime = 0;
		}
	}

	//-------------------------
	//�n�ʓG(1)
	//-------------------------
	if (EnemyType == ENEMY_GROUNDSPACEMANR)
	{
		m_SoundCount2++;

		//�ړ��ʂ̍ő�l
		if (EnemyMove.x <= -1.0f)
		{
			EnemyMove.x = -1.0f;
		}
		else if (EnemyMove.x >= 1.0f)
		{
			EnemyMove.x = 1.0f;
		}

		//�E���痈�āA�r���Ŏ~�܂�
		if (EnemyPos.x <= (CRenderer::SCREEN_WIDTH + 100.0f) && EnemyPos.x >= CRenderer::SCREEN_WIDTH - 200.0f)
		{
			if (m_SoundCount2 >= 20)
			{
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_MOTION);
				m_SoundCount2 = 0;
			}

			//�ړ�
			EnemyMove.x -= (D3DX_PI * 0.5f) * 0.05f;
		}
		else if (EnemyPos.x >= 1000.0f && EnemyPos.x <= 1001.0f)
		{
			EnemyMove.x = 0.0f;
		}

		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			CObject *pObj = CObject::GetMyObject(PRIORITY_3,nCnt);

			if (pObj != nullptr)
			{//�^�C�v���n�ʂ�������
				if (pObj->GetType() == CObject::OBJTYPE_GROUND)
				{
					//�n�ʂ̈ʒu�擾
					D3DXVECTOR3 ObjectPos = pObj->GetPos();

					//�n�ʂ̃T�C�Y�擾
					D3DXVECTOR3 ObjectSize = pObj->GetSize();

					//�n�ʂ̐F�擾
					D3DXCOLOR ObjectColer = pObj->GetCol();

					m_AttackTime = (rand() % 200) + 1;
					SetAttackCount(m_AttackTime);

					m_AttackTime++;

					//�G�ƒn�ʂ̓����蔻��
					if (ObjectPos.x + ObjectSize.x / 2 >= EnemyPos.x - EnemySize.x / 2
						&& ObjectPos.x - ObjectSize.x / 2 <= EnemyPos.x + EnemySize.x / 2
						&& ObjectPos.y - ObjectSize.y / 2 <= EnemyPos.y + EnemySize.y / 2 - 5.0f
						&& ObjectPos.y + ObjectSize.y / 2 >= EnemyPos.y - EnemySize.y / 2 + 5.0f)
					{
						if (m_AttackTime >= 200 && EnemyMove.x == 0)
						{
							m_state = STATE_ATTACK;
						}
						else
						{
							EnemyMove.y = 0;
						}
					}
					else
					{
						//�d�͕����Z
						EnemyMove.y += MAX_GRAVITY;
					}
				}
			}
		}

		EnemyAction();
	}

	//-------------------------
	//�n�ʓG(2)
	//-------------------------
	if (EnemyType == ENEMY_GROUNDSPACEMANL)
	{
		m_SoundCount3 ++;

		//�ړ��ʂ̍ő�l
		if (EnemyMove.x <= -1.0f)
		{
			EnemyMove.x = -1.0f;
		}
		else if (EnemyMove.x >= 1.0f)
		{
			EnemyMove.x = 1.0f;
		}

		//�����痈�āA�r���Ŏ~�܂�
		if (EnemyPos.x <= 200.0f && EnemyPos.x >= -100.0f)
		{
			if (m_SoundCount3 >= 20)
			{
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_MOTION);
				m_SoundCount3 = 0;
			}

			//�ړ�
			EnemyMove.x += (D3DX_PI * 0.5f) * 0.05f;
		}
		else if (EnemyPos.x >= 201.0f && EnemyPos.x <= 202.0f)
		{
			EnemyMove.x = 0.0f;
		}

		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			CObject *pObj = CObject::GetMyObject(PRIORITY_3,nCnt);

			if (pObj != nullptr)
			{//�^�C�v���n�ʂ�������
				if (pObj->GetType() == CObject::OBJTYPE_GROUND)
				{
					//�n�ʂ̈ʒu�擾
					D3DXVECTOR3 ObjectPos = pObj->GetPos();

					//�n�ʂ̃T�C�Y�擾
					D3DXVECTOR3 ObjectSize = pObj->GetSize();

					//�n�ʂ̐F�擾
					D3DXCOLOR ObjectColer = pObj->GetCol();

					m_AttackTime = (rand() % 200) + 1;
					SetAttackCount(m_AttackTime);

					m_AttackTime++;

					//�G�ƒn�ʂ̓����蔻��
					if (ObjectPos.x + ObjectSize.x / 2 >= EnemyPos.x - EnemySize.x / 2
						&& ObjectPos.x - ObjectSize.x / 2 <= EnemyPos.x + EnemySize.x / 2
						&& ObjectPos.y - ObjectSize.y / 2 <= EnemyPos.y + EnemySize.y / 2 - 10.0f
						&& ObjectPos.y + ObjectSize.y / 2 >= EnemyPos.y - EnemySize.y / 2 + 10.0f)
					{
						if (m_AttackTime >= 200 && EnemyMove.x == 0)
						{
							m_state = STATE_ATTACK;
						}
						else
						{
							EnemyMove.y = 0;
						}
					}
					else
					{
						//�d�͕����Z
						EnemyMove.y += MAX_GRAVITY;
					}
				}
			}
		}

		EnemyAction();
	}

	//�ʒu���X�V
	EnemyPos.x += EnemyMove.x;
	EnemyPos.y += EnemyMove.y;
	EnemyPos.z += EnemyMove.z;

	SetMove(EnemyMove);
	SetPos(EnemyPos);
	CObject2D::Update();
}

//����
CEnemy * CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,ENEMYTYPE type,int life)
{
		CEnemy *pEnemy = new CEnemy;
		
		if (pEnemy != nullptr)
		{
			pEnemy->SetEnemyType(type);
			pEnemy->Init();
			pEnemy->SetPos(pos);
			pEnemy->SetSize(size);
			pEnemy->SetLife(life);
			pEnemy->SetType(OBJTYPE_ENEMY);
		}
		else
		{
			assert(false);
		}

	return pEnemy;
}

void CEnemy::SetSkyEnemy(int nSkyEnemy)
{
	m_SkyEnemy = nSkyEnemy;
}

void CEnemy::SetSky(int nSky)
{
	m_Sky = nSky;
}

void CEnemy::SetGroundEnemy(int nGroundEnemy)
{
	m_GroundEnemy = nGroundEnemy;
}

void CEnemy::SetGroundEnemyL(int nGroundEnemyL)
{
	m_GroundEnemyL = nGroundEnemyL;
}

//�U�������֐�
void CEnemy::EnemyAction()
{
	D3DXVECTOR3 EnemyPos = GetPos();
	ENEMYTYPE EnemyType = GetEnemy();
	D3DXVECTOR3 EnemySize = CObject2D::GetSize();
	D3DXVECTOR3 EnemyMove = GetMove();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_3, nCnt);

		if (pObj != nullptr)
		{//�^�C�v���v���C���[��������
			if (pObj->GetType() == CObject::OBJTYPE_PLAYER)
			{
				//�v���C���[�̈ʒu�擾
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//�v���C���[�̃T�C�Y�擾
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				int nLife = pObj->GetLife();

				//�v���C���[�ƓG�̓����蔻��
				if (ObjectPos.x + ObjectSize.x / 2 >= EnemyPos.x - EnemySize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= EnemyPos.x + EnemySize.x / 2
					&& ObjectPos.y - ObjectSize.y / 2 <= EnemyPos.y + EnemySize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= EnemyPos.y - EnemySize.y / 2)
				{
					DamageCout();
				}

				//�v���C���[�̃��C�t��0�ȉ��ɂȂ�����
				if (nLife <= 0)
				{
					//�v���C���[�̏I������
					pObj->Uninit();
					CResult::SetState(CResult::STATE_GAMEOVER);
					CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);
				}
			}
		}
	}

	if (m_state == STATE_NORMAL)
	{
		m_nNormalCounter++;	//�J�E���^�[�����Z

		if ((m_nNormalCounter % 8) == 0)
		{
			SetLifeTexPos(4.0f, (float)m_nNormalPattern, 2.0f, 0.0f);

			//�p�^�[��No.���X�V����
			m_nNormalPattern++;
		}

		if (EnemyMove.x == 0)
		{
			SetLifeTexPos(4.0f, 0.0f, 2.0f, 0.0f);
		}
	}

	if (m_state == STATE_ATTACK)
	{
		m_nAttackCounter++;	//�J�E���^�[�����Z

		if ((m_nAttackCounter % 12) == 0)
		{
			SetLifeTexPos(4.0f, (float)m_nAttackPattern, 2.0f, 1.0f);

			//�p�^�[��No.���X�V����
			m_nAttackPattern++;

			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_ATTACK);		
		}

		if (m_nAttackPattern >= 4)
		{
			for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
			{
				CObject *pObj = CObject::GetMyObject(PRIORITY_3,nCnt);

				if (pObj != nullptr)
				{//�^�C�v���n�ʂ�������
					if (pObj->GetType() == CObject::OBJTYPE_GROUND)
					{
						//�U������
						int nLife = pObj->GetLife();
						nLife--;

						pObj->SetLife(nLife);

						if (nLife == 7)
						{
							pObj->UpdateTex();
						}

						if (nLife == 3)
						{
							pObj->UpdateTex();
						}

						if (nLife <= 0)
						{
							pObj->Uninit();
							CResult::SetState(CResult::STATE_GAMEOVER);
							CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);
						}
					}
				}
			}

			CBullet::SubLife();

			m_nAttackPattern = 0;
			m_state = STATE_NORMAL;
		}
	}

	SetMove(EnemyMove);
	SetPos(EnemyPos);
}

//�U���^�C�~���O��ݒ�
void CEnemy::SetAttackCount(int nAttack)
{
	m_AttackTime = nAttack;
}

//�^�C�v�̐ݒ�
void CEnemy::SetEnemyType(ENEMYTYPE type)
{
	m_type = type;
}

//�G�̗̑͐ݒ�
void CEnemy::SetLife(int nLife)
{
	m_Life = nLife;
}

void CEnemy::DamageCout()
{
	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_3, nCnt);

		if (pObj != nullptr)
		{//�^�C�v���v���C���[��������
			if (pObj->GetType() == CObject::OBJTYPE_PLAYER)
			{
				int nLife = pObj->GetLife();

				m_DamageCount++;

				if (m_DamageCount == 1)
				{
					//�v���C���[�̃��C�t��1���炷
					nLife--;

					//�v���C���[�̃��C�t���X�V�ݒ肷��
					pObj->SetLife(nLife);

					//�v���C���[�̗̑̓|���S�������炷
					CBullet::SubPlayerLife();
				}
				else if (m_DamageCount == 120)
				{
					m_DamageCount = 0;
				}
			}
		}
	}
}

int CEnemy::GetCount()
{
	return m_DamageCount;
}

//�󒆓G�̑�����Ԃ�
int CEnemy::GetSkyEnemyCnt()
{
	return m_SkyEnemy;
}

int CEnemy::GetSky()
{
	return m_Sky;
}

//�n�ʓG�̑�����Ԃ�
int CEnemy::GetGroundEnemyCnt()
{
	return m_GroundEnemy;
}

int CEnemy::GetGroundEnemyLCnt()
{
	return m_GroundEnemyL;
}

//�G�̗̑͏��擾
int CEnemy::GetLife()
{
	return m_Life;
}

//�^�C�v�̏��擾
int CEnemy::GetEnemyType()
{
	return m_type;
}

//�^�C�v�̏��擾
CEnemy::ENEMYTYPE CEnemy::GetEnemy()
{
	return m_type;
}

//�e�N�X�`���ǂݍ��ݏ���
HRESULT CEnemy::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TfTOTBkUoWq2Kha1661127459_1661127461.png",
		&m_pTexture[0]);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rXtd1zTfrhyYYxT1658972170_1658972221.png",
		&m_pTexture[1]);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gVBTlx8SI84VJTW1658972670_1658972767.png",
		&m_pTexture[2]);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Head.png",
		&m_pTexture[3]);

	return S_OK;
}

//�e�N�X�`���̔j��
void CEnemy::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}