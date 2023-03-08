//------------------------------
//
// オブジェクトの処理[object.cpp]
// Author:梶田大夢
//
//------------------------------
//---------------------------
//インクルード
//---------------------------
#include "object.h"

//---------------------------
//静的メンバ変数宣言
//---------------------------
CObject *CObject::m_apObject[MAX_PRI][MAX_DATA] = {};		//Objectの配列
int CObject::m_nNumAll = 0;									//オブジェクトの数

//コンストラクタ
CObject::CObject(int nPriority /*=3*/)
{
	for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
	{
		if (m_apObject[nPriority][nCnt] == nullptr)
		{
			m_apObject[nPriority][nCnt] = this;

			m_nID = nCnt;
			m_nPriority = nPriority;

			m_nNumAll++;
			break;
		}
	}

	m_type = OBJTYPE_NONE;
}

//デストラクタ
CObject::~CObject()
{
}

//全てのポリゴンの破棄処理
void CObject::ReleaseAll()
{
	for (int nCount = 0; nCount < MAX_PRI; nCount++)
	{
		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			if (m_apObject[nCount][nCnt] != nullptr)
			{
				m_apObject[nCount][nCnt]->Uninit();
			}
		}
	}
}

//更新処理
void CObject::UpdateAll()
{
	for (int nCount = 0; nCount < MAX_PRI; nCount++)
	{
		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			if (m_apObject[nCount][nCnt] != nullptr)
			{
				m_apObject[nCount][nCnt]->Update();
			}
		}
	}
}

//描画処理
void CObject::DrawAll()
{
	for (int nCount = 0; nCount < MAX_PRI; nCount++)
	{
		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			if (m_apObject[nCount][nCnt] != nullptr)
			{
				m_apObject[nCount][nCnt]->Draw();
			}
		}
	}
}

//破棄
void CObject::ReleaseMode()
{
	for (int nCount = 0; nCount < MAX_PRI; nCount++)
	{
		for (int nCnt = 0; nCnt < MAX_DATA; nCnt++)
		{
			if (m_apObject[nCount][nCnt] != nullptr)
			{
				if (m_apObject[nCount][nCnt]->GetType() != OBJTYPE_MODE)
				{
					// 終了
					m_apObject[nCount][nCnt]->Uninit();
				}
			}
		}
	}
}

//破棄処理
void CObject::Release()
{
	if (m_apObject[m_nPriority][m_nID] != nullptr)
	{
		const int nID = m_nID;
		const int nPri = m_nPriority;

		delete m_apObject[nPri][nID];
		m_apObject[nPri][nID] = nullptr;
		m_nNumAll--;
	}
}

//moveの情報取得
D3DXVECTOR3 CObject::GetMove()
{
	return m_move;
}

//moveの設定
void CObject::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//タイプ情報取得
CObject::EObjType CObject::GetType()
{
	return m_type;
}

//タイプの設定
void CObject::SetType(const EObjType type)
{
	m_type = type;
}

//オブジェクトの情報取得
CObject * CObject::GetMyObject(int nPriority,int nCnt)
{
	return m_apObject[nPriority][nCnt];
}

//moveにvec分加算
void CObject::AddMove(D3DXVECTOR3 vec)
{
	m_move += vec;
	SetMove(m_move);

	if (m_move.x <= -10.0f)
	{
		m_move.x = -10.0f;
	}
}

//moveにvec分加算
void CObject::SubMove(D3DXVECTOR3 vec)
{
	m_move -= vec;
	SetMove(m_move);

	if (m_move.x <= -10.0f)
	{
		m_move.x = -10.0f;
	}
}