//=============================================================================
//
// object2D.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"
#include "rendering.h"
#include "application.h"

//�ÓI�����o�[�ϐ��̐錾
LPDIRECT3DTEXTURE9 CObject_2D::m_pTextureAll[CObject_2D::TEXTURE_TYPE_MAX] = {};

char* CObject_2D::m_paTextPass[CObject::TEXTURE_TYPE_MAX] =
{
	" ",													//TextureNull

	"data\\TEXTURE\\Block.png",								//TEXTURE_BLOCK,
	"data\\TEXTURE\\sky002.jpg",							//TEXTURE_SKY,
	"data\\TEXTURE\\89_m.jpg",								//TEXTURE_GRASS,
	"data\\TEXTURE\\MeshField001.png",						//TEXTURE_ROCK,
	"data\\TEXTURE\\MagmaArea.png",							//TEXTURE_MAGMA,
	"data\\TEXTURE\\snow.png",								//TEXTURE_SNOW,
	"data\\TEXTURE\\snowarea.png",							//TEXTURE_SNOW_AREA,
	"data\\TEXTURE\\Characters.png",						//TEXTURE_CHARACTERS,
	"data\\TEXTURE\\Alphabet.png",							//TEXTURE_LETTERS,
	"data\\TEXTURE\\Numbers.png",							//TEXTURE_NUMBERS,
	"data\\TEXTURE\\Japanese2000unicode.png",				//TEXTURE_JAPANESE,
	"data\\TEXTURE\\sele.png",								//TEXTURE_CHARASET_FRAM,
	"data\\TEXTURE\\UI_Debug_Start.png",					//TEXTURE_MESSAGE_START,
	"data\\TEXTURE\\UI_Debug_Goal.png",						//TEXTURE_MESSAGE_GOAL,
	"data\\TEXTURE\\UI_PlayerNumber_1P.png",				//TEXTURE_1P_WIN,
	"data\\TEXTURE\\UI_PlayerNumber_2P.png",				//TEXTURE_2P_WIN,
	"data\\TEXTURE\\UI_PlayerNumber_3P.png",				//TEXTURE_3P_WIN,
	"data\\TEXTURE\\UI_PlayerNumber_4P.png",				//TEXTURE_4P_WIN,
	"data\\TEXTURE\\UI_GameResult_Win.png",					//TEXTURE_WINNER,
	"data\\TEXTURE\\UI_GameResult_Draw.png",				//TEXTURE_DRAW,
	"data\\TEXTURE\\Frame.png",								//TEXTURE_SELECT_FRAME,
	"data\\TEXTURE\\Lava.jpg",								//TEXTURE_LAVA,
	"data\\TEXTURE\\ice.png",								//TEXTURE_ICE,
	"data\\TEXTURE\\se.png",								//TEXTURE_BACKGROUND,
	"data\\TEXTURE\\Particle02.png",						//TEXTURE_PARTICLE_EFFECT,
	"data\\TEXTURE\\StageSelect\\stage01.png",				//TEXTURE_STAGESEL01,
	"data\\TEXTURE\\StageSelect\\stage02.png",				//TEXTURE_STAGESEL02,
	"data\\TEXTURE\\StageSelect\\stage03.png",				//TEXTURE_STAGESEL03,
	"data\\TEXTURE\\StageSelect\\stageR.png",				//TEXTURE_STAGESELR,
	"data\\TEXTURE\\UI_OK.png",								//TEXTURE_OK_UI,
	"data\\TEXTURE\\UI_TitleLogo.png",						//TEXTURE_TITLE_UI,
	"data\\TEXTURE\\unve.png",								//TEXTURE_STAGE_SELECT_BG,
	"data\\TEXTURE\\ButtonPress.png",						//TEXTURE_BUTTON_SELECT_UI,
	"data\\TEXTURE\\TutorialMove.png",						//TEXTURE_TUTORIAL_MOVE,
	"data\\TEXTURE\\TutorialButton.png",					//TEXTURE_TUTORIAL_BUTTON,
	"data\\TEXTURE\\PlayerSelCtrl.png",						//TEXTURE_PLAYER_SEL_CTRL,
};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CObject_2D::CObject_2D()
{
	//�����o�[�ϐ����N���A����
	m_pVtxBuff = nullptr;								//���_�o�b�t�@
	m_size = D3DXVECTOR2(0.0f, 0.0f);					//�|���S���̕��ƍ���
	m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�|���S���̌���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ���
	m_acc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_fRot = 0.0f;										//�|���S���̉�]�p�x
	m_fAngle = 0.0f;									//�|���S���̉�]�p�̊p�x
	m_fFrameRot = 0.0f;									//1�t���[���̉�]�p�x
	m_revolutionCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���]�̒��S�_
	m_fRevolutionSpeed = 0.0f;							//���]�̃X�s�[�h
	m_fRevolutionAngle = 0.0f;							//���]�̌��݊p�x
	m_fRevolutionRadius = 0.0f;							//���]�̔��a
	m_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�|���S���̈ʒu
	m_nCountAnim = 0;									//���݂̃e�N�X�`���p�^�[��
	m_nAnimPattern = 0;									//�A�j���[�V�����J�E���^�[
	m_nMaxTexPattern = 0;								//�e�N�X�`���̃p�^�[����
	m_nMaxTexColumn = 0;								//�e�N�X�`���̍s��
	m_nTexLine = 0;										//�e�N�X�`���̗�
	m_nFirstPattern = 0;								//�ŏ��̃A�j���[�V�����p�^�[��
	m_nAnimFrame = 0;									//�A�j���[�V�����p�^�[���̕ύX�t���[����
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);		//�e�N�X�`���̈ړ���
	m_textureAnimSpeed = Vec2Null;						//�e�N�X�`���̈ړ����x
	m_bFlipX = false;									//�e�N�X�`����X���W�����]���Ă��邩�ǂ���
	m_bFlipY = false;									//�e�N�X�`����Y���W�����]���Ă��邩�ǂ���
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			//���_�J�[���[
	m_textType = CObject::TEXTURE_TYPE_MAX;				//�e�N�X�`���̎��

	//���_�J���[
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}	

