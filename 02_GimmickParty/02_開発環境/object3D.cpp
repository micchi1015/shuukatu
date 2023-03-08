//=============================================================================
//
// object3D.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object3D.h"
#include "object2D.h"
#include "rendering.h"
#include "application.h"

//�ÓI�����o�[�ϐ��̐錾
//LPDIRECT3DTEXTURE9 CObject_3D::m_pTextureAll[CObject_3D::TextTypeMax] = {};

char* CObject_3D::m_paTextPass[CObject::TEXTURE_TYPE_MAX] =
{

};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CObject_3D::CObject_3D()
{
	m_pVtxBuff = nullptr;								//���_�o�b�t�@
	m_size = D3DXVECTOR2(0.0f, 0.0f);					//�|���S���̕��ƍ���
	m_dir = Vec3Null;									//�|���S���̌���
	m_move = Vec3Null;									//�ړ���
	m_acc = Vec3Null;									//����
	m_rot = Vec3Null;									//�|���S���̉�]�p�x
	m_fAngle = 0.0f;									//�|���S���̉�]�p�̊p�x
	m_fFrameRot = Vec3Null;								//1�t���[���̉�]�p�x
	m_pos = Vec3Null;									//�|���S���̈ʒu
	m_nCountAnim = 0;									//���݂̃e�N�X�`���p�^�[��
	m_nAnimPattern = 0;									//�A�j���[�V�����J�E���^�[
	m_nMaxTexPattern = 0;								//�e�N�X�`���̃p�^�[����
	m_nMaxTexColumn = 0;								//�e�N�X�`���̍s��
	m_nTexLine = 0;										//�e�N�X�`���̗�
	m_nFirstPattern = 0;								//�A�j���[�V�����̍ŏ��̃p�^�[��
	m_nAnimFrame = 0;									//�A�j���[�V�����p�^�[���̕ύX�t���[����
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);		//�e�N�X�`���̈ړ���
	m_bFlipX = false;									//�e�N�X�`����X���W�����]���Ă��邩�ǂ���
	m_bFlipY = false;									//�e�N�X�`����Y���W�����]���Ă��邩�ǂ���
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			//�J���[
	m_textType = CObject::TEXTURE_TYPE_MAX;				//�e�N�X�`���̎��
	m_pTexture = nullptr;								//�e�N�X�`���ւ̃|�C���^

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//���_�J���[
	}
}

