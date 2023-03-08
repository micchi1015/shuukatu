//------------------------------
//
// �����蔻��̏���[collision.cpp]
// Author:���c�喲
//
//------------------------------

//---------------------------
//�C���N���[�h�t�@�C��
//---------------------------
#include "collision.h"

//�R���X�g���N�^
CColision::CColision()
{
}

//�f�X�g���N�^
CColision::~CColision()
{
}

//---------------------------
//�~�̓����蔻��
//---------------------------
bool CColision::CollisionCircle(D3DXVECTOR3 Pos1, float fRadius1, D3DXVECTOR3 Pos2, float fRadius2)
{
	//�Q���̕��̂̔��a���m�̘a
	float fDiff = fRadius1 + fRadius2;

	//�v�Z�p�ϐ�
	float fCalculationX, fCalculationY;

	//X�̍���
	fCalculationX = Pos1.x - Pos2.x;
	//Y�̍���
	fCalculationY = Pos1.y - Pos2.y;

	//���݂̂Q�_�̋���
	float fLength = sqrtf(fCalculationX * fCalculationX + fCalculationY * fCalculationY);

	//�Q���̕��̂̔��a���m�̘a��茻�݂̂Q�_�̋��������������ǂ���
	if (fDiff >= fLength)
	{
		//��������
		return true;
	}

	//�������ĂȂ�
	return false;
}