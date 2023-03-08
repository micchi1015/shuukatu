//=============================================================================
//
// inputKeyboard.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef INPUT_KEYBOARD_H
#define INPUT_KEYBOARD_H

//�C���N���[�h�t�@�C��
#include "input.h"

//�L�[�{�[�h�̃N���X(�C���v�b�g�̔h���N���X)
class CInputKeyboard : public CInput
{
public:

	static const int NumMaxKey = 256;										//�{�^���̍ő吔
																			
	CInputKeyboard();														//�R���X�g���N�^
	~CInputKeyboard() override;												//�f�X�g���N�^
																
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, GUID guid) override;		//����������
	void Uninit(void) override;												//�I������
	void Update(void) override;												//�X�V����
																			
	static bool GetKeyboardPress(int nKey);									//�v���X�̔���
	static bool GetKeyboardTrigger(int nKey);								//�g���K�[�̔���
																			
private:																	
	static BYTE m_aKeyState[NumMaxKey];										//�L�[�v���X���
	static BYTE m_aKeyStateTrigger[NumMaxKey];								//�L�[�g���K�[���
};

#endif // !INPUT_KEYBOARD_H