//=============================================================================
//
// input.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "input.h"

//�ÓI�����o�[�ϐ��̐錾
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//�R���X�g���N�^
CInput::CInput()
{
	//�����o�[�ϐ����N���A����
	m_pDevice = nullptr;
}

//�f�X�g���N�^
CInput::~CInput()
{

}

//����������
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd, GUID guid)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(guid, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//�I������
void CInput::Uninit(void)
{
	//�C���v�b�g�f�o�C�X�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}

	//�f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}

//�C���v�b�g�f�o�C�X�̎擾����
LPDIRECTINPUTDEVICE8 CInput::GetInputDevice(void)
{
	return m_pDevice;
}