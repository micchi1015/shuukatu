//=============================================================================
//
// object.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include "application.h"
#include <random>

//=============================================================================
//�ÓI�����o�[�ϐ��̐錾 
//=============================================================================
CObject* CObject::m_pTop[CObject::Max_Priority] = {};				//�擪�̃I�u�W�F�N�g�ւ̃|�C��
CObject* CObject::m_pCurrent[CObject::Max_Priority] = {};			//����(��Ԍ��)�̃I�u�W�F�N�g�ւ̃|���^

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CObject::CObject()
{
	if (m_pCurrent[2] != nullptr)
	{//�I�u�W�F�N�g��������������
		m_pCurrent[2]->m_pNext = this;		//�O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�ւ̃|�C���^��ݒ肷��
		m_pPrev = m_pCurrent[2];			//�O�̃I�u�W�F�N�g�ւ̃|�C���^�̐ݒ�
		m_pCurrent[2] = this;				//���݂̃I�u�W�F�N�g�̍X�V
	}
	else
	{//�܂��I�u�W�F�N�g���Ȃ�������
		m_pTop[2] = this;					//�擪�̃I�u�W�F�N�g�ւ̃|�C�������̃C���X�^���X�̃A�h���X�ɂ���
		m_pCurrent[2] = this;				//����(��Ԍ��)�̃I�u�W�F�N�g�ւ̃|���^�����̃C���X�^���X�̃A�h���X�ɂ���
		m_pPrev = nullptr;					//�O�̃I�u�W�F�N�g�ւ̃|�C���^��null�ɐݒ肷��
	}

	m_pNext = nullptr;						//���̃I�u�W�F�N�g�ւ̃|�C���^��null�ɂ���

	m_nPriority = 3;						//�v���C�I���e�B��3�ɐݒ肷��
	m_bDeath = false;						//���S�t���O��false�ɐݒ肷��
}

CObject::CObject(int nPriority)
{
	if (m_pCurrent[nPriority - 1] != nullptr)
	{//�I�u�W�F�N�g���ɑ��݂���ꍇ
		m_pCurrent[nPriority - 1]->m_pNext = this;		//�O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�ւ̃|�C���^��ݒ肷��	
		m_pPrev = m_pCurrent[nPriority - 1];			//�O�̃I�u�W�F�N�g�ւ̃|�C���^�̐ݒ�
		m_pCurrent[nPriority - 1] = this;				//���݂̃I�u�W�F�N�g�̍X�V
	}
	else
	{//����͍ŏ��̃I�u�W�F�N�g��������	
		m_pTop[nPriority - 1] = this;					//�擪�̃I�u�W�F�N�g�ւ̃|�C�������̃C���X�^���X�̃A�h���X�ɂ���
		m_pCurrent[nPriority - 1] = this;				//����(��Ԍ��)�̃I�u�W�F�N�g�ւ̃|���^�����̃C���X�^���X�̃A�h���X�ɂ���
		m_pPrev = nullptr;								//�O�̃I�u�W�F�N�g�ւ̃|�C���^��null�ɐݒ肷��
	}

	m_pNext = nullptr;									//���̃I�u�W�F�N�g�ւ̃|�C���^��null�ɂ���

	m_nPriority = nPriority;							//���S�t���O��false�ɐݒ肷��
}														

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CObject::~CObject()
{

}

//�I�u�W�F�N�g����������
void CObject::Release(void)
{
	Uninit();				//�I������
	m_bDeath = true;		//���S�t���O��true�ɂ���
}

//�v���C�I���e�B�̐ݒ菈��
void CObject::SetPriority(int nPriority)
{
	//�v���C�I���e�B���͈͊O�ł͂Ȃ��悤�Ɋm�F����
	if (nPriority < 1)
	{
		nPriority = 1;
	}
	else if(nPriority > 5)
	{
		nPriority = 5;
	}
	
	if (m_pPrev != nullptr)
	{//�O�̃I�u�W�F�N�g�ւ̃|�C���^��null�ł͂Ȃ�������
		if (m_pNext != nullptr)
		{//�O�̃I�u�W�F�N�g�ւ̃|�C���^��null�ł͂Ȃ�������
			//�O�̃I�u�W�F�N�g�Ǝ��̃I�u�W�F�N�g���q��
			m_pPrev->m_pNext = m_pNext;			
			m_pNext->m_pPrev = m_pPrev;			
		}
		else
		{//���̃I�u�W�F�N�g����Ԍ�낾������A�O�̃I�u�W�F�N�g����Ԍ��ɂ���
			m_pPrev->m_pNext = nullptr;					
			m_pCurrent[m_nPriority - 1] = m_pPrev;		
		}
	}
	else
	{//�O�̃I�u�W�F�N�g�ւ̃|�C���^��null��������
		if (m_pNext != nullptr)
		{//���̃I�u�W�F�N�g�ւ̃|�C���^��null�ł͂Ȃ�������A���̃I�u�W�F�N�g��擪�ɂ���
			m_pNext->m_pPrev = nullptr;
			m_pTop[m_nPriority - 1] = m_pNext;
		}
		else
		{//���̃I�u�W�F�N�g�����Ȃ�������A�ÓI�ϐ���null�ɂ���
			m_pTop[m_nPriority - 1] = nullptr;
			m_pCurrent[m_nPriority - 1] = nullptr;
		}
	}

	m_nPriority = nPriority;			//�v���C�I���e�B�̐ݒ菈��

	//�V�����v���C�I���e�B�̔z��ɓ����
	if (m_pCurrent[nPriority - 1] != nullptr)
	{//���̃v���C�I���e�B�̔z��ɃI�u�W�F�N�g�����ɂ�������A��Ԍ��̃I�u�W�F�N�g�Ƃ��ē����
		m_pCurrent[nPriority - 1]->m_pNext = this;		
		m_pPrev = m_pCurrent[nPriority - 1];			
		m_pCurrent[nPriority - 1] = this;				
	}
	else
	{//���̃v���C�I���e�B�̔z��̍ŏ��̃I�u�W�F�N�g��������A���ʂɓ����
		m_pTop[nPriority - 1] = this;
		m_pCurrent[nPriority - 1] = this;
		m_pPrev = nullptr;
	}

	m_pNext = nullptr;			//���̃I�u�W�F�N�g�ւ̃|�C���^��null�ɂ���
}

