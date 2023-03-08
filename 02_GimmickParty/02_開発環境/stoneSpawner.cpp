//=============================================================================
//
// stoneSpawner.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stoneSpawner.h"
#include "fallingStone.h"

//�R���X�g���N�^
CStoneSpawner::CStoneSpawner()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;				//�ʒu
	m_shadowY = 0.0f;				//�e�̍���
	m_laterlBounds = 0.0f;  		//���̌��E
	m_nCntTime = 0;					//�t���[���J�E���^�[
	m_nSpawnTime = 0;				//�X�|�[���^�C��
	m_nMaxSpawn = 0;				//�ő�^�C��
	m_fAreaLength = 0.0f;			//�X�|�[���G���A�̒���
}

//�f�X�g���N�^
CStoneSpawner::~CStoneSpawner()
{

}

//����������
HRESULT CStoneSpawner::Init(void)
{
	m_pos = Vec3Null;				//�ʒu
	m_shadowY = 0.0f;				//�e�̍���
	m_laterlBounds = 0.0f;  		//���̌��E
	m_nCntTime = 0;					//�t���[���J�E���^�[
	m_nSpawnTime = 0;				//�X�|�[���^�C��
	m_nMaxSpawn = 0;				//�ő�^�C��
	m_fAreaLength = 0.0f;			//�X�|�[���G���A�̒���

	return S_OK;
}

//�I������
void CStoneSpawner::Uninit(void)
{

}

//�X�V����
void CStoneSpawner::Update(void)
{
	m_nCntTime--;					//�X�|�[���J�E���^�[���X�V����

	if (m_nCntTime <= 0)
	{//0�ɂȂ�����A

		//���̃I�u�W�F�N�g�̃X�|�[���f�B���C��ݒ肷��(�ő�X�|�[�����Ԃ�1�b�ȉ���������A���̂܂܎g���܂��B�����ł͂Ȃ�������A1�b����ݒ肳�ꂽ���Ԃ܂Ń����_���Ō��߂܂�)
		if (m_nMaxSpawn > 60)
		{
			m_nCntTime = CObject::random(60, m_nMaxSpawn);
		}
		else
		{
			m_nCntTime = m_nMaxSpawn;
		}

		//�X�|�[���G���A�������_���ŃX�|�[���̈ʒu�����߂܂�
		float fX, fZ, fDir;

		if (random(1, 101) % 2 == 0)
		{
			fDir = 1.0f;
		}
		else
		{
			fDir = -1.0f;
		}

		fX = m_pos.x + (fDir * ((float)random(5, (int)m_laterlBounds)));
		fZ = m_pos.z + (((float)random(-(int)m_fAreaLength, (int)m_fAreaLength)));

		//�I�u�W�F�N�g�𐶐�����
		CFallingStone::Create(CModel::MODEL_FALLING_STONE, D3DXVECTOR3(fX, m_pos.y, fZ), m_pos, m_shadowY, m_laterlBounds, fDir);
	}
}

//�`�揈��
void CStoneSpawner::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CStoneSpawner::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CStoneSpawner::GetPos(void)
{
	return m_pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CStoneSpawner::GetSize(void)
{
	return Vec2Null;
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================




//��������
CStoneSpawner* CStoneSpawner::Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fLaterlBounds, const float fLength, const int nMaxTime)
{
	CStoneSpawner* pSpawner = new CStoneSpawner;			//�C���X�^���X�𐶐�����

	if (FAILED(pSpawner->Init()))
	{//����������
		return nullptr;
	}

	//�ő�X�|�[�����Ԃ̐ݒ�
	int nTime = nMaxTime;

	if (nMaxTime <= 0)
	{//0�t���[���ȉ���������A1�t���[���ɐݒ肷��
		nTime = 1;
	}

	pSpawner->m_pos = pos;							//�ʒu�̐ݒ�
	pSpawner->m_shadowY = fShadowHeight;			//�e�̍����̐ݒ�
	pSpawner->m_laterlBounds = fLaterlBounds;		//�X�|�[���G���A�̕��̐ݒ�
	pSpawner->m_nMaxSpawn = nTime;					//�ő�X�|�[�����Ԃ̐ݒ�
	pSpawner->m_nCntTime = 400;						//�X�|�[���J�E���^�[�̏�����
	pSpawner->m_fAreaLength = fLength;				//�X�|�[���G���A�̒���

	//�G���A�̑O�̃��f���̐���
	CModel* pModel = CModel::Create(CModel::MODEL_CAUTION_SIGNAL, D3DXVECTOR3(pos.x - fLaterlBounds, fShadowHeight, pos.z - fLength));
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));				//�����̐ݒ�

	pModel = CModel::Create(CModel::MODEL_CAUTION_SIGNAL, D3DXVECTOR3(pos.x + fLaterlBounds, fShadowHeight, pos.z - fLength));
	pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));				//�����̐ݒ�
	pModel->SetShadowDraw(false);									//�e��`�悵�Ȃ��悤�ɐݒ肷��

	return pSpawner;								//���������C���X�^���X��Ԃ�
}