CObject_3D::CObject_3D(const int nPriority) : CObject::CObject(nPriority)
{
	m_pVtxBuff = nullptr;								//���_�o�b�t�@
	m_size = D3DXVECTOR2(0.0f, 0.0f);					//�|���S���̕��ƍ���
	m_dir = Vec3Null;									//�|���S���̌���
	m_move = Vec3Null;									//�ړ���
	m_acc = Vec3Null;									//����
	m_rot = Vec3Null;									//�|���S���̉�]�p�x
	m_fAngle = 0.0f;									//�|���S���̉�]�p�̊p�x
	m_fFrameRot = Vec3Null;								//1�t���[���̉�]�p�x
	m_pos = Vec3Null;									//�|���S���̈ʒu
	m_nCountAnim = 0;									//���݂̃e�N�X�`���p�^�[��
	m_nAnimPattern = 0;									//�A�j���[�V�����J�E���^�[
	m_nMaxTexPattern = 0;								//�e�N�X�`���̃p�^�[����
	m_nMaxTexColumn = 0;								//�e�N�X�`���̍s��
	m_nTexLine = 0;										//�e�N�X�`���̗�
	m_nFirstPattern = 0;								//�A�j���[�V�����̍ŏ��̃p�^�[��
	m_nAnimFrame = 0;									//�A�j���[�V�����p�^�[���̕ύX�t���[����
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);		//�e�N�X�`���̈ړ���
	m_bFlipX = false;									//�e�N�X�`����X���W�����]���Ă��邩�ǂ���
	m_bFlipY = false;									//�e�N�X�`����Y���W�����]���Ă��邩�ǂ���
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			//�J���[
	m_textType = CObject::TEXTURE_TYPE_MAX;				//�e�N�X�`���̎��
	m_pTexture = nullptr;								//�e�N�X�`���ւ̃|�C���^

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//���_�J���[
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CObject_3D::~CObject_3D()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CObject_3D::Init(void)
{
	CRenderer* Render = CApplication::GetRenderer();			//�����f�B���O�C���X�^���X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();			//�f�o�C�X�̎擾����

	m_size = D3DXVECTOR2(0.0f, 0.0f);							//�|���S���̕��ƍ����̐ݒ�
	m_dir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);						//�|���S���̌���
	m_move = Vec3Null;											//�ړ���
	m_acc = Vec3Null;											//����
	m_rot = Vec3Null;											//��]�p�x�̐ݒ�
	m_fAngle = 0.0f;											//��]�p�̊p�x���v�Z����
	m_fFrameRot = Vec3Null;										//1�t���[���̉�]�p�x
	m_pos = Vec3Null;											//�ʒu�̐ݒ�
	m_nCountAnim = 0;											//���݂̃e�N�X�`���p�^�[��
	m_nAnimPattern = 0;											//�A�j���[�V�����J�E���^�[
	m_nMaxTexPattern = 1;										//�e�N�X�`���̃p�^�[����
	m_nMaxTexColumn = 1;										//�e�N�X�`���̍s��
	m_nTexLine = 1;												//�e�N�X�`���̗�
	m_nFirstPattern = 0;										//�A�j���[�V�����̍ŏ��̃p�^�[��
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);				//�e�N�X�`���̈ړ���
	m_bFlipX = false;											//�e�N�X�`����X���W�����]���Ă��邩�ǂ���
	m_bFlipY = false;											//�e�N�X�`����Y���W�����]���Ă��邩�ǂ���
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);					//�J���[
	m_nAnimFrame = 0;											//�A�j���[�V�����p�^�[���̕ύX�t���[����
	m_pTexture = nullptr;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//���_�J���[
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = nullptr;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		// �@���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[nCnt].col = m_col;
	}

	SetTexture(TEXTURE_NULL);						//�e�N�X�`���̐ݒ�
	SetTextureParameter(1, 1, 1, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ�

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CObject_3D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�e�N�X�`���ւ̃|�C���^��null�ɂ���
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CObject_3D::Update()
{
	if (m_textureTranslation != Vec2Null)
	{
		VERTEX_3D* pVtx = nullptr;					//���_���ւ̃|�C���^
		VERTEX_3D  Vtx = {};

		//���_�o�b�t�@�̃��b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			Vtx = pVtx[nCnt];
			Vtx.tex += m_textureTranslation;
			pVtx[nCnt] = Vtx;
		}

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CObject_3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();							//�f�o�C�X�̎擾����
	D3DXMATRIX	mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X

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
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�l�p�`��`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
//�ʒu�̐ݒ菈��
//=============================================================================
void CObject_3D::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�|���S���̕��ƍ����̐ݒ菈��
void CObject_3D::SetSize(const D3DXVECTOR2 dim)
{
	m_size = dim;
	m_fAngle = atan2f(m_size.y, m_size.x);

	VERTEX_3D* pVtx = nullptr;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-dim.x, dim.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(dim.x, dim.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-dim.x, -dim.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(dim.x, -dim.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//�|���S���̕��ƍ����̐ݒ菈��
void CObject_3D::SetSize(const float x, const float y)
{
	m_size.x = x;
	m_size.y = y;
	m_fAngle = atan2f(m_size.y, m_size.x);

	VERTEX_3D* pVtx = nullptr;					//���_���ւ̃|�C���^

												//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-x, y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(x, y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-x, -y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(x, -y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//���x�̎擾����
const D3DXVECTOR3 CObject_3D::GetMove(void)
{
	return m_move;
}

//���x�̐ݒ菈��
void CObject_3D::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//�����̎擾����
const D3DXVECTOR3 CObject_3D::GetAcceleration(void)
{
	return m_acc;
}

//�����̐ݒ菈��
void CObject_3D::SetAcceleration(const D3DXVECTOR3 acc)
{
	m_acc = acc;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CObject_3D::GetSize(void)
{
	return m_size;
}

//��]�̐ݒ菈��
void CObject_3D::SetRotation(const D3DXVECTOR3 frameRot)
{
	m_fFrameRot = frameRot;
}

//��]���x�̉��Z����
void CObject_3D::AddAngularSpeed(const D3DXVECTOR3 speed)
{
	m_fFrameRot += speed;
}

//��]���x�̎擾����
const D3DXVECTOR3 CObject_3D::GetAngularSpeed(void)
{
	return m_fFrameRot;
}

//��]�p�x�̏����l�̎擾����
void CObject_3D::SetStartingRot(const D3DXVECTOR3 fStartRot)
{
	m_rot = fStartRot;
}

//��]�p�x�̎擾���� 
const D3DXVECTOR3 CObject_3D::GetRot(void)
{
	return m_rot;
}

//�I�u�W�F�N�g�̈ʒu�擾����
const D3DXVECTOR3 CObject_3D::GetPos(void)
{
	return m_pos;
}

//�e�N�X�`���A�j���[�V�����p�̃p�����[�^�ݒ菈��
void CObject_3D::SetTextureParameter(const int MaxPattern, const int LinePattern, const int ColumnPattern, const int nAnimFrame)
{
	m_nMaxTexColumn = ColumnPattern;				//�s���̐ݒ�
	m_nTexLine = LinePattern;						//�񐔂̐ݒ�
	m_nMaxTexPattern = MaxPattern;					//�A�j���[�V�����p�^�[���̍ő吔�̐ݒ�
	m_nAnimFrame = nAnimFrame;						//�A�j���[�V�����t���[�����̐ݒ�

	VERTEX_3D* pVtx = nullptr;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	UpdateTexture();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//���݂̃A�j���[�V�����p�^�[���̎擾����
const int CObject_3D::GetPresentAnimPattern(void)
{
	return m_nAnimPattern;				//�A�j���[�V�����p�^�[����Ԃ�
}

void CObject_3D::SetAnimPattern(const int PatternNum)
{
	m_nAnimPattern = PatternNum;
}

bool CObject_3D::GetFlipX(void)
{
	return m_bFlipX;
}

void CObject_3D::FlipX(void)
{
	m_bFlipX = !m_bFlipX;

	VERTEX_3D* pVtx = nullptr;
	VERTEX_3D Vtx;

	ZeroMemory(&Vtx, sizeof(VERTEX_2D));

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	Vtx.tex = pVtx[0].tex;
	pVtx[0].tex = pVtx[1].tex;
	pVtx[1].tex = Vtx.tex;
	Vtx.tex = pVtx[2].tex;
	pVtx[2].tex = pVtx[3].tex;
	pVtx[3].tex = Vtx.tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject_3D::FlipY(void)
{
	m_bFlipY = !m_bFlipY;

	VERTEX_3D* pVtx = nullptr;
	VERTEX_3D Vtx;

	ZeroMemory(&Vtx, sizeof(VERTEX_2D));

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	Vtx.tex = pVtx[0].tex;
	pVtx[0].tex = pVtx[2].tex;
	pVtx[2].tex = Vtx.tex;
	Vtx.tex = pVtx[1].tex;
	pVtx[1].tex = pVtx[3].tex;
	pVtx[3].tex = Vtx.tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//�J�[���[�̎擾����
const D3DXCOLOR CObject_3D::GetColor(void)
{
	return m_col;
}

//�J�[���[�̐ݒ菈��
void CObject_3D::SetColor(const D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//���_�o�b�t�@�̎擾����
	VERTEX_3D* pVtx = nullptr;								//���_���ւ̃|�C���^

	m_col = col;											//�J�[���[�̐ݒ�

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = col;
	}

	//���_�o�b�t�@�̃��b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//���_�P�̃J�[���[�ݒ菈��
void CObject_3D::SetVtxColor(const int nVtxIdx, const D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//���_�o�b�t�@�̎擾����
	VERTEX_3D* pVtx = nullptr;								//���_���ւ̃|�C���^

	m_VtxCol[nVtxIdx] = col;

	//���_�o�b�t�@�̃��b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[nVtxIdx].col = m_VtxCol[nVtxIdx];

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//�e�N�X�`���̈ړ��ʂ̐ݒ菈��
void CObject_3D::MoveTexCoordinates(const D3DXVECTOR2 move)
{
	m_textureTranslation = move;
}

//�e�N�X�`���̎�ނ̐ݒ菈��
void CObject_3D::SetTexture(TextType textType)
{
	LPDIRECT3DTEXTURE9 text = CObject_2D::GetTexturePointer(textType);
	m_pTexture = text;														//�e�N�X�`���̎�ނ̐ݒ�
}

//�A�j���[�V�����̍ŏ��̃p�^�[���̐ݒ菈��
void CObject_3D::SetAnimationBase(const int FirstPattern)
{
	m_nFirstPattern = FirstPattern;
}

//���_�o�b�t�@�̎擾����
LPDIRECT3DVERTEXBUFFER9 CObject_3D::GetVtxbuff(void)
{
	return m_pVtxBuff;
}

//��������
CObject_3D* CObject_3D::Create(void)
{
	CObject_3D* pObj3D = nullptr;

	pObj3D = new CObject_3D;

	if (FAILED(pObj3D->Init()))
	{
		if (pObj3D != nullptr)
		{
			delete pObj3D;
			pObj3D = nullptr;
		}

		return nullptr;
	}

	return pObj3D;
}


void CObject_3D::UpdateTexture(void)
{
	VERTEX_3D* pVtx = nullptr;					//���_���ւ̃|�C���^

												//���_�o�b�t�@�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fX = 1.0f / m_nTexLine;
	float fY = 1.0f / m_nMaxTexColumn;

	if (!m_bFlipX && !m_bFlipY)
	{
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	else if (m_bFlipX && !m_bFlipY)
	{
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	else if (!m_bFlipX && m_bFlipY)
	{
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	else
	{
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}