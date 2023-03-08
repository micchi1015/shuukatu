//-----------------------------
//
// 当たり判定
// Author：梶田大夢
//
//-----------------------------
#ifndef _COLLISION_H_		//このマクロ定義がされてなかったら
#define _COLLISION_H_		//二重インク―ルード防止のマクロ定義

#include"main.h"

//円の当たり判定クラス
class CColision
{
public:
	CColision();				//コンストラクタ
	~CColision();				//デストラクタ

	//円の当たり判定
	static bool CollisionCircle(D3DXVECTOR3 Pos1, float fRadius1, D3DXVECTOR3 Pos2, float fRadius2);
};
#endif