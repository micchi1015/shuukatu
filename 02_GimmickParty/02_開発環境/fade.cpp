//=============================================================================
//
// �t�F�[�h
// Author : tanimoto kosuke
//
//=============================================================================
#include "fade.h"
#include "application.h"
#include "rendering.h"

//---------------------------------------------------------
// �}�N����`
//---------------------------------------------------------
#define ALPHA_CHANGE	(0.03f)	// �t�F�[�h��a�l�̕ω���

//=====================================
// �f�t�H���g�R���X�g���N�^
//=====================================
CFade::CFade() : m_pVtxBuff(nullptr)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CFade::~CFade()
{

}

//=====================================
// ����������
//=====================================
HRESULT CFade::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = SCREEN_WIDTH;
	pVtx[3].pos.y = SCREEN_HEIGHT;
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_fAlpha = 1.0f;	// �|���S����s�����ɂ���

	return S_OK;
}

//=====================================
// �I������
//=====================================
void CFade::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=====================================
// �X�V����
//=====================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{// �������Ă��Ȃ���Ԃł͂Ȃ��ꍇ
		switch (m_fade)
		{
			// �t�F�[�h�A�E�g��Ԃ̏ꍇ
		case FADE_OUT:
			m_fAlpha += ALPHA_CHANGE;	// �|���S����s�����ɂ��Ă���

			if (m_fAlpha >= 1.0f)
			{// ���S�ɕs�����ɂȂ����ꍇ
				m_fAlpha = 1.0f;
				m_fade = FADE_CHANGE;  // �t�F�[�h�؂�ւ����
			}
			break;
			// �t�F�[�h�C����Ԃ̏ꍇ
		case FADE_IN:
			m_fAlpha -= ALPHA_CHANGE;	// �|���S�������X�ɓ����ɂ���

			if (m_fAlpha <= 0.0f)
			{// ���S�ɓ����ɂȂ����ꍇ
				m_fAlpha = 0.0f;
				m_fade = FADE_NONE;	// �t�F�[�h�؂�ւ����
			}
			break;
			// �t�F�[�h�؂�ւ���Ԃ̏ꍇ
		case FADE_CHANGE:
			//�|���S�������S�ɕs�����ȏꍇ
			if (m_fAlpha == 1.0f)
			{
				m_fade = FADE_IN;		// �t�F�[�h�C�����
			}
			break;
		default:
			break;
		}
		SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fAlpha));
	}
}

//=====================================
// �`�揈��
//=====================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���𖢎g�p�ɂ���
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=====================================
//�F�ݒ菈��(�S��)
//=====================================
void CFade::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=====================================
// �t�F�[�h�ݒ菈��
//=====================================
void CFade::SetFade()
{
	//�|���S�������S�ɕs�����ȏꍇ
	if (m_fAlpha == 1.0f)
	{
		m_fade = FADE_IN;		// �t�F�[�h�C�����
	}
	//�|���S�������S�ɓ����ȏꍇ
	else if (m_fAlpha == 0.0f)
	{
		m_fade = FADE_OUT;		// �������Ă��Ȃ����
	}
}

//=====================================
// �t�F�[�h��������
//=====================================
CFade *CFade::Create()
{
	CFade* pFade = new CFade;

	if (pFade != nullptr)
	{
		if (FAILED(pFade->Init()))
		{
			return nullptr;
		}
	}
	return pFade;
}