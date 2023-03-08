//=============================================================================
//
// animator.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ANIMATOR_H
#define ANIMATOR_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include <vector>

//=============================================================================
//�O���錾
//=============================================================================
class CModelPart;

class CAnimator
{
public:

	//�A�j���[�V�����̎��
	enum AnimType
	{
		ANIM_TYPE_PLAYER = 0,					//�v���C���[�A�j���[�V����
		ANIM_TYPE_MAX
	};

	//�L�[�̏��
	struct AnimKey
	{
		D3DXVECTOR3 RelativePos;				//�L�[�̈ʒu
		D3DXVECTOR3 RelativeRot;				//�L�[�̉�]
	};

	//�L�[�Z�b�g�̏��
	struct AnimKeySet
	{
		int nAnimFrames;						//�A�j���[�V�����t���[����
		std::vector <AnimKey> vAnimKey;			//�A�j���[�V�����L�[
	};

	//���[�V�����Z�b�g�̏��
	struct MotionSet
	{
		int nNextAnim;							//���̃A�j���[�V�����̔ԍ�
		std::vector <AnimKeySet> vAnimKeySet;	//�L�[�Z�b�g
	};

	//�A�j���[�V�����̏��
	struct ModelAnimationSet
	{
		std::vector <MotionSet> vAnimSets;		//���[�V�����Z�b�g
	};

	CAnimator();					//�R���X�g���N�^
	~CAnimator();					//�f�X�g���N�^

	HRESULT Init(void);				//����������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����

	void SetParts(std::vector <CModelPart*>* vParts);		//�p�[�c�̐ݒ菈��

	static void LoadAllAnimation(void);						//�S���̃A�j���[�V�����̓ǂݍ��ޏ���
	static void DestroyLoadedAnimation(void);				//�S���̃A�j���[�V�����̔j������
	static CAnimator* Create(std::vector <CModelPart*>* vParts, AnimType type);				//��������

	void SetPresentAnim(int nPresentAnim);					//�A�j���[�V�����̐ݒ菈��
	void SetLoopingAnim(int nPresentAnim);					//�A�j���[�V�����̐ݒ菈��(�A�j���[�V�������I������ꍇ�A���ɖ߂�)
private:

	//�A�j���[�V�����X�s�[�h
	struct animSpeed
	{
		D3DXVECTOR3 move;									//�ړ���
		D3DXVECTOR3 rotSpeed;								//��]�X�s�[�h
	};

	static char* m_pAnimPass[ANIM_TYPE_MAX];				//�A�j���[�V�����̊O���t�@�C���̑��΃p�X
															
	std::vector <CModelPart*>	 m_vParts;					//�p�[�c�̃x�N�g��
	std::vector <animSpeed>		 m_vAnimSpeed;				//�A�j���[�V�����X�s�[�h�̃x�N�g��
	int							 m_nPresentFrame;			//���݂̃t���[��
	int							 m_nPresentMotionSet;		//�Đ�����郂�[�V�����Z�b�g�̔ԍ�
	int							 m_nPresentAnim;			//�Đ������A�j���[�V�����̔ԍ�
	AnimType					 m_type;					//�A�j���[�V�����̎��
															
	static std::vector <ModelAnimationSet> m_vAnimAll;		//�S���̃A�j���[�V�����������Ă���x�N�g��
};




#endif
