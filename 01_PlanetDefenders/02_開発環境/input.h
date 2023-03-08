//-----------------------------
//
// [input.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//---------------------------
//�C���N���[�h
//---------------------------
#define DIRECTINPUT_VERSION			(0x0800)		//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"									//���͏����ɕK�v
#pragma comment(lib,"dinput8.lib")					//���͏����ɕK�v
#pragma comment(lib,"dxguid.lib")					// DirectX�R���|�[�l���g�Ɏg�p

//---------------------------
//�}�N����`
//---------------------------
#define NUM_KEY_MAX		(256)		//�L�[�̍ő吔

//---------------------------
//�C���v�b�g�N���X
//---------------------------
class CInput
{
public:
	CInput();					//�R���X�g���N�^
	virtual ~CInput() = 0;		//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd) = 0;	//����������
	virtual void Uninit() = 0;									//�I������
	virtual void Update() = 0;									//�X�V����

protected:
	static LPDIRECTINPUT8 m_pInput;					//Directlnput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;					//���̓f�o�C�X�ւ̃|�C���^
};

//---------------------------
//�C���v�b�g�L�[�{�[�h�N���X
//---------------------------
class CInputKeyboard: public CInput
{
public:
	CInputKeyboard();				//�R���X�g���N�^
	~CInputKeyboard()override;		//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;	//����������
	void Uninit()override;									//�I������
	void Update()override;									//�X�V����
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];						//�L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];				//�L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];				//�L�[�{�[�h�̃����[�X���
};
#endif