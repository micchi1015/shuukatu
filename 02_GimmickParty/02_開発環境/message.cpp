//=============================================================================
//
// message.cpp
// Author : tanimoto kosuke
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "message.h"
#include "game.h"
#include "application.h"
#include "menu.h"

bool CMessage::m_bStart = false;

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CMessage::CMessage()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CMessage::~CMessage()
{

}

//=====================================
// ����������
//=====================================
HRESULT CMessage::Init(void)
{
	m_nMessageIdx = 0;				// ���Ҕԍ��̏�����
	m_nMessageCounter = 0;			// ���b�Z�[�W�\�����Ԃ̏�����
	m_nNum = 0;						// �J�E���g�_�E�����݈ʒu�̏�����
	m_bStart = false;				// �Q�[���X�^�[�g����̏�����
	m_type = MESSAGE_COUNTDOWN;		// ���b�Z�[�W��ނ̏�����

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CMessage::Uninit(void)
{
	if (m_pObj2D != nullptr)
	{// �I�u�W�F�N�g2D�̏I��
		m_pObj2D->Release();
		m_pObj2D = nullptr;
	}
	if (m_pPlayer2D != nullptr)
	{// ���҉摜�̏I��
		m_pPlayer2D->Release();
		m_pPlayer2D = nullptr;
	}
	m_nMessageIdx = 0;				// ���b�Z�[�W�ԍ��̏I��
	m_nMessageCounter = 0;			// ���b�Z�[�W�\�����Ԃ̏I��
	m_nNum = 0;						// �J�E���g�_�E�����݈ʒu�̏I��
	m_bStart = false;				// �Q�[���X�^�[�g����̏I��
	m_type = MESSAGE_COUNTDOWN;		// ���b�Z�[�W��ނ̏I��
}

//=====================================
// �X�V����
//=====================================
void CMessage::Update(void)
{
	if (CApplication::GetPause() == false)
	{	// �|�[�Y���łȂ��ꍇ�̂ݍX�V
		if (m_nMessageCounter > 0)
		{// �J�E���g��0����̏ꍇ
			m_nMessageCounter--;

			if (m_nMessageCounter <= 0)
			{// �J�E���g��0�ȉ��ɂȂ����ꍇ
				if (m_type == MESSAGE_COUNTDOWN)
				{// �J�E���g�_�E�������̏ꍇ
					m_nNum--;
					if (m_nNum > 0)
					{// �J�E���g�_�E����0���傫���ꍇ
						m_nMessageCounter = CountDownLife;	// �J�E���g�_�E���p�̎�������
						m_pObj2D->SetAnimPattern(m_nNum);	// ���݂̃J�E���g�_�E����ݒ�
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COUNTDOWN);
						CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CHEERS01);
					}
					else
					{// �J�E���g�_�E����0�ȉ��̏ꍇ
						Destroy();			// �j������
						StartMessage();		// �X�^�[�g���b�Z�[�W
					}
				}
				else if (m_type == MESSAGE_GOAL)
				{// �S�[�������̏ꍇ
					Destroy();		// �j������
					WinMessage();	// ���҃��b�Z�[�W
				}
				else if (m_type == MESSAGE_WIN)
				{// ���ҏ����̏ꍇ
					CMenu::SetResult();	// ���U���g�p���j���[�ݒ菈��
				}
				else
				{// ����ȊO�̏ꍇ
					Destroy();		// �j������
				}
			}
		}
	}
}

//=====================================
// �J�E���g�_�E�����b�Z�[�W�\������
//=====================================
void CMessage::SetCountDown(int nNum)
{
	if (m_pObj2D == nullptr)
	{// �I�u�W�F�N�g2D�����g�p�̏ꍇ����
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(200.0f, 150.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_NUMBERS);
		m_pObj2D->SetTextureParameter(1, 5, 3, INT_MAX);
		m_pObj2D->SetPriority(5);
		m_nNum = nNum;
		m_pObj2D->SetAnimPattern(nNum);
		m_nMessageCounter = CountDownLife;
		m_type = MESSAGE_COUNTDOWN;

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COUNTDOWN);
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CHEERS01);
	}
}

