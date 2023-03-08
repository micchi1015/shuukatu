//=============================================================================
//
// animator.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "animator.h"
#include "modelPart.h"
#include <string>



//=============================================================================
//�ÓI�ϐ��̏���������
//=============================================================================

//�A�j���[�V�������̃e�L�X�g�t�@�C���̑��΃p�X
char* CAnimator::m_pAnimPass[ANIM_TYPE_MAX] =
{
	{"data\\ANIMATION\\PlayerAnim.txt"},
};

std::vector <CAnimator::ModelAnimationSet> CAnimator::m_vAnimAll;			//�S���̃A�j���[�V�������������Ă���x�N�g��

//�R���X�g���N�^
CAnimator::CAnimator()
{
	//�����o�[�ϐ����N���A����
	m_vParts.clear();					//�p�[�c�̃x�N�g�����N���A����
	m_vAnimSpeed.clear();				//�A�j���[�V�����X�s�[�h�̃x�N�g�����N���A����
	m_nPresentFrame = 0;				//���݂̃t���[��
	m_nPresentMotionSet = 0;			//���݂̃��[�V�����Z�b�g
	m_nPresentAnim = 0;					//���݂̃A�j���[�V����
	m_type = (AnimType)0;				//�A�j���[�V�����̎��
}

//�f�X�g���N�^
CAnimator::~CAnimator()
{

}

//����������
HRESULT CAnimator::Init(void)
{
	//�����o�[�ϐ��̏���������
	m_vParts.clear();					//�p�[�c�̃x�N�g�����N���A����
	m_vAnimSpeed.clear();				//�A�j���[�V�����X�s�[�h�̃x�N�g�����N���A����
	m_nPresentFrame = 0;				//���݂̃t���[��
	m_nPresentMotionSet = 0;			//���݂̃��[�V�����Z�b�g
	m_nPresentAnim = 0;					//���݂̃A�j���[�V����
	m_type = (AnimType)0;				//�A�j���[�V�����̎��

	return S_OK;
}

//�I������
void CAnimator::Uninit(void)
{
	//�x�N�g�����N���A����
	m_vParts.clear();
	m_vAnimSpeed.clear();
}

//�X�V����
void CAnimator::Update(void)
{
	m_nPresentFrame++;					//���݃t���[�����X�V����

	int nextAnim = m_vAnimAll.data()[m_type].vAnimSets[m_nPresentAnim].nNextAnim;			//���̃A�j���[�V����(�ȗ��p)

	for (int nCnt = 0; nCnt < (int)m_vParts.size(); nCnt++)
	{//�p�[�c�̃A�j���[�V��������
		if (m_vParts.data()[nCnt] != nullptr)
		{//�p�[�c��null�ł͂Ȃ�������
			if (m_vParts.data()[nCnt]->GetParent() != nullptr)
			{
				D3DXVECTOR3 pos = m_vParts.data()[nCnt]->GetPos();			//�ʒu�̎擾����
				D3DXVECTOR3 rot = m_vParts.data()[nCnt]->GetRot();			//�����̎擾����
				pos += m_vAnimSpeed.data()[nCnt].move;						//�ʒu�̍X�V����
				rot += m_vAnimSpeed.data()[nCnt].rotSpeed;					//�����̍X�V����
				m_vParts.data()[nCnt]->SetPos(pos);							//�ʒu�̐ݒ菈��
				m_vParts.data()[nCnt]->SetRot(rot);							//�����̐ݒ菈��
			}
		}
	}

	if (m_nPresentFrame > m_vAnimAll.data()[m_type].vAnimSets[m_nPresentAnim].vAnimKeySet[m_nPresentMotionSet].nAnimFrames)
	{//�A�j���[�V�����̃��[�V�����Z�b�g�ő�t���[�����z�����ꍇ
		int nNextSet = m_nPresentMotionSet + 1;				//���̃��[�V�����Z�b�g

		if (nNextSet >= (int)m_vAnimAll.data()[m_type].vAnimSets[m_nPresentAnim].vAnimKeySet.size())
		{//�A�j���[�V�����͏I������ꍇ�A���̃A�j���[�V�����ɐi��
			for (int nCnt = 0; nCnt < (int)m_vParts.size(); nCnt++)
			{//�p�[�c���̃A�j���[�V�������x�̌v�Z
				if (m_vParts.data()[nCnt] != nullptr)
				{//�p�[�c��null�ł͂Ȃ�������

					//�ړ��ʂ̌v�Z
					m_vAnimSpeed.data()[nCnt].move = (m_vAnimAll.data()[m_type].vAnimSets[nextAnim].vAnimKeySet[0].vAnimKey[nCnt].RelativePos - m_vParts.data()[nCnt]->GetPos())
						/ (float)m_vAnimAll.data()[m_type].vAnimSets[nextAnim].vAnimKeySet[0].nAnimFrames;

					//��]�X�s�[�h�̌v�Z
					m_vAnimSpeed.data()[nCnt].rotSpeed = (m_vAnimAll.data()[m_type].vAnimSets[nextAnim].vAnimKeySet[0].vAnimKey[nCnt].RelativeRot - m_vParts.data()[nCnt]->GetRot())
						/ (float)m_vAnimAll.data()[m_type].vAnimSets[nextAnim].vAnimKeySet[0].nAnimFrames;
				}
			}

			//���̃A�j���[�V�����̍ŏ��̃��[�V�����Z�b�g��ݒ肷��
			m_nPresentAnim = nextAnim;			
			m_nPresentMotionSet = 0;			
		}
		else
		{//�A�j���[�V�����͂܂��I����Ă��Ȃ��ꍇ�A���̃��[�V�����Z�b�g�ɐi��
			for (int nCnt = 0; nCnt < (int)m_vParts.size(); nCnt++)
			{//�p�[�c���̃A�j���[�V�������x�̌v�Z
				if (m_vParts.data()[nCnt] != nullptr)
				{//�p�[�c��null�ł͂Ȃ�������

				 //�ړ��ʂ̌v�Z
					m_vAnimSpeed.data()[nCnt].move = (m_vAnimAll.data()[m_type].vAnimSets[m_nPresentAnim].vAnimKeySet[m_nPresentMotionSet + 1].vAnimKey[nCnt].RelativePos - m_vParts.data()[nCnt]->GetPos())
						/ (float)m_vAnimAll.data()[m_type].vAnimSets[m_nPresentAnim].vAnimKeySet[0].nAnimFrames;

					//��]�X�s�[�h�̌v�Z
					m_vAnimSpeed.data()[nCnt].rotSpeed = (m_vAnimAll.data()[m_type].vAnimSets[m_nPresentAnim].vAnimKeySet[m_nPresentMotionSet + 1].vAnimKey[nCnt].RelativeRot - m_vParts.data()[nCnt]->GetRot())
						/ (float)m_vAnimAll.data()[m_type].vAnimSets[m_nPresentAnim].vAnimKeySet[m_nPresentMotionSet + 1].nAnimFrames;
				}
			}

			m_nPresentMotionSet++;			//���̃��[�V�����Z�b�g�ɐi��
		}
		m_nPresentFrame = 0;				//�t���[����0�ɖ߂�
	}
}

