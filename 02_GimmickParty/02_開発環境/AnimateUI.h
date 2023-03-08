//=============================================================================
//
// AnimateUI.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _ANIMATE_UI_H_
#define _ANIMATE_UI_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

class CAnimateUI : public CObject_2D
{
public:

	struct UIAnimation
	{
		D3DXVECTOR2 deltaSize;							//�T�C�Y�̌���	
		int			nChangeTime;						//�A�j���[�V����������
	};

	CAnimateUI();																//�R���X�g���N�^
	~CAnimateUI() override;														//�f�X�g���N�^
																				
	HRESULT Init(void) override;												//����������
	void Uninit(void) override;													//�I������
	void Update(void) override;													//�X�V����

	void AnimateColor(const bool bAnim);										//�J�[���[�A�j���[�V�����̐ݒ菈��
																				
	static CAnimateUI* Create(CObject::TextType texture, const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, UIAnimation animInfo);		//��������


private:

	static const D3DXCOLOR targetCol[6];				//�J�[���[�A�j���[�V�����̃^�[�Q�b�g
														
	UIAnimation m_AnimInfo;								//�A�j���[�V�������
	int			m_nCntAnim;								//�A�j���[�V�����J�E���^�[
	int			m_ntargetCol;							//�ړI�̃J�[���[�ԍ�
	D3DXCOLOR	m_deltaCol;								//�J�[���[�̌���
	bool		m_bAnimateColor;						//�J�[���[�A�j���[�V���������邩�ǂ���

};







#endif