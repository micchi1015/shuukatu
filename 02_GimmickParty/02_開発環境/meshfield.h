//=============================================================================
//
// meshfield.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include <vector>

class CMeshfield : public CObject
{
public:
	CMeshfield();										//�R���X�g���N�^
	CMeshfield(const int nPriority);					//�R���X�g���N�^
	~CMeshfield() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	void SetPriority(const int nPriority);				//�v���C�I���e�B�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����
	const int GetLine(void) { return m_nLineVertex; }
	const float GetFriction(void);						//���C�W���̎擾����

	void SetTexture(CObject::TextType texture);			//�e�N�X�`���̐ݒ菈��
	void SetTextureTiling(D3DXVECTOR2 TileSize);		//�e�N�X�`���̑傫���̐ݒ菈��
	void SetTextureTiling(float fTileSize);				//�e�N�X�`���̑傫���̐ݒ菈��	
	void SetTextureAnim(const D3DXVECTOR2 animSpeed);	//�e�N�X�`���A�j���[�V�����̐ݒ菈��
	void SetTextureAnim(const float fX, const float fY);//�e�N�X�`���A�j���[�V�����̐ݒ菈��
	void StopTextureAnim(void);							//�e�N�X�`���A�j���[�V�����̒�~����
	void SetAnimation(const bool bAnim);															//�A�j���[�V�����̐ݒ菈��
	void SetAnimation(const bool bAnim, const float fAngularSpeed, const float fAmplitude);			//�A�j���[�V�����̐ݒ菈��

	void ChangeHeight(const int nStartVtx, const int nEndVtx, const float fHeight);					//���_�̍����̐ݒ菈��

	static CMeshfield* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
		const D3DXVECTOR2 unitSize, const int NumberLines, const int NumberColumns);							//��������
	static CMeshfield* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
		const D3DXVECTOR2 unitSize, const int NumberLines, const int NumberColumns, const int nPriority);		//��������
	static CMeshfield* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
		const D3DXVECTOR2 unitSize, const int NumberLines, const int NumberColumns, const float fFriction);							//��������
	static CMeshfield* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, 
		const D3DXVECTOR2 unitSize, const int NumberLines, const int NumberColumns, const int nPriority, const float fFriction);		//��������

	static bool FieldInteraction(CObject* pObj);							//�����蔻��̏���
	static CMeshfield* FieldInteraction(CObject* pObj, float* fHeight);		//�����蔻��̏���

private:
	void SetVertex(void);								//���_�C���f�b�N�X�̐ݒ菈��

	static const int MAX_FIELD_PRIORITY = 2;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;					//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;						//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_rot;									//����
	D3DXVECTOR2 m_size;									//�P�ʂ̃T�C�Y
	D3DXVECTOR2 m_LateralCoords;						//X���W�͈̔�
	D3DXMATRIX m_mtxWorld;								//�����h�}�g���b�N�X
	int m_nVertexNumber;								//���b�V���t�B�[���h�̒��_��
	int m_nIntexNumber;									//���b�V���t�B�[���h�̃C���f�b�N�X��
	int m_nPolygonNumber;								//���b�V���t�B�[���h�̃|���S����
	int m_nLineVertex;									//�v�Z�p�̃O���[�o���ϐ�(�� + 1)
	int m_nColumnVertex;								//�v�Z�p�̃O���[�o���ϐ�(�s�� + 1)
	float m_fFriction;									//���C�W��
	float m_fAnimAngle;									//�A�j���[�V�����悤�̊p�x
	float m_fAnimSpeed;									//�A�j���[�V�����X�s�[�h
	float m_fAmplitude;									//�A�j���[�V�����̐U��
	bool m_bTextureAnim;								//�e�N�X�`���A�j���[�V�����̃t���O
	bool m_bAnim;										//�A�j���[�V�����̃t���O
	D3DXVECTOR2 m_animSpeed;							//�e�N�X�`���A�j���[�V�����X�s�[�h
	int m_nPriority;									//�v���C�I���e�B

	static std::vector <CMeshfield*> m_vMeshfield;		//���b�V���t�B�[���h�ւ̃|�C���^�̃x�N�g��

};


#endif