//���f���p�[�c�̐ݒ菈��
void CAnimator::SetParts(std::vector <CModelPart*>* vParts)
{
	m_vParts = *vParts;
}





//�S���̃A�j���[�V������ǂݍ��ޏ���
void CAnimator::LoadAllAnimation(void)
{
	m_vAnimAll.clear();			//�x�N�g�����N���A����

	for (int nCnt = 0; nCnt < ANIM_TYPE_MAX; nCnt++)
	{//�S���̃A�j���[�V������ǂݍ���
		if (m_pAnimPass[nCnt] != nullptr)
		{//���΃p�X��null�ł͂Ȃ�������
			FILE* pFile = fopen(m_pAnimPass[nCnt], "r");		//�t�@�C�����J��

			if (pFile != nullptr)
			{//�J������
				ModelAnimationSet set;							//�V�������[�V�����Z�b�g��錾����
				ZeroMemory(&set, sizeof(ModelAnimationSet));	//���[�V�����Z�b�g������������
				int nAnimSet = -1;								//���݂̃A�j���[�V�����J�E���^�[������������
				int nKeySet = -1;								//���݂̃L�[�Z�b�g������������
				int nKey = -1;									//���݂̃L�[������������
				char pStr[512] = {};							//�������錾����

				fscanf(pFile, "%s", pStr);						

				while (strcmp(pStr, "END_SCRIPT") != 0)
				{//�X�N���v�g�̏I���܂Ői��
					fscanf(pFile, "%s", pStr);

					if (strcmp(pStr, "MOTION_SET") == 0)
					{//���[�V�����Z�b�g��ǂݍ��ޏ���
						MotionSet motionSet;							//�V�������[�V�����Z�b�g��錾����
						motionSet.nNextAnim = 0;
						nAnimSet++;										//���[�V�����Z�b�g�̃J�E���^�[���C���N�������g����
						nKeySet = -1;									//�L�[�Z�b�g�����ɖ߂�

						while (strcmp(pStr, "END_MOTION_SET") != 0)
						{//���[�V�����Z�b�g�̓ǂݍ��݂��I���܂Ői��
							fscanf(pFile, "%s", pStr);

							if (strcmp(pStr, "NEXT") == 0)
							{//���̃A�j���[�V�����̓ǂݍ���
								int nNext = 0;
								fscanf(pFile, "%s %d", pStr, &nNext);

								motionSet.nNextAnim = nNext;		//���̃A�j���[�V������ݒ肷��
							}
							else if (strcmp(pStr, "KEY_SET") == 0)
							{//�L�[�Z�b�g�̓ǂݍ��ޏ���
								AnimKeySet keySet;							//�V�����L�[�Z�b�g��錾����
								keySet.nAnimFrames = 0;
								nKeySet++;									//�L�[�Z�b�g���C���N�������g����
								nKey = -1;									//�L�[�J�E���^�[�����ɖ߂�

								while (strcmp(pStr, "END_KEY_SET") != 0)
								{//�L�[�Z�b�g�̓ǂݍ��݂��I���܂Ői��
									fscanf(pFile, "%s", pStr);

									if (strcmp(pStr, "FRAME") == 0)
									{//�t���[�����̓ǂݍ��ޏ���
										int nFrames = 0;
										fscanf(pFile, "%s %d", pStr, &nFrames);

										keySet.nAnimFrames = nFrames;		//�t���[�����̐ݒ菈��
									}
									else if (strcmp(pStr, "KEY") == 0)
									{//�L�[�̓ǂݍ��ޏ���
										AnimKey key;						//�V�����L�[��錾����
										key.RelativePos = Vec3Null;			
										key.RelativeRot = Vec3Null;			
										nKey++;								//�L�[�J�E���^�[���C���N�������g����

										char pString[512] = {};				//�������錾����

										fscanf(pFile, "%s", pString);

										while (strcmp(pString, "END_KEY") != 0)
										{//�L�[�̓ǂݍ��݂��I���܂Ői��
											float x = 0.0f;					
											float y = 0.0f;					
											float z = 0.0f;					
											fscanf(pFile, "%s", pString);

											if (strcmp(pString, "POS") == 0)
											{//�ʒu�̓ǂݍ��ޏ���
												fscanf(pFile, "%s", pString);

												fscanf(pFile, "%s", pStr);	//X���W�̓ǂݍ��ޏ���
												std::string s = pStr;		//std::string�ɕϊ�����
												x = std::stof(s);			//float�ɕϊ�����

												fscanf(pFile, "%s", pStr);	//Y���W�̓ǂݍ��ޏ���
												s = pStr;					//std::string�ɕϊ�����
												y = std::stof(s);			//float�ɕϊ�����

												fscanf(pFile, "%s", pStr);	//Z���W�̓ǂݍ��ޏ���
												s = pStr;					//std::string�ɕϊ�����
												z = std::stof(s);			//float�ɕϊ�����

												key.RelativePos = D3DXVECTOR3(x, y, z);		//�ʒu�̐ݒ菈��
											}
											else if (strcmp(pString, "ROT") == 0)
											{//��]�̓ǂݍ��ޏ���
												fscanf(pFile, "%s", pString);

												fscanf(pFile, "%s", pStr);	//X���W�̓ǂݍ��ޏ���
												std::string s = pStr;		//std::string�ɕϊ�����
												x = std::stof(s);			//float�ɕϊ�����

												fscanf(pFile, "%s", pStr);	//Y���W�̓ǂݍ��ޏ���
												s = pStr;					//std::string�ɕϊ�����
												y = std::stof(s);			//float�ɕϊ�����

												fscanf(pFile, "%s", pStr);	//Z���W�̓ǂݍ��ޏ���
												s = pStr;					//std::string�ɕϊ�����
												z = std::stof(s);			//float�ɕϊ�����

												key.RelativeRot = D3DXVECTOR3(x, y, z);		//��]�̐ݒ菈��
											}
										}	

										keySet.vAnimKey.push_back(key);		//�L�[�Z�b�g�̃x�N�g���ɃL�[������
									}
								}

								motionSet.vAnimKeySet.push_back(keySet);	//���[�V�����Z�b�g�̃x�N�g���ɃL�[�Z�b�g������
							}
						}

						set.vAnimSets.push_back(motionSet);			//�A�j���[�V�����̃x�N�g���Ƀ��[�V�����Z�b�g������
					}
				}

				m_vAnimAll.push_back(set);			//�S���̃A�j���[�V�����̃x�N�g���ɓǂݍ��񂾃A�j���[�V����������
			}
		}
	}
}

