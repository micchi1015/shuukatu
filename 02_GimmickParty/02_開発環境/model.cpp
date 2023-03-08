//=============================================================================
//
// model.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"
#include "application.h"
#include "rendering.h"
#include "directionalLight.h"


//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================

LPD3DXMESH		CModel::m_pMeshAll[MODEL_MAX] = {};					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER	CModel::m_pBuffMatAll[MODEL_MAX] = {};				//�}�e���A�����ւ̃|�C���^
DWORD			CModel::m_nNumMatAll[MODEL_MAX] = {};				//�}�e���A�����̐�
std::vector <LPDIRECT3DTEXTURE9>     CModel::m_vModelTexture[CModel::MODEL_MAX];		//���f���̃e�N�X�`���ւ̃|�C���^�̃x�N�g��

//���f����X�t�@�C���̑��΃p�X
char*			CModel::m_pModelPass[MODEL_MAX] =
{
	{ "data\\MODELS\\Player02\\Player02_Body.x" },						//MODEL_BODY,				
	{ "data\\MODELS\\Player02\\Player02_Head.x" },						//MODEL_HEAD,
	{ "data\\MODELS\\Player02\\Player02_Arm_Left.x" },					//MODEL_LEFT_ARM,
	{ "data\\MODELS\\Player02\\Player02_Hand_Left.x" },					//MODEL_LEFT_HAND,
	{ "data\\MODELS\\Player02\\Player02_Arm_Right.x" },					//MODEL_RIGHT_ARM,
	{ "data\\MODELS\\Player02\\Player02_Hand_Right.x" },				//MODEL_RIGHT_HAND,
	{ "data\\MODELS\\Player02\\Player02_Leg_Left.x" },					//MODEL_LEFT_LEG,
	{ "data\\MODELS\\Player02\\Player02_Foot_Left.x" },					//MODEL_LEFT_FOOT,
	{ "data\\MODELS\\Player02\\Player02_Leg_Right.x" },					//MODEL_RIGHT_LEG,
	{ "data\\MODELS\\Player02\\Player02_Foot_Right.x" },				//MODEL_RIGHT_FOOT,
																		
	{ "data\\MODELS\\Player02\\PlayerParts\\SantaHead.x" },				//MODEL_HEAD_SANTA,
	{ "data\\MODELS\\Player02\\PlayerParts\\PumpHead.x" },				//MODEL_HEAD_PUMPKIN,
	{ "data\\MODELS\\Player02\\PlayerParts\\TopHatHead.x" },			//MODEL_HEAD_TOPHAT,
	{ "data\\MODELS\\Player02\\PlayerParts\\KatanaHead.x" },			//MODEL_HEAD_KATANA,
	{ "data\\MODELS\\Player02\\PlayerParts\\DragonHead.x" },			//MODEL_HEAD_DRAGON,
	{ "data\\MODELS\\Player02\\PlayerParts\\oqtoHead.x" },				//MODEL_HEAD_OCTOPUS,
	{ "data\\MODELS\\Player02\\PlayerParts\\snowman.x" },				//MODEL_HEAD_SNOWMAN,
	{ "data\\MODELS\\Player02\\PlayerParts\\ToyBoxHead.x" },			//MODEL_HEAD_TOYBOX,
	{ "data\\MODELS\\Player02\\PlayerParts\\SummerTimeHead.x" },		//MODEL_HEAD_SUMMER,
	{ "data\\MODELS\\Player02\\PlayerParts\\TreeHead.x" },				//MODEL_HEAD_TREE,
																		
	{ "data\\MODELS\\Coin\\Coin00.x" },									//MODEL_COIN_0,
	{ "data\\MODELS\\Coin\\Coin01.x" },									//MODEL_COIN_1,
	{ "data\\MODELS\\Coin\\Coin02.x" },									//MODEL_COIN_2,
	{ "data\\MODELS\\Coin\\Coin03.x" },									//MODEL_COIN_3,
																		
	{ "data\\MODELS\\Environment\\Mountains\\Fuji.x" },					//MODEL_MOUNT_FUJI,
	{ "data\\MODELS\\Environment\\Mountains\\FujiYuki.x" },				//MODEL_MOUNT_FUJI_YUKI,
	{ "data\\MODELS\\Environment\\Balloon\\Balloon.x" },				//MODEL_BALLOON,
	{ "data\\MODELS\\Environment\\tree\\tree1.x" },						//MODEL_TREE1,
	{ "data\\MODELS\\Environment\\tree\\tree2.x" },						//MODEL_TREE2,
	{ "data\\MODELS\\Environment\\windmill\\windmill.x" },				//MODEL_WINDMILL,
	{ "data\\MODELS\\Environment\\airship\\airship.x" },				//MODEL_AIRSHIP,
	{ "data\\MODELS\\Environment\\stone\\stone.x" },					//MODEL_STONE,
																		
	{ "data\\MODELS\\Stage_gimmick\\NeedleBall\\NeedleBall.x" },		//MODEL_SPIKE_BALL,
	{ "data\\MODELS\\Stage_gimmick\\LavaFloor\\Lava.x" },				//MODEL_LAVA_FLOOR,
	{ "data\\MODELS\\Stage_gimmick\\BoundPole\\BoundPole.x" },			//MODEL_BOUNCE_POLE,
																		
	{ "data\\MODELS\\traps\\jump\\jump.x" },							//MODEL_TRAMPOLINE,
	{ "data\\MODELS\\traps\\fallstone\\fallstone.x" },					//MODEL_FALLING_STONE,
	{ "data\\MODELS\\traps\\IcePillar\\IcePillar_TrapType.x" },			//MODEL_ICE_PILLAR,
																		
	{ "data\\MODELS\\sign\\fallstonesign.x" },							//MODEL_CAUTION_SIGNAL,
																		
	{ "data\\MODELS\\Goal\\Goal01.x" },									//MODEL_GOAL,
};

