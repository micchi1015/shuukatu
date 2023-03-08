//=============================================================================
//
// meshfield.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "meshfield.h"
#include "application.h"
#include "rendering.h"
#include "object2D.h"

std::vector <CMeshfield*> CMeshfield::m_vMeshfield;

//�R���X�g���N�^
CMeshfield::CMeshfield()
{
	//�����o�[�ϐ����N���A����
	m_pVtxBuff = nullptr;								//���_�o�b�t�@
	m_pIdxBuff = nullptr;								//�C���f�b�N�X�o�b�t�@
	m_pTexture = nullptr;								//�e�N�X�`���ւ̃|�C���^
	m_pos = Vec3Null;									//�ʒu
	m_rot = Vec3Null;									//����
	m_size = Vec2Null;									//�T�C�Y
	m_LateralCoords = Vec2Null;							//��
	D3DXMatrixIdentity(&m_mtxWorld);					//���[���h�}�g���b�N�X
	m_nVertexNumber = 0;								//���_��
	m_nIntexNumber = 0;									//�C���f�b�N�X��
	m_nPolygonNumber = 0;								//�|���S����
	m_nLineVertex = 0;									//��s�̒��_��
	m_nColumnVertex = 0;								//���̒��_��
	m_fFriction = 0.0f;									//���C�W��
	m_fAnimAngle = 0.0f;								//�A�j���[�V�����p�̊p�x
	m_fAnimSpeed = 0.0f;								//�A�j���[�V�����X�s�[�h
	m_fAmplitude = 0.0f;								//�A�j���[�V�����̐U��
	m_nPriority = 0;									//�v���C�I���e�B
	m_bTextureAnim = false;								//�e�N�X�`���A�j���[�V�����̃t���O
	m_bAnim = false;									//�A�j���[�V�����̃t���O
	m_animSpeed = Vec2Null;								//�A�j���[�V�����X�s�[�h
														
	m_vMeshfield.push_back(this);						//���b�V���t�B�[���h�̃A�h���X�������Ă���x�N�g���ɂ��̃|�C���^��ۑ�����
}

CMeshfield::CMeshfield(const int nPriority) : CObject::CObject(nPriority)
{
	//�����o�[�ϐ����N���A����
	m_pVtxBuff = nullptr;								//���_�o�b�t�@
	m_pIdxBuff = nullptr;								//�C���f�b�N�X�o�b�t�@
	m_pTexture = nullptr;								//�e�N�X�`���ւ̃|�C���^
	m_pos = Vec3Null;									//�ʒu
	m_rot = Vec3Null;									//����
	m_size = Vec2Null;									//�T�C�Y
	m_LateralCoords = Vec2Null;							//��
	D3DXMatrixIdentity(&m_mtxWorld);					//���[���h�}�g���b�N�X
	m_nVertexNumber = 0;								//���_��
	m_nIntexNumber = 0;									//�C���f�b�N�X��
	m_nPolygonNumber = 0;								//�|���S����
	m_nLineVertex = 0;									//��s�̒��_��
	m_nColumnVertex = 0;								//���̒��_��
	m_fFriction = 0.0f;									//���C�W��
	m_fAnimAngle = 0.0f;								//�A�j���[�V�����p�̊p�x
	m_fAnimSpeed = 0.0f;								//�A�j���[�V�����X�s�[�h
	m_fAmplitude = 0.0f;								//�A�j���[�V�����̐U��
	m_nPriority = 0;									//�v���C�I���e�B
	m_bTextureAnim = false;								//�e�N�X�`���A�j���[�V�����̃t���O
	m_bAnim = false;									//�A�j���[�V�����̃t���O
	m_animSpeed = Vec2Null;								//�A�j���[�V�����X�s�[�h

	m_vMeshfield.push_back(this);						//���b�V���t�B�[���h�̃A�h���X�������Ă���x�N�g���ɂ��̃|�C���^��ۑ�����
}

//�f�X�g���N�^
CMeshfield::~CMeshfield()
{

}

