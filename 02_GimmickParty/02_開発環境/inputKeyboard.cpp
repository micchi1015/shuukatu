//=============================================================================
//
// inputKeyboard.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "inputKeyboard.h"

//�ÓI�����o�[�ϐ��̐錾
BYTE CInputKeyboard::m_aKeyState[NumMaxKey] = {};
BYTE CInputKeyboard::m_aKeyStateTrigger[NumMaxKey] = {};

//�R���X�g���N�^
CInputKeyboard::CInputKeyboard()
{

}

//�f�X�g���N�^
CInputKeyboard::~CInputKeyboard()
{

}

//����������
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd, GUID guid)
{
	//��{�N���X�̏���������
	if (FAILED(CInput::Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	//�f�o�C�X�t�H�[�}�b�g��ݒ�
	if (FAILED(CInput::GetInputDevice()->SetDataFormat(&c_dfDIKeyboard)))
	{
		return -1;
	}

	//�������[�h��ݒ�
	if (FAILED(CInput::GetInputDevice()->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return -1;
	}

	CInput::GetInputDevice()->Acquire();

	return S_OK;
}

//����������
void CInputKeyboard::Uninit(void)
{
	//��{�N���X�̏I������
	CInput::Uninit();
}

//�X�V����
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NumMaxKey];		//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(CInput::GetInputDevice()->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NumMaxKey; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = ((~m_aKeyState[nCntKey]) & aKeyState[nCntKey]);		//�L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];											//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		CInput::GetInputDevice()->Acquire();
	}
}

//�L�[�{�[�h�̃v���X
bool CInputKeyboard::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�̃g���K�[
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}