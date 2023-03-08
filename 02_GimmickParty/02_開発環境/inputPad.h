//=============================================================================
//
// inputPad.h
// Author : KAJITA HIROMU
//
//=============================================================================

#ifndef INPUT_PAD_H
#define INPUT_PAD_H

//�C���N���[�h�t�@�C��
#include "input.h"
#include "XInput.h"

//���C�u���������N
#pragma comment(lib,"xinput.lib")

//====================================
//�}�N����`
//====================================


class CInputPad : public CInput
{
public:
	//====================================
	//�񋓌^
	//====================================
	//�L�[���(�W���C�p�b�h)
	enum JOYKEY
	{
		JOYKEY_UP = 0,				//�\���{�^����
		JOYKEY_DOWN,				//�\���{�^����
		JOYKEY_LEFT,				//�\���{�^����
		JOYKEY_RIGHT,				//�\���{�^���E
		JOYKEY_START,				//�X�^�[�g�{�^��
		JOYKEY_BACK,				//�o�b�N�{�^��
		JOYKEY_LEFT_THUMB,			//���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,			//�E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,		//L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,		//R�P�{�^��
		JOYKEY_LEFT_TRIGGER,		//L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,		//R�Q�g���K�[
		JOYKEY_A,					//A�{�^��
		JOYKEY_B,					//B�{�^��
		JOYKEY_X,					//X�{�^��
		JOYKEY_Y,					//Y�{�^��
		JOYKEY_LEFT_STICK,			//���X�e�B�b�N
		JOYKEY_RIGHT_STICK,			//�E�X�e�B�b�N
		JOYKEY_MAX
	};

	CInputPad();															//�R���X�g���N�^
	~CInputPad();															//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, GUID guid) override;		//����������
	void Uninit(void) override;												//�I������
	void Update(void) override;												//�X�V����

	static bool GetJoypadPress(JOYKEY Key, int nPlayer);					//�W���C�p�b�h�v���X����
	static bool GetJoypadTrigger(JOYKEY Key, int nPlayer);					//�W���C�p�b�h�g���K�[����
	static D3DXVECTOR3 GetJoypadStick(JOYKEY Key, int nPlayer);				//�W���C�p�b�h�X�e�B�b�N����
	static int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer);				//�W���C�p�b�h�g���K�[�y�_������
	static void JoypadVibration(int nTime, WORD nStrength, int nPlayer);	//�W���C�p�b�h�U������

private:
	static XINPUT_STATE m_JoyKeyState[PLAYER_MAX];							//�W���C�p�b�g�̃v���X���
	static XINPUT_STATE m_JoyKeyStateTrigger[PLAYER_MAX];					//�W���C�p�b�g�̃g���K�[���
	static D3DXVECTOR3 m_JoyStickPos[PLAYER_MAX];							//�W���C�X�e�B�b�N�̌X��
	static int m_nTime[PLAYER_MAX];											//�U����������
	static WORD m_nStrength[PLAYER_MAX];									//�U���̋��� (0 - 65535)

	XINPUT_VIBRATION m_JoyMoter[PLAYER_MAX];								//�W���C�p�b�h�̃��[�^�[

};

#endif // !INPUT_MOUSE_H
