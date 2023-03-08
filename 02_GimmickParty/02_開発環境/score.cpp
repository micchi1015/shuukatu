//=============================================================================
//
// score.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score.h"


std::vector <CScore*> CScore::m_vScore;

//�R���X�g���N�^
CScore::CScore()
{
	//�����o�[�ϐ����N���A����
	m_nScore = 0;				//�X�R�A
	m_nPlayerIdx = 0;			//�v���C���[�C���f�b�N�X
}

//�f�X�g���N�^
CScore::~CScore()
{

}

//����������
HRESULT CScore::Init(void)
{
	//����������
	m_nScore = 50;					//�X�R�A
	m_nPlayerIdx = -1;				//�v���C���[�C���f�b�N�X

	return S_OK;
}

//�I������
void CScore::Uninit(void)
{

}

//�X�R�A�𑫂�����
void CScore::AddScore(const int nScore)
{
	m_nScore += nScore;				//�X�R�A�����Z����

	if (m_nScore < 0)
	{//�X�R�A��0�ȉ��ɂȂ�����A0�ɖ߂�
		m_nScore = 0;
	}
}

//�X�R�A���擾����
const int CScore::GetScore(void)
{
	return m_nScore;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================




//�X�R�A�𑫂�����
void CScore::AddScore(const int nPlayerIdx, const int nScore)
{
	m_vScore.data()[nPlayerIdx]->AddScore(nScore);				//�X�R�A�����Z����

	int score = m_vScore.data()[nPlayerIdx]->GetScore();		//�X�R�A�̎擾

	if (score < 0)
	{//�X�R�A��0�ȉ��ɂȂ�����A0�ɖ߂�
		m_vScore.data()[nPlayerIdx]->AddScore(-score);
	}
}

//�X�R�A���擾����
const int CScore::GetScore(const int nPlayerIdx)
{
	return m_vScore.data()[nPlayerIdx]->m_nScore;
}


//�N���A����
void CScore::Clear(void)
{
	//�X�R�A�̃C���X�^���X��S���j������
	for (int nCnt = 0; nCnt < (int)m_vScore.size(); nCnt++)
	{
		m_vScore.data()[nCnt]->Uninit();
		delete m_vScore.data()[nCnt];
		m_vScore.data()[nCnt] = nullptr;
	}

	m_vScore.clear();
}

//��������
CScore* CScore::Create(const int nPlayerIdx)
{
	CScore* pScore = new CScore;			//�C���X�^���X�𐶐�����

	if (FAILED(pScore->Init()))
	{//����������
		return nullptr;
	}

	pScore->m_nPlayerIdx = nPlayerIdx;			//�v���C���[�C���f�b�N�X�̐ݒ�

	m_vScore.push_back(pScore);					//�X�R�A��ۑ�����
	
	return pScore;								//���������C���X�^���X��Ԃ�
}