//-----------------------------
//
// [application.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
//---------------------------
//�C���N���[�h
//---------------------------
#include "main.h"

//---------------------------
//�O���錾
//---------------------------
class CInputKeyboard;
class CScore;
class CMode;

//---------------------------
//�A�v���P�[�V�����N���X
//---------------------------
class CApplication
{
public:
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_RANKING,
		MODE_MAX
	};

	CApplication();		//�R���X�g���N�^
	~CApplication();	//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	//����������
	void Uninit();		//�I������
	void Update();		//�X�V����
	void Draw();		//�`�揈��

	static CRenderer *GetRendere();				//Rendere�̏��擾
	static CInputKeyboard *GetInputKeyboard();	//Keyboard�̏��擾

	static void SetMode(MODE mode);
	static MODE GetMode();

private:
	static CRenderer *m_pRenderer;				//Rendere�̃|�C���^�ϐ�
	static CInputKeyboard *m_pInputKeyboard;	//Keyboard�̃|�C���^�ϐ�
	static CObject *m_pMode;
	static MODE m_mode;

	int m_Index;
	int m_count;
};
#endif