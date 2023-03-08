//=============================================================================
//
// icePillarSpawner.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _ICE_PILLAR_SPAWNER_H_
#define _ICE_PILLAR_SPAWNER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"


class CIcePillarSpawner : public CObject
{
public:
	CIcePillarSpawner();														//�R���X�g���N�^
	~CIcePillarSpawner();														//�f�X�g���N�^

	HRESULT Init(void) override;												//����������
	void Uninit(void) override;													//�I������
	void Update(void) override;													//�X�V����
	void Draw(void) override;													//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;										//�ʒu�̐ݒ菈��
	const D3DXVECTOR3 GetPos(void) override;											//�ʒu�̎擾����

	const D3DXVECTOR2 GetSize(void) override;											//�T�C�Y�̎擾����

	static CIcePillarSpawner* Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fLaterlBounds, const float fLength, const int nMaxTime);		//��������

private:

	D3DXVECTOR3 m_pos;				//�ʒu
	float		m_shadowY;			//�e�̍���
	float		m_laterlBounds;		//�X�|�[���G���A�̕�
	float		m_fAreaLength;		//�X�|�[���G���A�̒���
	int			m_nCntTime;			//�t���[���J�E���^�[
	int			m_nSpawnTime;		//�X�|�[���^�C��
	int			m_nMaxSpawn;		//�ő�^�C��

};





#endif