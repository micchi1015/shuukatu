//=============================================================================
//
// font.cpp
// Author : tanimoto kosuke
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "font.h"

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CFont::CFont()
{

}

CFont::CFont(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CFont::~CFont()
{

}

//=====================================
// ����������
//=====================================
HRESULT CFont::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CFont::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//=====================================
// �X�V����
//=====================================
void CFont::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//=====================================
// �`�揈��
//=====================================
void CFont::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

//=====================================
// ��������
//=====================================
CFont* CFont::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* letter)
{
	CFont* pFont = new CFont(5);		//����(Priority = 5)

	//����������
	if (FAILED(pFont->Init()))
	{
		return nullptr;
	}

	pFont->SetPos(pos);									//�ʒu�̐ݒ�
	pFont->SetSize(size);								//�T�C�Y�̐ݒ�

	pFont->SetTexture(CObject::TEXTURE_JAPANESE);		//�e�N�X�`���̐ݒ�
	pFont->SetTextureParameter(1, 20, 10, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 0;

	// �Ђ炪��(-126)�Ɣz��[0]����v����ꍇ
	if (letter[0] == -126)
	{
		int aLetter = -97;	// �ŏ��̕������n�܂�ʒu(-97)

		for (int nCnt = 0; nCnt < 83; nCnt++)
		{// �摜�̂Ђ炪��83��������1��؂���
			if (letter[1] == aLetter + nCnt)
			{// ���͂��ꂽ�����ƌ��݂̕�������v�����ꍇ
				Cell = nCnt;	// �����̈ʒu����
				break;
			}
		}

		// "��"�܂őΉ�
		if (Cell < 0 || Cell > 83)
		{
			pFont->Release();
			return nullptr;
		}
		else
		{
			pFont->SetAnimPattern(Cell);	// �摜�̎w�肳�ꂽ�����̕����݂̂�؂���
		}
	}
	// �J�^�J�i(-125)�Ɣz��[0]����v����ꍇ
	else if (letter[0] == -125)
	{
		// "�~"�܂ł̃J�^�J�i
		if (letter[1] >= 64)
		{
			int aLetter = 64;	// �ŏ��̕������n�܂�ʒu(64)
			int aKatakana = 96;	// �J�^�J�i���n�܂�ʒu(96)

			for (int nCnt = 0; nCnt < 63; nCnt++)
			{// �摜�̃J�^�J�i63��������1��؂���
				if (letter[1] == aLetter + nCnt)
				{// ���͂��ꂽ�����ƌ��݂̕�������v�����ꍇ
					Cell = nCnt + aKatakana;	// �����̈ʒu����
					break;
				}
			}

			if (Cell < aKatakana || Cell > aKatakana + 63)
			{// �摜�̃J�^�J�i63��������1��؂���
				pFont->Release();
				return nullptr;
			}
			else
			{
				pFont->SetAnimPattern(Cell);	// �摜�̎w�肳�ꂽ�����̕����݂̂�؂���
			}
		}
		// "��"�ȍ~�̃J�^�J�i
		else
		{
			int aLetter = -128;		// �ŏ��̕������n�܂�ʒu(-128)
			int aKatakana = 159;	// �J�^�J�i���n�܂�ʒu(159)

			for (int nCnt = 0; nCnt < 23; nCnt++)
			{// �摜�̃J�^�J�i23��������1��؂���
				if (letter[1] == aLetter + nCnt)
				{// ���͂��ꂽ�����ƌ��݂̕�������v�����ꍇ
					Cell = nCnt + aKatakana;	// �����̈ʒu����
					break;
				}
			}

			if (Cell < aKatakana || Cell > aKatakana + 23)
			{// �摜�̃J�^�J�i23��������1��؂���
				pFont->Release();
				return nullptr;
			}
			else
			{
				pFont->SetAnimPattern(Cell);	// �摜�̎w�肳�ꂽ�����̕����݂̂�؂���
			}
		}
	}
	// �L��(-127)�Ɣz��[0]����v����ꍇ
	else if (letter[0] == -127)
	{
		if (letter[1] == -127)
		{
			pFont->SetAnimPattern(95);	//��
		}
		else if (letter[1] == 69)
		{
			pFont->SetAnimPattern(186);	//�E
		}
		else if (letter[1] == 91)
		{
			pFont->SetAnimPattern(187);	//�[
		}
	}

	return pFont;
}