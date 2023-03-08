//=============================================================================
//
// modelPart.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "modelPart.h"
#include "application.h"
#include "rendering.h"
#include "directionalLight.h"

//�R���X�g���N�^
CModelPart::CModelPart()
{
	//�����o�[�ϐ����N���A����
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_shadowPosY = 0.0f;							//�e�̍���
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_BODY;					//���f���̎��
	m_pParent = nullptr;							//�e�ւ̃|�C���^
	m_vModelTexture.clear();						//�e�N�X�`���ւ̃|�C���^
	m_vCol.clear();									//�}�e���A���̐F
}													

//�f�X�g���N�^
CModelPart::~CModelPart()
{

}

//����������
HRESULT CModelPart::Init(void)
{
	//����������
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_shadowPosY = 0.0f;							//�e�̍���
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_BODY;					//���f���̎��
	m_pParent = nullptr;							//�e�ւ̃|�C���^
	m_vModelTexture.clear();						//�e�N�X�`���ւ̃|�C���^
	m_vCol.clear();									//�}�e���A���̐F

	return S_OK;
}

//�I������
void CModelPart::Uninit(void)
{
	m_vCol.clear();					//�}�e���A���̐F���N���A����
}

//�X�V����
void CModelPart::Update(void)
{

}

//�`�揈��
void CModelPart::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow, mtxParent;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;									//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;										//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR4 vecLight;									//���C�g�̌���
	D3DXVECTOR3 pos, Normal;								//���e�p�̈ʒu�Ɩ@��
	D3DXPLANE planeField;									//��

	if (m_pParent != nullptr)
	{//�e������ꍇ�A�e�̃}�g���b�N�X���擾����
		mtxParent = m_pParent->GetMatrix();
	}

	//�X�e���V���o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//�X�e���V���e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

	//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	//���C�g�̌�����ݒ肷��
	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);
	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);

	pos = D3DXVECTOR3(0.0f, m_shadowPosY, 0.0f);				//�ʂ̍���
	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//�ʂ̖@��

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxShadow);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//�e�̕`��p�̃}�g���b�N�X�����
	D3DXPlaneFromPointNormal(&planeField, &pos, &Normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		D3DXCOLOR col = pMat[nCntMat].MatD3D.Diffuse;					//�}�e���A���̐F��ۑ�����

		//�}�e���A���̐F��^�����ɂ���
		pMat[nCntMat].MatD3D.Diffuse.r = 0.0f;
		pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
		pMat[nCntMat].MatD3D.Diffuse.b = 0.0f;
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		//�}�e���A���̐F�����ɖ߂�
		pMat[nCntMat].MatD3D.Diffuse.r = col.r;
		pMat[nCntMat].MatD3D.Diffuse.g = col.g;
		pMat[nCntMat].MatD3D.Diffuse.b = col.b;
		pMat[nCntMat].MatD3D.Diffuse.a = col.a;
	}

	pMat = nullptr;

	//�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//�X�e���V���e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);


	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//�}�e���A���̐F���ݒ肳��Ă�����A���̃}�e���A���̐F��ς�����A�`�悵�āA���ɖ߂�
		D3DXCOLOR c = {};
		bool bCol = false;

		for (int i = 0; i < (int)m_vCol.size(); i++)
		{
			if (m_vCol.data()[i].nMatNumber == nCntMat)
			{
				bCol = true;
				c = pMat[nCntMat].MatD3D.Diffuse;
				pMat[nCntMat].MatD3D.Diffuse = m_vCol.data()[i].col;
				break;
			}
		}

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		if (bCol)
		{
			pMat[nCntMat].MatD3D.Diffuse = c;
		}
	}

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//�X�e���V���o�b�t�@�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//�`�揈��
void CModelPart::Draw(D3DXMATRIX mtxParent)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow;					//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;									//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;										//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR4 vecLight;									//���C�g�̌���
	D3DXVECTOR3 pos, Normal;								//���e�p�̈ʒu�Ɩ@��
	D3DXPLANE planeField;									//��

															//���C�g�̌�����ݒ肷��
	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);
	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);

	pos = D3DXVECTOR3(0.0f, m_shadowPosY, 0.0f);							//�ʂ̍���
	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);									//�ʂ̖@��

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxShadow);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//�e�̕`��p�̃}�g���b�N�X�����
	D3DXPlaneFromPointNormal(&planeField, &pos, &Normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//�X�e���V���o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//�X�e���V���e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

	//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		D3DXCOLOR col = pMat[nCntMat].MatD3D.Diffuse;					//�}�e���A���̐F��ۑ�����

		//�}�e���A���̐F��^�����ɂ���
		pMat[nCntMat].MatD3D.Diffuse.r = 0.0f;
		pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
		pMat[nCntMat].MatD3D.Diffuse.b = 0.0f;
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		//�}�e���A���̐F�����ɖ߂�
		pMat[nCntMat].MatD3D.Diffuse.r = col.r;
		pMat[nCntMat].MatD3D.Diffuse.g = col.g;
		pMat[nCntMat].MatD3D.Diffuse.b = col.b;
		pMat[nCntMat].MatD3D.Diffuse.a = col.a;
	}

	pMat = nullptr;

	//�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//�X�e���V���e�X�g�̔�r���@�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);


	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//�}�e���A���̐F���ݒ肳��Ă�����A���̃}�e���A���̐F��ς�����A�`�悵�āA���ɖ߂�
		D3DXCOLOR c = {};
		bool bCol = false;

		for (int i = 0; i < (int)m_vCol.size(); i++)
		{
			if (m_vCol.data()[i].nMatNumber == nCntMat)
			{
				bCol = true;
				c = pMat[nCntMat].MatD3D.Diffuse;
				pMat[nCntMat].MatD3D.Diffuse = m_vCol.data()[i].col;
				break;
			}
		}

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_vModelTexture.data()[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		if (bCol)
		{
			pMat[nCntMat].MatD3D.Diffuse = c;
		}
	}

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	pDevice->SetTexture(0, nullptr);

	//�X�e���V���o�b�t�@�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//�e�̐ݒ菈��
