//=============================================================================
//
// silhouette.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _SILHOUETTE_H_
#define _SILHOUETTE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

class CSilhouette : public CObject_2D
{
public:
	CSilhouette();							//�R���X�g���N�^
	~CSilhouette() override;				//�f�X�g���N�^
											
	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Draw(void) override;				//�`�揈��
											
	static CSilhouette* Create(void);		//��������

private:

};




#endif
#pragma once
