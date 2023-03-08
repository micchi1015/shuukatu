//------------------------------
//
//�|���S������[polygon.cpp]
//Author:���c�喲
//
//------------------------------
//---------------------------
//�C���N���[�h
//---------------------------
#include "application.h"
#include "game.h"
#include "renderer.h"
#include "playerlifepolygon.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
LPDIRECT3DTEXTURE9 CPlayerLifePolygon::m_pTexture;				//�e�N�X�`���ւ̃|�C���^
CPlayerLifePolygon *CPlayerLifePolygon::m_Polygon;
int	CPlayerLifePolygon::m_Life = 1;

//�R���X�g���N�^
CPlayerLifePolygon::CPlayerLifePolygon(int nPriority) : CObject2D(nPriority)
{
	SetType(OBJTYPE_LIFEBER);
}

//�f�X�g���N�^
CPlayerLifePolygon::~CPlayerLifePolygon()
{
}

//�X�R�A�̏��������� 
HRESULT CPlayerLifePolygon::Init()
{
	CObject2D::Init();
	BindTexture(m_pTexture);
	SetColer(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	return S_OK;
}

//�X�R�A�̍X�V����
void CPlayerLifePolygon::Update()
{
	CObject2D::Update();
}

CPlayerLifePolygon * CPlayerLifePolygon::Create(const D3DXVECTOR3 pos)
{
	CPlayerLifePolygon *pPolygon = new CPlayerLifePolygon;

	if (pPolygon != nullptr)
	{
		pPolygon->Init();
		pPolygon->SetPos(pos);
		pPolygon->SetSize(D3DXVECTOR3(20.0f, 33.0f, 0.0f));
		pPolygon->SetType(OBJTYPE_LIFEBER);
		pPolygon->SetLife(1);
	}

	return pPolygon;
}

//���C�t�̐ݒ�
void CPlayerLifePolygon::SetLife(int nLife)
{
	m_Life = nLife;
}

//���C�t�̒l��Ԃ�
int CPlayerLifePolygon::GetPlayerLife()
{
	return m_Life;
}

//�e�N�X�`���̍X�V
void CPlayerLifePolygon::UpdateLife(int nCnt)
{
	m_Polygon = CGame::GetPlayerLifePolygon(nCnt);
	m_Polygon->Uninit();
}

//�e�N�X�`���ǂݍ���
HRESULT CPlayerLifePolygon::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\polygon.png",
		&m_pTexture);

	return S_OK;
}

//�e�N�X�`���̔j��
void CPlayerLifePolygon::Unload()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}