//����������
HRESULT CMeshfield::Init(void)
{
	m_pVtxBuff = nullptr;								//���_�o�b�t�@
	m_pIdxBuff = nullptr;								//�C���f�b�N�X�o�b�t�@
	m_pTexture = nullptr;								//�e�N�X�`���ւ̃|�C���^
	m_pos = Vec3Null;									//�ʒu
	m_rot = Vec3Null;									//����
	m_size = Vec2Null;									//�T�C�Y
	m_LateralCoords = Vec2Null;							//��
	D3DXMatrixIdentity(&m_mtxWorld);					//���[���h�}�g���b�N�X
	m_nVertexNumber = 0;								//���_��
	m_nIntexNumber = 0;									//�C���f�b�N�X��
	m_nPolygonNumber = 0;								//�|���S����
	m_nLineVertex = 0;									//��s�̒��_��
	m_nColumnVertex = 0;								//���̒��_��
	m_fFriction = 0.1f;									//���C�W��
	m_fAnimAngle = 0.0f;								//�A�j���[�V�����p�̊p�x
	m_fAnimSpeed = D3DX_PI * 0.025f;					//�A�j���[�V�����X�s�[�h
	m_fAmplitude = 25.0f;								//�A�j���[�V�����̐U��
	m_nPriority = 0;									//�v���C�I���e�B
	m_animSpeed = Vec2Null;								//�A�j���[�V�����X�s�[�h
	m_bTextureAnim = false;								//�e�N�X�`���A�j���[�V�����̃t���O
	m_bAnim = false;									//�A�j���[�V�����̃t���O

	return S_OK;
}

//�I������
void CMeshfield::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	//�e�N�X�`���ւ̃|�C���^��null�ɂ���
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

	int a = m_vMeshfield.size();

	//���̃C���X�^���X�̃A�h���X������
	for (int nCnt = 0; nCnt < a; nCnt++)
	{
		if (m_vMeshfield.data()[nCnt] == this)
		{
			m_vMeshfield.erase(m_vMeshfield.begin() + nCnt);
			break;
		}
	}
}

//�X�V����
void CMeshfield::Update(void)
{
	//�e�N�X�`���A�j���[�V�����̃t���O��true��������A
	if (m_bTextureAnim)
	{
		//���_���ւ̃|�C���^
		VERTEX_3D*pVtx = nullptr;
		VERTEX_3D Vtx;
		ZeroMemory(&Vtx, sizeof(VERTEX_3D));

		//���_�o�b�t�@�����b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���̐ݒ�
		for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
		{
			Vtx.tex = pVtx[nCnt].tex;
			Vtx.tex += m_animSpeed;
			pVtx[nCnt].tex = Vtx.tex;
		}

		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();
	}
	if (m_bAnim)
	{//�A�j���[�V�����̃t���O��true��������(�g�݂����ȃA�j���[�V����)
		VERTEX_3D*pVtx = nullptr;
		VERTEX_3D Vtx;
		ZeroMemory(&Vtx, sizeof(VERTEX_3D));

		//���_�o�b�t�@�����b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���̐ݒ�
		for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
		{
			Vtx.pos = pVtx[nCnt].pos;													//���_�̈ʒu���擾
			Vtx.pos.y += m_fAmplitude * sinf(m_fAnimAngle * (nCnt / m_nLineVertex));	//Y���W���X�V����
			pVtx[nCnt].pos = Vtx.pos;													//�V�����ʒu�̐ݒ�
		}

		m_fAnimAngle += m_fAnimSpeed;													//�p�x�̍X�V

		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();

	}
}

//�`�揈��
void CMeshfield::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans;											//�v�Z�p�}�g���b�N�X

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

	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`�揈��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexNumber, 0, m_nPolygonNumber);

	pDevice->SetTexture(0, NULL);
}

//�ʒu�̐ݒ菈��
void CMeshfield::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�v���C�I���e�B�̐ݒ菈��
void CMeshfield::SetPriority(const int nPriority)
{
	m_nPriority = nPriority;

	//�͈͊O�̒l���Ȃ��悤�Ɋm�F����
	if (m_nPriority < 0)
	{
		m_nPriority = 0;
	}
	else if (m_nPriority >= MAX_FIELD_PRIORITY)
	{
		m_nPriority = MAX_FIELD_PRIORITY - 1;
	}
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CMeshfield::GetSize(void)
{
	return m_size;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CMeshfield::GetPos(void)
{
	return m_pos;
}

//���C�W���̎擾����
const float CMeshfield::GetFriction(void)
{
	return m_fFriction;
}

//�e�N�X�`���̐ݒ菈��
void CMeshfield::SetTexture(CObject::TextType texture)
{
	LPDIRECT3DTEXTURE9 text = CObject_2D::GetTexturePointer(texture);		//���[�h�����e�N�X�`���̃|�C���^���擾
	m_pTexture = text;														//�e�N�X�`����ݒ肷��
}

