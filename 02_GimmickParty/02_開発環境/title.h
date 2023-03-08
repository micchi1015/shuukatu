//=============================================================================
//
// title.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CPlayerModel;
class CAnimateUI;

//---------------------------
//�N���X�錾
//---------------------------
class CTitle : public CMode
{
public:
	CTitle();											//�R���X�g���N�^
	~CTitle() override;									//�f�X�g���N�^
														
	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
														
	static CTitle* Create(void);						//��������
private:												
														
	static const int MAX_TITLE_MODEL = 7;				//���f���̍ő吔
														
	CPlayerModel* m_pModel[MAX_TITLE_MODEL];			//�v���C���[���f���ւ̃|�C���^
	CAnimateUI*   m_pTitle;								//UI�ւ̃|�C���^

};

#endif // !_TITLE_H_
