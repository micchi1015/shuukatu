//------------------------------
//
// “–‚½‚è”»’è‚Ìˆ—[collision.cpp]
// Author:Š“c‘å–²
//
//------------------------------

//---------------------------
//ƒCƒ“ƒNƒ‹[ƒhƒtƒ@ƒCƒ‹
//---------------------------
#include "collision.h"

//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
CColision::CColision()
{
}

//ƒfƒXƒgƒ‰ƒNƒ^
CColision::~CColision()
{
}

//---------------------------
//‰~‚Ì“–‚½‚è”»’è
//---------------------------
bool CColision::CollisionCircle(D3DXVECTOR3 Pos1, float fRadius1, D3DXVECTOR3 Pos2, float fRadius2)
{
	//‚Q‚±‚Ì•¨‘Ì‚Ì”¼Œa“¯Žm‚Ì˜a
	float fDiff = fRadius1 + fRadius2;

	//ŒvŽZ—p•Ï”
	float fCalculationX, fCalculationY;

	//X‚Ì·•ª
	fCalculationX = Pos1.x - Pos2.x;
	//Y‚Ì·•ª
	fCalculationY = Pos1.y - Pos2.y;

	//Œ»Ý‚Ì‚Q“_‚Ì‹——£
	float fLength = sqrtf(fCalculationX * fCalculationX + fCalculationY * fCalculationY);

	//‚Q‚±‚Ì•¨‘Ì‚Ì”¼Œa“¯Žm‚Ì˜a‚æ‚èŒ»Ý‚Ì‚Q“_‚Ì‹——£‚ª¬‚³‚¢‚©‚Ç‚¤‚©
	if (fDiff >= fLength)
	{
		//“–‚½‚Á‚½
		return true;
	}

	//“–‚½‚Á‚Ä‚È‚¢
	return false;
}