//�e�N�X�`���̑傫���̐ݒ菈��
void CMeshfield::SetTextureTiling(D3DXVECTOR2 TileSize)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (TileSize.x * (nCnt % m_nColumnVertex)), 0.0f + (TileSize.y * (nCnt / m_nColumnVertex)));
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//�e�N�X�`���̑傫���̐ݒ菈��
void CMeshfield::SetTextureTiling(float fTileSize)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (fTileSize * (nCnt % m_nColumnVertex)), 0.0f + (fTileSize * (nCnt / m_nColumnVertex)));
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//�e�N�X�`���A�j���[�V�����̐ݒ菈��
void CMeshfield::SetTextureAnim(const D3DXVECTOR2 animSpeed)
{
	m_bTextureAnim = true;
	m_animSpeed = animSpeed;
}

//�e�N�X�`���A�j���[�V�����̐ݒ菈��
void CMeshfield::SetTextureAnim(const float fX, const float fY)
{
	m_bTextureAnim = true;
	m_animSpeed = D3DXVECTOR2(fX, fY);
}

//�e�N�X�`���A�j���[�V�����̒�~����
void CMeshfield::StopTextureAnim(void)
{
	m_bTextureAnim = false;
	m_animSpeed = Vec2Null;
}

//�A�j���[�V�����̐ݒ菈��
void CMeshfield::SetAnimation(const bool bAnim)
{
	m_bAnim = bAnim;
}

//�A�j���[�V�����̐ݒ菈��
void CMeshfield::SetAnimation(const bool bAnim, const float fAngularSpeed, const float fAmplitude)
{
	m_bAnim = bAnim;
	m_fAmplitude = fAmplitude;
	m_fAnimSpeed = fAngularSpeed;
}

//���_�̍����̐ݒ菈��
void CMeshfield::ChangeHeight(const int nStartVtx, const int nEndVtx, const float fHeight)
{
	int nStart = nStartVtx, nEnd = nEndVtx;

	//���݂��Ă��钸�_�͈̔͊O�C���f�b�N�X���Ȃ��悤�Ɋm�F����
	if (nStart < 0)
	{
		nStart = 0;
	}
	if (nEnd > m_nVertexNumber)
	{
		nEnd = m_nVertexNumber;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = nullptr;
	VERTEX_3D Vtx = {};

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	for (int nCnt = nStart; nCnt < nEnd; nCnt++)
	{
		Vtx = pVtx[nCnt];

		//�e�N�X�`�����W�̐ݒ�
		Vtx.pos.y = fHeight;

		pVtx[nCnt] = Vtx;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CMeshfield* CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 unitSize, const int nColumn, const int nLine)
{
	CMeshfield* pField = new CMeshfield(3);				//���b�V���t�B�[���h�𐶐�����

	if (FAILED(pField->Init()))
	{//����������
		return nullptr;
	}

	pField->m_pos = pos;						//�ʒu�̐ݒ�
	pField->m_rot = rot;						//�����̐ݒ�
	pField->m_size = unitSize;					//�T�C�Y�̐ݒ�
	pField->m_nColumnVertex = nLine;			//1�̗�̒��_�̐ݒ�
	pField->m_nLineVertex = nColumn;			//1�̍s�̒��_�̐ݒ�
	pField->SetVertex();						//���_�̐ݒ菈��

	return pField;								//���������C���X�^���X��Ԃ�
}

//��������
CMeshfield* CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 unitSize, const int nColumn, const int nLine, const int nPriority)
{
	CMeshfield* pField = new CMeshfield(nPriority);			//���b�V���t�B�[���h�𐶐�����

	if (FAILED(pField->Init()))
	{//����������
		return nullptr;
	}

	pField->m_pos = pos;						//�ʒu�̐ݒ�
	pField->m_rot = rot;						//�����̐ݒ�
	pField->m_size = unitSize;					//�T�C�Y�̐ݒ�
	pField->m_nColumnVertex = nLine;			//1�̗�̒��_�̐ݒ�
	pField->m_nLineVertex = nColumn;			//1�̍s�̒��_�̐ݒ�
	pField->SetVertex();						//���_�̐ݒ菈��

	return pField;								//���������C���X�^���X��Ԃ�
}

//��������
CMeshfield* CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 unitSize, const int nColumn, const int nLine, const float fFriction)
{
	CMeshfield* pField = new CMeshfield(3);		//���b�V���t�B�[���h�𐶐�����

	if (FAILED(pField->Init()))
	{//����������
		return nullptr;
	}

	pField->m_pos = pos;						//�ʒu�̐ݒ�
	pField->m_rot = rot;						//�����̐ݒ�
	pField->m_size = unitSize;					//�T�C�Y�̐ݒ�
	pField->m_nColumnVertex = nLine;			//1�̗�̒��_�̐ݒ�
	pField->m_nLineVertex = nColumn;			//1�̍s�̒��_�̐ݒ�
	pField->SetVertex();						//���_�̐ݒ菈��
	pField->m_fFriction = fFriction;			//���C�W���̐ݒ�


	return pField;								//���������C���X�^���X��Ԃ�
}

