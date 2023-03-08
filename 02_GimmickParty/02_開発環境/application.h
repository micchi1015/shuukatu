//=============================================================================
//
// application.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef APPLICATION_H
#define APPLICATION_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "sound.h"

//�O���錾
class CRenderer;
class CInput;
class CInputMouse;
class CInputPad;
class CSound;
class CFade;
class CCamera;
class CDebugProc;
class CMode;
class CHalfSphere;
class CMenu;
class CMessage;

//�A�v���P�[�V�����̃N���X
class CApplication
{
public:
	enum Mode
	{
		Mode_Title = 0,		// �^�C�g��
		Mode_PlayerSelect,	// �v���C���[�I�����
		Mode_StageSelect,	// �X�e�[�W�I�����
		Mode_Game_Race,		// �Q�[��_����
		Mode_Tutorial,		// �`���[�g���A��

		Mode_Max
	};

	CApplication();										//�R���X�g���N�^
	~CApplication();									//�f�X�g���N�^
														
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	static CRenderer* GetRenderer(void);				//�����f�B���O�C���X�^���X�̎擾����
	static CInputMouse* GetMouse(void);					//�}�E�X�C���X�^���X�̎擾����
	static CInputPad* GetPad(void);						//�p�b�h�̎擾����
	static HWND GetWindow(void);						//�E�C���h�E�̎擾����
	static CSound* GetSound(void);						//�T�E���h�̎擾����
	static CCamera* GetCamera(void);					//�J�����̎擾����
	static CFade* GetFade(void);						//�t�F�[�h�̎擾����

	static Mode GetMode(void);							// ���[�h�̎擾����
	static void SetMode(Mode mode);						// ���[�h�̐ݒ菈��
	void ChangeMode();									// ���[�h�̕ύX����

	static bool GetPause(void);							// �|�[�Y�̎擾����
	static void SetPause(const bool bPause);			// �|�[�Y�̐ݒ菈��

	static int GetStageSelect() { return m_nStageSelect; }							// �I�����ꂽ�X�e�[�W�ԍ��̎擾����
	static void SetStageSelect(int StageSelect) { m_nStageSelect = StageSelect; }	// �X�e�[�W�ԍ��̐ݒ菈��

	static CMessage* GetMsg(void) { return m_pMessage; }		//���b�Z�[�W�̎擾����

private:
	static int m_nStageSelect;							//�I�𒆂̃X�e�[�W�Z���N�g
	static bool m_bPause;								//�|�[�Y���ł��邩�ǂ���

	static HWND m_hWnd;									//�N���C�G���g���
	static CRenderer* m_pRenderer;						//�����f�B���O�C���X�^���X�ւ̃|�C���^
	static CInput* m_pInput[2];							//�C���v�b�g�f�o�C�X�ւ̃|�C���^
	static CInputMouse* m_pMouse;						//�}�E�X�C���X�^���X
	static CInputPad* m_pPad;							//�p�b�h�̃C���X�^���X
	static CSound* m_pSound;							//�T�E���h�̃C���X�^���X�ւ̃|�C���^
	static CFade* m_pFade;								//�t�F�[�h�̃C���X�^���X�ւ̃|�C���^
	static CCamera* m_pCamera;							//�J�����̃C���X�^���X�ւ̃|�C���^
	static CMode* m_pMode;								//���[�h�̃C���X�^���X�ւ̃|�C���^
	static CMenu* m_pMenu;								//���j���[�̃C���X�^���X�ւ̃|�C���^
	static CMessage* m_pMessage;						//���b�Z�[�W�̃C���X�^���X�ւ̃|�C���^
	static CDebugProc* m_pDebug;						//�f�o�b�O�e�L�X�g�̃C���X�^���X

	static Mode m_mode;		//���݃��[�h
	static Mode m_modeNext;	//���̃��[�h
};

#endif // !APPLICATION_H
