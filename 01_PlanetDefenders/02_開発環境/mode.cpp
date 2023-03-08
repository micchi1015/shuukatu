//-------------------------
//
//モードの処理[mode.cpp]
//Author:梶田大夢
//
//-------------------------
//---------------------------
//インクルード
//---------------------------
#include "game.h"
#include "result.h"
#include "title.h"
#include "mode.h"

//静的メンバ変数宣言
CTitle *CMode::m_pTitle = nullptr;
CGame *CMode::m_pGame = nullptr;
CResult *CMode::m_pResult = nullptr;

//コンストラクタ
CMode::CMode()
{
	SetType(OBJTYPE_MODE);
}

//デストラクタ
CMode::~CMode()
{
}