//=============================================================================
//
// score.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include <vector>

//=============================================================================
//�O���錾
//=============================================================================


class CScore
{
public:	
	CScore();							//�R���X�g���N�^
	~CScore();							//�f�X�g���N�^
										
	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void AddScore(const int nScore);	//�X�R�A�𑫂�����	
	const int GetScore(void);			//�X�R�A���擾����
									
	static void AddScore(const int nPlayerIdx, const int nScore);	//�X�R�A�𑫂�����
	static const int GetScore(const int nPlayerIdx);				//�X�R�A���擾����
	static void Clear(void);										//�N���A����
	static CScore* Create(const int nPlayerIdx);					//��������

private:

	int m_nScore;					//�X�R�A
	int m_nPlayerIdx;				//�v���C���[�̃C���f�b�N�X

	static std::vector <CScore*> m_vScore;				//�X�R�A�ւ̃|�C���^�������Ă���x�N�g��

};



#endif