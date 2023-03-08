//=============================================================================
//
// icePillarSpawner.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "icePillarSpawner.h"
#include "icePillar.h"


//�R���X�g���N�^
CIcePillarSpawner::CIcePillarSpawner()
{
	m_pos = Vec3Null;				//�ʒu
	m_shadowY = 0.0f;				//�e�̍���
	m_laterlBounds = 0.0f;  		//�X�|�[���G���A�̕�
	m_nCntTime = 0;					//�t���[���J�E���^�[
	m_nSpawnTime = 0;				//�X�|�[���^�C��
	m_nMaxSpawn = 0;				//�ő�^�C��
	m_fAreaLength = 0.0f;			//�X�|�[���G���A�̒���
}

//�f�X�g���N�^
CIcePillarSpawner::~CIcePillarSpawner()
{

}

//����������
HRESULT CIcePillarSpawner::Init(void)
{
	m_pos = Vec3Null;				//�ʒu
	m_shadowY = 0.0f;				//�e�̍���
	m_laterlBounds = 0.0f;  		//�X�|�[���G���A�̕�
	m_nCntTime = 0;					//�t���[���J�E���^�[
	m_nSpawnTime = 0;				//�X�|�[���^�C��
	m_nMaxSpawn = 0;				//�ő�^�C��
	m_fAreaLength = 0.0f;			//�X�|�[���G���A�̒���

	return S_OK;
}

//�I������
void CIcePillarSpawner::Uninit(void)
{

}

//�X�V����
void CIcePillarSpawner::Update(void)
{
	m_nCntTime--;			//�X�|�[���J�E���^�[���X�V����

	if (m_nCntTime <= 0)
	{//�X�|�[������
		if (m_nMaxSpawn > 60)
		{//�X�|�[�����Ԃ�ݒ肷��(1�b�ȉ���������A���̂܂ܐݒ肷��B1�b�ȏゾ������A�����_���Ō��߂܂�)
			m_nCntTime = CObject::random(60, m_nMaxSpawn);
		}
		else
		{
			m_nCntTime = m_nMaxSpawn;
		}

		//�����_���Ō��������߂܂�
		float fX, fZ, fDir;

		if (random(1, 101) % 2 == 0)
		{
			fDir = 1.0f;
		}
		else
		{
			fDir = -1.0f;
		}

		//�X�|�[���ʒu�̐ݒ�
		fX = m_pos.x + (fDir * ((float)random(5, (int)m_laterlBounds)));
		fZ = m_pos.z + (((float)random(-(int)m_fAreaLength, (int)m_fAreaLength)));

		//�I�u�W�F�N�g�𐶐�����
		CIcePillar::Create(CModel::MODEL_ICE_PILLAR, D3DXVECTOR3(fX, m_pos.y, fZ), m_shadowY);
	}
}

//�`�揈��
void CIcePillarSpawner::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CIcePillarSpawner::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CIcePillarSpawner::GetPos(void)
{
	return m_pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CIcePillarSpawner::GetSize(void)
{
	return Vec2Null;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CIcePillarSpawner* CIcePillarSpawner::Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fLaterlBounds, const float fLength, const int nMaxTime)
{
	CIcePillarSpawner* pSpawner = new CIcePillarSpawner;			//�I�u�W�F�N�g�𐶐�����

	if (FAILED(pSpawner->Init()))
	{//����������
		return nullptr;
	}

	int nTime = nMaxTime;				//�X�|�[�����Ԃ̐ݒ�

	if (nMaxTime <= 0)
	{//�X�|�[�����Ԃ�1�ȉ��ł͂Ȃ��悤�Ɋm�F����
		nTime = 1;
	}

	pSpawner->m_pos = pos;								//�ʒu�̐ݒ�
	pSpawner->m_shadowY = fShadowHeight;				//�e�̍����̐ݒ�
	pSpawner->m_laterlBounds = fLaterlBounds;			//�X�|�[���G���A�̕��̐ݒ�
	pSpawner->m_nMaxSpawn = nTime;						//�ő�X�|�[�����Ԃ̐ݒ�
	pSpawner->m_nCntTime = 400;							//�f�B���C�̐ݒ�
	pSpawner->m_fAreaLength = fLength;					//�X�|�[���G���A�̒����̐ݒ�

	return pSpawner;
}