//=====================================
// �X�^�[�g���b�Z�[�W�\������
//=====================================
void CMessage::StartMessage(void)
{
	if (m_pObj2D == nullptr)
	{// �I�u�W�F�N�g2D�����g�p�̏ꍇ����
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(360.0f, 200.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_START);
		m_pObj2D->SetPriority(5);
		m_nMessageCounter = 30;
		m_type = MESSAGE_START;
		m_bStart = true;
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GAMESTART);
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_PISTOL);
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CHEERS02);
	}
}

//=====================================
// �S�[�����b�Z�[�W�\������
//=====================================
void CMessage::GoalMessage(int nMessageIdx)
{
	if (m_pObj2D == nullptr)
	{// �I�u�W�F�N�g2D�����g�p�̏ꍇ����
		m_pObj2D = CObject_2D::Create();
		m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f));
		m_pObj2D->SetSize(D3DXVECTOR2(300.0f, 100.0f));
		m_pObj2D->SetTexture(CObject::TEXTURE_MESSAGE_GOAL);
		m_pObj2D->SetPriority(5);
		m_nMessageCounter = 120;
		m_type = MESSAGE_GOAL;
		m_bStart = false;
		// ���s�ԍ���������
		m_nMessageIdx = nMessageIdx;

		CApplication::GetSound()->Stop();

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WHISTLE_FINISH);
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CHEERS02);

		// �Q�[���I������
		CGame::SetEndGame();
	}
}


//=====================================
// �S�[�����b�Z�[�W�\������
//=====================================
void CMessage::WinMessage()
{
	if (m_pObj2D == nullptr)
	{// �I�u�W�F�N�g2D�����g�p�̏ꍇ����
		if (m_nMessageIdx != 0)
		{// ���_�ł͂Ȃ��ꍇ
			// WIN����
			m_pObj2D = CObject_2D::Create();
			m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 8 * 5, 100.0f, 0.0f));
			m_pObj2D->SetSize(D3DXVECTOR2(180.0f, 60.0f));
			m_pObj2D->SetTexture(CObject::TEXTURE_WINNER);
			m_pObj2D->SetPriority(5);
		}

		if (m_pPlayer2D == nullptr)
		{
			// ���s���b�Z�[�W����
			m_pPlayer2D = CObject_2D::Create();
			m_pPlayer2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 8 * 3, 100.0f, 0.0f));
			m_pPlayer2D->SetSize(D3DXVECTOR2(100.0f, 60.0f));
			m_pPlayer2D->SetPriority(5);

			switch (m_nMessageIdx)
			{// �ԍ��Ńv���C���[��ύX����
			case 0:
				m_pPlayer2D->SetTexture(CObject::TEXTURE_DRAW);
				m_pPlayer2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f));
				m_pPlayer2D->SetSize(D3DXVECTOR2(240.0f, 80.0f));
				break;
			case 1:
				m_pPlayer2D->SetTexture(CObject::TEXTURE_1P_WIN);
				break;
			case 2:
				m_pPlayer2D->SetTexture(CObject::TEXTURE_2P_WIN);
				break;
			case 3:
				m_pPlayer2D->SetTexture(CObject::TEXTURE_3P_WIN);
				break;
			case 4:
				m_pPlayer2D->SetTexture(CObject::TEXTURE_4P_WIN);
				break;
			default:
				m_pPlayer2D->SetTexture(CObject::TEXTURE_NULL);
				break;
			}

			m_type = MESSAGE_WIN;
			m_nMessageCounter = 120;
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WIN);
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CHEERS02);
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_RESULT);
		}
	}
}

//=====================================
// �I������
//=====================================
void CMessage::Destroy(void)
{
	if (m_pObj2D != nullptr)
	{// �I�u�W�F�N�g2D�����g�p�̏ꍇ����
		m_pObj2D->Release();
		m_pObj2D = nullptr;
	}
	m_nMessageCounter = 0;	// ���b�Z�[�W�\�����Ԃ̏�����
}


//=====================================
// ��������
//=====================================
CMessage* CMessage::Create()
{
	CMessage* pMessage = new CMessage;

	//����������
	if (FAILED(pMessage->Init()))
	{
		return nullptr;
	}

	return pMessage;
}