//=============================================================================
//
// hitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "CylinderHitbox.h"
#include "line.h"
#include "score.h"

//�R���X�g���N�^
CCylinderHitbox::CCylinderHitbox()
{
	//�����o�[�ϐ����N���A����

	//�f�o�b�O�p�̐�
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		m_pLine[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CCylinderHitbox::~CCylinderHitbox()
{

}

//����������
HRESULT CCylinderHitbox::Init(void)
{
	if (FAILED(CHitbox::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�f�o�b�O�p�̐�
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		m_pLine[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CCylinderHitbox::Uninit(void)
{
	//�f�o�b�O�p�̐��̔j��
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		if (m_pLine[nCnt] != nullptr)
		{
			m_pLine[nCnt]->Release();
			m_pLine[nCnt] = nullptr;
		}
	}

	//��{�N���X�̏I������
	CHitbox::Uninit();
}

//�X�V����
void CCylinderHitbox::Update(void)
{
	if (GetType() == TYPE_PLAYER)
	{//�v���C���[�̃q�b�g�{�b�N�X��������A
		std::vector <CHitbox*>* pHbx = GetAllHitbox();			//�S���̃q�b�g�{�b�N�X���擾����

		for (int nCnt = 0; nCnt < (int)pHbx->size(); nCnt++)
		{//�擾�����q�b�g�{�b�N�X��S�����肷��

			if (pHbx->data()[nCnt] != this && pHbx->data()[nCnt]->GetParent() != GetParent())
			{//�e�������ł͂Ȃ�������

				HITBOX_SHAPE shape = pHbx->data()[nCnt]->GetShape();			//�`�̎擾

				switch (shape)
				{
				case CHitbox::SHAPE_SPHERE:
					break;

				case CHitbox::SHAPE_BOX:

				{//��`�̏ꍇ

					if (PointBoxHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetRot(), pHbx->data()[nCnt]->GetSize()))
					{//���������ꍇ

						if (!GetInvincibility())
						{//���G��Ԃł͂Ȃ�������

							if (GetType() == TYPE_PLAYER && (pHbx->data()[nCnt]->GetType() == TYPE_VANISHING || pHbx->data()[nCnt]->GetType() == TYPE_OBSTACLE))
							{
								pHbx->data()[nCnt]->SetCollisionState(true);
							}

							if (GetType() == TYPE_PLAYER && pHbx->data()[nCnt]->GetScore() != 0)
							{//�X�R�A����������A�X�R�A��ݒ肷��
								if (GetPlayerIdx() >= 0)
								{
									CScore::AddScore(GetPlayerIdx(), pHbx->data()[nCnt]->GetScore());
								}
							}

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//�G�t�F�N�g����������A�G�t�F�N�g��ݒ肷��
								SetEffect(pHbx->data()[nCnt]->GetEffect());
							}

							if (pHbx->data()[nCnt]->GetEffect() == CHitbox::EFFECT_BOUNCE)
							{
								D3DXVECTOR3 dir = GetParent()->GetPos() - pHbx->data()[nCnt]->GetPos();
								pHbx->data()[nCnt]->SetDirection(dir);
							}

							if (pHbx->data()[nCnt]->GetDirection() != Vec3Null)
							{
								SetDirection(pHbx->data()[nCnt]->GetDirection());
							}
						}
					}
				}

				break;

				case CHitbox::SHAPE_CYLINDER:

				{//�V�����_�[�̏ꍇ

					if (CylinderCylinderHit(pHbx->data()[nCnt]->GetPos(), pHbx->data()[nCnt]->GetSize()))
					{//���������ꍇ

						if (!GetInvincibility())
						{//���G��Ԃł͂Ȃ�������

							pHbx->data()[nCnt]->SetCollisionState(true);		//����������Ԃɂ���

							if (GetType() == TYPE_PLAYER && pHbx->data()[nCnt]->GetScore() != 0)
							{//�X�R�A����������A�X�R�A�̐ݒ�

								if (GetPlayerIdx() >= 0)
								{
									CScore::AddScore(GetPlayerIdx(), pHbx->data()[nCnt]->GetScore());
								}
							}

							if (GetEffect() == EFFECT_MAX && pHbx->data()[nCnt]->GetEffect() != EFFECT_MAX)
							{//�G�t�F�N�g����������A�G�t�F�N�g��ݒ肷��
								SetEffect(pHbx->data()[nCnt]->GetEffect());
							}

							if (pHbx->data()[nCnt]->GetEffect() == CHitbox::EFFECT_BOUNCE)
							{
								D3DXVECTOR3 dir = GetParent()->GetPos() - pHbx->data()[nCnt]->GetPos();
								pHbx->data()[nCnt]->SetDirection(dir);
							}

							if (pHbx->data()[nCnt]->GetDirection() != Vec3Null)
							{
								SetDirection(pHbx->data()[nCnt]->GetDirection());
							}
						}
					}
				}

				break;

				default:
					break;
				}
			}
		}
	}

	//�f�o�b�O�p�̐��̍X�V
	for (int nCnt = 0; nCnt < 18; nCnt++)
	{
		if (m_pLine[nCnt] != nullptr)
		{
			m_pLine[nCnt]->SetPos(GetPos());
		}
	}

	//��{�N���X�̍X�V
	CHitbox::Update();
}


//=============================================================================
//
//							�ÓI�֐�
//
//=============================================================================

//��������
CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;				//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	pHitbox->SetPos(pos);								//�ʒu�̐ݒ�
	pHitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	pHitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	pHitbox->SetType(type);								//��ނ̐ݒ�
	pHitbox->SetShape(CHitbox::SHAPE_CYLINDER);			//�`�̐ݒ�
	pHitbox->SetParent(pParent);						//�e�̐ݒ�

#ifdef _DEBUG

	//�f�o�b�O�p�̐��̐���
	D3DXVECTOR3 Vtx[12];

	for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			Vtx[(nCnt2 * 6) + nCnt] = D3DXVECTOR3(size.x * cosf((2.0f * D3DX_PI * nCnt) / 6), size.y * nCnt2, size.z * sinf((2.0f * D3DX_PI * nCnt) / 6));
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		pHitbox->m_pLine[nCnt] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 1], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 6] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 6], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 12] = CLine::Create(pos, Vec3Null, Vtx[nCnt + 6], Vtx[nCnt + 7], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[0], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[11], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[17] = CLine::Create(pos, Vec3Null, Vtx[11], Vtx[6], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

#endif // !_DEBUG

	return pHitbox;
}

//��������
CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, CObject* pParent, const int nPlayerIdx)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;		//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	pHitbox->SetPos(pos);								//�ʒu�̐ݒ�
	pHitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	pHitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	pHitbox->SetType(type);								//��ނ̐ݒ�
	pHitbox->SetShape(CHitbox::SHAPE_CYLINDER);			//�`�̐ݒ�
	pHitbox->SetParent(pParent);						//�e�̐ݒ�
	pHitbox->SetPlayerIdx(nPlayerIdx);					//�v���C���[�C���f�b�N�X�̐ݒ�

