//=============================================================================
//
// message.h
// Author : tanimoto kosuke
//
//=============================================================================
#ifndef _MESSAGE_H
#define _MESSAGE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

//---------------------------
//�N���X�錾
//---------------------------
class CMessage
{
public:
	// ���b�Z�[�W���
	enum MESSAGE
	{
		MESSAGE_COUNTDOWN = 0,
		MESSAGE_START,
		MESSAGE_GOAL,
		MESSAGE_WIN,
		MESSAGE_MAX
	};
	CMessage();
	~CMessage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetCountDown(int nNum);		// �J�E���g�_�E�����b�Z�[�W�\������
	void StartMessage(void);			// �X�^�[�g���b�Z�[�W�\������
	void GoalMessage(int nMessageIdx);	// �S�[�����b�Z�[�W�\������
	void WinMessage();					// �������b�Z�[�W�\������

	void Destroy();						// �j������

	static CMessage* Create();			//��������
	static void SetStart(bool start) { m_bStart = start; }	// �Q�[���X�^�[�g�ݒ菈��
	static bool GetStart(void) { return m_bStart; }			// �Q�[���X�^�[�g�擾����

private:
	static const int CountDownLife = 60;	// �J�E���g�_�E���̎���
	static bool m_bStart;					// �Q�[���X�^�[�g����

	int m_nMessageIdx;						// ���҂̔ԍ�
	int m_nMessageCounter;					// ���b�Z�[�W�\������
	int m_nNum;								// �J�E���g�_�E�����݈ʒu
	CObject_2D* m_pObj2D;					// �I�u�W�F�N�g2D�̃|�C���^
	CObject_2D* m_pPlayer2D;				// ���҉摜�̃|�C���^
	MESSAGE m_type;							// ���b�Z�[�W���
};

#endif // !_MESSAGE_H
