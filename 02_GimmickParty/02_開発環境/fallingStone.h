//=============================================================================
//
// fallingStone.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FALLING_STONE_H_
#define _FALLING_STONE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"
#include <vector>

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;

class CFallingStone : public CObject
{
public:
	CFallingStone();												//�R���X�g���N�^
	~CFallingStone() override;										//�f�X�g���N�^

	virtual HRESULT Init(void) override;							//����������
	virtual void Uninit(void) override;								//�I������
	virtual void Update(void) override;								//�X�V����
	virtual void Draw(void) override;								//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;					//�ʒu�̐ݒ菈��
	const D3DXVECTOR3 GetPos(void) override;						//�ʒu�̎擾����

	const D3DXVECTOR2 GetSize(void) override;						//�T�C�Y�̎擾����

	void StartRotation(const D3DXVECTOR3 frameRot);					//��]�J�n�̐ݒ菈��
	void StopRotating(void);										//��]��~����
	void SetDirection(const float fLateralDirection);				//�����̐ݒ菈��


	//��������
	static CFallingStone* Create(CModel::ModelType type, D3DXVECTOR3 pos, const D3DXVECTOR3 spawnPos, const float ShadowHeight, const float fBound, const float fDir);			//��������

private:

	LPD3DXMESH				m_pMesh;												//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;												//�}�e���A�����ւ̃|�C���^
	DWORD					m_nNumMat;												//�}�e���A�����̐�
	D3DXVECTOR3				m_pos;													//���݂̈ʒu
	D3DXVECTOR3				m_LastPos;												//�O��̈ʒu
	D3DXVECTOR3				m_move;													//���f���̈ړ���
	D3DXVECTOR3				m_rot;													//����
	D3DXVECTOR3				m_spawnPos;												//�X�|�[���̃I�u�W�F�N�g�̈ʒu
	D3DXMATRIX				m_mtxWorld;												//���[���h�}�g���b�N�X
	float					m_shadowPosY;											//�e�̍���
	float					m_fBound;												//�e�̃G���A�̕�
	float					m_fDir;													//�����̕���
	D3DXVECTOR3				m_frameRot;												//��]���x
	CModel::ModelType		m_type;													//���f���̎��
	std::vector <LPDIRECT3DTEXTURE9> m_vModelTexture;								//���f���̃e�N�X�`���ւ̃|�C���^
	CCylinderHitbox*		m_pHitbox;

};



#endif