#ifdef _DEBUG

	//�f�o�b�O�p�̐��̐���
	D3DXVECTOR3 Vtx[12];

	for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			Vtx[(nCnt2 * 6) + nCnt] = D3DXVECTOR3(size.x * cosf((2.0f * D3DX_PI * nCnt) / 6), size.y * nCnt2, size.z * sinf((2.0f * D3DX_PI * nCnt) / 6));
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		pHitbox->m_pLine[nCnt] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 1], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 6] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 6], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 12] = CLine::Create(pos, Vec3Null, Vtx[nCnt + 6], Vtx[nCnt + 7], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	}

	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[0], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[11], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	pHitbox->m_pLine[17] = CLine::Create(pos, Vec3Null, Vtx[11], Vtx[6], D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

#endif // !_DEBUG

	return pHitbox;					//���������C���X�^���X��Ԃ�
}

//��������
CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;				//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	pHitbox->SetPos(pos);								//�ʒu�̐ݒ�
	pHitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	pHitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	pHitbox->SetType(type);								//��ނ̐ݒ�
	pHitbox->SetShape(CHitbox::SHAPE_CYLINDER);			//�`�̐ݒ�
	pHitbox->SetParent(pParent);						//�e�̐ݒ�
	pHitbox->SetScore(nScore);							//�X�R�A�̐ݒ�

