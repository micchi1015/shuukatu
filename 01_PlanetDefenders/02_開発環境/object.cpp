//------------------------------
//
// �I�u�W�F�N�g�̏���[object.cpp]
// Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include "object.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
CObject *CObject::m_apObject[MAX_PRI][MAX_DATA] = {};		//Object�̔z��
int CObject::m_nNumAll = 0;									//�I�u�W�F�N�g�̐�

//�R���X�g���N�^
CObject::CObject(int nPriority /*=3*/)
{
	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		if (m_apObject[nPriority][nCnt] == nullptr)
		{
			m_apObject[nPriority][nCnt] = this;

			m_nID = nCnt;
			m_nPriority = nPriority;

			m_nNumAll++;
			break;
		}
	}

	m_type = OBJTYPE_NONE;
}

//�f�X�g���N�^
CObject::~CObject()
{
}

//�S�Ẵ|���S���̔j������
void CObject::ReleaseAll()
{
	for (int nCount = 0; nCount < MAX_PRI; nCount++)
	{
		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			if (m_apObject[nCount][nCnt] != nullptr)
			{
				m_apObject[nCount][nCnt]->Uninit();
			}
		}
	}
}

//�X�V����
void CObject::UpdateAll()
{
	for (int nCount = 0; nCount < MAX_PRI; nCount++)
	{
		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			if (m_apObject[nCount][nCnt] != nullptr)
			{
				m_apObject[nCount][nCnt]->Update();
			}
		}
	}
}

//�`�揈��
void CObject::DrawAll()
{
	for (int nCount = 0; nCount < MAX_PRI; nCount++)
	{
		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			if (m_apObject[nCount][nCnt] != nullptr)
			{
				m_apObject[nCount][nCnt]->Draw();
			}
		}
	}
}

//�j��
void CObject::ReleaseMode()
{
	for (int nCount = 0; nCount < MAX_PRI; nCount++)
	{
		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			if (m_apObject[nCount][nCnt] != nullptr)
			{
				if (m_apObject[nCount][nCnt]->GetType() != OBJTYPE_MODE)
				{
					// �I��
					m_apObject[nCount][nCnt]->Uninit();
				}
			}
		}
	}
}

//�j������
void CObject::Release()
{
	if (m_apObject[m_nPriority][m_nID] != nullptr)
	{
		const int nID = m_nID;
		const int nPri = m_nPriority;

		delete m_apObject[nPri][nID];
		m_apObject[nPri][nID] = nullptr;
		m_nNumAll--;
	}
}

//move�̏��擾
D3DXVECTOR3 CObject::GetMove()
{
	return m_move;
}

//move�̐ݒ�
void CObject::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//�^�C�v���擾
CObject::EObjType CObject::GetType()
{
	return m_type;
}

//�^�C�v�̐ݒ�
void CObject::SetType(const EObjType type)
{
	m_type = type;
}

//�I�u�W�F�N�g�̏��擾
CObject * CObject::GetMyObject(int nPriority,int nCnt)
{
	return m_apObject[nPriority][nCnt];
}

//move��vec�����Z
void CObject::AddMove(D3DXVECTOR3 vec)
{
	m_move += vec;
	SetMove(m_move);

	if (m_move.x <= -10.0f)
	{
		m_move.x = -10.0f;
	}
}

//move��vec�����Z
void CObject::SubMove(D3DXVECTOR3 vec)
{
	m_move -= vec;
	SetMove(m_move);

	if (m_move.x <= -10.0f)
	{
		m_move.x = -10.0f;
	}
}