//��������
CMeshfield* CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 unitSize, const int nColumn, const int nLine, const int nPriority, const float fFriction)
{
	CMeshfield* pField = new CMeshfield(nPriority);			//���b�V���t�B�[���h�𐶐�����

	if (FAILED(pField->Init()))
	{//����������
		return nullptr;
	}

	pField->m_pos = pos;						//�ʒu�̐ݒ�
	pField->m_rot = rot;						//�����̐ݒ�
	pField->m_size = unitSize;					//�T�C�Y�̐ݒ�
	pField->m_nColumnVertex = nLine;			//1�̗�̒��_�̐ݒ�
	pField->m_nLineVertex = nColumn;			//1�̍s�̒��_�̐ݒ�
	pField->SetVertex();						//���_�̐ݒ菈��
	pField->m_fFriction = fFriction;			//���C�W���̐ݒ�

	return pField;								//���������C���X�^���X��Ԃ�
}

//���b�V���t�B�[���h�Ƃ̓����蔻��
bool CMeshfield::FieldInteraction(CObject* pObj)
{
	int nFieldNum = m_vMeshfield.size();		//���b�V���t�B�[���h�̐����擾����

	D3DXVECTOR3 pos = pObj->GetPos();			//�I�u�W�F�N�g�̈ʒu�̎擾

	for (int nCntField = 0; nCntField < nFieldNum; nCntField++)
	{//�S���̃��b�V���t�B�[���h���m�F����
		CMeshfield* pField = m_vMeshfield.data()[nCntField];		//���݂̃��b�V���t�B�[���h��ݒ肷��

		VERTEX_3D* pVtx = nullptr;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N
		pField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		WORD*pIdx = nullptr;		//�C���f�b�N�X���ւ̃|�C���^

		//�C���f�b�N�X�o�b�t�@�����b�N
		pField->m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCnt = 0; nCnt < pField->m_nPolygonNumber; nCnt++)
		{//���b�V���t�B�[���h�̑S���̃|���S�����m�F����

			//�v�Z�p�̃x�N�g��
			D3DXVECTOR3 Vtx[3] = {};
			D3DXVECTOR3 Edge[3] = {};
			D3DXVECTOR3 Distance[3] = {};
			D3DXVECTOR3 Cross[3] = {};

			//�|���S���̒��_���W�̐ݒ�
			Vtx[0] = pVtx[pIdx[nCnt]].pos;			
			Vtx[1] = pVtx[pIdx[nCnt + 1]].pos;
			Vtx[2] = pVtx[pIdx[nCnt + 2]].pos;

			//�v�Z�p�̃}�g���b�N�X
			D3DXMATRIX mtxOut, mtxTrans, mtxRot;

			//�����h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxOut);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pField->m_rot.y, pField->m_rot.x, pField->m_rot.z);
			D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pField->m_pos.x, pField->m_pos.y, pField->m_pos.z);
			D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

			//���_���W���O���[�o�����W�ɕϊ�����
			D3DXVec3TransformCoord(&Vtx[0], &Vtx[0], &mtxOut);
			D3DXVec3TransformCoord(&Vtx[1], &Vtx[1], &mtxOut);
			D3DXVec3TransformCoord(&Vtx[2], &Vtx[2], &mtxOut);

			//�e���_���玟�̒��_�܂ł̃x�N�g��
			Edge[0] = Vtx[1] - Vtx[0];
			Edge[1] = Vtx[2] - Vtx[1];
			Edge[2] = Vtx[0] - Vtx[2];

			//�e���_����I�u�W�F�N�g�܂ł̃x�N�g��
			Distance[0] = pos - Vtx[0];
			Distance[1] = pos - Vtx[1];
			Distance[2] = pos - Vtx[2];

			//��ݒ肵���x�N�g���̊O�ς��v�Z����
			D3DXVec3Cross(&Cross[0], &Edge[0], &Distance[0]);
			D3DXVec3Cross(&Cross[1], &Edge[1], &Distance[1]);
			D3DXVec3Cross(&Cross[2], &Edge[2], &Distance[2]);

			if (Cross[0].y * Cross[1].y >= 0 && Cross[0].y * Cross[2].y >= 0 && Cross[1].y * Cross[2].y >= 0)
			{//�����������Ȃ�A�I�u�W�F�N�g�̓|���S���Əd�Ȃ��Ă���

				//�|���S���̖ʂ̖@�����v�Z����
				D3DXVECTOR3 Normal = Vec3Null;		

				//�|���S���̌����ɂ���ĊO�ς̕������Ⴄ�̂ŁA�����܂�
				if (nCnt % 2 == 0)
				{
					D3DXVec3Cross(&Normal, &Edge[0], &Edge[1]);
				}
				else
				{
					D3DXVec3Cross(&Normal, &Edge[1], &Edge[0]);
				}

				D3DXVec3Normalize(&Normal, &Normal);				//�@���𐳋K������

				float Y = (Vtx[0].y) - ((((pos.x - (Vtx[0].x)) * Normal.x) + ((pos.z - Vtx[0].z) * Normal.z)) / Normal.y);			//�I�u�W�F�N�g�����鏊�̃|���S���̍���

				if (pos.y < Y && pos.y + 50.0f >= Y)
				{//�I�u�W�F�N�g�̓|���S���ɂ߂荞�񂾏ꍇ�A�����o��
					pos.y = Y;
					pObj->SetPos(pos);				//�ʒu�̐ݒ�
					return true;					//true��Ԃ�
					break;
				}
			}
			
		}

		//�C���f�b�N�X�o�b�t�@���A�����b�N
		pField->m_pIdxBuff->Unlock();

		//���_�o�b�t�@�̃A�����b�N
		pField->m_pVtxBuff->Unlock();
	}

	return false;
}