#ifdef _DEBUG

	//�f�o�b�O�p�̐��̐���
	D3DXVECTOR3 Vtx[12];

	for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			Vtx[(nCnt2 * 6) + nCnt] = D3DXVECTOR3(size.x * cosf((2.0f * D3DX_PI * nCnt) / 6), size.y * nCnt2, size.z * sinf((2.0f * D3DX_PI * nCnt) / 6));
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		pHitbox->m_pLine[nCnt] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 1], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 6] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 12] = CLine::Create(pos, Vec3Null, Vtx[nCnt + 6], Vtx[nCnt + 7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[0], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[11], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[17] = CLine::Create(pos, Vec3Null, Vtx[11], Vtx[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif // !_DEBUG

	return pHitbox;						//���������C���X�^���X��Ԃ�
}

CCylinderHitbox* CCylinderHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 RelativePos, const D3DXVECTOR3 size, HITBOX_TYPE type, int nScore, CObject* pParent, CHitbox::INTERACTION_EFFECT effect)
{
	CCylinderHitbox* pHitbox = new CCylinderHitbox;				//�q�b�g�{�b�N�X�̐���

	if (FAILED(pHitbox->Init()))
	{//����������
		return nullptr;
	}

	pHitbox->SetRelativePos(RelativePos);				//���Έʒu�̐ݒ�
	pHitbox->SetPos(pos);								//�ʒu�̐ݒ�
	pHitbox->SetLastPos(pos);							//�O��̈ʒu�̐ݒ�
	pHitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	pHitbox->SetType(type);								//��ނ̐ݒ�
	pHitbox->SetShape(CHitbox::SHAPE_CYLINDER);			//�`�̐ݒ�
	pHitbox->SetParent(pParent);						//�e�̐ݒ�
	pHitbox->SetScore(nScore);							//�X�R�A�̐ݒ�
	pHitbox->SetEffect(effect);							//�G�t�F�N�g�̐ݒ�

#ifdef _DEBUG

	//�f�o�b�O�p�̐��̐���
	D3DXVECTOR3 Vtx[12];

	for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
	{
		for (int nCnt = 0; nCnt < 6; nCnt++)
		{
			Vtx[(nCnt2 * 6) + nCnt] = D3DXVECTOR3(size.x * cosf((2.0f * D3DX_PI * nCnt) / 6), size.y * nCnt2, size.z * sinf((2.0f * D3DX_PI * nCnt) / 6));
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		pHitbox->m_pLine[nCnt] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 1], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 6] = CLine::Create(pos, Vec3Null, Vtx[nCnt], Vtx[nCnt + 6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		pHitbox->m_pLine[nCnt + 12] = CLine::Create(pos, Vec3Null, Vtx[nCnt + 6], Vtx[nCnt + 7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	pHitbox->m_pLine[5] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[0], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[11] = CLine::Create(pos, Vec3Null, Vtx[5], Vtx[11], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	pHitbox->m_pLine[17] = CLine::Create(pos, Vec3Null, Vtx[11], Vtx[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif // !_DEBUG

	return pHitbox;					//���������C���X�^���X��Ԃ�
}


//=============================================================================
//
//						�@�@�@�@�v���C�x�[�g�֐�
//
//=============================================================================



//�V�����_�[�ƃV�����_�[�̓����蔻��
bool CCylinderHitbox::CylinderCylinderHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos, thisSize;				//���̃q�b�g�{�b�N�X�̑O��ʒu�̎擾
	thisPos = GetPos();							//���̃q�b�g�{�b�N�X�̌��݈ʒu�̎擾
	thisSize = GetSize();						//���̃q�b�g�{�b�N�X�̂̃T�C�Y�擾

	float fTop, fBottom;				//���̃q�b�g�{�b�N�X�̏㑤�Ɖ���

	fTop = pos.y + size.y;				//�㑤�̍��W
	fBottom = pos.y;					//�����̍��W

	if (fTop >= thisPos.y && fBottom <= thisPos.y + thisSize.y)
	{//Y���W���d�Ȃ����ꍇ

		float fDistance, fRadius;
		fDistance = sqrtf(((pos.x - thisPos.x) * (pos.x - thisPos.x)) + ((pos.z - thisPos.z) * (pos.z - thisPos.z)));		//����
		fRadius = size.x + thisSize.x;				//���a�̑����Z

		if (fDistance < fRadius)
		{//�����͔��a�̑����Z��菬����������

			D3DXVECTOR3 thisLast = GetLastPos();					//�O��̈ʒu�̎擾
			D3DXVECTOR3 parentPos = GetParent()->GetPos();			//�e�̎擾

			if (thisLast.y + thisSize.y <= pos.y)
			{//�����瓖�������ꍇ
				thisPos.y = (pos.y - thisSize.y - 0.01f);		//�V�����ʒu�̌v�Z
				parentPos = thisPos - GetRelativePos();			
				GetParent()->SetPos(parentPos);					//�e�������o��
				SetLastPos(thisPos);							//�O��̈ʒu�̐ݒ�
			}
			else if (thisLast.y >= pos.y + size.y)
			{//�ォ�瓖�������ꍇ
				thisPos.y = (pos.y + size.y + 0.01f);			//�V�����ʒu�̌v�Z
				parentPos = thisPos - GetRelativePos();
				GetParent()->SetPos(parentPos);					//�e�������o��
				SetLastPos(thisPos);							//�O��̈ʒu�̐ݒ�
			}
			else
			{//�����瓖�������ꍇ
				D3DXVECTOR3 dist = thisPos - pos;					//�������v�Z����
				float fHeight = parentPos.y;						//���݂̍���
				dist.y = 0.0f;										
				D3DXVec3Normalize(&dist, &dist);					//�����𐳋K������
				dist.x *= fRadius + 0.001f;							
				dist.z *= fRadius + 0.001f;							
				dist.x += pos.x;									
				dist.z += pos.z;									
				parentPos = dist - GetRelativePos();				//�V�����ʒu���v�Z����
				parentPos.y = fHeight;								//���̍�����ݒ肷��
				GetParent()->SetPos(parentPos);						//�e�̈ʒu�̐ݒ�
			}

			return true;				//true��Ԃ�
		}
	}

	return false;						//false��Ԃ�
}


//bool CCylinderHitbox::CylinderBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
//{
//	D3DXVECTOR3 thisPos = GetPos();
//	D3DXVECTOR3 thisSize = GetSize();
//
//	if (thisPos.y + thisSize.y >= pos.y && thisPos.y <= pos.y + size.y)
//	{
//		D3DXVECTOR3 Vtx[4] = {};
//		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
//		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
//		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
//		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);
//
//		D3DXMATRIX mtxW, mtxRot, MtxTrans;
//		D3DXMatrixIdentity(&mtxW);
//		D3DXMatrixTranslation(&MtxTrans, pos.x, pos.y, pos.z);
//		D3DXMatrixMultiply(&mtxW, &mtxW, &MtxTrans);
//		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
//		D3DXMatrixMultiply(&mtxW, &mtxW, &mtxRot);
//
//		for (int nCnt = 0; nCnt < 4; nCnt++)
//		{
//			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxW);
//		}
//
//		D3DXVECTOR3 edgeVector[4], ObjVector[4], Cross[4];
//
//		edgeVector[0] = Vtx[1] - Vtx[0];
//		edgeVector[1] = Vtx[2] - Vtx[1];
//		edgeVector[2] = Vtx[3] - Vtx[2];
//		edgeVector[3] = Vtx[0] - Vtx[3];
//
//		D3DXVECTOR3 YVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		D3DXVECTOR3 Normal[4] = {};
//		D3DXVECTOR3 nearPoint[4] = {};
//
//		for (int nCnt = 0; nCnt < 4; nCnt++)
//		{
//			/*D3DXVECTOR3 vDis = thisPos - pos;
//			vDis.y = 0.0f;
//			D3DXVec3Normalize(&vDis, &vDis);*/
//			D3DXVECTOR3 normCross = Vec3Null;
//			D3DXVec3Cross(&Normal[nCnt], &edgeVector[nCnt], &YVector);
//			D3DXVec3Normalize(&Normal[nCnt], &Normal[nCnt]);
//			D3DXVec3Cross(&normCross, &edgeVector[nCnt], &Normal[nCnt]);
//
//			if (normCross.y > 0.0f)
//			{
//				Normal[nCnt].x *= -1.0f;
//				Normal[nCnt].y *= -1.0f;
//				Normal[nCnt].z *= -1.0f;
//			}
//
//			nearPoint[nCnt] = thisPos + D3DXVECTOR3(Normal[nCnt].x * thisSize.x /** 0.5f*/, 0.0f, Normal[nCnt].z * thisSize.z /** 0.5f*/);
//		}
//		int nIdx = 0;
//		int nVtxIdx = 0;
//		bool bInt = false;
//
//		for (int nCnt = 0; nCnt < 4; nCnt++)
//		{
//			ObjVector[0] = nearPoint[nCnt] - Vtx[0];
//			ObjVector[1] = nearPoint[nCnt] - Vtx[1];
//			ObjVector[2] = nearPoint[nCnt] - Vtx[2];
//			ObjVector[3] = nearPoint[nCnt] - Vtx[3];
//
//			ObjVector[0].y = 0.0f;
//			ObjVector[1].y = 0.0f;
//			ObjVector[2].y = 0.0f;
//			ObjVector[3].y = 0.0f;
//
//			D3DXVec3Cross(&Cross[0], &edgeVector[0], &ObjVector[0]);
//			D3DXVec3Cross(&Cross[1], &edgeVector[1], &ObjVector[1]);
//			D3DXVec3Cross(&Cross[2], &edgeVector[2], &ObjVector[2]);
//			D3DXVec3Cross(&Cross[3], &edgeVector[3], &ObjVector[3]);
//
//			if (Cross[0].y * Cross[1].y >= 0 && Cross[0].y * Cross[2].y >= 0 && Cross[0].y * Cross[3].y >= 0 && Cross[1].y * Cross[2].y >= 0 && Cross[1].y * Cross[3].y >= 0 && Cross[2].y * Cross[3].y >= 0)
//			{
//				nIdx = nCnt;
//				bInt = true;
//				nVtxIdx = nCnt + 2;
//
//				if (nVtxIdx >= 4)
//				{
//					nVtxIdx -= 4;
//				}
//
//				break;
//			}
//		}
//		if (bInt)
//		{
//			D3DXVECTOR3 LastPos = GetLastPos();
//			D3DXVECTOR3 parentPos = GetParent()->GetPos();
//
//			if (LastPos.y >= pos.y + size.y)
//			{
//				//D3DXVECTOR3 diff = Vec3Null;
//				//diff.y = (pos.y + size.y) - thisPos.y;
//				thisPos.y = pos.y + size.y + 0.001f;
//				//SetPos(thisPos);
//				parentPos = thisPos - GetRelativePos();
//				GetParent()->SetPos(parentPos);
//			}
//			else if (LastPos.y + thisSize.y <= pos.y)
//			{
//				//D3DXVECTOR3 diff = Vec3Null;
//				//diff.y = (pos.y - thisSize.y) - thisPos.y;
//				thisPos.y = (pos.y - thisSize.y) - 0.0001f;
//				//SetPos(thisPos);
//				parentPos = thisPos - GetRelativePos();
//				GetParent()->SetPos(parentPos);
//			}
//			else
//			{
//				D3DXVECTOR3 Center = thisPos - Vtx[nVtxIdx];
//				Center.y = 0.0f;
//				D3DXVECTOR3 radius = nearPoint[nIdx] - thisPos;
//				radius.y = 0.0f;
//				D3DXVECTOR3 versRad = Vec3Null;
//				D3DXVec3Normalize(&versRad, &radius);
//
//				D3DXVECTOR3 c[2] = {};
//				D3DXVec3Cross(&c[0], &Center, &edgeVector[nVtxIdx]);
//				D3DXVec3Cross(&c[1], &versRad, &edgeVector[nVtxIdx]);
//				float f1, f2;
//				f1 = D3DXVec3Length(&c[1]);
//				f2 = D3DXVec3Length(&c[0]);
//
//				if (f2 == 0.0f)
//				{
//					return false;
//				}
//
//				float fK = f1 / f2;
//
//				D3DXVECTOR3 edgeNormal = Vec3Null, dir = Vec3Null;
//				D3DXVec3Normalize(&edgeNormal, &edgeVector[nVtxIdx]);
//				dir = thisPos - GetLastPos();
//				dir.y = 0.0f;
//				D3DXVec3Normalize(&dir, &dir);
//				
//				float fAngle, fLength;
//
//				fAngle = acosf(D3DXVec3Dot(&edgeNormal, &dir));
//
//				D3DXVECTOR3 T = D3DXVECTOR3(thisPos.x + (versRad.x * fK), 0.0f, thisPos.z + (versRad.z * fK));
//				D3DXVECTOR3 TVec = nearPoint[nIdx] - T;
//				TVec.y = 0.0f;
//				fLength = D3DXVec3Length(&TVec);
//
//				D3DXVECTOR3 newPos = nearPoint[nIdx] + D3DXVECTOR3(0.001f + Normal[nVtxIdx].x/* * (thisSize.x * 0.25f)*/, 0.0f, 0.001f + Normal[nVtxIdx].z /** (thisSize.z * 0.25f)*/) + D3DXVECTOR3(Normal[nVtxIdx].x * (fLength + 0.001f) * sinf(fAngle), 0.0f, Normal[nVtxIdx].z * (fLength + 0.001f) * sinf(fAngle));
//
//				GetParent()->SetPos(newPos - GetRelativePos());
//
//			}
//
//
//			return true;
//		}
//	}
//
//	return false;
//}

//�_�Ƌ�`�̓����蔻��
bool CCylinderHitbox::PointBoxHit(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	D3DXVECTOR3 thisPos = GetPos();						//���̃q�b�g�{�b�N�X�̑O��ʒu�̎擾
	D3DXVECTOR3 thisSize = GetSize();					//���̃q�b�g�{�b�N�X�̌��݈ʒu�̎擾
	D3DXVECTOR3 thisLastPos = GetLastPos();				//���̃q�b�g�{�b�N�X�̂̃T�C�Y�擾

	if (thisPos.y + thisSize.y > pos.y && thisPos.y < pos.y + size.y)
	{//Y���W���d�Ȃ����ꍇ

		D3DXVECTOR3 Vtx[4], V[4], P[4], PCtrl, R[4], RCtrl, N;	//�v�Z�p�̃x�N�g��
		D3DXMATRIX mtxOut, mtxTrans, mtxRot;					//�v�Z�p�̃}�g���b�N�X
		float fResult;											//�v�Z�p�̕ϐ�

		//���_�̑��΍��W�̐ݒ�
		Vtx[0] = D3DXVECTOR3(-size.x, 0.0f, size.z);
		Vtx[1] = D3DXVECTOR3(size.x, 0.0f, size.z);
		Vtx[2] = D3DXVECTOR3(size.x, 0.0f, -size.z);
		Vtx[3] = D3DXVECTOR3(-size.x, 0.0f, -size.z);

		//���΍��W�����΍��W�ɕϊ�����
		D3DXMatrixIdentity(&mtxOut);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxTrans);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			D3DXVec3TransformCoord(&Vtx[nCnt], &Vtx[nCnt], &mtxOut);
		}

		//�e���_���玟�̒��_�܂ł̃x�N�g�����v�Z����
		V[0] = Vtx[1] - Vtx[0];
		V[1] = Vtx[2] - Vtx[1];
		V[2] = Vtx[3] - Vtx[2];
		V[3] = Vtx[0] - Vtx[3];

		//�e���_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g�����v�Z����
		P[0] = D3DXVECTOR3(thisPos.x - Vtx[0].x, 0.0f, thisPos.z - Vtx[0].z);
		P[1] = D3DXVECTOR3(thisPos.x - Vtx[1].x, 0.0f, thisPos.z - Vtx[1].z);
		P[2] = D3DXVECTOR3(thisPos.x - Vtx[2].x, 0.0f, thisPos.z - Vtx[2].z);
		P[3] = D3DXVECTOR3(thisPos.x - Vtx[3].x, 0.0f, thisPos.z - Vtx[3].z);

		//��̃x�N�g���̊O�ς��v�Z����
		D3DXVec3Cross(&R[0], &V[0], &P[0]);
		D3DXVec3Cross(&R[1], &V[1], &P[1]);
		D3DXVec3Cross(&R[2], &V[2], &P[2]);
		D3DXVec3Cross(&R[3], &V[3], &P[3]);

		if (R[0].y * R[1].y >= 0 && R[1].y * R[2].y >= 0 && R[2].y * R[3].y >= 0 && R[3].y * R[0].y >= 0)
		{//�S���̊O�ς̕�����������������A���������Ƃ����Ӗ��ł�

			if (thisLastPos.y >= pos.y + size.y && thisPos.y < pos.y + size.y)
			{//�ォ�瓖�������ꍇ

				//�V�����ʒu�̌v�Z
				thisPos.y = pos.y + size.y + 0.01f;
				SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�

				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�

				return true;			//true��Ԃ�
			}
			else if (thisLastPos.y + thisSize.y <= pos.y && thisPos.y + thisSize.y > pos.y)
			{//�����瓖�������ꍇ

				 //�V�����ʒu�̌v�Z
				thisPos.y = pos.y - thisSize.y - 0.01f;

				SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�
				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�

				return true;			//true��Ԃ�
			}
			else
			{//�����瓖�������ꍇ

				for (int Count = 0; Count < 4; Count++)
				{
					//�ǂ����瓖�����������߂�

					PCtrl = D3DXVECTOR3(thisLastPos.x - Vtx[Count].x, 0.0f, thisLastPos.z - Vtx[Count].z);
					D3DXVec3Cross(&RCtrl, &V[Count], &PCtrl);

					D3DXVECTOR3 Ctrl;

					if (RCtrl.y * R[Count].y <= 0)
					{//�ǂ����瓖������������������

						P[0] = D3DXVECTOR3(thisPos.x - thisLastPos.x, 0.0f, thisPos.z - thisLastPos.z);				//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g��
						P[1] = D3DXVECTOR3(Vtx[Count].x - thisLastPos.x, 0.0f, Vtx[Count].z - thisLastPos.z);		//�O��̈ʒu���璸�_�܂ł̃x�N�g��
						D3DXVec3Normalize(&N, &P[0]);			//�O��̈ʒu���猻�݂̈ʒu�܂ł̃x�N�g���𐳋K������

						//��̃x�N�g���Ƌ�`�̕ӂ̃x�N�g���̊O�ς��v�Z����
						D3DXVec3Cross(&R[0], &P[1], &V[Count]);
						D3DXVec3Cross(&R[1], &N, &V[Count]);

						if (R[1].y == 0)
						{
							break;
						}

						fResult = R[0].y / R[1].y;

						if (fResult > 0)
						{
							fResult -= 0.001f;
						}
						else if (fResult < 0)
						{
							fResult += 0.001f;
						}

						D3DXVECTOR3 Cross, VtxtoPos, VtxtoCross;
						float Dot, Lenght1, Lenght2, Alpha;

						Cross = D3DXVECTOR3(thisLastPos.x + (N.x * fResult), 0.0f, thisLastPos.z + (N.z * fResult));			//��_���W
						VtxtoPos = D3DXVECTOR3(thisPos.x - Vtx[Count].x, 0.0f, thisPos.z - Vtx[Count].z);						//���_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g��
						VtxtoCross = D3DXVECTOR3(Cross.x - Vtx[Count].x, 0.0f, Cross.z - Vtx[Count].z);							//���_�����_�܂ł̃x�N�g��

						D3DXVec3Normalize(&N, &VtxtoCross);			//���_�����_�܂ł̃x�N�g���𐳋K������

						//���_�����_�܂ł̃x�N�g���ƒ��_���炱�̃q�b�g�{�b�N�X�̈ʒu�܂ł̃x�N�g���̓��ς��v�Z����
						Dot = D3DXVec3Dot(&VtxtoCross, &VtxtoPos);
						Lenght1 = sqrtf((VtxtoCross.x * VtxtoCross.x) + (VtxtoCross.z * VtxtoCross.z));		//��̃x�N�g���̒������v�Z����
						Lenght2 = sqrtf((VtxtoPos.x * VtxtoPos.x) + (VtxtoPos.z * VtxtoPos.z));				//��̃x�N�g���̒������v�Z����

						if ((Lenght1 * Lenght2) * (Lenght1 * Lenght2) >= Dot * Dot && Lenght1 * Lenght2 != 0)
						{//���
							//�V�����ʒu���v�Z����
							Alpha = acosf((Dot) / (Lenght1 * Lenght2));

							fResult = (Lenght2 * cosf(Alpha));

							//�V�����ʒu�̐ݒ�
							thisPos.x = Vtx[Count].x + (N.x * (fResult));
							thisPos.z = Vtx[Count].z + (N.z * (fResult));
						}
						else
						{//�G���[����������A�V�����ʒu����_���W�ɐݒ肷��

							thisPos.x = thisLastPos.x + (N.x * fResult);
							thisPos.z = thisLastPos.z + (N.z * fResult);
						}

						break;
					}
				}

				GetParent()->SetPos(thisPos - GetRelativePos());		//�e�̈ʒu�̐ݒ�
				SetLastPos(thisPos);									//�O��̈ʒu�̐ݒ�
				SetPos(thisPos);										//���݂̈ʒu�̐ݒ�

				return true;			//true��Ԃ�
			}
		}
	}

	return false;						//false��Ԃ�
}