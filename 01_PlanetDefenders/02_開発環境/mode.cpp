//-------------------------
//
//���[�h�̏���[mode.cpp]
//Author:���c�喲
//
//-------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include "game.h"
#include "result.h"
#include "title.h"
#include "mode.h"

//�ÓI�����o�ϐ��錾
CTitle *CMode::m_pTitle = nullptr;
CGame *CMode::m_pGame = nullptr;
CResult *CMode::m_pResult = nullptr;

//�R���X�g���N�^
CMode::CMode()
{
	SetType(OBJTYPE_MODE);
}

//�f�X�g���N�^
CMode::~CMode()
{
}