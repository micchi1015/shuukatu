//-----------------------------
//
// [rendere.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _RENDERE_H_
#define _RENDERE_H_

//---------------------------
//�����_���[�N���X
//---------------------------
class CRenderer
{
public:
	static const int SCREEN_WIDTH = 1280;		// �X�N���[���̕�
	static const int SCREEN_HEIGHT = 720;		// �X�N���[���̍���

public:
	CRenderer();			//�R���X�g���N�^
	~CRenderer();			//�f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow);	//����������
	void Uninit();							//�I������
	void Update();							//�X�V����
	void Draw();							//�`�揈��

	LPDIRECT3DDEVICE9 GetD3DDevice();		//m_pD3DDevice�̒l��Ԃ�

private:
	void DrawFPS();		//FPS�̕`�揈��
	
	LPDIRECT3D9					m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9			m_pD3DDevice;	// Device�I�u�W�F�N�g
	LPD3DXFONT					m_pFont;		// �t�H���g
};
#endif