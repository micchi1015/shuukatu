//-----------------------------------------
//
//�����L���O����[ranking.cpp]
//Author:���c�喲
//
//-----------------------------------------
#include <stdio.h>
#include "application.h"
#include "fade.h"
#include "input.h"
#include "number.h"
#include "score.h"
#include "sound.h"
#include "ranking.h"
#include "renderer.h"

//---------------------------
//�ÓI�����o�ϐ��錾
//---------------------------
CNumber *CRanking::m_apNumber[MAX_RANKINGRANK][MAX_RANKING] = {};
int CRanking::aData[MAX_RANKINGRANK] = {};
int CRanking::m_nRanking = 0;

//�R���X�g���N�^
CRanking::CRanking()
{
}

//�f�X�g���N�^
CRanking::~CRanking()
{
}

//����������
HRESULT CRanking::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRendere()->GetD3DDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\02-1.jpg",
		&m_pTexture[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\vnB0FGfi6u2lpsh1663908208_1663908211.png",
		&m_pTexture[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_pTexture[2]);

	m_pObject2D[0] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), PRIORITY_3);
	m_pObject2D[0]->SetSize(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D[0]->BindTexture(m_pTexture[0]);

	m_pObject2D[1] = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, CRenderer::SCREEN_HEIGHT / 2, 0.0f), PRIORITY_3);
	m_pObject2D[1]->SetSize(D3DXVECTOR3(1200.0f, 800.0f, 0.0f));
	m_pObject2D[1]->BindTexture(m_pTexture[1]);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			m_apNumber[nCnt][nCntRanking] = CNumber::Create(D3DXVECTOR3(50.0f *nCntRanking + 525.0f, 72.5f *nCnt + 230.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
			m_apNumber[nCnt][nCntRanking]->BindTexture(m_pTexture[2]);
		}
	}

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM003);

	//�t�@�C���ǂݍ��ݏ���
	Load();

	return S_OK;
}

//�I������
void CRanking::Uninit(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`�����W�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			if (m_apNumber[nCnt][nCntRanking] != nullptr)
			{
				m_apNumber[nCnt][nCntRanking]->Uninit();
			}
		}
	}

	CObject::Release();
}

//�X�V����
void CRanking::Update(void)
{
	CInputKeyboard *pInputKeyboard = CApplication::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_pFade->GetFade() == CFade::FADE_NONE)
	{//ENTER�L�[�������ꂽ
		//�t�@�C�������o������
		Save();
		//���[�h�ݒ�
		CFade::SetFade(CFade::FADE_OUT, CApplication::MODE_TITLE);
	}
}

//�`�揈��
void CRanking::Draw(void)
{
}

//�t�@�C���ǂݍ��ݏ���
void CRanking::Load(void)
{
	//�t�@�C���|�C���^�錾
	FILE*pFile;

	//�t�@�C�����J��
	pFile = fopen("data\\save\\ranking.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (int nCntData = 0; nCntData < MAX_RANKINGRANK; nCntData++)
		{
			//�t�@�C���ɐ��l�������o��
			fscanf(pFile, "%d\n", &aData[nCntData]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***");
	}
}

//�t�@�C�������o������
void CRanking::Save(void)
{
	//�t�@�C���|�C���^�錾
	FILE*pFile;

	//�t�@�C�����J��
	pFile = fopen("data\\save\\ranking.txt", "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
		{
			//�t�@�C���ɐ��l�������o��
			fprintf(pFile, "%d\n", aData[nCnt]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***");
	}
}

//�X�R�A�̐ݒ菈��
void CRanking::SetRankingScore()
{
	int aPosTexU[MAX_RANKINGRANK][MAX_RANKING];

	if (m_nRanking > aData[MAX_RANKINGRANK - 1])
	{
		aData[MAX_RANKINGRANK - 1] = m_nRanking;
	}
	
	for (int nCount = 0; nCount < MAX_RANKINGRANK - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < MAX_RANKINGRANK; nCount2++)
		{
			if (aData[nCount] < aData[nCount2])
			{
				int nMin = aData[nCount];
				aData[nCount] = aData[nCount2];
				aData[nCount2] = nMin;
			}
		}
	}

	for (int nCntScore = 0; nCntScore < MAX_RANKINGRANK; nCntScore++)
	{
		aPosTexU[nCntScore][0] = aData[nCntScore] % 100000000 / 1000000;
		aPosTexU[nCntScore][1] = aData[nCntScore] % 10000000 / 1000000;
		aPosTexU[nCntScore][2] = aData[nCntScore] % 1000000 / 100000;
		aPosTexU[nCntScore][3] = aData[nCntScore] % 100000 / 10000;
		aPosTexU[nCntScore][4] = aData[nCntScore] % 10000 / 1000;
		aPosTexU[nCntScore][5] = aData[nCntScore] % 1000 / 100;
		aPosTexU[nCntScore][6] = aData[nCntScore] % 100 / 10;
		aPosTexU[nCntScore][7] = aData[nCntScore] % 10 / 1;
	}

	//�e�N�X�`�����W�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_RANKINGRANK; nCnt++)
	{
		for (int nCntScore = 0; nCntScore < MAX_RANKING; nCntScore++)
		{
			m_apNumber[nCnt][nCntScore]->SetTexPos(10.0f, (float)aPosTexU[nCnt][nCntScore]);
		}
	}
}

//�����L���O���̎擾
void CRanking::GetRanking(int Ranking)
{
	m_nRanking = Ranking;
}

//����
CRanking * CRanking::Create()
{
	CRanking *pRanking= new CRanking;

	if (pRanking != nullptr)
	{
		pRanking->Init();
	}

	return pRanking;
}
