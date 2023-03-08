//-------------------------------------
//
//�n�[�t�X�t�B�A�w�b�_�[[halfsphere.h]
//Author:���c�喲
//
//-------------------------------------
#ifndef  _HALFSPHERE_H_				//���̃}�N����`������ĂȂ�������
#define  _HALFSPHERE_H_				//��d�C���N���[�h�h�~�̃}�N����`

#include "object.h"
#include <vector>

//---------------------------
//�}�N����`
//---------------------------
#define HALFSPHEAR_X_BLOCK	(15)							//X�����̃u���b�N��
#define HALFSPHEAR_Z_BLOCK	(15)							//Z�����̃u���b�N��

#define MAX_SPHERE	(2)

#define HALFSPHEAR_VERTEX_NUM	((HALFSPHEAR_X_BLOCK + 1) * (HALFSPHEAR_Z_BLOCK + 1))
#define HALFSPHEAR_INDEXNUM		((HALFSPHEAR_X_BLOCK + 1) * 2 * HALFSPHEAR_Z_BLOCK + (HALFSPHEAR_Z_BLOCK - 1) * 2)
#define HALFSPHEAR_PRIMITIVE_NUM	(HALFSPHEAR_X_BLOCK * (HALFSPHEAR_Z_BLOCK * 2) + (HALFSPHEAR_Z_BLOCK - 1) * 4)

//---------------------------
//�N���X�錾
//---------------------------
class CHalfSphere : public CObject
{
public:
	enum SPHERE_TEX
	{
		SPHERE_UP = 0,
		SPHERE_DOWN,
		SPHERE_MAX
	};

	CHalfSphere();
	CHalfSphere(const int nPriority);					//�R���X�g���N�^
	~CHalfSphere() override;

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;	//�I������
	void Update(void) override;	//�X�V����
	void Draw(void) override;	//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	void SetSize(const D3DXVECTOR3 size);				//�T�C�Y�̐ݒ�
	void SetRot(const D3DXVECTOR3 rot);
	void SetTex(const SPHERE_TEX tex);

	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����
	const D3DXVECTOR3 GetRot(void);

	static CHalfSphere* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,D3DXVECTOR3 rot, SPHERE_TEX tex);		//��������

	void BindTexture(LPDIRECT3DTEXTURE9	pTexture);			//�e�N�X�`������
	void LoadTexture(const char *aFileName);				//�e�N�X�`���̓ǂݍ���

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_size;						//�T�C�Y
	D3DXVECTOR3 m_rot;						//����
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

	SPHERE_TEX m_tex;
};

#endif
