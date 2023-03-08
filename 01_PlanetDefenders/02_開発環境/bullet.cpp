//-------------------------
//
//�e�̏���[bullet.cpp]
//Author:���c�喲
//
//-------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "bullet.h"
#include "collision.h"
#include "enemy.h"
#include "explosion.h"
#include "fade.h"
#include "game.h"
#include "life.h"
#include "object.h"
#include "object2D.h"
#include "renderer.h"
#include "result.h"
#include "score.h"
#include "sound.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = nullptr;				//�e�N�X�`���ւ̃|�C���^
CPolygon *CBullet::m_pPolygon = nullptr;						//�n�ʂ̗̑̓|���S���̃|�C���^�ϐ�
CPlayerLifePolygon *CBullet::m_pPlayerLifePolygon = nullptr;	//�v���C���[�̗̑̓|���S���̃|�C���^�ϐ�
int CBullet::m_Polygon = 0;										//�n�ʗp�ϐ�
int CBullet::m_PlayerLifePolygon = 0;							//�v���C���[�p�ϐ�

//�R���X�g���N�^
CBullet::CBullet(int nPriority) : CObject2D(nPriority)
{
}

//�f�X�g���N�^
CBullet::~CBullet()
{
}

//����������
HRESULT CBullet::Init()
{
	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	//�e�N�X�`������
	switch (m_type)
	{
	case BULLET_PLAYER:
		BindTexture(m_pTexture);
		break;

	case BULLET_ENEMY:
		BindTexture(m_pTexture);
		break;

	default:
		break;
	}

	//bullet�̏�񏉊���
	m_nLife = 150;
	
	return S_OK;
}

