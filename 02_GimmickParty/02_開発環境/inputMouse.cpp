//=============================================================================
//
// inputMouse.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "inputMouse.h"

//�R���X�g���N�^
CInputMouse::CInputMouse()
{
	
}

//�f�X�g���N�^
CInputMouse::~CInputMouse()
{

}

//����������
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd, GUID guid)
{
	//��{�N���X�̏���������
	if (FAILED(CInput::Init(hInstance, hWnd, GUID_SysMouse)))
	{
		return -1;
	}

	//�f�o�C�X�t�H�[�}�b�g��ݒ�
	if (FAILED(CInput::GetInputDevice()->SetDataFormat(&c_dfDIMouse)))
	{
		return -1;
	}
	//�������[�h��ݒ�
	if (FAILED(CInput::GetInputDevice()->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return -1;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(CInput::GetInputDevice()->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	CInput::GetInputDevice()->Acquire();

	return S_OK;
}

//�I������
void CInputMouse::Uninit(void)
{
	//��{�N���X�̏I������
	CInput::Uninit();
}

//�X�V����
void CInputMouse::Update(void)
{
	LPDIRECTINPUTDEVICE8 pDevice = CInput::GetInputDevice();

	if (SUCCEEDED(pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState)))
	{

	}
	else
	{
		pDevice->Acquire();
	}
}

//�}�E�X��Ԃ̎擾����
DIMOUSESTATE* CInputMouse::GetMouseState(void)
{
	return &m_MouseState;
}

//���N���b�N�̃g���K�[
bool CInputMouse::GetMouseLeftClick(void)
{
	return (GetKeyState(VK_LBUTTON) & 0x8000) ? true : false;
}

//�E�N���b�N�̃g���K�[
bool CInputMouse::GetMouseRightClick(void)
{
	return (GetKeyState(VK_RBUTTON) & 0x8000) ? true : false;
}