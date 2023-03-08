//=============================================================================
//
// modelPart.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MODEL_PART_H
#define _MODEL_PART_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

class CModelPart
{
public:

	CModelPart();																		//�R���X�g���N�^
	~CModelPart();																		//�f�X�g���N�^

	HRESULT Init(void);																	//����������
	void Uninit(void);																	//�I������
	void Update(void);																	//�X�V����
	void Draw(void);																	//�`�揈��
	void Draw(D3DXMATRIX mtxParent);													//�`�揈��

	void SetParent(CModelPart* pParent);												//�e�̐ݒ菈��
	CModelPart* GetParent(void);														//�e�̎擾����

	void SetPos(const D3DXVECTOR3 pos);													//�ʒu�̐ݒ菈��
	const D3DXVECTOR3 GetPos(void);														//�ʒu�̎擾����

	void SetRot(const D3DXVECTOR3 rot);													//�����̐ݒ菈��
	const D3DXVECTOR3 GetRot(void);														//�����̎擾����

	const D3DXVECTOR3 GetSize(void);													//�T�C�Y�̎擾����
	D3DXMATRIX GetMatrix(void);															//�}�g���b�N�X�̎擾����

	void SetShadowHeight(const float fHeight);											//�e�̍����̐ݒ菈��

	void SetModelColor(const int nNumMat, const D3DXCOLOR col);
	void SetModel(CModel::ModelType model);

	static CModelPart* Create(CModel::ModelType type, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);								//��������

private:

	LPD3DXMESH				m_pMesh;												//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;												//�}�e���A�����ւ̃|�C���^
	DWORD					m_nNumMat;												//�}�e���A�����̐�
	D3DXVECTOR3				m_pos;													//���݂̈ʒu
	D3DXVECTOR3				m_LastPos;												//�O��̈ʒu
	D3DXVECTOR3				m_move;													//���f���̈ړ���
	D3DXVECTOR3				m_rot;													//����
	D3DXMATRIX				m_mtxWorld;												//���[���h�}�g���b�N�X
	float					m_shadowPosY;											//�e�̍���
	CModel::ModelType		m_type;													//���f���̎��
	std::vector <LPDIRECT3DTEXTURE9> m_vModelTexture;								//���f���̃e�N�X�`���ւ̃|�C���^
	CModelPart*				m_pParent;												//�e�ւ̃|�C���^
	std::vector <CModel::ModelColor> m_vCol;										//���f���̐F
};

#endif