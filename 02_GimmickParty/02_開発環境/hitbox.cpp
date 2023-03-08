//=============================================================================
//
// hitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "hitbox.h"

//=============================================================================
//
//								�ÓI�ϐ�
//
//=============================================================================
std::vector <CHitbox*> CHitbox::m_vHitbox;

//�R���X�g���N�^
CHitbox::CHitbox()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;							//�ʒu
	m_RelativePos = Vec3Null;					//���Έʒu
	m_LastPos = Vec3Null;						//�O��̈ʒu
	m_size = Vec3Null;							//�T�C�Y
	m_rot = Vec3Null;							//����
	m_shape = (HITBOX_SHAPE)0;					//�G�t�F�N�g�̌���
	m_type = (HITBOX_TYPE)0;					//�`
	m_effect = (INTERACTION_EFFECT)0;			//���
	m_bCollided = false;						//�G�t�F�N�g
	m_pParent = nullptr;						//�����Ɠ����������ǂ���
	m_nPlayerIdx = 0;							//�e
	m_nScore = 0;								//�v���C���[�C���f�b�N�X
	m_bInvincible = false;						//�X�R�A
	m_dir = Vec3Null;							//���G��Ԃł��邩�ǂ���

	m_vHitbox.push_back(this);					//���̃C���X�^���X��ǉ�����
}

//�f�X�g���N�^
CHitbox::~CHitbox()
{

}

//����������
HRESULT CHitbox::Init(void)
{
	//����������
	m_pos = Vec3Null;				//�ʒu
	m_LastPos = Vec3Null;			//���Έʒu
	m_RelativePos = Vec3Null;		//�O��̈ʒu
	m_size = Vec3Null;				//�T�C�Y
	m_rot = Vec3Null;				//����
	m_shape = (HITBOX_SHAPE)0;		//�G�t�F�N�g�̌���
	m_type = (HITBOX_TYPE)0;		//�`
	m_effect = EFFECT_MAX;			//���
	m_bCollided = false;			//�G�t�F�N�g
	m_pParent = nullptr;			//�����Ɠ����������ǂ���
	m_nPlayerIdx = -1;				//�e
	m_nScore = 0;					//�v���C���[�C���f�b�N�X
	m_bInvincible = false;			//�X�R�A
	m_dir = Vec3Null;				//���G��Ԃł��邩�ǂ���

	return S_OK;
}

//�I������
void CHitbox::Uninit(void)
{

}

//�X�V����
void CHitbox::Update(void)
{
	m_LastPos = m_pos;				//�O��̈ʒu�̍X�V����

	if (m_pParent != nullptr)
	{//�e����������A�ʒu���X�V����
		D3DXVECTOR3 newPos = m_pParent->GetPos() + m_RelativePos;
		m_pos = newPos;
	}
}

//�q�b�g�{�b�N�X1�̔j������
void CHitbox::Release(void)
{
	for (int nCnt = 0; nCnt < (int)m_vHitbox.size(); nCnt++)
	{
		if (m_vHitbox.data()[nCnt] == this)
		{
			m_vHitbox.data()[nCnt]->Uninit();
			m_vHitbox.erase(m_vHitbox.begin() + nCnt);
			delete this;
		}
	}
}

//�ʒu�̎擾����
D3DXVECTOR3 CHitbox::GetPos(void)
{
	return m_pos;
}

//���Έʒu�̎擾����
D3DXVECTOR3 CHitbox::GetRelativePos(void)
{
	return m_RelativePos;
}

//�O��̈ʒu�̎擾����
D3DXVECTOR3 CHitbox::GetLastPos(void)
{
	return m_LastPos;
}

//�T�C�Y�̎擾����
D3DXVECTOR3 CHitbox::GetSize(void)
{
	return m_size;
}

//�����̎擾����
D3DXVECTOR3 CHitbox::GetRot(void)
{
	return m_rot;
}

//�`�̎擾����
CHitbox::HITBOX_SHAPE CHitbox::GetShape(void)
{
	return m_shape;
}

//��ނ̎擾����
CHitbox::HITBOX_TYPE CHitbox::GetType(void)
{
	return m_type;
}

//�e�̎擾����
CObject* CHitbox::GetParent(void)
{
	return m_pParent;
}

//�G�t�F�N�g�̎擾����
CHitbox::INTERACTION_EFFECT CHitbox::GetEffect(void)
{
	return m_effect;
}

//�G�t�F�N�g�̌����̎擾����
const D3DXVECTOR3 CHitbox::GetDirection(void)
{
	return m_dir;
}


//�ʒu�̐ݒ菈��
void CHitbox::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos + m_RelativePos;
}

//���Έʒu�̐ݒ菈��
void CHitbox::SetRelativePos(const D3DXVECTOR3 pos)
{
	m_RelativePos = pos;
}

//�O��̈ʒu�̐ݒ菈��
void CHitbox::SetLastPos(const D3DXVECTOR3 pos)
{
	m_LastPos = pos;
}

//�T�C�Y�̐ݒ菈��
void CHitbox::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}

//�`�̐ݒ菈��
void CHitbox::SetShape(const HITBOX_SHAPE shape)
{
	m_shape = shape;
}

//��ނ̐ݒ菈��
void CHitbox::SetType(const HITBOX_TYPE type)
{
	m_type = type;
}

//�e�̐ݒ菈��
void CHitbox::SetParent(CObject* pParent)
{
	m_pParent = pParent;
}

//�����Ɠ����������ǂ����̐ݒ菈��
void CHitbox::SetCollisionState(bool bCollision)
{
	m_bCollided = bCollision;
}

//�v���C���[�C���f�b�N�X�̐ݒ菈��
void CHitbox::SetPlayerIdx(const int nPlayerIdx)
{
	m_nPlayerIdx = nPlayerIdx;
}

//�X�R�A�̐ݒ菈��
void CHitbox::SetScore(const int nScore)
{
	m_nScore = nScore;
}

//�G�t�F�N�g�̐ݒ菈��
void CHitbox::SetEffect(INTERACTION_EFFECT effect)
{
	m_effect = effect;
}

//���G��Ԃ̐ݒ菈��
void CHitbox::SetInvincibility(const bool bInv)
{
	m_bInvincible = bInv;
}

//�G�t�F�N�g�̌����̐ݒ菈��
void CHitbox::SetDirection(const D3DXVECTOR3 dir)
{
	m_dir = dir;
}

//�����Ɠ����������ǂ���
bool CHitbox::GetCollisionState(void)
{
	return m_bCollided;
}

//�v���C���[�C���f�b�N�X�̎擾����
const int CHitbox::GetPlayerIdx(void)
{
	return m_nPlayerIdx;
}

//�X�R�A�̎擾����
const int CHitbox::GetScore(void)
{
	return m_nScore;
}

//���G��Ԃł��邩�ǂ����̎擾����
const bool CHitbox::GetInvincibility(void)
{
	return m_bInvincible;
}







//�q�b�g�{�b�N�X�S���̔j������
void CHitbox::ReleaseAll(void)
{
	CHitbox* pHitbox = nullptr;

	for (int nCnt = 0; nCnt < (int)m_vHitbox.size(); nCnt++)
	{
		pHitbox = m_vHitbox.data()[nCnt];
		delete pHitbox;
		pHitbox = nullptr;
	}

	m_vHitbox.clear();
}

std::vector <CHitbox*>* CHitbox::GetAllHitbox(void)
{
	return &m_vHitbox;
}