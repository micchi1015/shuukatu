//=============================================================================
//
// �t�F�[�h.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <d3dx9.h>

//---------------------------
//�O���錾
//---------------------------
class CObject2D;

//---------------------------
//�N���X
//---------------------------
class CFade 
{
public:
	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;			//xyz���W
		float rhw;					//rhw
		D3DCOLOR col;				//�J�[���[
		D3DXVECTOR2 tex;			//�e�N�X�`�����W
	};

	enum FADE
	{
		FADE_NONE = 0,	// �������Ă��Ȃ����
		FADE_IN,		// �t�F�[�h�C��(���X�ɓ����ɂ�����)
		FADE_OUT,		// �t�F�[�h�A�E�g(���X�ɕs�����ɂ�����)
		FADE_CHANGE,	// �t�F�[�h�؂�ւ�
		FADE_MAX
	};

	CFade();
	~CFade();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetColor(D3DXCOLOR col);		// �t�F�[�h�̐F�ύX����
	void SetFade();						// �t�F�[�h�̐ݒ菈��

	static CFade *Create();

	FADE GetFade() { return m_fade; }	//�t�F�[�h�̎擾����
private:
	float m_fAlpha;						// �|���S��(�t�F�[�h)��a�l
	FADE m_fade;						// ���݂̃t�F�[�h
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@

};

#endif // !_PLAYER_H_