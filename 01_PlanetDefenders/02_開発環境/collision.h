//-----------------------------
//
// �����蔻��
// Author�F���c�喲
//
//-----------------------------
#ifndef _COLLISION_H_		//���̃}�N����`������ĂȂ�������
#define _COLLISION_H_		//��d�C���N�\���[�h�h�~�̃}�N����`

#include"main.h"

//�~�̓����蔻��N���X
class CColision
{
public:
	CColision();				//�R���X�g���N�^
	~CColision();				//�f�X�g���N�^

	//�~�̓����蔻��
	static bool CollisionCircle(D3DXVECTOR3 Pos1, float fRadius1, D3DXVECTOR3 Pos2, float fRadius2);
};
#endif