CObject_2D::CObject_2D(const int nPriority) : CObject::CObject(nPriority)
{
	//�����o�[�ϐ����N���A����
	m_pVtxBuff = nullptr;								//���_�o�b�t�@
	m_size = D3DXVECTOR2(0.0f, 0.0f);					//�|���S���̕��ƍ���
	m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�|���S���̌���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ���
	m_acc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_fRot = 0.0f;										//�|���S���̉�]�p�x
	m_fAngle = 0.0f;									//�|���S���̉�]�p�̊p�x
	m_fFrameRot = 0.0f;									//1�t���[���̉�]�p�x
	m_revolutionCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���]�̒��S�_
	m_fRevolutionSpeed = 0.0f;							//���]�̃X�s�[�h
	m_fRevolutionAngle = 0.0f;							//���]�̌��݊p�x
	m_fRevolutionRadius = 0.0f;							//���]�̔��a
	m_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�|���S���̈ʒu
	m_nCountAnim = 0;									//���݂̃e�N�X�`���p�^�[��
	m_nAnimPattern = 0;									//�A�j���[�V�����J�E���^�[
	m_nMaxTexPattern = 0;								//�e�N�X�`���̃p�^�[����
	m_nMaxTexColumn = 0;								//�e�N�X�`���̍s��
	m_nTexLine = 0;										//�e�N�X�`���̗�
	m_nFirstPattern = 0;								//�ŏ��̃A�j���[�V�����p�^�[��
	m_nAnimFrame = 0;									//�A�j���[�V�����p�^�[���̕ύX�t���[����
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);		//�e�N�X�`���̈ړ���
	m_textureAnimSpeed = Vec2Null;						//�e�N�X�`���̈ړ����x
	m_bFlipX = false;									//�e�N�X�`����X���W�����]���Ă��邩�ǂ���
	m_bFlipY = false;									//�e�N�X�`����Y���W�����]���Ă��邩�ǂ���
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);			//���_�J���[
	m_textType = CObject::TEXTURE_TYPE_MAX;				//�e�N�X�`���̎��

	//���_�J���[
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CObject_2D::~CObject_2D()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CObject_2D::Init(void)
{
	//����������
	CRenderer* Render = CApplication::GetRenderer();			//�����f�B���O�C���X�^���X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();			//�f�o�C�X�̎擾����

	m_size = D3DXVECTOR2(0.0f, 0.0f);							//�|���S���̕��ƍ����̐ݒ�
	m_dir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);						//�|���S���̌���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�ړ���
	m_acc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//����
	m_fRot = 0.0f;												//��]�p�x�̐ݒ�
	m_fAngle = 0.0f;											//��]�p�̊p�x���v�Z����
	m_fFrameRot = 0.0f;											//1�t���[���̉�]�p�x
	m_revolutionCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���]�̒��S�_
	m_fRevolutionSpeed = 0.0f;									//���]�̃X�s�[�h
	m_fRevolutionAngle = 0.0f;									//���]�̌��݊p�x
	m_fRevolutionRadius = 0.0f;									//���]�̔��a
	m_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu�̐ݒ�
	m_nCountAnim = 0;											//���݂̃e�N�X�`���p�^�[��
	m_nAnimPattern = 0;											//�A�j���[�V�����J�E���^�[
	m_nMaxTexPattern = 1;										//�e�N�X�`���̃p�^�[����
	m_nMaxTexColumn = 1;										//�e�N�X�`���̍s��
	m_nTexLine = 1;												//�e�N�X�`���̗�
	m_nFirstPattern = 0;										//�ŏ��̃A�j���[�V�����p�^�[��
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);				//�e�N�X�`���̈ړ���
	m_textureAnimSpeed = Vec2Null;								//�e�N�X�`���̈ړ����x
	m_bFlipX = false;											//�e�N�X�`����X���W�����]���Ă��邩�ǂ���
	m_bFlipY = false;											//�e�N�X�`����Y���W�����]���Ă��邩�ǂ���
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);					//�|���S���̃J���[
	m_nAnimFrame = 0;											//�A�j���[�V�����p�^�[���̕ύX�t���[����

	//���_�J���[
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx = nullptr;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = (m_posPolygon.x) + sinf(m_fRot + (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (m_size.x);
	pVtx[0].pos.y = (m_posPolygon.y) + cosf(m_fRot + (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (m_size.x);
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = (m_posPolygon.x) + sinf(m_fRot + m_fAngle) * (m_size.x);
	pVtx[1].pos.y = (m_posPolygon.y) + cosf(m_fRot + m_fAngle) * (m_size.x);
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = (m_posPolygon.x) + sinf(m_fRot - (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (m_size.x);
	pVtx[2].pos.y = (m_posPolygon.y) + cosf(m_fRot - (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (m_size.x);
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = (m_posPolygon.x) + sinf(m_fRot - m_fAngle) * (m_size.x);
	pVtx[3].pos.y = (m_posPolygon.y) + cosf(m_fRot - m_fAngle) * (m_size.x);
	pVtx[3].pos.z = 0.0f;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		// rhw�̐ݒ�
		pVtx[nCnt].rhw = 1.0f;
		// ���_�J���[�̐ݒ�
		pVtx[nCnt].col = m_col;
	}

	SetTexture(TEXTURE_NULL);					//�e�N�X�`���̐ݒ�
	SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CObject_2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CObject_2D::Update()
{
	VERTEX_2D* pVtx = nullptr;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nCountAnim++;								//�A�j���[�V�����J�E���^�[�̍X�V

	if (m_nCountAnim >= m_nAnimFrame)
	{
		m_nCountAnim = 0;						//�A�j���[�V�����J�E���^�[��0�ɖ߂�
		m_nAnimPattern++;						//�A�j���[�V�����p�^�[���̍X�V

		if (m_nAnimPattern >= m_nFirstPattern + m_nMaxTexPattern)
		{//�A�j���[�V�����̍Ō�̃p�^�[���𒴂����ꍇ
			m_nAnimPattern = m_nFirstPattern;					//�A�j���[�V�����p�^�[����߂�
		}
	}

	if (m_fRevolutionRadius != 0.0f)
	{//���]���x��0�ł͂Ȃ�������
		m_revolutionCenter += GetMove();			//���S�_���W�̍X�V

		//�ʒu�̍X�V
		m_posPolygon.x = m_revolutionCenter.x + (cosf(m_fRevolutionAngle) * (m_fRevolutionRadius));
		m_posPolygon.y = m_revolutionCenter.y + (sinf(m_fRevolutionAngle) * (m_fRevolutionRadius));
	}

	float dim = sqrtf((m_size.x * m_size.x) + (m_size.y * m_size.y));

	//���_���W�̍X�V
	pVtx[0].pos.x = (m_posPolygon.x) + sinf(D3DX_PI * 0.5f + m_fRot + (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (dim);
	pVtx[0].pos.y = (m_posPolygon.y) + cosf(D3DX_PI * 0.5f + m_fRot + (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (dim);
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = (m_posPolygon.x) + sinf(D3DX_PI * 0.5f + m_fRot + m_fAngle) * (dim);
	pVtx[1].pos.y = (m_posPolygon.y) + cosf(D3DX_PI * 0.5f + m_fRot + m_fAngle) * (dim);
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = (m_posPolygon.x) + sinf(D3DX_PI * 0.5f + m_fRot - (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (dim);
	pVtx[2].pos.y = (m_posPolygon.y) + cosf(D3DX_PI * 0.5f + m_fRot - (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (dim);
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = (m_posPolygon.x) + sinf(D3DX_PI * 0.5f + m_fRot - m_fAngle) * (dim);
	pVtx[3].pos.y = (m_posPolygon.y) + cosf(D3DX_PI * 0.5f + m_fRot - m_fAngle) * (dim);
	pVtx[3].pos.z = 0.0f;

	m_fRevolutionAngle += m_fRevolutionSpeed;

	if (m_textureAnimSpeed != Vec2Null)
	{
		m_textureTranslation += m_textureAnimSpeed;
	}

	UpdateTexture();				//�e�N�X�`���̍X�V

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_posPolygon += m_move;
	m_move += m_acc;

	//��]�p�x�̍X�V
	m_fRot += m_fFrameRot;
	if (m_fRot >= D3DX_PI * 2.0f)
	{
		m_fRot -= D3DX_PI * 2.0f;
	}
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CObject_2D::Draw()
{
	CRenderer* Render = CApplication::GetRenderer();							//�����f�B���O�C���X�^���X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();							//�f�o�C�X�̎擾����

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureAll[m_textType]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
}

//=============================================================================
//�ʒu�̐ݒ菈��
//=============================================================================
void CObject_2D::SetPos(const D3DXVECTOR3 pos)
{
	m_posPolygon = pos;
}

//�|���S���̕��ƍ����̐ݒ菈��
void CObject_2D::SetSize(const D3DXVECTOR2 dim)
{
	m_size = dim;
	m_fAngle = atan2f(m_size.y, m_size.x);
}

//�|���S���̕��ƍ����̐ݒ菈��
void CObject_2D::SetSize(const float x, const float y)
{
	m_size.x = x;
	m_size.y = y;
	m_fAngle = atan2f(m_size.y, m_size.x);
}

//���x�̎擾����
const D3DXVECTOR3 CObject_2D::GetMove(void)
{
	return m_move;
}

//���x�̐ݒ菈��
void CObject_2D::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//�����̎擾����
const D3DXVECTOR3 CObject_2D::GetAcceleration(void)
{
	return m_acc;
}

//�����̐ݒ菈��
void CObject_2D::SetAcceleration(const D3DXVECTOR3 acc)
{
	m_acc = acc;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CObject_2D::GetSize(void)
{
	return m_size;
}

//��]�̐ݒ菈��
void CObject_2D::SetRotation(const float fFrameRot)
{
	m_fFrameRot = fFrameRot;
}

//��]���x�̉��Z����
void CObject_2D::AddAngularSpeed(const float fSpeed)
{
	m_fFrameRot += fSpeed;
}

//��]���x�̎擾����
const float CObject_2D::GetAngularSpeed(void)
{
	return m_fFrameRot;
}

//��]�p�x�̏����l�̎擾����
void CObject_2D::SetStartingRot(const float fStartRot)
{
	m_fRot = fStartRot;
}

//��]�p�x�̎擾���� 
const float CObject_2D::GetRot(void)
{
	return m_fRot;
}

//���]�̐ݒ菈��
void CObject_2D::SetRevolution(const D3DXVECTOR3 Center,
	const float fAngularSpeed, const float fRadius)
{
	m_revolutionCenter = Center;
	m_fRevolutionSpeed = fAngularSpeed;
	m_fRevolutionRadius = fRadius;
}

//���]�̒��S�_�̐ݒ菈��
void CObject_2D::SetRevolutionCenter(const D3DXVECTOR3 Center)
{
	m_revolutionCenter = Center;
}

void CObject_2D::SetPresentRevolutionAngle(const float fAngle)
{
	m_fRevolutionAngle = fAngle;
}

//���]�̒��S�_�̎擾����
const D3DXVECTOR3 CObject_2D::GetRevolutionCenter(void)
{
	return m_revolutionCenter;
}

void CObject_2D::AddRevolutionSpeed(const float fSpeed)
{
	m_fRevolutionSpeed += fSpeed;
}

//�I�u�W�F�N�g�̈ʒu�擾����
const D3DXVECTOR3 CObject_2D::GetPos(void)
{
	return m_posPolygon;
}

//�e�N�X�`���A�j���[�V�����p�̃p�����[�^�ݒ菈��
void CObject_2D::SetTextureParameter(const int MaxPattern, const int LinePattern, const int ColumnPattern, const int nAnimFrame)
{
	m_nMaxTexColumn = ColumnPattern;				//�s���̐ݒ�
	m_nTexLine = LinePattern;						//�񐔂̐ݒ�
	m_nMaxTexPattern = MaxPattern;					//�A�j���[�V�����p�^�[���̍ő吔�̐ݒ�
	m_nAnimFrame = nAnimFrame;						//�A�j���[�V�����t���[�����̐ݒ�

	VERTEX_2D* pVtx = nullptr;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	UpdateTexture();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//���݂̃A�j���[�V�����p�^�[���̎擾����
const int CObject_2D::GetPresentAnimPattern(void)
{
	return m_nAnimPattern;				//�A�j���[�V�����p�^�[����Ԃ�
}

void CObject_2D::SetAnimPattern(const int PatternNum)
{
	m_nAnimPattern = PatternNum;
}

void CObject_2D::SetAnimationBase(const int FirstPattern)
{
	m_nFirstPattern = FirstPattern;
}

void CObject_2D::MoveTexCoordinates(const D3DXVECTOR2 move)
{
	m_textureAnimSpeed = move;
}

bool CObject_2D::GetFlipX(void)
{
	return m_bFlipX;
}

void CObject_2D::FlipX(void)
{
	m_bFlipX = !m_bFlipX;

	VERTEX_2D* pVtx = nullptr;
	VERTEX_2D Vtx;

	ZeroMemory(&Vtx, sizeof(VERTEX_2D));

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	Vtx.tex = pVtx[0].tex;
	pVtx[0].tex = pVtx[1].tex;
	pVtx[1].tex = Vtx.tex;
	Vtx.tex = pVtx[2].tex;
	pVtx[2].tex = pVtx[3].tex;
	pVtx[3].tex = Vtx.tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject_2D::FlipY(void)
{
	m_bFlipY = !m_bFlipY;

	VERTEX_2D* pVtx = nullptr;
	VERTEX_2D Vtx;

	ZeroMemory(&Vtx, sizeof(VERTEX_2D));

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	Vtx.tex = pVtx[0].tex;
	pVtx[0].tex = pVtx[2].tex;
	pVtx[2].tex = Vtx.tex;
	Vtx.tex = pVtx[1].tex;
	pVtx[1].tex = pVtx[3].tex;
	pVtx[3].tex = Vtx.tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//�J�[���[�̎擾����
const D3DXCOLOR CObject_2D::GetColor(void)
{
	return m_col;
}

//�J�[���[�̐ݒ菈��
void CObject_2D::SetColor(const D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//���_�o�b�t�@�̎擾����
	VERTEX_2D* pVtx = nullptr;								//���_���ւ̃|�C���^

	m_col = col;											//�J�[���[�̐ݒ�

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = col;
	}

															//���_�o�b�t�@�̃��b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//���_�P�̃J�[���[�ݒ菈��
void CObject_2D::SetVtxColor(const int nVtxIdx, const D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//���_�o�b�t�@�̎擾����
	VERTEX_2D* pVtx = nullptr;								//���_���ւ̃|�C���^

	m_VtxCol[nVtxIdx] = col;

	//���_�o�b�t�@�̃��b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[nVtxIdx].col = m_VtxCol[nVtxIdx];

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//�e�N�X�`���̎�ނ̐ݒ菈��
void CObject_2D::SetTexture(TextType textType)
{
	m_textType = textType;				//�e�N�X�`���̎�ނ̐ݒ�
}

//���_�o�b�t�@�̎擾����
LPDIRECT3DVERTEXBUFFER9 CObject_2D::GetVtxbuff(void)
{
	return m_pVtxBuff;
}

//�e�N�X�`���S���̃��[�h����
void CObject_2D::LoadTextures(void)
{
	CRenderer* Render = CApplication::GetRenderer();			//�����f�B���O�C���X�^���X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();			//�f�o�C�X�̎擾����

	for (int nCnt = 0; nCnt < TEXTURE_TYPE_MAX; nCnt++)
	{
		if (m_pTextureAll[nCnt] != nullptr)
		{//�|�C���^��null�`�F�b�N
			m_pTextureAll[nCnt]->Release();
			m_pTextureAll[nCnt] = nullptr;
		}

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			m_paTextPass[nCnt],
			&m_pTextureAll[nCnt]);
	}
}

//�e�N�X�`���S���̔j������
void CObject_2D::DestroyLoadedTextures(void)
{
	for (int nCnt = 0; nCnt < TEXTURE_TYPE_MAX; nCnt++)
	{
		if (m_pTextureAll[nCnt] != nullptr)
		{
			m_pTextureAll[nCnt]->Release();
			m_pTextureAll[nCnt] = nullptr;
		}
	}
}

//�e�N�X�`���̎擾����
LPDIRECT3DTEXTURE9 CObject_2D::GetTexturePointer(CObject::TextType type)
{
	return m_pTextureAll[type];
}

//��������
CObject_2D* CObject_2D::Create(void)
{
	CObject_2D* pObj2D = nullptr;

	pObj2D = new CObject_2D;

	if (FAILED(pObj2D->Init()))
	{
		if (pObj2D != nullptr)
		{
			delete pObj2D;
			pObj2D = nullptr;
		}

		return nullptr;
	}

	return pObj2D;
}


void CObject_2D::UpdateTexture(void)
{
	VERTEX_2D* pVtx = nullptr;					//���_���ւ̃|�C���^

												//���_�o�b�t�@�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fX = 1.0f / m_nTexLine;
	float fY = 1.0f / m_nMaxTexColumn;

	if (!m_bFlipX && !m_bFlipY)
	{
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	else if(m_bFlipX && !m_bFlipY)
	{
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	else if (!m_bFlipX && m_bFlipY)
	{
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	else
	{
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}