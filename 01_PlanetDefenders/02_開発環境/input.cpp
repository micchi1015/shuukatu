//-------------------------
//
//���͂̏���[input.cpp]
//Author:���c�喲
//
//-------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include "input.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//�R���X�g���N�^
CInput::CInput()
{
	m_pInput = nullptr;			//Directlnput�I�u�W�F�N�g�ւ̃|�C���^
	m_pDevice= nullptr;			//���̓f�o�C�X�ւ̃|�C���^
}

//�f�X�g���N�^
CInput::~CInput()
{
}

//�R���X�g���N�^
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = {};
		m_aKeyStateTrigger[nCnt] = {};
		m_aKeyStateRelease[nCnt] = {};
	}
}

//�f�X�g���N�^
CInputKeyboard::~CInputKeyboard()
{

}

//����������
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Directinput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g�̂�ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X��
	m_pDevice->Acquire();

	return S_OK;
}

//�I������
void CInputKeyboard::Uninit()
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if (m_pInput != NULL)
	{	
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//�X�V����
void CInputKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyStateTrigger[nCntKey] ^ 0);
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//Press����
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//Trigger����
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//Release����
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}