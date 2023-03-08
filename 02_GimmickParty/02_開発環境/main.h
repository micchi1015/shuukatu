//=============================================================================
//
// main.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef MAIN_H
#define MAIN_H

//*****************************************************************************
// ���C�u�����[�����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define	DEBUG_NEW	new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace
{
	// �E�C���h�E�̃N���X��
	LPCTSTR CLASS_NAME = _T("AppClass");
	// �E�C���h�E�̃L���v�V������
	LPCTSTR WINDOW_NAME = _T("3D Team Work");
}

//#define PLAYER_MAX		(4)		//�v���C���[�̍ő�l��

// �X�N���[���̕�
const int SCREEN_WIDTH = 1280;
// �X�N���[���̍���
const int SCREEN_HEIGHT = 720;
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
// 3D���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
// �����_�t�H�[�}�b�g
const DWORD FVF_VERTEX_LINE = (D3DFVF_XYZ | D3DFVF_DIFFUSE);

const int PLAYER_MAX = 4;

const D3DXVECTOR2 Vec2Null = D3DXVECTOR2(0.0f, 0.0f);
const D3DXVECTOR3 Vec3Null = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const D3DXCOLOR ColorNull = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

const D3DXCOLOR ColorWhite = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

const D3DXCOLOR ColorRed = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);				//��
const D3DXCOLOR ColorGreen = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);				//��
const D3DXCOLOR ColorBlue = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);				//��
const D3DXCOLOR ColorMagenta = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);			//�}�[���^
const D3DXCOLOR ColorCyan = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);				//�V�A��
const D3DXCOLOR ColorYellow = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);			//��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int GetFPS(void);							//FPS�̎擾����

#endif // !MAIN_H
