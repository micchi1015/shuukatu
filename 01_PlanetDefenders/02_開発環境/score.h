//--------------------------------
//
//[score.h]
//Author:���c�喲
//
//--------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object.h"

//---------------------------
//�O���錾
//---------------------------
class CNumber;

//---------------------------
//�}�N����`
//---------------------------
#define MAX_SCORE	(8)		//�X�R�A�̌���

//---------------------------
//�X�R�A�N���X
//---------------------------
class CScore : public CObject
{
public:
	explicit CScore(int nPriority = PRIORITY_4);	//�R���X�g���N�^
	~CScore() override;		//�f�X�g���N�^

	HRESULT Init() override;	//����������
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	static CScore *Create();	//�|���S���̐���

	void SetScore(int nScore);	//�X�R�A�̐ݒ菈��
	void AddScore(int nValue);	//�X�R�A�̉��Z����
	int GetScore();				//�X�R�A���̎擾����

	void SetPos(const D3DXVECTOR3 pos) override {};	//Pos�̒l��ݒ�
	const D3DXVECTOR3 GetPos() override { return D3DXVECTOR3(); }		//pos�̒l���擾����
	const D3DXVECTOR3 GetSize() override { return D3DXVECTOR3(); };		//�T�C�Y�̏��擾
	const D3DXCOLOR GetCol() override { return D3DXCOLOR(); };			//�J���[�̏��擾

private:
	CNumber *m_apNumber[MAX_SCORE];		//Number�^�̔z��
	int m_nScore;						//�X�R�A�̒l
};
#endif