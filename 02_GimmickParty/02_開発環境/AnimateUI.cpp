//=============================================================================
//
// AnimateUI.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "AnimateUI.h"


const D3DXCOLOR CAnimateUI::targetCol[6] =
{
	ColorRed,						//��
	ColorYellow,					//��
	ColorGreen,						//��
	ColorCyan,						//�V�A��
	ColorBlue,						//��
	ColorMagenta					//�}�[���^
};

//�R���X�g���N�^
CAnimateUI::CAnimateUI()
{
	//�����o�[�ϐ����N���A����
	ZeroMemory(&m_AnimInfo, sizeof(m_AnimInfo));		//�A�j���[�V�������
	m_nCntAnim = 0;										//�A�j���[�V�����J�E���^�[
	m_bAnimateColor = false;							//�J�[���[�A�j���[�V���������邩�ǂ���
	m_ntargetCol = 0;									//�ړI�̃J�[���[�ԍ�
	m_deltaCol = ColorNull;								//�J�[���[�̌���
}

//�f�X�g���N�^
CAnimateUI::~CAnimateUI()
{

}

//����������
HRESULT CAnimateUI::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	ZeroMemory(&m_AnimInfo, sizeof(m_AnimInfo));	//�A�j���[�V�������
	m_nCntAnim = 0;									//�A�j���[�V�����J�E���^�[
	m_bAnimateColor = false;						//�J�[���[�A�j���[�V���������邩�ǂ���
	m_deltaCol = ColorNull;							//�J�[���[�̌���
	m_ntargetCol = 0;								//�ړI�̃J�[���[�ԍ�

	return S_OK;
}

//�I������
void CAnimateUI::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CAnimateUI::Update(void)
{
	if (m_AnimInfo.nChangeTime != 0)
	{//�A�j���[�V�������Ԃ�0�ł͂Ȃ��ꍇ

		m_nCntAnim++;			//�J�E���^�[���C���N�������g����

		if (m_nCntAnim >= m_AnimInfo.nChangeTime)
		{//�ݒ肵�����Ԃ𒴂�����

			m_AnimInfo.deltaSize.x *= -1.0f;		//�T�C�Y�A�j���[�V�������t�ɂ���
			m_AnimInfo.deltaSize.y *= -1.0f;		//�T�C�Y�A�j���[�V�������t�ɂ���
			m_nCntAnim = 0;							//�J�E���^�[��0�ɖ߂�

			if (m_bAnimateColor)
			{//�J�[���[�A�j���[�V�����̏ꍇ

				m_ntargetCol++;				//�ړI�̃J�[���[�̍X�V

				if (m_ntargetCol >= 6)
				{//�Ō�̃J�[���[�𒴂�����
					m_ntargetCol = 0;			//���ɖ߂�
				}

				D3DXCOLOR target = targetCol[m_ntargetCol];			//�ړI�̃J�[���[��ݒ肷��
				D3DXCOLOR col = GetColor();							//���݂̃J�[���[��ݒ肷��

				//�J�[���[�̌������v�Z����
				m_deltaCol = target - col;							
				m_deltaCol.r /= m_AnimInfo.nChangeTime;				
				m_deltaCol.g /= m_AnimInfo.nChangeTime;				
				m_deltaCol.b /= m_AnimInfo.nChangeTime;				
				m_deltaCol.a = 0.0f;								
			}
		}

		D3DXVECTOR2 size = GetSize();				//���݂̃T�C�Y�̎擾

		size -= m_AnimInfo.deltaSize;				//�T�C�Y�̍X�V

		//�T�C�Y��0�ȉ��ɂȂ�Ȃ��悤��
		if (size.x < 0.0f)
		{
			size.x = 0.0f;
		}
		if (size.y < 0.0f)
		{
			size.y = 0.0f;
		}

		SetSize(size);							//�T�C�Y�̐ݒ菈��

		if (m_bAnimateColor)
		{//�J�[���[�A�j���[�V�����̏ꍇ

			D3DXCOLOR col = GetColor();			//���݂̃J�[���[�̎擾

			col += m_deltaCol;					//�J�[���[�̍X�V
												
			SetColor(col);						//�J�[���[�̐ݒ�
		}
	}

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�J�[���[�A�j���[�V�����̐ݒ菈��
void CAnimateUI::AnimateColor(const bool bAnim)
{
	m_bAnimateColor = bAnim;				
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CAnimateUI* CAnimateUI::Create(CObject::TextType texture, const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, UIAnimation animInfo)
{
	CAnimateUI* pUi = new CAnimateUI;				//UI�̐���

	if (FAILED(pUi->Init()))
	{//����������
		return nullptr;
	}

	pUi->SetTexture(texture);						//�e�N�X�`���̐ݒ�
	pUi->SetPos(pos);								//�ʒu�̐ݒ�
	pUi->SetSize(size);								//�T�C�Y�̐ݒ�
	pUi->SetColor(col);								//�J�[���[�̐ݒ�
	pUi->SetPriority(5);							//�v���C�I���e�B�̐ݒ�
	pUi->m_AnimInfo = animInfo;						//�A�j���[�V�������̐ݒ�

	return pUi;										//���������C���X�^���X��Ԃ�
}