//�����蔻��̏���
CMeshfield* CMeshfield::FieldInteraction(CObject* pObj, float* fHeight)
{
	int nFieldNum = m_vMeshfield.size();				//���b�V���t�B�[���h�̐����擾����

	D3DXVECTOR3 pos = pObj->GetPos();					//�I�u�W�F�N�g�̈ʒu�̎擾

	for (int nCntPriority = 0; nCntPriority < MAX_FIELD_PRIORITY; nCntPriority++)
	{//�v���C�I���e�B�̏��ԂŊm�F����
		for (int nCntField = 0; nCntField < nFieldNum; nCntField++)
		{//�S���̃��b�V���t�B�[���h���m�F����
			CMeshfield* pField = m_vMeshfield.data()[nCntField];		//���݂̃��b�V���t�B�[���h��ݒ肷��

			if (pField->m_nPriority == nCntPriority)
			{
				VERTEX_3D* pVtx = nullptr;				//���_���ւ̃|�C���^

				//���_�o�b�t�@�����b�N
				pField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				WORD*pIdx = nullptr;		//�C���f�b�N�X���ւ̃|�C���^

				//�C���f�b�N�X�o�b�t�@�����b�N
				pField->m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

				for (int nCnt = 0; nCnt < pField->m_nPolygonNumber; nCnt++)
				{//���b�V���t�B�[���h�̑S���̃|���S�����m�F����

					//�v�Z�p�̃x�N�g��
					D3DXVECTOR3 Vtx[3] = {};
					D3DXVECTOR3 Edge[3] = {};
					D3DXVECTOR3 Distance[3] = {};
					D3DXVECTOR3 Cross[3] = {};

					//�|���S���̒��_���W�̐ݒ�
					Vtx[0] = pVtx[pIdx[nCnt]].pos;
					Vtx[1] = pVtx[pIdx[nCnt + 1]].pos;
					Vtx[2] = pVtx[pIdx[nCnt + 2]].pos;

					//�v�Z�p�̃}�g���b�N�X
					D3DXMATRIX mtxOut, mtxTrans, mtxRot;

					//�����h�}�g���b�N�X�̏�����
					D3DXMatrixIdentity(&mtxOut);

					//�����𔽉f
					D3DXMatrixRotationYawPitchRoll(&mtxRot, pField->m_rot.y, pField->m_rot.x, pField->m_rot.z);
					D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);

					//�ʒu�𔽉f
					D3DXMatrixTranslation(&mtxTrans, pField->m_pos.x, pField->m_pos.y, pField->m_pos.z);
					D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

					//���_���W���O���[�o�����W�ɕϊ�����
					D3DXVec3TransformCoord(&Vtx[0], &Vtx[0], &mtxOut);
					D3DXVec3TransformCoord(&Vtx[1], &Vtx[1], &mtxOut);
					D3DXVec3TransformCoord(&Vtx[2], &Vtx[2], &mtxOut);

					//�e���_���玟�̒��_�܂ł̃x�N�g��
					Edge[0] = Vtx[1] - Vtx[0];
					Edge[1] = Vtx[2] - Vtx[1];
					Edge[2] = Vtx[0] - Vtx[2];

					//�e���_����I�u�W�F�N�g�܂ł̃x�N�g��
					Distance[0] = pos - Vtx[0];
					Distance[1] = pos - Vtx[1];
					Distance[2] = pos - Vtx[2];

					//��ݒ肵���x�N�g���̊O�ς��v�Z����
					D3DXVec3Cross(&Cross[0], &Edge[0], &Distance[0]);
					D3DXVec3Cross(&Cross[1], &Edge[1], &Distance[1]);
					D3DXVec3Cross(&Cross[2], &Edge[2], &Distance[2]);

					if (Cross[0].y * Cross[1].y >= 0 && Cross[0].y * Cross[2].y >= 0 && Cross[1].y * Cross[2].y >= 0)
					{//�����������Ȃ�A�I�u�W�F�N�g�̓|���S���Əd�Ȃ��Ă���

						 //�|���S���̖ʂ̖@�����v�Z����
						D3DXVECTOR3 Normal = Vec3Null;

						//�|���S���̌����ɂ���ĊO�ς̕������Ⴄ�̂ŁA�����܂�
						if (nCnt % 2 == 0)
						{
							D3DXVec3Cross(&Normal, &Edge[0], &Edge[1]);
						}
						else
						{
							D3DXVec3Cross(&Normal, &Edge[1], &Edge[0]);
						}

						D3DXVec3Normalize(&Normal, &Normal);			//�@���𐳋K������

						float Y = (Vtx[0].y) - ((((pos.x - (Vtx[0].x)) * Normal.x) + ((pos.z - Vtx[0].z) * Normal.z)) / Normal.y);			//�I�u�W�F�N�g�����鏊�̃|���S���̍���

						if (pos.y < Y && pos.y + 50.0f >= Y)
						{//�I�u�W�F�N�g�̓|���S���ɂ߂荞�񂾏ꍇ�A�����o��
							pos.y = Y;
							pObj->SetPos(pos);			//�ʒu�̐ݒ�
							*fHeight = Y;				//������ݒ肷��
							return pField;
							break;
						}
					}

				}

				//�C���f�b�N�X�o�b�t�@���A�����b�N
				pField->m_pIdxBuff->Unlock();

				//���_�o�b�t�@�̃A�����b�N
				pField->m_pVtxBuff->Unlock();
			}
		}
	}

	return nullptr;
}


