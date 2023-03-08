//=============================================================================
//
// camera.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//class CBoxHitbox;

class CCamera
{
public:
	CCamera();											//�R���X�g���N�^
	~CCamera();											//�f�X�g���N�^
														
	HRESULT Init(void);									//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Set(void);										//�ݒ菈��

	const D3DXVECTOR3 GetPos(void);						//�ʒu�i���_�j�̎擾����
	const D3DXVECTOR3 GetRot(void);						//�����̎擾����
	const D3DXVECTOR3 GetDirection(void);				//���_���璍���_�܂ł̃x�N�g����Ԃ�����
	const D3DXVECTOR3 CCamera::GetFocalPoint(void);		//�����_�̎擾����
														
	void SetFocalPoint(const D3DXVECTOR3 pos);			//�����_�̐ݒ菈��
	void SetPos(const D3DXVECTOR3 posV, const D3DXVECTOR3 posR);	//���_�A�����_�̐ݒ�

	static CCamera* Create(D3DXVECTOR3 pos, D3DXVECTOR3 focalPoint);		//��������

private:
	static const float CAMERA_SPEED;

	D3DXVECTOR3 m_posV;						//���_
	D3DXVECTOR3 m_posR;						//�����_
	D3DXVECTOR3 m_DestPosV;					//�ړI�̎��_
	D3DXVECTOR3 m_DestPosR;					//�ړI�̒����_
	D3DXVECTOR3 m_vecU;						//������x�N�g��
	D3DXMATRIX  m_mtxProjection;			//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX  m_mtxView;					//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_rotDest;					//�ړI�̌���
	float		m_fLenght;					//XZ�ʂ̎��_�ƒ����_�̊Ԃ̋���
	int			m_nDelay;					//

	//CBoxHitbox *m_pHitBox;
};

#endif // !_CAMERA_H_