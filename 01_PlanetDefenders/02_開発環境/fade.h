//--------------------------------
//
//�t�F�[�h�w�b�_�[[fade.h]
//Author:���c�喲
//
//--------------------------------
#ifndef _FADE_H_
#define _FADE_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "main.h"
#include "mode.h"
#include "object2D.h"

//---------------------------
//�t�F�[�h�N���X
//---------------------------
class CFade : public CObject2D
{
public:
	enum FADE			//�t�F�[�h�̏��
	{
		FADE_NONE = 0,	//�������ĂȂ����
		FADE_IN,		//�t�F�[�h�C�����
		FADE_OUT,		//�t�F�[�h�A�E�g���
		FADE_COUNTIN,
		FADE_COUNTOUT,
		FADE_SETMODE,
		FADE_MAX
	};

	explicit CFade(int nPriority = PRIORITY_5);
	~CFade();

	void Init(CApplication::MODE modeNext);		//�t�F�[�h�̏���������
	void Uninit(void) override;					//�t�F�[�h�̏I������
	void Update(void) override;					//�t�F�[�h�̍X�V����

	static void SetFade(FADE m_pFade,CApplication::MODE modeNext);	//�t�F�[�h�̐ݒ菈��
	FADE GetFade(void);

	static CFade *Create(CApplication::MODE modeNext);

private:
	static CApplication::MODE m_ModeNext;	//���̉��(���[�h)
	static FADE m_pfade;					//�t�F�[�h�̏��	
	static D3DXCOLOR m_color;				//�J���[
};
#endif