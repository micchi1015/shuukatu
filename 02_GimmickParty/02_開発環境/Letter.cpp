//=============================================================================
//
// Letter.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "Letter.h"
#include <string>

//�R���X�g���N�^
CLetter::CLetter()
{			
	m_pPreviousLetter = nullptr;			//�O�̕���
	m_pNextLetter = nullptr;				//���̕���
}

//�R���X�g���N�^
CLetter::CLetter(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{
	m_pPreviousLetter = nullptr;			//�O�̕���
	m_pNextLetter = nullptr;				//���̕���
}

//�f�X�g���N�^
CLetter::~CLetter()
{

}

//����������
HRESULT CLetter::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_pPreviousLetter = nullptr;		//�O�̕���
	m_pNextLetter = nullptr;			//���̕���

	return S_OK;
}

//�I������
void CLetter::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CLetter::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�I������
void CLetter::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

//�����̕ϊ�����
bool CLetter::Convert(const char symbol)
{
	char aLetter = 33;		//Unicode��!(10�i��)

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 27;

	for (int nCnt = 0; nCnt < 93; nCnt++)
	{//~�܂Ŋm�F����
		if (symbol == aLetter)
		{//������������A�ԍ���ۑ����āA�~�܂�
			Cell = nCnt;
			break;
		}

		aLetter += 1;			
	}

	if (Cell < 0 || Cell > 93)
	{//�͈͊O�̕�����������Afalse��Ԃ�
		return false;
	}
	else
	{//�ϊ��o������A�A�j���[�V�����p�^�[����ݒ肵�āAtrue��Ԃ�
		SetAnimPattern(Cell);
		return true;
	}
}

//�O�̕����̐ݒ菈��
void CLetter::SetPrevLetter(CLetter* pPrev)
{
	m_pPreviousLetter = pPrev;
}

//���̕����̐ݒ菈��
void CLetter::SetNextLetter(CLetter* pNext)
{
	m_pNextLetter = pNext;
}

//�O�̕����̎擾����
CLetter* CLetter::GetPrevLetter(void)
{
	return m_pPreviousLetter;
}

//���̕����̐ݒ菈��
CLetter* CLetter::GetNextLetter(void)
{
	return m_pNextLetter;
}


//==================================================================================================================
//
//											�ÓI�֐�
//
//==================================================================================================================

//��������
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter)
{
	CLetter* pLetter = new CLetter(3);								//����

	//����������
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}

	pLetter->SetPos(pos);									//�ʒu�̐ݒ�
	pLetter->SetSize(size);									//�T�C�Y�̐ݒ�
															
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);		//�e�N�X�`���̐ݒ�
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	char aLetter = 33;				//Unicode��!(10�i��)

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 27;

	for (int nCnt = 0; nCnt < 93; nCnt++)
	{//~�܂Ŋm�F����
		if (letter == aLetter)
		{//������������A�ԍ���ۑ����āA�~�܂�
			Cell = nCnt;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 0 || Cell > 93)
	{//�͈͊O�̕�����������Afalse��Ԃ�
			pLetter->Release();
			return nullptr;
	}
	else
	{//�ϊ��o������A�A�j���[�V�����p�^�[����ݒ肵�āAtrue��Ԃ�
		pLetter->SetAnimPattern(Cell);
	}

	return pLetter;				//���������C���X�^���X��Ԃ�
}

CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter, const int nPriority)
{
	CLetter* pLetter = new CLetter(nPriority);						//����

	//����������
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}
	
	pLetter->SetPos(pos);									//�ʒu�̐ݒ�
	pLetter->SetSize(size);									//�T�C�Y�̐ݒ�
	//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//��]�p�x�̐ݒ�
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);		//�e�N�X�`���̐ݒ�
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	char aLetter = 33;				//Unicode��!(10�i��)

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 27;

	for (int nCnt = 0; nCnt < 93; nCnt++)
	{//~�܂Ŋm�F����
		if (letter == aLetter)
		{//������������A�ԍ���ۑ����āA�~�܂�
			Cell = nCnt;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 0 || Cell > 93)
	{//�͈͊O�̕�����������Afalse��Ԃ�
		pLetter->Release();
		return nullptr;
	}
	else
	{//�ϊ��o������A�A�j���[�V�����p�^�[����ݒ肵�āAtrue��Ԃ�
		pLetter->SetAnimPattern(Cell);
	}

	return pLetter;				//���������C���X�^���X��Ԃ�
} 