void CModelPart::SetParent(CModelPart* pParent)
{
	m_pParent = pParent;
}

//�e�̎擾����
CModelPart* CModelPart::GetParent(void)
{
	return m_pParent;
}

//�ʒu�̐ݒ菈��
void CModelPart::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CModelPart::GetPos(void)
{
	return m_pos;
}

//�����̐ݒ菈��
void CModelPart::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//�����̎擾����
const D3DXVECTOR3 CModelPart::GetRot(void)
{
	return m_rot;
}

//�T�C�Y�̎擾����
const D3DXVECTOR3 CModelPart::GetSize(void)
{
	return Vec3Null;
}

//�}�g���b�N�X�̎擾����
D3DXMATRIX CModelPart::GetMatrix(void)
{
	return m_mtxWorld;
}

//�e�̍����̐ݒ菈��
void CModelPart::SetShadowHeight(const float fHeight)
{
	m_shadowPosY = fHeight;
}

//�J�[���[�̐ݒ菈��
void CModelPart::SetModelColor(const int nNumMat, const D3DXCOLOR col)
{
	//�V�����}�e���A�������ɓ��ꂽ���ǂ����m�F����A������������A�㏑������
	for (int nCnt = 0; nCnt < (int)m_vCol.size(); nCnt++)
	{
		if (m_vCol.data()[nCnt].nMatNumber == nNumMat)
		{
			CModel::ModelColor mCol = {};
			mCol.nMatNumber = nNumMat;
			mCol.col = col;
			m_vCol.data()[nCnt] = mCol;
			return;
		}
	}

	//�V�����}�e���A���̐F��ۑ�����
	CModel::ModelColor mCol = {};
	mCol.nMatNumber = nNumMat;
	mCol.col = col;

	m_vCol.push_back(mCol);
}

//���f���̐ݒ菈��
void CModelPart::SetModel(CModel::ModelType model)
{
	//�K�v�ȃ����o�[�ϐ����N���A����
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_nNumMat = 0;
	m_vModelTexture.clear();

	CModel::GetModel(model, &m_pMesh, &m_pBuffMat, &m_nNumMat);			//���f���̎擾����
	CModel::GetTextures(m_vModelTexture, model);						//�e�N�X�`���̎擾����
}



//=============================================================================
//								�ÓI�֐�
//=============================================================================




//��������
CModelPart* CModelPart::Create(CModel::ModelType type, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CModelPart* pModel = new CModelPart;					//�C���X�^���X�𐶐�����

	if (FAILED(pModel->Init()))
	{//����������
		return nullptr;
	}

	pModel->m_pos = pos;					//�ʒu�̐ݒ�
	pModel->m_rot = rot;					//�����̐ݒ�
	pModel->m_LastPos = pos;				//�O��̈ʒu�̐ݒ�
	pModel->m_type = type;					//��ނ̐ݒ�
	pModel->m_shadowPosY = pos.y;			//�e�̍����̐ݒ�

	CModel::GetModel(type, &pModel->m_pMesh, &pModel->m_pBuffMat, &pModel->m_nNumMat);			//���f���̐ݒ菈��
	CModel::GetTextures(pModel->m_vModelTexture, type);											//�e�N�X�`���̐ݒ菈��

	return pModel;							//���������C���X�^���X��Ԃ�
}