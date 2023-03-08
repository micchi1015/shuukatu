//=============================================================================
//
// model.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "playerModel.h"
#include "animator.h"
#include "modelPart.h"
#include "application.h"
#include "rendering.h"
#include "inputKeyboard.h"
#include "UIString.h"
#include "inputPad.h"
#include "playerSelect.h"
#include "AnimateUI.h"
#include "fade.h"

CModel::ModelType CPlayerModel::m_HeadTypeAll[HEAD_MAX]
{
	CModel::MODEL_HEAD,
	CModel::MODEL_HEAD_SANTA,
	CModel::MODEL_HEAD_PUMPKIN,
	CModel::MODEL_HEAD_TOPHAT,
	CModel::MODEL_HEAD_KATANA,
	CModel::MODEL_HEAD_TOYBOX,
	CModel::MODEL_HEAD_SUMMER,
	CModel::MODEL_HEAD_TREE,
	CModel::MODEL_HEAD_DRAGON,
	CModel::MODEL_HEAD_OCTOPUS,
	CModel::MODEL_HEAD_SNOWMAN
	
};

CModel::ModelType CPlayerModel::m_HeadType[PLAYER_MAX] =
{
	CModel::MODEL_HEAD,
	CModel::MODEL_HEAD,
	CModel::MODEL_HEAD,
	CModel::MODEL_HEAD
};

D3DXCOLOR CPlayerModel::m_playersCol[PLAYER_MAX] =
{
	ColorWhite,
	ColorWhite,
	ColorWhite,
	ColorWhite
};