//�X�V����
void CBullet::Update()
{
	//pos,size,move���i�[
	D3DXVECTOR3 BulletPos = CObject2D::GetPos();
	D3DXVECTOR3 BulletSize = GetSize();
	D3DXVECTOR3 BulletMove = CObject::GetMove();

	//�e�̈ʒu�̍X�V
	BulletPos += BulletMove;

	//�e�̎����̃J�E���g�_�E��
	m_nLife--;

	//�e�̈ʒu���X�V
	CObject2D::SetPos(BulletPos);

	//�X�V����
	CObject2D::Update();

	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		CObject *pObj = CObject::GetMyObject(PRIORITY_3,nCnt);

		if (pObj != nullptr)
		{
			//-------------------------
			//�e�ƓG�̓����蔻��
			//-------------------------
			if (pObj->GetType() == CObject::OBJTYPE_ENEMY && m_type == BULLET_PLAYER && (pObj->GetEnemyType() == CEnemy::ENEMY_SKYSPACEMAN || pObj->GetEnemyType() == CEnemy::ENEMY_SKY))
			{//�^�C�v���G���v���C���[�̒e��������
				//�G�̈ʒu�擾
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//�G�̃T�C�Y�擾
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				//�G�̃��C�t�擾
				int ObjectLife = pObj->GetLife();

				//�G�ƒe�̓����蔻��
				if (ObjectPos.y - ObjectSize.y / 2 <= BulletPos.y + BulletSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= BulletPos.y - BulletSize.y / 2
					&& ObjectPos.x + ObjectSize.x / 2 >= BulletPos.x - BulletSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= BulletPos.x + BulletSize.x / 2)
				{
					//�G�ɓ���������e�̃��C�t��0�ɂ���
					m_nLife = 0;

					//�G�̃��C�t��1���炷
					ObjectLife--;

					//�G�̃��C�t���X�V�ݒ肷��
					pObj->SetLife(ObjectLife);

					//�G�̃��C�t��0�ȉ��ɂȂ�����
					if (ObjectLife <= 0)
					{
						//score��10�ǉ�
						CGame::GetScore()->AddScore(1000);

						//�G�̏I������
						pObj->Uninit();
					}
				}
			}

			//-------------------------
			//�e�ƓG�̓����蔻��
			//-------------------------
			if (pObj->GetType() == CObject::OBJTYPE_ENEMY && m_type == BULLET_PLAYER && (pObj->GetEnemyType() == CEnemy::ENEMY_GROUNDSPACEMANR || pObj->GetEnemyType() == CEnemy::ENEMY_GROUNDSPACEMANL))
			{//�^�C�v���G���v���C���[�̒e��������
			 //�G�̈ʒu�擾
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//�G�̃T�C�Y�擾
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				//�G�̃��C�t�擾
				int ObjectLife = pObj->GetLife();

				//�G�ƒe�̓����蔻��
				if (ObjectPos.y - ObjectSize.y / 2 <= BulletPos.y + BulletSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= BulletPos.y - BulletSize.y / 2
					&& ObjectPos.x + ObjectSize.x / 2 - 15.0f>= BulletPos.x - BulletSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 + 15.0f <= BulletPos.x + BulletSize.x / 2)
				{
					//�G�ɓ���������e�̃��C�t��0�ɂ���
					m_nLife = 0;

					//�G�̃��C�t��1���炷
					ObjectLife--;

					//�G�̃��C�t���X�V�ݒ肷��
					pObj->SetLife(ObjectLife);

					//�G�̃��C�t��0�ȉ��ɂȂ�����
					if (ObjectLife <= 0)
					{
						//score��10�ǉ�
						CGame::GetScore()->AddScore(1000);

						//�G�̏I������
						pObj->Uninit();
					}
				}
			}

			//-------------------------
			//�e�ƃv���C���[�̓����蔻��
			//-------------------------
			if (pObj->GetType() == CObject::OBJTYPE_PLAYER && m_type == BULLET_ENEMY)
			{//�^�C�v���v���C���[���G�̒e��������
				//�v���C���[�̈ʒu�擾
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//�v���C���[�̃T�C�Y�擾
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				//�v���C���[�̃��C�t�擾
				int ObjectLife = pObj->GetLife();

				//�v���C���[�ƒe�̓����蔻��
				if (ObjectPos.y - ObjectSize.y / 2 <= BulletPos.y + BulletSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= BulletPos.y - BulletSize.y / 2
					&& ObjectPos.x + ObjectSize.x / 2 >= BulletPos.x - BulletSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= BulletPos.x + BulletSize.x / 2)
				{
					//�e�̃��C�t��0�ɂ���
					m_nLife = 0;

					//�v���C���[�̃��C�t��1���炷
					ObjectLife--;

					//�v���C���[�̃��C�t���X�V�ݒ肷��
					pObj->SetLife(ObjectLife);

					//�v���C���[�̗̑̓|���S�������炷
					SubPlayerLife();

					//�v���C���[�̃��C�t��0�ȉ��ɂȂ�����
					if (ObjectLife <= 0)
					{
						//�v���C���[�̏I������
						pObj->Uninit();
						CResult::SetState(CResult::STATE_GAMEOVER);
						CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);		
					}
				}
			}

			//-------------------------
			//�e�ƒn�ʂ̓����蔻��
			//-------------------------
			if (pObj->GetType() == CObject::OBJTYPE_GROUND && m_type == BULLET_ENEMY)
			{//�^�C�v���n�ʂ��G�̒e��������
				//�n�ʂ̈ʒu�擾
				D3DXVECTOR3 ObjectPos = pObj->GetPos();

				//�n�ʂ̃T�C�Y�擾
				D3DXVECTOR3 ObjectSize = pObj->GetSize();

				//�n�ʂ̃��C�t�擾
				int ObjectLife = pObj->GetLife();

				//�n�ʂƒe�̓����蔻��
				if (ObjectPos.y - ObjectSize.y / 2 <= BulletPos.y + BulletSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= BulletPos.y - BulletSize.y / 2
					&& ObjectPos.x + ObjectSize.x / 2 >= BulletPos.x - BulletSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= BulletPos.x + BulletSize.x / 2)
				{
					//�e�̃��C�t��0�ɂ���
					m_nLife = 0;

					//�n�ʂ̃��C�t��1���炷
					ObjectLife--;

					//�n�ʂ̃��C�t���X�V�ݒ肷��
					pObj->SetLife(ObjectLife);

					//�n�ʂ̗̑�7�Ńe�N�X�`���摜�ύX
					if (ObjectLife == 7)
					{
						pObj->UpdateTex();
					}
					//�n�ʂ̗̑�3�Ńe�N�X�`���摜�ύX
					if (ObjectLife == 3)
					{
						pObj->UpdateTex();
					}

					//�n�ʂ̗̑̓|���S�������炷
					SubLife();

					if (ObjectLife <= 0)
					{//�n�ʂ̃��C�t��0�ȉ��ɂȂ�����
					 //�n�ʂ̏I������
						pObj->Uninit();
						CResult::SetState(CResult::STATE_GAMEOVER);
						CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_RESULT);
					}
				}
			}
		}
	}

	if (m_nLife <= 0)
	{//�e�̃��C�t��0�ȉ��ɂȂ�����
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_EXP);

		//��������
   		CExplosion::Create(D3DXVECTOR3(BulletPos.x, BulletPos.y, 0),D3DXVECTOR3(50.0f,50.0f,0.0f));

		//�I������
		Uninit();
	}
	else
	{	
		if (BulletPos.y <= 0)
		{//�e�̈ʒu����ʊO�ɂȂ�����
			//�I������
			Uninit();
		}
		else if (BulletPos.x <= 0 || BulletPos.x >= CRenderer::SCREEN_WIDTH)
		{//�e�̈ʒu����ʊO�ɂȂ�����
			//�I������
 			Uninit();
		}
	}
}

