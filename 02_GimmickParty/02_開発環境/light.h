//=============================================================================
//
// light.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

class CLight
{
public:
	CLight();								//�R���X�g���N�^
	virtual ~CLight();						//�f�X�g���N�^
										
	virtual HRESULT Init(void);				//����������
	virtual void Uninit(void);				//�I������
	virtual void Update(void);				//�X�V����

	void Release(void);						//�j������

	const int GetLightIdx(void);			//�C���f�b�N�X�̎擾����

	static void ReleaseAll(void);			//�S���̔j������

private:

	static const int MaxLight = 5;			//���C�g�̍ő吔

	int m_nIdx;								//�C���f�b�N�X

	static CLight* m_pLight[MaxLight];		//���C�g�ւ̃|�C���^
};

#endif // !_LIGHT_H_