//===============================================================================
//
//								�ÓI�֐�
//
//===============================================================================

//=============================================================================
//�S���̏I������
//=============================================================================
void CObject::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject* pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{
				CObject* pNext = pCurrent->m_pNext;

				if (pCurrent->m_pPrev != nullptr)
				{
					if (pCurrent->m_pNext != nullptr)
					{//���X�g�̒���������
						pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;
						pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;
					}
					else
					{//���X�g�̍Ō�̃I�u�W�F�N�g��������
						pCurrent->m_pPrev->m_pNext = nullptr;
						m_pCurrent[pCurrent->m_nPriority - 1] = pCurrent->m_pPrev;
					}
				}
				else
				{
					if (pCurrent->m_pNext != nullptr)
					{//���X�g�̍ŏ��̃I�u�W�F�N�g��������
						pCurrent->m_pNext->m_pPrev = nullptr;
						m_pTop[pCurrent->m_nPriority - 1] = pCurrent->m_pNext;
					}
					else
					{//���̃I�u�W�F�N�g�����Ȃ��ꍇ
						m_pTop[pCurrent->m_nPriority - 1] = nullptr;
						m_pCurrent[pCurrent->m_nPriority - 1] = nullptr;
					}
				}

				pCurrent->Uninit();			//�I������
				delete pCurrent;			//���������������

				pCurrent = pNext;
			}
		}
	}
}

//=============================================================================
//�S���̍X�V����
//=============================================================================
void CObject::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject* pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{
				CObject* pNext = pCurrent->m_pNext;

				if (!pCurrent->m_bDeath)
				{
					if (CApplication::GetPause() == false)
					{// �|�[�Y���ł͂Ȃ��ꍇ
						pCurrent->Update();
					}
					else if(pCurrent->m_nPriority >= 4)
					{// UI�͓�����
						pCurrent->Update();
					}
				}
				pCurrent = pNext;
			}
		}
	}

	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject* pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{

				CObject* pNext = pCurrent->m_pNext;

				if (pCurrent->m_bDeath)
				{
					if (pCurrent->m_pPrev != nullptr)
					{
						if (pCurrent->m_pNext != nullptr)
						{//���X�g�̒���������
							pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;
							pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;
						}
						else
						{//���X�g�̍Ō�̃I�u�W�F�N�g��������
							pCurrent->m_pPrev->m_pNext = nullptr;
							m_pCurrent[pCurrent->m_nPriority - 1] = pCurrent->m_pPrev;
						}
					}
					else
					{
						if (pCurrent->m_pNext != nullptr)
						{//���X�g�̍ŏ��̃I�u�W�F�N�g��������
							pCurrent->m_pNext->m_pPrev = nullptr;
							m_pTop[pCurrent->m_nPriority - 1] = pCurrent->m_pNext;
						}
						else
						{//���̃I�u�W�F�N�g�����Ȃ��ꍇ
							m_pTop[pCurrent->m_nPriority - 1] = nullptr;
							m_pCurrent[pCurrent->m_nPriority - 1] = nullptr;
						}
					}

					//pCurrent->Uninit();
					delete pCurrent;
				}

				pCurrent = pNext;
			}
		}
	}
}

//=============================================================================
//�S���̕`�揈��
//=============================================================================
void CObject::DrawAll(void)
{
	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject* pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{
				if (!pCurrent->m_bDeath)
				{
					pCurrent->Draw();
				}

				pCurrent = pCurrent->m_pNext;
			}
		}
	}
}

//=============================================================================
//��������
//=============================================================================

//�I�u�W�F�N�g�̎擾����
CObject** CObject::GetObj(void)
{
	return &m_pTop[0];
}

std::random_device rd;
std::mt19937 gen(rd());

//������Ԃ�����
int CObject::random(const int low, const int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}