//�e�̐���
CBullet *CBullet::Create(const D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,BULLETTYPE type)
{
	CBullet *pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		pBullet->Init();
		pBullet->SetPos(pos);
		pBullet->SetType(OBJTYPE_BULLET);
		pBullet->SetBulletType(type);
		pBullet->SetSize(D3DXVECTOR3(10.0f,10.0f,0.0f));
		pBullet->SetMove(move);
		pBullet->SetColer(col);
	}
	else
	{
		assert(false);
	}

	return pBullet;
}

//�^�C�v�̎擾
CBullet::BULLETTYPE CBullet::GetType()
{
	return m_type;
}

//�^�C�v�̐ݒ�
void CBullet::SetBulletType(BULLETTYPE type)
{
	m_type = type;
}

//�e�̎��
int CBullet::GetBulletType()
{
	return m_type;
}

//�n�ʂ̗̑͂����炷
void CBullet::SubLife()
{
	//���C�t�̃��C�t�擾
	int ObjectLife = CPolygon::GetLife();

	//���C�t�̃��C�t��1���炷
	ObjectLife--;

	//���C�t��0�ȉ��ɂȂ�����
	if (ObjectLife <= 0)
	{
		//���C�t�̉摜�ύX
		m_pPolygon->UpdateLife(m_Polygon);
		m_Polygon++;
	}
}

//�v���C���[�̗̑͂����炷
void CBullet::SubPlayerLife()
{
	//���C�t�̃��C�t�擾
	int ObjectLife = CPlayerLifePolygon::GetPlayerLife();

	//���C�t�̃��C�t��1���炷
	ObjectLife--;

	//���C�t��0�ȉ��ɂȂ�����
	if (ObjectLife <= 0)
	{
		//���C�t�̉摜�ύX
		m_pPlayerLifePolygon->UpdateLife(m_PlayerLifePolygon);
		m_PlayerLifePolygon++;
	}
}

void CBullet::SetPolygon(int m_polygon)
{
	m_Polygon = m_polygon;
}

void CBullet::SetLifePolygon(int m_PlayerLife)
{
	m_PlayerLifePolygon = m_PlayerLife;
}

//�e�N�X�`���ǂݍ���
HRESULT CBullet::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CBullet::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}