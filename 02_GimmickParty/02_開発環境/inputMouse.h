//=============================================================================
//
// inputMouse.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef INPUT_MOUSE_H
#define INPUT_MOUSE_H

//�C���N���[�h�t�@�C��
#include "input.h"

class CInputMouse : public CInput
{
public:
	CInputMouse();																//�R���X�g���N�^
	~CInputMouse();																//�f�X�g���N�^
																				
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, GUID guid) override;			//����������
	void Uninit(void) override;													//�I������
	void Update(void) override;													//�X�V����

	DIMOUSESTATE*GetMouseState(void);											//�}�E�X���̎擾����
	bool GetMouseLeftClick(void);												//�}�E�X�̍��N���b�N��Ԃ̎擾����
	bool GetMouseRightClick(void);												//�}�E�X�̉E�N���b�N��Ԃ̎擾����

private:

	DIMOUSESTATE m_MouseState;						// �}�E�X���

};

#endif // !INPUT_MOUSE_H