//�R���X�g���N�^
CPlayerModel::CPlayerModel()
{
	//�����o�[�ϐ����N���A����
	m_pAnimator = nullptr;					//�A�j���[�^�[�ւ̃|�C���^
	m_pos = Vec3Null;						//�ʒu
	m_rot = Vec3Null;						//����
	m_nPresentColor = ColorNull;			//���݂̃J�[���[�C���f�b�N�X
	m_nIdx = 0;								//�C���f�b�N�X
	m_nPresentHead = 0;						//���݂̓�
											
	m_pIcon = nullptr;						//�A�C�R���ւ̃|�C���^
	m_pUiString = nullptr;					//UI�ւ̃|�C���^
	m_pOK = nullptr;						//2D�|���S���ւ̃|�C���^
	m_pParent = nullptr;					//�e�ւ̃|�C���^

	for (int nCnt = 0; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CPlayerModel::~CPlayerModel()
{

}

//����������
HRESULT CPlayerModel::Init(void)
{
	m_pAnimator = nullptr;					//�A�j���[�^�[�ւ̃|�C���^
	m_pos = Vec3Null;						//�ʒu
	m_rot = Vec3Null;						//����
	m_nPresentColor = ColorWhite;			//���݂̃J�[���[�C���f�b�N�X
	m_nIdx = 0;								//�C���f�b�N�X
	m_nPresentHead = 0;						//���݂̓�
	m_bDecision = false;					//���肵�����ǂ���

	m_pIcon = nullptr;						//�A�C�R���ւ̃|�C���^
	m_pUiString = nullptr;					//UI�ւ̃|�C���^
	m_pOK = nullptr;						//2D�|���S���ւ̃|�C���^
	m_pParent = nullptr;					//�e�ւ̃|�C���^

	for (int nCnt = 0; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{//���f���̕����ւ̃|�C���^
		m_pModel[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CPlayerModel::Uninit(void)
{
	m_playersCol[m_nIdx] = m_presentColor;				//�F�̐ݒ�

	//���f���p�[�c�̏I������
	for (int nCnt = 0; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Uninit();
			delete m_pModel[nCnt];
			m_pModel[nCnt] = nullptr;
		}
	}

	//�A�j���[�^�[�̔j������
	if (m_pAnimator != nullptr)
	{
		m_pAnimator->Uninit();
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}
	//�A�C�R���̔j��
	if (m_pIcon != nullptr)
	{
		m_pIcon->Release();
		m_pIcon = nullptr;
	}
	//UI�̔j��
	if (m_pUiString != nullptr)
	{
		m_pUiString->Release();
		m_pUiString = nullptr;
	}
	//2D�|���S���̔j��
	if (m_pOK != nullptr)
	{
		m_pOK->Release();
		m_pOK = nullptr;
	}
	//�e�ւ̃|�C���^��null�ɂ���
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}
}

//�X�V����
void CPlayerModel::Update(void)
{
	if (m_pAnimator != nullptr)
	{//�A�j���[�^�[�ւ̃|�C���^��null�ł͂Ȃ�������A�X�V����
		m_pAnimator->Update();
	}

	if (CApplication::GetFade()->GetFade() == CFade::FADE_NONE)
	{//�t�F�[�h���ł͂Ȃ�������
		if (m_bSelect)
		{
			if (!m_bDecision)
			{//�܂����肵�Ă��Ȃ�������
				if (CInputKeyboard::GetKeyboardTrigger(DIK_D) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_RIGHT, m_nIdx))
				{//�L�[�{�[�h��D�L�[�A���̓p�b�h�̉E�{�^���������ꂽ�ꍇ

					m_nPresentColor++;			//���݂̐F���X�V����

					
					if (m_nPresentColor >= CPlayer::PLAYER_COLOR_MAX)
					{//Max�𒴂�����A0�ɖ߂�
						m_nPresentColor = 0;
					}

					m_presentColor = CPlayer::GetPlayerColors()[m_nPresentColor];		//�F�̐ݒ�

					if (m_pModel[CPlayer::BODY] != nullptr)
					{//�̂ւ̃|�C���^��null�ł͂Ȃ�������A�F���X�V����
						m_pModel[CPlayer::BODY]->SetModelColor(2, m_presentColor);
					}
					if (m_pIcon != nullptr)
					{//�A�C�R���ւ̃|�C���^��null�ł͂Ȃ�������A�F���X�V����
						m_pIcon->SetColor(m_presentColor);
					}
					if (m_pUiString != nullptr)
					{//UI�ւ̃|�C���^��null�ł͂Ȃ�������A�F���X�V����
						m_pUiString->ChangeColor(m_presentColor);
					}
				}
				else if (CInputKeyboard::GetKeyboardTrigger(DIK_A) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_LEFT, m_nIdx))
				{//�L�[�{�[�h��A�L�[�A���̓p�b�h�̍��{�^���������ꂽ�ꍇ
					m_nPresentColor--;				//���݂̐F���X�V����

					if (m_nPresentColor < 0)
					{//0�ȉ��ɂȂ�����AMax - 1�ɖ߂�
						m_nPresentColor = CPlayer::PLAYER_COLOR_MAX - 1;
					}

					m_presentColor = CPlayer::GetPlayerColors()[m_nPresentColor];		//�F�̐ݒ�

					if (m_pModel[CPlayer::BODY] != nullptr)
					{//�̂ւ̃|�C���^��null�ł͂Ȃ�������A�F���X�V����
						m_pModel[CPlayer::BODY]->SetModelColor(2, m_presentColor);
					}
					if (m_pIcon != nullptr)
					{//�A�C�R���ւ̃|�C���^��null�ł͂Ȃ�������A�F���X�V����
						m_pIcon->SetColor(m_presentColor);
					}
					if (m_pUiString != nullptr)
					{//UI�ւ̃|�C���^��null�ł͂Ȃ�������A�F���X�V����
						m_pUiString->ChangeColor(m_presentColor);
					}
				}

				if (CInputKeyboard::GetKeyboardTrigger(DIK_S) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_DOWN, m_nIdx))
				{//�L�[�{�[�h��S�L�[�A���̓p�b�h�̉��{�^���������ꂽ�ꍇ

					m_nPresentHead--;					//���݂̓��̎�ނ��X�V����

					if (m_nPresentHead < 0)
					{//0�ȉ��ɂȂ�����AMax - 1�ɖ߂�
						m_nPresentHead = HEAD_MAX - 1;
					}

					if (m_pModel[CPlayer::HEAD] != nullptr)
					{//���ւ̃|�C���^��null�ł͂Ȃ�������A���̎�ނ�ݒ肷��
						m_pModel[CPlayer::HEAD]->SetModel(m_HeadTypeAll[m_nPresentHead]);
					}

					m_HeadType[m_nIdx] = m_HeadTypeAll[m_nPresentHead];			//���̎�ނ�ۑ�����
				}
				else if (CInputKeyboard::GetKeyboardTrigger(DIK_W) || CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_UP, m_nIdx))
				{//�L�[�{�[�h��W�L�[�A���̓p�b�h�̏�{�^���������ꂽ�ꍇ

					m_nPresentHead++;					//���݂̓��̎�ނ��X�V����

					if (m_nPresentHead >= HEAD_MAX)
					{//Max�𒴂�����A0�ɖ߂�
						m_nPresentHead = 0;
					}

					if (m_pModel[CPlayer::HEAD] != nullptr)
					{//���ւ̃|�C���^��null�ł͂Ȃ�������A���̎�ނ�ݒ肷��
						m_pModel[CPlayer::HEAD]->SetModel(m_HeadTypeAll[m_nPresentHead]);
					}

					m_HeadType[m_nIdx] = m_HeadTypeAll[m_nPresentHead];				//���̎�ނ�ۑ�����
				}

				if (CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_B, m_nIdx))
				{//��������
					m_bDecision = true;
					
					if (m_pParent != nullptr)
					{
						m_pParent->AddPlayerCounnt(1);				//���肵���v���C���[�l�����C���N�������g����
					}

					if (m_pOK == nullptr)
					{//2D�|���S���ւ̃|�C���^��null��������A��������
						CAnimateUI::UIAnimation animInfo;
						animInfo.deltaSize = D3DXVECTOR2(0.5f, 0.5f);
						animInfo.nChangeTime = 30;
						m_pOK = CAnimateUI::Create(CObject::TEXTURE_OK_UI, D3DXVECTOR3(((float)SCREEN_WIDTH / 5.0f) * (m_nIdx + 1), (float)SCREEN_HEIGHT * 0.425f, 0.0f), D3DXVECTOR2(65.0f, 40.0f),
							D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.75f), animInfo);
						m_pOK->AnimateColor(true);
					}
				}
			}
			else
			{//���肵����
				if (CInputPad::GetJoypadTrigger(CInputPad::JOYKEY_A, m_nIdx))
				{//�������f
					m_bDecision = false;
					m_pParent->AddPlayerCounnt(-1);

					if (m_pOK != nullptr)
					{//2D�|���S���̔j��
						m_pOK->Release();
						m_pOK = nullptr;
					}
				}
			}
		}
	}
}

