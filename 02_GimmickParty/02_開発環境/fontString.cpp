//=============================================================================
//
// fontString.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "fontString.h"
#include "Application.h"

static const int ScaleSpeed = 4;		// �g�呬�x

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CFontString::CFontString()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CFontString::~CFontString()
{

}

//=====================================
// ����������
//=====================================
HRESULT CFontString::Init(void)
{
	m_nNum = 0;				// �������̏�����
	m_fScale = 0.0f;		// �����̑傫��������
	m_bScale = false;		// �����̊g�唻�菉����
	m_bSellect = false;		// �����̑I�𔻒菉����
	
	return S_OK;
}

//=====================================
// �I������
//=====================================
void CFontString::Uninit(void)
{
	for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
	{// ������̏I������
		if (m_pFont[nCnt] != nullptr)
		{
			m_pFont[nCnt]->Release();
			m_pFont[nCnt] = nullptr;
		}
	}
}

//=====================================
// �X�V����
//=====================================
void CFontString::Update(void)
{
	SizeScale();	// �����̊g�又��
}

//=====================================
// �T�C�Y�ύX����
//=====================================
void CFontString::SizeScale(void)
{
	// ���݂��̑I�������I������Ă���ꍇ
	if (m_bSellect == true)
	{
		if (m_bScale == false)
		{// �������g�債�Ă���ꍇ
			m_fScale += ScaleSpeed / 10.0f;
			if (m_fScale > 5.0f)
			{// ���������̒l�܂Ŋg�債���ꍇ
				m_bScale = true;	// �������k��������
			}
		}
		else
		{// �������k�����Ă���ꍇ
			m_fScale -= ScaleSpeed / 10.0f;
			if (m_fScale < -5.0f)
			{// ���������̒l�܂ŏk�������ꍇ
				m_bScale = false;	// �������g�傳����
			}
		}

		for (int nCnt = 0; nCnt < m_nNum; nCnt++)
		{// �����̑傫���ݒ菈��
			m_pFont[nCnt]->SetSize(D3DXVECTOR2(m_sizeYuan.x + m_fScale, m_sizeYuan.y + m_fScale));
		}
	}
}

//=====================================
// �T�C�Y���Z�b�g����
//=====================================
void CFontString::SizeReset(void)
{
	m_bSellect = false;	// �����I�𔻒�̏�����
	m_fScale = 0.0f;	// �����̑傫���̏�����
	m_bScale = false;	// �����̊g�又���̏�����

	for (int nCnt = 0; nCnt < m_nNum; nCnt++)
	{// �����̑傫���ݒ菈��
		m_pFont[nCnt]->SetSize(D3DXVECTOR2(m_sizeYuan.x + m_fScale, m_sizeYuan.y + m_fScale));
	}
}

//=====================================
// �F�̐ݒ菈��
//=====================================
void CFontString::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < m_nNum; nCnt++)
	{// �����̐F�ݒ菈��
		m_pFont[nCnt]->SetColor(col);
	}
}

//=====================================
// ���ݔԍ��̐ݒ菈��
//=====================================
void CFontString::SetSellect(void)
{
	m_bSellect = true;
}

//=====================================
// ��������
//=====================================
CFontString* CFontString::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const std::string letter)
{
	CFontString* pFontString = new CFontString;
	
	if (FAILED(pFontString->Init()))
	{
		return nullptr;
	}

	for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
	{// �����̏�����
		pFontString->m_pFont[nCnt] = nullptr;
	}

	// string�^�̕��������擾
	int nTex = strlen(letter.c_str());

	float maxSizeX = size.x * 2;	// �T�C�Y2���̊Ԋu���󂯂�
	for (int nLatter = 0; nLatter < nTex; nLatter += 2)
	{
		// ���݈ʒu����1�����i�ޏ���
		std::string sLatter = letter.substr(nLatter, 2);

		// �����𒆉��ɔz�u���Astring�^����*char�^��1���������o��
		if (nTex / 2 % 2 == 1)
		{
			pFontString->m_pFont[pFontString->m_nNum] = CFont::Create(D3DXVECTOR3(pos.x - (maxSizeX * (nTex / 4)) + ((maxSizeX * pFontString->m_nNum)), pos.y, pos.z), size, sLatter.c_str());
		}
		else
		{
			pFontString->m_pFont[pFontString->m_nNum] = CFont::Create(D3DXVECTOR3(pos.x - (maxSizeX * ((nTex / 4) - 1)) + (maxSizeX * pFontString->m_nNum) - (maxSizeX / 2), pos.y, pos.z), size, sLatter.c_str());
		}

		// �ŏ��̃T�C�Y��o�^����
		pFontString->m_sizeYuan = size;

		// �ԍ�������U��
		pFontString->m_nNum++;
	}

	return pFontString;
}