//�R���X�g���N�^
CModel::CModel()
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_frameRot = Vec3Null;							//1�t���[���̉�]�p�x
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_BODY;					//���f���̎��
	m_vCol.clear();									//�}�e���A���̐F
	m_bShadow = true;								//�e��`�悷�邩�ǂ���
	m_fShadowHeight = 0.0f;							//�e�̍���
}

CModel::CModel(const int nPriority) : CObject::CObject(nPriority)
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_frameRot = Vec3Null;							//1�t���[���̉�]�p�x
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_BODY;					//���f���̎��
	m_vCol.clear();									//�}�e���A���̐F
	m_bShadow = true;								//�e��`�悷�邩�ǂ���
	m_fShadowHeight = 0.0f;							//�e�̍���
}

//�f�X�g���N�^
CModel::~CModel()
{

}

//����������
HRESULT CModel::Init(void)
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_frameRot = Vec3Null;							//1�t���[���̉�]�p�x
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_vCol.clear();									//�}�e���A���̐F
	m_bShadow = true;								//�e��`�悷�邩�ǂ���
	m_fShadowHeight = -149.9f;						//�e�̍���

	return S_OK;
}

//�I������
void CModel::Uninit(void)
{
	m_vCol.clear();				//�}�e���A���̐F���N���A����
}

//�X�V����
void CModel::Update(void)
{
	m_LastPos = m_pos;			//�O��̈ʒu�̍X�V

	if (m_frameRot != nullptr)
	{//��]���x��0�ł͂Ȃ�������
		m_rot += m_frameRot;			//��]�p�x���X�V����
	}
}

//�`�揈��
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;							//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR4 vecLight;							//���C�g�̌���
	D3DXVECTOR3 pos, Normal;						//���e�p�̈ʒu�Ɩ@��
	D3DXPLANE planeField;							//��

		//���C�g�̌�����ݒ肷��
		D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
		D3DXVec3Normalize(&dir, &dir);
		vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);

		pos = D3DXVECTOR3(0.0f, m_fShadowHeight, 0.0f);				//�ʂ̍���
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

		if (m_bShadow)
		{//�e�̕`��̃t���O��true��������

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

			D3DXCOLOR col = pMat[nCntMat].MatD3D.Diffuse;			//�}�e���A���̐F��ۑ�����

			//�}�e���A���̐F��^�����ɂ���
			pMat[nCntMat].MatD3D.Diffuse.r = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.b = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);

			//�}�e���A���̐F�����ɖ߂�
			pMat[nCntMat].MatD3D.Diffuse.r = col.r;
			pMat[nCntMat].MatD3D.Diffuse.g = col.g;
			pMat[nCntMat].MatD3D.Diffuse.b = col.b;
			pMat[nCntMat].MatD3D.Diffuse.a = col.a;
		}


		//�X�e���V���o�b�t�@��L���ɂ���
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		//�X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		//�X�e���V���e�X�g�̔�r���@�̐ݒ�
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

		//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

		pMat = nullptr;

		//�ێ��������}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}


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

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//�X�e���V���o�b�t�@�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	pMat = nullptr;
	
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
		pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		if (bCol)
		{
			pMat[nCntMat].MatD3D.Diffuse = c;
		}
	}

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//�ʒu�̐ݒ菈��
void CModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//���f���̌����ݒ菈��
void CModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//���f���̌����̎擾����
const D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//�|���S���̃T�C�Y�̎擾����
const D3DXVECTOR2 CModel::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

//���f���̐ݒ菈��
void CModel::SetModel(const ModelType type)
{
	m_pMesh = m_pMeshAll[type];
	m_pBuffMat = m_pBuffMatAll[type];
	m_nNumMat = m_nNumMatAll[type];
	m_type = type;
}

//��]���x�̐ݒ菈��
void CModel::StartRotation(const D3DXVECTOR3 frameRot)
{
	m_frameRot = frameRot;
}

//��]���~�܂鏈��
void CModel::StopRotating(void)
{
	m_frameRot = Vec3Null;
}

//�J�[���[�̐ݒ菈��
void CModel::SetModelColor(const int nNumMat, const D3DXCOLOR col)
{
	ModelColor mCol = {};
	mCol.nMatNumber = nNumMat;
	mCol.col = col;

	m_vCol.push_back(mCol);
}

