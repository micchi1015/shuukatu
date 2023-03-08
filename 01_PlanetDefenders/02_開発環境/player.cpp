//------------------------------
//
// �v���C���[�̏���[player.cpp]
// Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include "input.h"
#include "object2D.h"
#include "player.h"
#include "renderer.h"
#include "sound.h"
#include "umbrella.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = nullptr;		//�e�N�X�`���ւ̃|�C���^
int				   CPlayer::m_ColorTime = 0;
int				   CPlayer::m_Life = 0;

//�R���X�g���N�^
CPlayer::CPlayer()
{
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{
}

//����������
HRESULT CPlayer::Init()
{
	CObject2D::Init();

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�v���C���[���̏�����
	m_nDirectionMove = 0;
	mIndex = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;

	BindTexture(m_pTexture);
	
	SetLifeTexPos(8.0f, (float)m_nPatternAnim, 2.0f, 1.0f);

	return S_OK;
}

//�X�V����
void CPlayer::Update()
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();
	D3DXVECTOR3 PlayerPos = GetPos();
	D3DXVECTOR3 PlayerSize = CObject2D::GetSize();

	//�ړ��ʂ̍ő�l
	if (m_playermove.x <= -25.0f)
	{
		m_playermove.x = -25.0f;
	}
	else if (m_playermove.x >= 25.0f)
	{
		m_playermove.x = 25.0f;
	}

	if (CGame::GetState() == CGame::STATE_EXE)
	{
		//�ړ�
		m_nCounterAnim++;

		if ((m_nCounterAnim % 8) == 0)
		{
			if (pInputKeyboard->GetPress(DIK_A))
			{//A�L�[�������ꂽ
			 //�ړ��ʂ��X�V(����������)
				m_nDirectionMove = 0;
				m_playermove.x -= (D3DX_PI * 0.5f) * 3.5f;

				m_nPatternAnim = (m_nPatternAnim + 1) % 8;		//�p�^�[��NO.���X�V����
				SetLifeTexPos(8.0f, (float)m_nPatternAnim, 2.0f, 1.0f);
			}
			else if (pInputKeyboard->GetPress(DIK_D))
			{//D�L�[�������ꂽ
			 //�ړ��ʂ��X�V(����������)
				m_nDirectionMove = 1;
				m_playermove.x += (D3DX_PI * 0.5f) *3.5f;

				m_nPatternAnim = (m_nPatternAnim + 1) % 8;		//�p�^�[��NO.���X�V����
				SetLifeTexPos(8.0f, (float)m_nPatternAnim, 2.0f, 0.0f);
			}
		}

		//�P
		if (pInputKeyboard->GetTrigger(DIK_C) == true)
		{
			CUmbrella::Create(D3DXVECTOR3(PlayerPos.x + 10.0f, PlayerPos.y - 30.0f, 0.0f));
			mIndex = 1;
		}
		else if (pInputKeyboard->GetPress(DIK_C) == false)
		{
			//�󒆒e
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
			{
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_SHOOT);
				CBullet::Create(D3DXVECTOR3(PlayerPos.x, PlayerPos.y - GetSize().y / 2.0f, 0.0f), D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), CBullet::BULLET_PLAYER);
			}

			//�n��e
			if (m_nDirectionMove == 0)
			{
				if (pInputKeyboard->GetTrigger(DIK_LSHIFT) == true)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_SHOOT);
					CBullet::Create(D3DXVECTOR3(PlayerPos.x - (GetSize().x / 2), PlayerPos.y, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CBullet::BULLET_PLAYER);
				}
			}
			else if (m_nDirectionMove == 1)
			{
				if (pInputKeyboard->GetTrigger(DIK_LSHIFT) == true)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_SHOOT);
					CBullet::Create(D3DXVECTOR3(PlayerPos.x + (GetSize().x / 2), PlayerPos.y, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CBullet::BULLET_PLAYER);
				}
			}

			for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
			{
				CObject *pObj = CObject::GetMyObject(PRIORITY_3, nCnt);

				if (pObj != nullptr)
				{//�^�C�v���P��������
					if (pObj->GetType() == CObject::OBJTYPE_UMBRELLA)
					{
						if (mIndex == 1)
						{
							pObj->Uninit();
						}
					}
				}
			}

			mIndex = 0;
		}
	}

	SetPos(PlayerPos);
	SetMove(m_playermove);
	CObject2D::Update();

	//�ʒu���X�V
	PlayerPos.x += m_playermove.x;
	PlayerPos.y += m_playermove.y;
	PlayerPos.z += m_playermove.z;

	//�ړ��ʂ��X�V(����������)
	m_playermove.x += (0.0f - m_playermove.x) * 0.1f;
	m_playermove.y += (0.0f - m_playermove.y) * 0.1f;
	m_playermove.z += (0.0f - m_playermove.z) * 0.1f;

	//�ړ�����
	if (PlayerPos.x + (PlayerSize.x / 2) >= CRenderer::SCREEN_WIDTH)
	{
		PlayerPos.x = CRenderer::SCREEN_WIDTH - (PlayerSize.x / 2);
		m_playermove.x = 0.0f;
		SetMove(m_playermove);
		SetPos(PlayerPos);
	}
	else if (PlayerPos.x - (PlayerSize.x / 2) <= 0)
	{
		PlayerPos.x = 0 + (PlayerSize.x / 2);
		m_playermove.x = 0.0f;
		SetMove(m_playermove);
		SetPos(PlayerPos);
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

				//�v���C���[�ƒn�ʂ̓����蔻��
				if (ObjectPos.x + ObjectSize.x / 2 >= PlayerPos.x - PlayerSize.x / 2
					&& ObjectPos.x - ObjectSize.x / 2 <= PlayerPos.x + PlayerSize.x / 2
					&& ObjectPos.y - ObjectSize.y / 2 <= PlayerPos.y + PlayerSize.y / 2
					&& ObjectPos.y + ObjectSize.y / 2 >= PlayerPos.y - PlayerSize.y / 2)
				{
					m_playermove.y = 0;
				}
				else
				{
					//�d�͕����Z
					m_playermove.y += MAX_GRAVITY;
				}
			}
		}
	}
}

//����
CPlayer * CPlayer::Create()
{
	CPlayer *pObject2D = new CPlayer;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(D3DXVECTOR3(640.0f,600.0f,0.0f));
		pObject2D->SetType(OBJTYPE_PLAYER);
		pObject2D->SetSize(D3DXVECTOR3(50.0f, 80.0f, 0.0f));
		pObject2D->SetLife(7);
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//���C�t�̐ݒ�
void CPlayer::SetLife(int nLife)
{
	m_Life = nLife;
}

//���C�t�̏��擾
int CPlayer::GetLife()
{
	return m_Life;
}

int CPlayer::GetPlayerLife()
{
	return m_Life;
}

//�e�N�X�`���ǂݍ���
HRESULT CPlayer::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\E.png",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CPlayer::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}