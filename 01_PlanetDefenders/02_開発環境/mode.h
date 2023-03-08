//-----------------------------
//
// [mode.h]
// Author:���c�喲
//
//-----------------------------
#ifndef _MODE_H_
#define _MODE_H_

//---------------------------
//�C���N���[�h
//---------------------------
#include "object.h"

//---------------------------
//�O���錾
//---------------------------
class CTitle;
class CGame;
class CResult;

//---------------------------
//���[�h�N���X
//---------------------------
class CMode : public CObject
{
public:
	CMode();			//�R���X�g���N�^
	~CMode() override;	//�f�X�g���N�^

	virtual HRESULT Init() override { return S_OK; }	//����������
	virtual void Uninit() override {};					//�I������
	virtual void Update() override {};					//�X�V����
	virtual void Draw() override {};					//�`�揈��

	void SetPos(const D3DXVECTOR3 pos)override {};				//Pos�̒l��ݒ�

	const D3DXVECTOR3 GetPos() override {return D3DXVECTOR3();}			//pos�̒l���擾����
	const D3DXVECTOR3 GetSize() override { return D3DXVECTOR3(); }		//�T�C�Y�̏��擾
	const D3DXCOLOR GetCol() override { return D3DXCOLOR(); }			//col�̏��擾
	
private:
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
};

#endif