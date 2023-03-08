//=============================================================================
//
// icePillar.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _ICE_PILLAR_H_
#define _ICE_PILLAR_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"
#include <vector>


//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;

class CIcePillar : public CObject
{
public:
	CIcePillar();																		//�R���X�g���N�^
	~CIcePillar() override;																//�f�X�g���N�^

	virtual HRESULT Init(void) override;												//����������
	virtual void Uninit(void) override;													//�I������
	virtual void Update(void) override;													//�X�V����
	virtual void Draw(void) override;													//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;										//�ʒu�̐ݒ菈��
	const D3DXVECTOR3 GetPos(void) override;											//�ʒu�̎擾����

	const D3DXVECTOR2 GetSize(void) override;											//�T�C�Y�̎擾����

	static CIcePillar* Create(CModel::ModelType type, D3DXVECTOR3 pos, const float ShadowHeight);			//��������

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
	int						m_nLife;												//���C�t
	std::vector <LPDIRECT3DTEXTURE9> m_vModelTexture;								//���f���̃e�N�X�`���ւ̃|�C���^
	CCylinderHitbox*		m_pHitbox;												//��̃q�b�g�{�b�N�X
	CCylinderHitbox*		m_pDamageHitbox;										//���̃q�b�g�{�b�N�X
};



#endif