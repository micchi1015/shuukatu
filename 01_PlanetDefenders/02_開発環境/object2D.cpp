//------------------------------
//
// �I�u�W�F�N�g2D�̏���[object2D.cpp]
// Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include <assert.h>

#include "application.h"
#include "input.h"
#include "object.h"
#include "object2D.h"
#include "main.h"
#include "renderer.h"

//�R���X�g���N�^
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;	//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = nullptr;	//���_�o�b�t�@�ւ̃|�C���^
}

//�f�X�g���N�^
CObject2D::~CObject2D()
{
}

//����������
HRESULT CObject2D::Init()
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D *pVtx;

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//���̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);													//��]
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nTimer = 0.0f;																		//����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x -  m_size.x / 2, m_pos.y - m_size.y / 2,0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x +  m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x +  m_size.x / 2, m_pos.y + m_size.y / 2, 0);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//�I������
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();
}

//�X�V����
void CObject2D::Update()
{
	D3DXVECTOR3 move = GetMove();

	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0);

	//�ʒu���X�V
	m_pos.x += move.x;
	m_pos.y += move.y;
	m_pos.z += move.z;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//�`�揈��
void CObject2D::Draw()
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	0,2);										

	//�e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);
}

//�|���S���̐����E�ݒ菈��
CObject2D *CObject2D::Create(const D3DXVECTOR3 pos, int nPriority)
{
	CObject2D *pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//pos�̐ݒ�
void CObject2D::SetPos(const D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

	 m_pos = pos;

	 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	 m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	 pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	 pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0);
	 pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0);
	 pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0);

	 //���_�o�b�t�@���A�����b�N
	 m_pVtxBuff->Unlock();
}

//�J���[�̐ݒ�
void CObject2D::SetColer(const D3DXCOLOR col)
{
	m_col = col;
}

//size�̐ݒ�
void CObject2D::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}

//pos�̏��擾
const D3DXVECTOR3 CObject2D::GetPos()
{
	return m_pos;
}

//size�̏��擾
const D3DXVECTOR3 CObject2D::GetSize()
{
	return m_size;
}

//col�̏��擾
const D3DXCOLOR CObject2D::GetCol()
{
	return m_col;
}

//�e�N�X�`������
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//���e�N�X�`���摜�̐ݒ�
void CObject2D::SetTexPos(float BesideSplit, float nNumIndex)
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndex / BesideSplit, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nNumIndex +1) / BesideSplit,0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumIndex / BesideSplit,1.0f);
	pVtx[3].tex = D3DXVECTOR2((nNumIndex + 1) / BesideSplit, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//�e�N�X�`���摜�̐ݒ�
void CObject2D::SetLifeTexPos(float BesideSplit, float nNumIndexX, float Split, float nNumIndexY)
{
	//���_���W�ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumIndexX / BesideSplit, (nNumIndexY) / Split);
	pVtx[1].tex = D3DXVECTOR2((nNumIndexX + 1) / BesideSplit, (nNumIndexY) / Split);
	pVtx[2].tex = D3DXVECTOR2(nNumIndexX / BesideSplit, (nNumIndexY + 1) / Split);
	pVtx[3].tex = D3DXVECTOR2((nNumIndexX + 1) / BesideSplit, (nNumIndexY + 1) / Split);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}