//�A�j���[�V�����̔j������
void CAnimator::DestroyLoadedAnimation(void)
{
	//�A�j���[�V�����̃x�N�g�����N���A����
	m_vAnimAll.clear();
}

//��������
CAnimator* CAnimator::Create(std::vector <CModelPart*>* vParts, AnimType type)
{
	CAnimator* pAnimator = new CAnimator;				//�A�j���[�^�[�𐶐�����

	if (FAILED(pAnimator->Init()))
	{//����������
		return nullptr;
	}

	pAnimator->SetParts(vParts);				//�p�[�c�̐ݒ菈��
	pAnimator->m_type = type;					//��ނ̐ݒ�

	for (int nCnt = 0; nCnt < (int)pAnimator->m_vParts.size(); nCnt++)
	{//�p�[�c���̃A�j���[�V�����X�s�[�h�̌v�Z
		animSpeed speed;
		speed.move = (m_vAnimAll.data()[type].vAnimSets[0].vAnimKeySet[0].vAnimKey[nCnt].RelativePos - pAnimator->m_vParts.data()[nCnt]->GetPos())
			/ (float)m_vAnimAll.data()[type].vAnimSets[0].vAnimKeySet[0].nAnimFrames;
		speed.rotSpeed = (m_vAnimAll.data()[type].vAnimSets[0].vAnimKeySet[0].vAnimKey[nCnt].RelativeRot - pAnimator->m_vParts.data()[nCnt]->GetRot())
			/ (float)m_vAnimAll.data()[type].vAnimSets[0].vAnimKeySet[0].nAnimFrames;
		pAnimator->m_vAnimSpeed.push_back(speed);			//�v�Z�����X�s�[�h�̐ݒ�
	}

	return pAnimator;					//���������A�j���[�^�[��Ԃ�
}

