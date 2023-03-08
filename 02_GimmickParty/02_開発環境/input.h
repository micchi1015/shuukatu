//=============================================================================
//
// input.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef INPUT_H
#define INPUT_H

//�C���N���[�h�t�@�C��
#include "main.h"

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"

//���C�u���������N
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

//�C���v�b�g�̊�{�N���X
class CInput
{
public:

	CInput();																//�R���X�g���N�^
	virtual ~CInput();														//�f�X�g���N�^
																
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, GUID guid);		//����������
	virtual void Uninit(void);												//�I������
	virtual void Update(void) = 0;											//�X�V����
																			
	LPDIRECTINPUTDEVICE8 GetInputDevice(void);								//�C���v�b�g�f�o�C�X�̎擾����
																
private:														
	static LPDIRECTINPUT8 m_pInput;					//�C���v�b�g�f�o�C�X												
	LPDIRECTINPUTDEVICE8 m_pDevice;					//�f�o�C�X	
};

#endif // !INPUT_H