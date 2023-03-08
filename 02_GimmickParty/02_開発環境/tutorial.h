//=============================================================================
//
// tutorial.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "game.h"

//---------------------------
//�O���錾
//---------------------------
class CStage;
class CObject_2D;
class CFontString;

//---------------------------
//�N���X�錾
//---------------------------
class CTutorial : public CGame
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void SetObject(void);

	static CStage* GetStage(void) { return m_pStage; }	// �X�e�[�W�̎擾����

	static CTutorial* Create(void);			//��������
private:
	static const D3DXVECTOR2 m_fontSize;	// �t�H���g�̑傫��
	static const D3DXCOLOR m_fontColor;		// �t�H���g�̐F
	static CStage* m_pStage;				// �X�e�[�W�̃C���X�^���X�ւ̃|�C���^

	CObject_2D* m_pUi;
	CFontString* m_pFont;
	bool m_bChange;
};

#endif // !_GAME_H_