//�A�j���[�V�����̐ݒ菈��
void CAnimator::SetPresentAnim(int nPresentAnim)
{
	if (m_nPresentAnim != nPresentAnim)
	{
		m_nPresentAnim = nPresentAnim;
		m_nPresentFrame = 0;
		m_nPresentMotionSet = 0;

		for (int nCnt = 0; nCnt < (int)m_vParts.size(); nCnt++)
		{//�p�[�c���̃A�j���[�V�����X�s�[�h�̌v�Z

			m_vAnimSpeed.data()[nCnt].move = (m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].vAnimKey[nCnt].RelativePos - m_vParts.data()[nCnt]->GetPos())
				/ (float)m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].nAnimFrames;
			m_vAnimSpeed.data()[nCnt].rotSpeed = (m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].vAnimKey[nCnt].RelativeRot - m_vParts.data()[nCnt]->GetRot())
				/ (float)m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].nAnimFrames;
		}
	}
}

//�A�j���[�V�����̐ݒ菈��
void CAnimator::SetLoopingAnim(int nPresentAnim)
{
	if (m_nPresentAnim == nPresentAnim)
	{
		int a, b;
		a = (int)m_vAnimAll.data()[m_type].vAnimSets[m_nPresentAnim].vAnimKeySet.size();
		b = (int)m_vAnimAll.data()[m_type].vAnimSets[m_nPresentAnim].vAnimKeySet[m_nPresentMotionSet].nAnimFrames;

		if (m_nPresentMotionSet >= a - 1 &&
			m_nPresentFrame >= b - 1)
		{
			m_nPresentAnim = nPresentAnim;
			m_nPresentFrame = 0;
			m_nPresentMotionSet = 0;

			for (int nCnt = 0; nCnt < (int)m_vParts.size(); nCnt++)
			{//�p�[�c���̃A�j���[�V�����X�s�[�h�̌v�Z

				m_vAnimSpeed.data()[nCnt].move = (m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].vAnimKey[nCnt].RelativePos - m_vParts.data()[nCnt]->GetPos())
					/ (float)m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].nAnimFrames;
				m_vAnimSpeed.data()[nCnt].rotSpeed = (m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].vAnimKey[nCnt].RelativeRot - m_vParts.data()[nCnt]->GetRot())
					/ (float)m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].nAnimFrames;
			}
		}
	}
	else
	{
		m_nPresentAnim = nPresentAnim;
		m_nPresentFrame = 0;
		m_nPresentMotionSet = 0;

		for (int nCnt = 0; nCnt < (int)m_vParts.size(); nCnt++)
		{//�p�[�c���̃A�j���[�V�����X�s�[�h�̌v�Z

			m_vAnimSpeed.data()[nCnt].move = (m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].vAnimKey[nCnt].RelativePos - m_vParts.data()[nCnt]->GetPos())
				/ (float)m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].nAnimFrames;
			m_vAnimSpeed.data()[nCnt].rotSpeed = (m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].vAnimKey[nCnt].RelativeRot - m_vParts.data()[nCnt]->GetRot())
				/ (float)m_vAnimAll.data()[m_type].vAnimSets[nPresentAnim].vAnimKeySet[0].nAnimFrames;
		}
	}
}