//���_�C���f�b�N�X�̐ݒ菈��
void CMeshfield::SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	//���_���̌v�Z
	m_nVertexNumber = m_nLineVertex * m_nColumnVertex;
	//�|���S�����̌v�Z
	m_nPolygonNumber = (((((m_nColumnVertex - 1) * 2) + 2) * 2) + ((((m_nColumnVertex - 1) * 2) + 4) * ((m_nLineVertex - 1) - 2)));
	//�C���f�b�N�X���̌v�Z
	m_nIntexNumber = (((((m_nColumnVertex - 1) * 2) + 2) * 2) + ((((m_nColumnVertex - 1) * 2) + 4) * ((m_nLineVertex - 1) - 2))) + 2;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertexNumber,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIntexNumber,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_LateralCoords.x = m_pos.x;
	m_LateralCoords.y = m_pos.x + (m_size.x * (m_nColumnVertex - 1));

	//���_���̐ݒ�
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		//���_�̈ʒu�̏�����
		pVtx[nCnt].pos = D3DXVECTOR3((float)(m_size.x * (nCnt % m_nColumnVertex)), /*(float)CObject::random(-500, 500) * 0.1f*/0.0f, (float)(-m_size.y * (nCnt / m_nColumnVertex)));
		//���_�̖@���̏�����
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//���_�J���[�̏�����
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (1.0f * (nCnt % m_nColumnVertex)), 0.0f + (1.0f * (nCnt / m_nColumnVertex)));

		if (nCnt < 60)
		{
			pVtx[nCnt].pos.y += 50.0f;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	WORD*pIdx = nullptr;		//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nStart = 0;		//�v�Z�p�̃��[�J���ϐ�

						//�C���f�b�N�X���̐ݒ�
	for (int nCnt = 0; nCnt < m_nLineVertex - 1; nCnt++)
	{
		for (int nCntColumn = 0; nCntColumn < m_nColumnVertex * 2; nCntColumn += 2)
		{
			//��s�̃C���f�b�N�X�̐ݒ�
			pIdx[(nCnt * m_nColumnVertex) + nCntColumn + nStart] = (WORD)(m_nColumnVertex + (m_nColumnVertex * (nCnt)) + (nCntColumn / 2));
			int a = m_nColumnVertex + (m_nColumnVertex * (nCnt)) + (nCntColumn / 2);
			pIdx[(nCnt * m_nColumnVertex) + nCntColumn + nStart + 1] = (WORD)((m_nColumnVertex * (nCnt)) + (nCntColumn / 2));
			a = (m_nColumnVertex * (nCnt)) + (nCntColumn / 2);
			a++;

			if (nCntColumn + 2 >= 2 * m_nColumnVertex && nCnt != m_nLineVertex - 2)
			{
				//�k�ރ|���S���p�̃C���f�b�N�X�̐ݒ�
				pIdx[(nCnt * m_nColumnVertex) + nCntColumn + nStart + 2] = (WORD)((m_nColumnVertex * (nCnt)) + (nCntColumn / 2));
				pIdx[(nCnt * m_nColumnVertex) + nCntColumn + nStart + 3] = (WORD)(m_nColumnVertex + (m_nColumnVertex * (nCnt + 1)));
				nStart += 2 + m_nColumnVertex;
			}

		}

	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	pVtx = nullptr;

	pIdx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�̖@���̌v�Z
	for (int nCnt = 0; nCnt < m_nIntexNumber - 2; nCnt++)
	{
		if (pIdx[nCnt] != pIdx[nCnt + 1] && pIdx[nCnt] != pIdx[nCnt + 2] && pIdx[nCnt + 1] != pIdx[nCnt + 2])
		{
			D3DXVECTOR3 V1, V2, Norm, N;

			V1 = pVtx[pIdx[nCnt + 1]].pos - pVtx[pIdx[nCnt]].pos;
			V2 = pVtx[pIdx[nCnt + 2]].pos - pVtx[pIdx[nCnt + 1]].pos;


			if (nCnt % 2 == 0)
			{
				D3DXVec3Cross(&Norm, &V1, &V2);
			}
			else
			{
				D3DXVec3Cross(&Norm, &V2, &V1);
			}

			D3DXVec3Normalize(&Norm, &Norm);

			N = pVtx[pIdx[nCnt]].nor + Norm;
			//D3DXVec3Normalize(&N, &N);
			pVtx[pIdx[nCnt]].nor = N;
			N = pVtx[pIdx[nCnt + 1]].nor + Norm;
			//D3DXVec3Normalize(&N, &N);
			pVtx[pIdx[nCnt + 1]].nor = N;
			N = pVtx[pIdx[nCnt + 2]].nor + Norm;
			//D3DXVec3Normalize(&N, &N);
			pVtx[pIdx[nCnt + 2]].nor = N;
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�@���̐ݒ�
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		D3DXVECTOR3 N = pVtx[nCnt].nor;
		D3DXVec3Normalize(&N, &N);
		pVtx[nCnt].nor = N;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}