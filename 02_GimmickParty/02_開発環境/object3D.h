//=============================================================================
//
// object3D.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef OBJECT_3D_H
#define OBJECT_3D_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBullet;

//=============================================================================
//2D�|���S���̃N���X
//=============================================================================
class CObject_3D : public CObject
{
public:
	CObject_3D();																	//�R���X�g���N�^
	CObject_3D(const int nPriority);												//�R���X�g���N�^
	virtual ~CObject_3D() override;													//�f�X�g���N�^

	virtual HRESULT Init(void) override;											//����������
	virtual void Uninit(void) override;												//�I������
	virtual void Update(void) override;												//�X�V����
	virtual void Draw(void) override;												//�I������

public:
	void SetPos(const D3DXVECTOR3 pos) override;									//�ʒu�̐ݒ菈��
	void SetSize(const D3DXVECTOR2 dim);											//�|���S���̕��ƍ����̐ݒ菈��
	void SetSize(const float x, const float y);										//�|���S���̕��ƍ����̐ݒ菈��
	const D3DXVECTOR2 GetSize(void) override;										//�|���S���̃T�C�Y�̎擾����
	const D3DXVECTOR3 GetMove(void);												//���x�̎擾����
	void SetMove(const D3DXVECTOR3 move);											//���x�̐ݒ菈��
	const D3DXVECTOR3 GetAcceleration(void);										//�����̎擾����
	void SetAcceleration(const D3DXVECTOR3 acc);									//�����̐ݒ菈��
	void SetRotation(const D3DXVECTOR3 frameRot);									//��]�̐ݒ菈��
	void AddAngularSpeed(const D3DXVECTOR3 speed);									//��]���x�̉��Z����
	const D3DXVECTOR3 GetAngularSpeed(void);										//��]���x�̎擾����
	void SetStartingRot(const D3DXVECTOR3 fStartRot);								//��]�p�x�̏����l
	const D3DXVECTOR3 GetRot(void);													//��]�p�x�̎擾����

	const D3DXVECTOR3 GetPos(void) override;										//�ʒu�̎擾����
	void SetTextureParameter(const int MaxPattern, const int LinePattern,
		const int ColumnPattern, const int nAnimFrame);								//�e�N�X�`���̃p�����[�^�̐ݒ菈��
	const int GetPresentAnimPattern(void);											//���݂̃A�j���[�V�����p�^�[���̎擾����
	void SetAnimPattern(const int PatternNum);										//���݂̃A�j���[�V�����p�^�[���̐ݒ菈��
	bool GetFlipX(void);															//�e�N�X�`����X���W�����]���Ă��邩�ǂ������擾����
	void FlipX(void);																//�e�N�X�`����X���W�𔽓]����
	void FlipY(void);																//�e�N�X�`����Y���W�𔽓]����
	const D3DXCOLOR GetColor(void);													//�J�[���[�̎擾����
	void SetColor(const D3DXCOLOR col);												//�J�[���[�̐ݒ菈��
	void SetVtxColor(const int nVtxIdx, const D3DXCOLOR col);						//���_�P�̃J�[���[�ݒ菈��
	void MoveTexCoordinates(const D3DXVECTOR2 move);								//�e�N�X�`���̈ړ��ʂ̐ݒ菈��

	void SetTexture(TextType textType);												//�e�N�X�`���̎�ނ̐ݒ菈��
	void SetAnimationBase(const int FirstPattern);									//�A�j���[�V�����̍ŏ��̃p�^�[���̐ݒ菈��
	LPDIRECT3DVERTEXBUFFER9 GetVtxbuff(void);										//���_�o�b�t�@�̎擾����

	static CObject_3D* Create(void);												//CObject_2D�̐�������

private:

	static char* m_paTextPass[CObject::TEXTURE_TYPE_MAX];								

	void UpdateTexture(void);									//�e�N�X�`�����W�̍X�V����

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//���_�o�b�t�@

//================================================================================================================
	//�I�u�W�F�N�g�̈ʒu�ƈړ��ʂƊ֌W������ϐ�
	D3DXVECTOR3 m_pos;											//�|���S���̈ʒu
	D3DXVECTOR3 m_dir;											//�|���S���̌���
	D3DXVECTOR3 m_move;											//�ړ���
	D3DXVECTOR3 m_acc;											//����
	D3DXVECTOR3 m_rot;											//�|���S���̉�]�p�x
	float m_fAngle;												//�|���S���̉�]�p�̊p�x
	D3DXVECTOR3 m_fFrameRot;									//1�t���[���̉�]�p�x
	D3DXVECTOR2 m_size;											//�|���S���̕��ƍ���
	D3DXMATRIX m_mtxWorld;										//���[���h�}�g���b�N�X
//================================================================================================================
//================================================================================================================
//�e�N�X�`���ƃA�j���[�V�����Ɗ֌W������ϐ�
	int m_nAnimPattern;											//���݂̃e�N�X�`���p�^�[��
	int m_nCountAnim;											//�A�j���[�V�����J�E���^�[
	int m_nMaxTexPattern;										//�e�N�X�`���̃p�^�[����
	int m_nMaxTexColumn;										//�e�N�X�`���̍s��
	int m_nTexLine;												//�e�N�X�`���̗�
	int m_nFirstPattern;										//�A�j���[�V�����̍ŏ��̃p�^�[��
	int m_nAnimFrame;											//�A�j���[�V�����p�^�[���̕ύX�t���[����
	D3DXVECTOR2 m_textureTranslation;							//�e�N�X�`���̈ړ���
	bool m_bFlipX;												//�e�N�X�`����X���W�����]���Ă��邩�ǂ���
	bool m_bFlipY;												//�e�N�X�`����Y���W�����]���Ă��邩�ǂ���
	D3DXCOLOR m_col;											//�J�[���[
	D3DXCOLOR m_VtxCol[4];										//���_�J�[���[
	TextType m_textType;										//�e�N�X�`���̎��
	LPDIRECT3DTEXTURE9 m_pTexture;								//�e�N�X�`���ւ̃|�C���^
//================================================================================================================
//================================================================================================================
//�ÓI�ϐ�
//================================================================================================================

};



#endif