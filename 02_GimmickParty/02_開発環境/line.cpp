//=============================================================================
//
// line.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "line.h"
#include "application.h"
#include "rendering.h"

//�R���X�g���N�^
CLine::CLine() : CObject(5)
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;				//�ʒu
	m_rot = Vec3Null;				//����
	m_col = ColorWhite;				//�J�[���[
	m_start = Vec3Null;				//�J�n�_
	m_finish = Vec3Null;			//�I���_
	m_pVtxBuff = nullptr;			//���_�o�b�t�@
}

//�f�X�g���N�^
CLine::~CLine()
{

}

//����������
HRESULT CLine::Init(void)
{
	//�����o�[�ϐ��̏�����
	m_pos = Vec3Null;			//�ʒu
	m_rot = Vec3Null;			//����
	m_col = ColorWhite;			//�J�[���[
	m_start = Vec3Null;			//�J�n�_
	m_finish = Vec3Null;		//�I���_
	m_pVtxBuff = nullptr;		//���_�o�b�t�@

	return S_OK;
}

//�I������
void CLine::Uninit(void)
{
	//���_�o�b�t�@�̔j������
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//�X�V����
void CLine::Update(void)
{

}

//�`�揈��
void CLine::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X

	//���C�g�𖳌����ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	

	//�����h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�����h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_LINE));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_LINE);

	//�l�p�`��`�悷��
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//�ʒu�̐ݒ菈��
void CLine::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CLine::GetSize(void)
{
	return Vec2Null;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CLine::GetPos(void)
{
	return m_pos;
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================




//��������
CLine* CLine::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 start, const D3DXVECTOR3 end, D3DXCOLOR col)
{
	CLine* pLine = new CLine;			//���̐���

	if (FAILED(pLine->Init()))
	{//����������
		return nullptr;
	}

	pLine->m_pos = pos;				//�ʒu�̐ݒ�
	pLine->m_rot = rot;				//�����̐ݒ�
	pLine->m_start = start;			//�J�n�_�̐ݒ�
	pLine->m_finish = end;			//�I���_�̐ݒ�
	pLine->m_col = col;				//�J�[���[�̐ݒ�

	pLine->SetLine();				//���_�̐ݒ菈��

	return pLine;					//������������Ԃ�
}

//��������
CLine* CLine::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 start, const D3DXVECTOR3 end)
{
	CLine* pLine = new CLine();		//���̐���

	if (FAILED(pLine->Init()))
	{//����������
		return nullptr;
	}

	pLine->m_pos = pos;										//�ʒu�̐ݒ�
	pLine->m_rot = rot;										//�����̐ݒ�
	pLine->m_start = start;									//�J�n�_�̐ݒ�
	pLine->m_finish = end;									//�I���_�̐ݒ�
	pLine->m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//�J�[���[�̐ݒ�

	pLine->SetLine();				//���_�̐ݒ菈��

	return pLine;					//������������Ԃ�
}


//========================================================================================================================
//
//			�v���C�x�[�g�֐�
//
//========================================================================================================================


//���_�̐ݒ菈��
void CLine::SetLine(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_LINE) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_LINE,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_LINE*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = m_start;
	pVtx[1].pos = m_finish;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}