//�`�揈��
void CPlayerModel::Draw(void)
{
	D3DXMATRIX mtxTrans, mtxRot;												//�v�Z�p�̃}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);											//���[���h�}�g���b�N�X�̏���������

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	m_pModel[CPlayer::BODY]->Draw(m_mtxWorld);											//�ŏ��̃��f���̕`�揈��

	for (int nCnt = 1; nCnt < CPlayer::PARTS_MAX; nCnt++)
	{//���̃��f���̕`�揈��
		if (m_pModel[nCnt] != nullptr)
		{
			m_pModel[nCnt]->Draw();
		}
	}
}


//�ʒu�̐ݒ菈��
void CPlayerModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�����̐ݒ菈��
void CPlayerModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

void CPlayerModel::SetStage(CPlayerSelect* pStage)
{
	m_pParent = pStage;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CPlayerModel::GetSize(void)
{
	return Vec2Null;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CPlayerModel::GetPos(void)
{
	return m_pos;
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================




//�J�[���[�̎擾����
const D3DXCOLOR*  CPlayerModel::GetPlayerColors(void)
{
	return m_playersCol;
}

//���̎�ނ̎擾����
CModel::ModelType CPlayerModel::GetHeadType(int nIdx)
{
	return m_HeadType[nIdx];
}


//��������
CPlayerModel* CPlayerModel::Create(const D3DXVECTOR3 pos, int nIdx, bool bUi)
{
	if (nIdx >= PLAYER_MAX)
	{//�v���C���[�̍ő�l���𒴂�����A�������Ȃ�
		return nullptr;
	}

	CPlayerModel* pModel = new CPlayerModel;				//�C���X�^���X�𐶐�����

	if (FAILED(pModel->Init()))
	{//����������
		return nullptr;
	}

	pModel->m_pos = pos;										//�ʒu�̐ݒ�
	pModel->m_rot = Vec3Null;									//�����̐ݒ�
	pModel->m_nIdx = nIdx;										//�C���f�b�N�X�̐ݒ�
	pModel->m_nPresentColor = nIdx;								//�F�̐ݒ�
	pModel->m_presentColor = CPlayer::GetPlayerColors()[nIdx];	//���݂̐F�̐ݒ�
	pModel->m_bSelect = bUi;									

	pModel->m_pos = pos;
	pModel->m_pModel[CPlayer::BODY] = CModelPart::Create(CModel::MODEL_BODY, D3DXVECTOR3(0.0f, 17.0f, 0.0f), Vec3Null);				//�̂̃��f���𐶐�����

	pModel->m_pModel[CPlayer::HEAD] = CModelPart::Create(CModel::MODEL_HEAD, D3DXVECTOR3(0.0f, 7.0f, 0.0f), Vec3Null);				//���̃��f���𐶐�����
	pModel->m_pModel[CPlayer::HEAD]->SetParent(pModel->m_pModel[CPlayer::BODY]);																//���̐e��ݒ肷��

	pModel->m_pModel[CPlayer::LEFT_ARM] = CModelPart::Create(CModel::MODEL_LEFT_ARM, D3DXVECTOR3(8.0f, 3.0f, 0.0f), Vec3Null);		//���r�̃��f���𐶐�����
	pModel->m_pModel[CPlayer::LEFT_ARM]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//���r�̐e��ݒ肷��

	pModel->m_pModel[CPlayer::LEFT_HAND] = CModelPart::Create(CModel::MODEL_LEFT_HAND, D3DXVECTOR3(9.0f, 0.0f, 0.0f), Vec3Null);		//����̃��f���𐶐�����
	pModel->m_pModel[CPlayer::LEFT_HAND]->SetParent(pModel->m_pModel[CPlayer::LEFT_ARM]);														//����̐e��ݒ肷��

	pModel->m_pModel[CPlayer::RIGHT_ARM] = CModelPart::Create(CModel::MODEL_RIGHT_ARM, D3DXVECTOR3(-8.0f, 3.0f, 0.0f), Vec3Null);	//�E�r�̃��f���𐶐�����
	pModel->m_pModel[CPlayer::RIGHT_ARM]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//�E�r�̐e��ݒ肷��

	pModel->m_pModel[CPlayer::RIGHT_HAND] = CModelPart::Create(CModel::MODEL_RIGHT_HAND, D3DXVECTOR3(-9.0f, 0.0f, 0.0f), Vec3Null);	//�E��̃��f���𐶐�����
	pModel->m_pModel[CPlayer::RIGHT_HAND]->SetParent(pModel->m_pModel[CPlayer::RIGHT_ARM]);													//�E��̐e��ݒ肷��

	pModel->m_pModel[CPlayer::LEFT_LEG] = CModelPart::Create(CModel::MODEL_LEFT_LEG, D3DXVECTOR3(3.0f, -9.0f, 0.0f), Vec3Null);		//�����ڂ̃��f���𐶐�����
	pModel->m_pModel[CPlayer::LEFT_LEG]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//�����ڂ̐e��ݒ肷��

	pModel->m_pModel[CPlayer::LEFT_FOOT] = CModelPart::Create(CModel::MODEL_LEFT_FOOT, D3DXVECTOR3(0.1f, -5.0f, 0.0f), Vec3Null);	//�����̃��f���𐶐�����
	pModel->m_pModel[CPlayer::LEFT_FOOT]->SetParent(pModel->m_pModel[CPlayer::LEFT_LEG]);														//�����̐e��ݒ肷��

	pModel->m_pModel[CPlayer::RIGHT_LEG] = CModelPart::Create(CModel::MODEL_RIGHT_LEG, D3DXVECTOR3(-3.0f, -9.0f, 0.0f), Vec3Null);	//�E���ڂ̃��f���𐶐�����
	pModel->m_pModel[CPlayer::RIGHT_LEG]->SetParent(pModel->m_pModel[CPlayer::BODY]);															//�E���ڂ̐e��ݒ肷��

	pModel->m_pModel[CPlayer::RIGHT_FOOT] = CModelPart::Create(CModel::MODEL_RIGHT_FOOT, D3DXVECTOR3(-0.1f, -5.0f, 0.0f), Vec3Null);//�E���̃��f���𐶐�����
	pModel->m_pModel[CPlayer::RIGHT_FOOT]->SetParent(pModel->m_pModel[CPlayer::RIGHT_LEG]);													//�E���̐e��ݒ肷��

	//�����������f�����A�j���[�^�[�ɑ������
	std::vector <CModelPart*> vParts;
	vParts.clear();
	vParts.push_back(pModel->m_pModel[CPlayer::BODY]);
	vParts.push_back(pModel->m_pModel[CPlayer::HEAD]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_ARM]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_HAND]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_ARM]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_HAND]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_LEG]);
	vParts.push_back(pModel->m_pModel[CPlayer::LEFT_FOOT]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_LEG]);
	vParts.push_back(pModel->m_pModel[CPlayer::RIGHT_FOOT]);

	pModel->m_pAnimator = CAnimator::Create(&vParts, CAnimator::ANIM_TYPE_PLAYER);				//�A�j���[�^�[�̐���

	pModel->m_pAnimator->SetPresentAnim(5);														//���݂̃A�j���[�V�����̐ݒ�

	pModel->m_pModel[CPlayer::BODY]->SetModelColor(2, pModel->m_presentColor);					//�F�̐ݒ�

	if (bUi)
	{//�v���C���[�I����ʂ�������A

		//�A�C�R���̐���
		pModel->m_pIcon = CObject_2D::Create();
		pModel->m_pIcon->SetPos(D3DXVECTOR3(((float)SCREEN_WIDTH / 5.0f) * (nIdx + 1), (float)SCREEN_HEIGHT * 0.725f, 0.0f));		//�A�C�R���̈ʒu�̐ݒ�
		pModel->m_pIcon->SetSize(D3DXVECTOR2(100.0f, 15.0f));																		//�A�C�R���̃T�C�Y�̐ݒ�
		pModel->m_pIcon->SetTexture(CObject::TEXTURE_NULL);																			//�A�C�R���̃e�N�X�`���̐ݒ�
		pModel->m_pIcon->SetColor(pModel->m_presentColor);																			//�A�C�R���̐F�̐ݒ�
																															
		pModel->m_pAnimator->SetPresentAnim(0);			//�A�j���[�V�����̐ݒ�

		//UI�̕�����̐ݒ�
		std::string str;
		str.clear();
		str = std::to_string(nIdx + 1);
		str += "P";
		const char* pStr = str.c_str();
		pModel->m_pUiString = CUIString::Create(D3DXVECTOR3((((float)SCREEN_WIDTH / 5.0f) * (nIdx + 1)) - 50.0f, (float)SCREEN_HEIGHT * 0.275f, 0.0f), D3DXVECTOR2(100.0f, 60.0f), pModel->m_presentColor, pStr);
	
	}
	else
	{//�����_���ŐF�Ɠ��̎�ނ�ݒ肷��𐶐�����
		int nColor = random(0, (int)CPlayer::PLAYER_COLOR_MAX - 1);

		pModel->m_pModel[CPlayer::HEAD]->SetModel(m_HeadTypeAll[random(0, (int)HEAD_MAX - 1)]);
		pModel->m_pModel[CPlayer::BODY]->SetModelColor(2, CPlayer::GetPlayerColors()[nColor]);
	}

	m_HeadType[nIdx] = m_HeadTypeAll[0];			

	return pModel;									//���������C���X�^���X��Ԃ�
}