//=============================================================================
//
// environment.h
// Author : Kajita Hiromu
//
//=============================================================================

#ifndef _ENVIROMENT_H_
#define _ENVIROMENT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================

class CEnvironment : public CModel
{
public:
	//���R�E���̎��
	enum EnvironmentType
	{
		ENVIRONMENT_MOUNT = 0,
		ENVIRONMENT_MOUNT_YUKI,
		ENVIRONMENT_BALLOON,
		ENVIRONMENT_TREE1,
		ENVIRONMENT_TREE2,
		ENVIRONMENT_WINDMILL,
		ENVIRONMENT_AIRSHIP,
		ENVIRONMENT_STONE,
		ENVIRONMENT_TYPE_MAX
	};

	CEnvironment();										//�R���X�g���N�^
	~CEnvironment() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	static CEnvironment* Create(D3DXVECTOR3 pos, EnvironmentType type);	//��������

private:
};

#endif //!_ENVIROMENT_H_