//�e���`�悳��Ă��邩�ǂ����̐ݒ菈��
void CModel::SetShadowDraw(const bool bDraw)
{
	m_bShadow = bDraw;
}

//�e�̍����̐ݒ菈��
void CModel::SetShadowHeight(const float fHeight)
{
	m_fShadowHeight = fHeight;
}



//=============================================================================
//								�ÓI�֐�
//=============================================================================




//���f�����̎擾����
void CModel::GetModel(ModelType type, LPD3DXMESH* pMesh, LPD3DXBUFFER* pBuffMat, DWORD* numMat)
{
	*pMesh = m_pMeshAll[type];				//���b�V���ւ̃|�C���^�̐ݒ�
	*pBuffMat = m_pBuffMatAll[type];		//�}�e���A���ւ̃|�C���^�̐ݒ�
	*numMat = m_nNumMatAll[type];			//�}�e���A�����̐ݒ�
}

//���f���S���̓ǂݍ��ݏ���
void CModel::LoadAllModels(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < CModel::MODEL_MAX; nCnt++)
	{
		m_vModelTexture[nCnt].clear();				//�e�N�X�`�����N���A����

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_pModelPass[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMatAll[nCnt],
			NULL,
			&m_nNumMatAll[nCnt],
			&m_pMeshAll[nCnt]);

		D3DXMATERIAL *pMat = nullptr;				//�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMatAll[nCnt]->GetBufferPointer();

		for (int a = 0; a < (int)m_nNumMatAll[nCnt]; a++)
		{//�}�e���A�̃e�N�X�`�����ݒ肳��Ă�����A�������āA�ۑ�����
			LPDIRECT3DTEXTURE9 pTex = nullptr;

			D3DXCreateTextureFromFile(pDevice, pMat->pTextureFilename, &pTex);
			pMat++;
			m_vModelTexture[nCnt].push_back(pTex);
		}
	}	
}

//���f���S���̔j������
void CModel::DestroyAllModels(void)
{
	for (int nCnt = 0; nCnt < CModel::MODEL_MAX; nCnt++)
	{
		//���b�V���̔j��
		if (m_pMeshAll[nCnt] != nullptr)
		{
			m_pMeshAll[nCnt]->Release();
			m_pMeshAll[nCnt] = nullptr;
		}

		//�}�e���A���̔j��
		if (m_pBuffMatAll[nCnt] != nullptr)
		{
			m_pBuffMatAll[nCnt]->Release();
			m_pBuffMatAll[nCnt] = nullptr;
		}
	}
}

//�e�N�X�`���̎擾����
void CModel::GetTextures(std::vector <LPDIRECT3DTEXTURE9>& vTex, CModel::ModelType type)
{
	vTex.clear();

	for (int nCnt = 0; nCnt < (int)m_nNumMatAll[type]; nCnt++)
	{
		vTex.push_back(m_vModelTexture[type].data()[nCnt]);
	}
}

//��������
CModel* CModel::Create(ModelType type, D3DXVECTOR3 pos)
{
	CModel* pModel = new CModel(3);						//���f���𐶐�����

	if (FAILED(pModel->Init()))
	{//����������
		return nullptr;
	}

	pModel->m_pos = pos;								//�ʒu�̐ݒ�
	pModel->m_LastPos = pos;							//�O��̈ʒu�̐ݒ�
	pModel->m_move = Vec3Null;							//�ړ��ʂ̐ݒ�
	pModel->m_rot = Vec3Null;							//�����̐ݒ�
	pModel->m_pMesh = m_pMeshAll[type];					//���b�V���ւ̃|�C���^�̎擾
	pModel->m_pBuffMat = m_pBuffMatAll[type];			//�}�e���A���ւ̃|�C���^�̎擾
	pModel->m_nNumMat = m_nNumMatAll[type];				//�}�e���A�����̎擾
	pModel->m_type = type;								//��ނ̐ݒ�

	return pModel;										//���������C���X�^���X��Ԃ�
}

CModel* CModel::Create(ModelType type, D3DXVECTOR3 pos, const int nPriority)
{
	CModel* pModel = new CModel(nPriority);				//���f���𐶐�����

	if (FAILED(pModel->Init()))
	{//����������
		return nullptr;
	}

	pModel->m_pos = pos;								//�ʒu�̐ݒ�
	pModel->m_LastPos = pos;							//�O��̈ʒu�̐ݒ�
	pModel->m_move = Vec3Null;							//�ړ��ʂ̐ݒ�
	pModel->m_rot = Vec3Null;							//�����̐ݒ�
	pModel->m_pMesh = m_pMeshAll[type];					//���b�V���ւ̃|�C���^�̎擾
	pModel->m_pBuffMat = m_pBuffMatAll[type];			//�}�e���A���ւ̃|�C���^�̎擾
	pModel->m_nNumMat = m_nNumMatAll[type];				//�}�e���A�����̎擾
	pModel->m_type = type;								//��ނ̐ݒ�

	return pModel;										//���������C���X�^���X��Ԃ�
}