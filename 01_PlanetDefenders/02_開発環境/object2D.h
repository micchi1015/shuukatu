//-----------------------------
//
// [object2D.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object.h"

//--------------------------
//�}�N����`
//--------------------------
//���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//--------------------------
// �\���̒�`
//--------------------------
// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

//---------------------------
//�I�u�W�F�N�g2D�N���X
//---------------------------
class CObject2D : public CObject
{
public:
	explicit CObject2D(int nPriority = PRIORITY_3);			//�R���X�g���N�^
	~CObject2D() override;	//�f�X�g���N�^

	virtual HRESULT Init() override;						//����������
	virtual void Uninit() override;							//�I������
	virtual void Update() override;							//�X�V����
	virtual void Draw() override;							//�`�揈��
	virtual void SetPos(const D3DXVECTOR3 pos) override;	//Pos�̒l��ݒ�

	void SetColer(const D3DXCOLOR col);						//coler�̐ݒ�
	void SetSize(const D3DXVECTOR3 size);					//size�̒l��ݒ�
	void SetTexPos(float BesideSplit, float nNumIndex);		//Tex�̐ݒ�
	void SetLifeTexPos(float BesideSplit, float nNumIndexX, float Split, float nNumIndexY);		//Tex�̐ݒ�
	const D3DXVECTOR3 GetPos() override;					//pos�̒l���擾����
	const D3DXVECTOR3 GetSize() override;					//�T�C�Y�̏��擾
	const D3DXCOLOR GetCol() override;						//col�̏��擾

	static CObject2D *Create(const D3DXVECTOR3 pos,int nPriority);		//�|���S���̐���
	void BindTexture(LPDIRECT3DTEXTURE9	pTexture);						//�e�N�X�`������	

private:
	LPDIRECT3DTEXTURE9			m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;			//���W�ʒu
	D3DXVECTOR3					m_rot;			//��]��	
	D3DXVECTOR3					m_size;			//�T�C�Y
	D3DXCOLOR					m_col;			//�J���[

	float m_nTimer;		//����
};

#endif

