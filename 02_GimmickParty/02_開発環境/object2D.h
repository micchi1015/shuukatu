//=============================================================================
//
// object2D.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef OBJECT_2D_H
#define OBJECT_2D_H

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
class CObject_2D : public CObject
{
public:
	CObject_2D();																	//�R���X�g���N�^
	CObject_2D(const int nPriority);												//�R���X�g���N�^
	virtual ~CObject_2D() override;													//�f�X�g���N�^
														
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
	void SetRotation(const float fFrameRot);										//��]�̐ݒ菈��
	void AddAngularSpeed(const float fSpeed);										//��]���x�̉��Z����
	const float GetAngularSpeed(void);												//��]���x�̎擾����
	void SetStartingRot(const float fStartRot);										//��]�p�x�̏����l
	const float GetRot(void);														//��]�p�x�̎擾����
	void SetRevolution(const D3DXVECTOR3 Center, 									//���]�̐ݒ菈��
		const float fAngularSpeed, const float fRadius);							
	void SetRevolutionCenter(const D3DXVECTOR3 Center);								//���]�̒��S�_�̐ݒ菈��
	void SetPresentRevolutionAngle(const float fAngle);								//���݂̌��]�p�x�̐ݒ菈��
	const D3DXVECTOR3 GetRevolutionCenter(void);									//���]�̒��S�_�̎擾����
	void AddRevolutionSpeed(const float fSpeed);									//���]���x�̉��Z����

	const D3DXVECTOR3 GetPos(void) override;										//�ʒu�̎擾����
	void SetTextureParameter(const int MaxPattern, const int LinePattern,
		const int ColumnPattern, const int nAnimFrame);								//�e�N�X�`���̃p�����[�^�̐ݒ菈��
	const int GetPresentAnimPattern(void);											//���݂̃A�j���[�V�����p�^�[���̎擾����
	void SetAnimPattern(const int PatternNum);										//���݂̃A�j���[�V�����p�^�[���̐ݒ菈��
	void SetAnimationBase(const int FirstPattern);									//�A�j���[�V�����̍ŏ��̃p�^�[���̐ݒ菈��
	void MoveTexCoordinates(const D3DXVECTOR2 move);								//�e�N�X�`���̈ړ��ʂ̐ݒ菈��
	bool GetFlipX(void);															//�e�N�X�`����X���W�����]���Ă��邩�ǂ������擾����
	void FlipX(void);																//�e�N�X�`����X���W�𔽓]����
	void FlipY(void);																//�e�N�X�`����Y���W�𔽓]����
	const D3DXCOLOR GetColor(void);													//�J�[���[�̎擾����
	void SetColor(const D3DXCOLOR col);												//�J�[���[�̐ݒ菈��
	void SetVtxColor(const int nVtxIdx, const D3DXCOLOR col);						//���_�P�̃J�[���[�ݒ菈��

	void SetTexture(TextType textType);												//�e�N�X�`���̎�ނ̐ݒ菈��
	LPDIRECT3DVERTEXBUFFER9 GetVtxbuff(void);										//���_�o�b�t�@�̎擾����

	static void LoadTextures(void);													//�e�N�X�`����S�����[�h���鏈��
	static void DestroyLoadedTextures(void);										//�e�N�X�`����S���j�����鏈��
	static LPDIRECT3DTEXTURE9 GetTexturePointer(CObject::TextType type);			//�e�N�X�`���ւ̃|�C���^�̎擾����

	static CObject_2D* Create(void);												//CObject_2D�̐�������

private:

	static char* m_paTextPass[CObject::TEXTURE_TYPE_MAX];

	void UpdateTexture(void);									//�e�N�X�`�����W�̍X�V����

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//���_�o�b�t�@

	//================================================================================================================
	//�I�u�W�F�N�g�̈ʒu�ƈړ��ʂƊ֌W������ϐ�
	D3DXVECTOR3 m_posPolygon;									//�|���S���̈ʒu
	D3DXVECTOR3 m_dir;											//�|���S���̌���
	D3DXVECTOR3 m_move;											//�ړ���
	D3DXVECTOR3 m_acc;											//����
	float m_fRot;												//�|���S���̉�]�p�x
	float m_fAngle;												//�|���S���̉�]�p�̊p�x
	float m_fFrameRot;											//1�t���[���̉�]�p�x
	D3DXVECTOR3 m_revolutionCenter;								//���]�̒��S�_
	float m_fRevolutionSpeed;									//���]�̃X�s�[�h
	float m_fRevolutionAngle;									//���]�̌��݊p�x
	float m_fRevolutionRadius;									//���]�̔��a
	D3DXVECTOR2 m_size;											//�|���S���̕��ƍ���
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
	D3DXVECTOR2 m_textureAnimSpeed;								//�e�N�X�`���̈ړ����x
	bool m_bFlipX;												//�e�N�X�`����X���W�����]���Ă��邩�ǂ���
	bool m_bFlipY;												//�e�N�X�`����Y���W�����]���Ă��邩�ǂ���
	D3DXCOLOR m_col;											//�J�[���[
	D3DXCOLOR m_VtxCol[4];										//���_�J�[���[
	TextType m_textType;										//�e�N�X�`���̎��
	//================================================================================================================
	//================================================================================================================
	//�ÓI�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTextureAll[TEXTURE_TYPE_MAX];		//�e�N�X�`���ւ̃|�C���^�̔z��
	//================================================================================================================

};



#endif