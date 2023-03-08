//=============================================================================
//
// effect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"
#include "application.h"
#include "rendering.h"


//�R���X�g���N�^
CEffect::CEffect()
{
	//�����o�[�ϐ����N���A����
	m_rotSpeed = Vec3Null;				//��]���x
	m_move = Vec3Null;					//�ړ���
	m_deltaCol = ColorNull;				//�F�̌���
	m_fDeltaSize = 0.0f;				//�T�C�Y�̌���
	m_nLife = 0;						//���C�t
}

//�f�X�g���N�^
CEffect::~CEffect()
{

}

//����������
HRESULT CEffect::Init(void)
{
	//����������

	if (FAILED(CBillboard::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	m_rotSpeed = Vec3Null;			//��]���x
	m_move = Vec3Null;				//�ړ���
	m_deltaCol = ColorNull;			//�F�̌���
	m_fDeltaSize = 0.0f;			//�T�C�Y�̌���
	m_nLife = 0;					//���C�t

	return S_OK;
}

//�I������
void CEffect::Uninit(void)
{
	CBillboard::Uninit();			//��{�N���X�̏I������
}

//�X�V����
void CEffect::Update(void)
{
	{
		m_nLife--;				//���C�t���f�N�������g����

		if (m_nLife <= 0)
		{//���C�t��0�ȉ��ɂȂ�����A�j������
			Release();
			return;
		}

		//�ʒu�̍X�V
		D3DXVECTOR3 pos = GetPos();
		pos += m_move;
		SetPos(pos);

		//��]�̍X�V
		D3DXVECTOR3 rot = GetRot();
		rot += m_rotSpeed;
		SetRot(rot);

		//�F�̍X�V
		D3DXCOLOR col = GetColor();
		col += m_deltaCol;

		if (col.r <= 0.0f && col.g <= 0.0 && col.b <= 0.0f || col.a <= 0.0f)
		{//�^�����ɂȂ�����A���͓����ɂȂ�����A�j������
			Release();
			return;
		}

		SetColor(col);				//�J�[���[�̐ݒ�

		//�T�C�Y�̍X�V
		D3DXVECTOR2 Size = GetSize();
		Size.x += m_fDeltaSize;
		Size.y += m_fDeltaSize;
		
		if (Size.x <= 0.0f || Size.y <= 0.0f)
		{//�T�C�Y��0�ȉ��ɂȂ�����A�j������
			Release();
			return;
		}

		SetSize(Size);				//�T�C�Y�̐ݒ�
	}

	CBillboard::Update();			//��{�N���X�̍X�V����
}

//�`�揈��
void CEffect::Draw(void)
{
	//�f�o�C�X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->CRenderer::GetDevice();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();				//��{�N���X�̕`�揈��

	// �ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rotSpeed, const D3DXVECTOR3 move, const D3DXCOLOR col, const D3DXCOLOR deltaCol, const float fSize, const float fdeltaSize, const int nLife)
{	
	CEffect* pEffect = new CEffect;				//�G�t�F�N�g�𐶐�����

	if (FAILED(pEffect->Init()))
	{//����������
		return nullptr;
	}

	pEffect->SetPos(pos);								//�ʒu�̐ݒ�
	pEffect->m_rotSpeed = rotSpeed;						//��]���x�̐ݒ�
	pEffect->m_move = move;								//�ړ��ʂ̐ݒ�
	pEffect->SetColor(col);								//�F�̐ݒ�
	pEffect->m_deltaCol = deltaCol;						//�F�̌����̐ݒ�
	pEffect->SetSize(D3DXVECTOR2(fSize, fSize));		//�T�C�Y�̐ݒ�
	pEffect->m_fDeltaSize = fdeltaSize;					//�T�C�Y�̌����̐ݒ�
	pEffect->m_nLife = nLife;							//���C�t�̐ݒ�
	pEffect->SetPriority(4);							//�v���C�I���e�B�̐ݒ�

	return pEffect;										//���������C���X�^���X��Ԃ�
}