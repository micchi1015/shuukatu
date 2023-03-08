//=============================================================================
//
// gamedebug.cpp
// Author : tanimoto kosuke
//
//=============================================================================
#include "gamedebug.h"
#include "input.h"
#include "application.h"
#include "meshfield.h"
#include "object2D.h"
#include "object3D.h"
#include "billboard.h"
#include "model.h"
#include "player.h"
#include "UIString.h"
#include "Letter.h"
//#include "fade.h"
#include "inputKeyboard.h"
#include "debugProc.h"

CMeshfield *CGameDebug::m_pField = nullptr;
CPlayer* CGameDebug::m_pPlayer[PLAYER_MAX] = {};

//=====================================
// デフォルトコンストラクタ
//=====================================
CGameDebug::CGameDebug()
{

}

//=====================================
// デストラクタ
//=====================================
CGameDebug::~CGameDebug()
{

}

//=====================================
// 初期化処理
//=====================================
HRESULT CGameDebug::Init(void)
{
	//CGame::Init();

	// メッシュフィールドの生成
	//m_pField = CMeshfield::Create(D3DXVECTOR3(-1000.0f, -150.0f, 1000.0f), Vec3Null, D3DXVECTOR2(50.0f, 50.0f), 30, 30, 3);
	//m_pField->SetTexture(CObject::TEXTURE_BLOCK);
	//m_pField->SetTextureTiling(0.33f);

	//CObject_2D* pObj2D = CObject_2D::Create();
	//pObj2D->SetPos(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	//pObj2D->SetSize(D3DXVECTOR2(20.0f, 20.0f));
	//pObj2D->SetTexture(CObject::TEXTURE_LETTERS);
	//pObj2D->SetTextureParameter(5, 13, 2, 60);
	//pObj2D->SetAnimPattern(15);
	//pObj2D->SetAnimationBase(15);

	//// オブジェクト3Dの生成
	//CObject_3D* pObj = CObject_3D::Create();
	//pObj->SetPos(D3DXVECTOR3(0.0f, -200.0f, 300.0f));
	//pObj->SetSize(D3DXVECTOR2(100.0f, 100.0f));
	//pObj->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	//pObj->SetStartingRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//pObj->SetTexture(CObject::TEXTURE_BLOCK);
	//pObj->SetTextureParameter(1, 1, 1, INT_MAX);

	// モデルの生成
	//CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, -150.0f));
	//CModel::Create(CModel::MODEL_JEWEL_TEAR, D3DXVECTOR3(0.0f, -100.0f, 150.0f));

	// プレイヤーの生成
	//m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, -100.0f, -100.0f),0);

	// ビルボードの生成
	//CBillboard* pBillboard = CBillboard::Create(D3DXVECTOR3(-150.0f, 0.0f, 300.0f), D3DXVECTOR2(50.0f, 50.0f), 3);
	//pBillboard->SetTexture(CObject::TEXTURE_BLOCK);

	// UIStringの生成
	//CUIString::Create(D3DXVECTOR3(100.0f, 200.0f, 0.0f), D3DXVECTOR2(250.0f, 25.0f), D3DXCOLOR(0.2f, 1.0f, 0.5f, 1.0f), "Sentence A, 125 $%&");

	//CLetter::Create(D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 'r', 5);

	//CLetter::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 4, 5);
	//UI
	//m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 140.0f, 50.0f, 0.0f));

	return S_OK;
}

//=====================================
// 終了処理
//=====================================
void CGameDebug::Uninit(void)
{
	//CGame::Uninit();

	//for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	//{
	//	if (m_pPlayer[nCnt] != nullptr)
	//	{
	//		m_pPlayer[nCnt]->Release();
	//		m_pPlayer[nCnt] = nullptr;
	//	}
	//}
	//
	//if (m_pField != nullptr)
	//{
	//	m_pField->Release();
	//	m_pField = nullptr;
	//}
}

//=====================================
// 更新処理
//=====================================
void CGameDebug::Update(void)
{
	//CGame::Update();
	//CDebugProc::Print("\n[F2] : デバッグモードを終了\n");

	//if (CInputKeyboard::GetKeyboardTrigger(DIK_F2))
	//{//エンターキーを押したら
	//	CApplication::SetMode(CApplication::Mode_Game_Race);
	//}
}

//=====================================
// 生成処理
//=====================================
CGameDebug* CGameDebug::Create(void)
{
	//CGameDebug* pGameDebug = new CGameDebug;

	//if (FAILED(pGameDebug->Init()))
	//{
	//	return nullptr;
	//}

	return S_OK;
}