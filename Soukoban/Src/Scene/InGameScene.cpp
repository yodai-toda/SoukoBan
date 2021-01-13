
#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

// 実行ステップ定義
enum
{
	STEP_START_JINGLE,	// スタートジングル
	STEP_INPUT,			// 入力待ち
	STEP_CLEAR_JINGLE,	// クリアジングル	
	STEP_END,			// シーン終了
};

// 倉庫番のサンプルステージ
const int g_SampleStage[STAGE_HEIGHT][STAGE_WIDTH] =
{
	0,0,0,1,1,1,1,1,0,0,0,
	0,0,0,1,3,3,3,1,0,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	1,1,1,1,1,0,1,1,1,1,1,
	1,0,0,4,0,0,1,0,0,0,1,
	1,0,1,0,0,4,0,4,0,0,1,
	1,0,0,0,1,1,1,0,0,0,1,
	1,1,1,0,1,0,1,0,1,1,1,
	0,0,1,0,1,0,1,0,1,0,0,
	0,0,1,0,0,0,0,0,1,0,0,
	0,0,1,0,0,2,0,0,1,0,0,
	0,0,1,1,1,0,1,1,1,0,0,
};

// staticなメンバ変数を初期化
int InGameScene::m_MoveCount = 0;

InGameScene::InGameScene()
	: m_PlayerX( 0 )
	, m_PlayerY( 0 )
{
	Reset();
	Load();
	m_AnimationCounter = 0;
	m_SpriteNumber = 0;
	m_Step = STEP_START_JINGLE;
}

InGameScene::~InGameScene()
{
	InitGraph();
}

void InGameScene::Exec()
{
	switch( m_Step )
	{
	case STEP_START_JINGLE:	step_StartJingle();	break;
	case STEP_INPUT:		step_Input();		break;
	case STEP_CLEAR_JINGLE:	step_ClearJingle();	break;
	default:									break;
	}
}

void InGameScene::Draw()
{
	// ステージの中身と、プレイヤーを描画
	for( int y = 0; y < STAGE_HEIGHT; y++ )
	{
		for( int x = 0; x < STAGE_WIDTH; x++ )
		{
			switch( m_StageData[y][x] )
			{
			case ObjectType_Ground: DrawGraph( x * CHIP_WIDTH, y * CHIP_HEIGHT, m_Graph[16], TRUE );		break;
			case ObjectType_Wall: DrawGraph( x * CHIP_WIDTH, y * CHIP_HEIGHT, m_Graph[15], TRUE );			break;
			case ObjectType_Target:DrawGraph( x * CHIP_WIDTH, y * CHIP_HEIGHT, m_Graph[12], TRUE );			break;
			case ObjectType_UnsetCrate: DrawGraph( x * CHIP_WIDTH, y * CHIP_HEIGHT, m_Graph[14], TRUE );	break;
			case ObjectType_SetCrate:	DrawGraph( x * CHIP_WIDTH, y * CHIP_HEIGHT, m_Graph[13], TRUE );	break;
			}
		}
	}

	// プレイヤーの位置を表示
	switch( m_Dir )
	{
	case DirType_Up:	
		if( m_SpriteNumber == 0 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[0], TRUE );
		}
		else if( m_SpriteNumber == 1 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[1], TRUE );
		}
		else if( m_SpriteNumber == 2 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[2], TRUE );
		}
		break;
	case DirType_Down:	
		if( m_SpriteNumber == 0 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[3], TRUE );
		}
		else if( m_SpriteNumber == 1 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[4], TRUE );
		}
		else if( m_SpriteNumber == 2 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[5], TRUE );
		}
		break;
	case DirType_Left:	
		if( m_SpriteNumber == 0 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[6], TRUE );
		}
		else if( m_SpriteNumber == 1 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[7], TRUE );
		}
		else if( m_SpriteNumber == 2 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[8], TRUE );
		}
		break;
	case DirType_Right:	
		if( m_SpriteNumber == 0 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[9], TRUE );
		}
		else if( m_SpriteNumber == 1 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[10], TRUE );
		}
		else if( m_SpriteNumber == 2 )
		{
			DrawGraph( m_PlayerX * CHIP_WIDTH, m_PlayerY * CHIP_HEIGHT, m_Graph[11], TRUE );
		}
		break;
	}
	
	m_AnimationCounter++;
	if( m_AnimationCounter >= 12 )
	{
		m_AnimationCounter = 0;
		m_SpriteNumber++;
		if( m_SpriteNumber >= 3 )
		{
			m_SpriteNumber = 0;
		}
	}

	if( IsClear() == true )
	{
		DrawGraph( 15, 50, m_Graph[17], TRUE );
	}
}

bool InGameScene::IsEnd() const
{
	return ( m_Step == STEP_END );
}

void InGameScene::step_StartJingle()
{
	m_Step = STEP_INPUT;
}

void InGameScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if( pInputMng->IsPush( KeyType_Reset ) )
	{
		Reset();
	}
	else if( pInputMng->IsPush( KeyType_Up ) )
	{
		Move( DirType_Up );
	}
	else if( pInputMng->IsPush( KeyType_Down ) )
	{
		Move( DirType_Down );
	}
	else if( pInputMng->IsPush( KeyType_Left ) )
	{
		Move( DirType_Left );
	}
	else if( pInputMng->IsPush( KeyType_Right ) )
	{
		Move( DirType_Right );
	}

	if( IsClear() == true )
	{
		SceneManager::m_MoveCount = m_MoveCount;
		m_Step = STEP_CLEAR_JINGLE;
	}
}

void InGameScene::step_ClearJingle()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if( pInputMng->IsPush( KeyType_Enter ) )
	{
		m_Step = STEP_END;
		SceneManager::GetInstance()->SetNextScene( SceneID_Result );
	}
}

// ゲームのクリア判定
// true  = クリアしている
// false = 未クリア
bool InGameScene::IsClear() const
{
	for( int y = 0; y < STAGE_HEIGHT; y++ )
	{
		for( int x = 0; x < STAGE_WIDTH; x++ )
		{
			if( m_StageData[y][x] == ObjectType_UnsetCrate )
			{
				return false;
			}
		}
	}

	return true;
}

// 初期化状態にリセット
void InGameScene::Reset()
{
	// ステージデータを初期化
	/*
		g_SampleStageの中身を
		m_StageDataへコピー(読み込み)する
		この時、配列の中身が、objectType_Player だったら、
		その時のx,yをm_PlayerX(Y)へ代入し、m_StageDataへは、ObjctType_Ground を代入する
	*/

	for( int y = 0; y < STAGE_HEIGHT; y++ )
	{
		for( int x = 0; x < STAGE_WIDTH; x++ )
		{
			m_StageData[y][x] = g_SampleStage[y][x];
			if( m_StageData[y][x] == ObjectType_Player )
			{
				m_PlayerX = x;
				m_PlayerY = y;
				m_StageData[y][x] = ObjectType_Ground;
			}
		}
	}
	m_Dir = DirType_Up;
	m_MoveCount = 0;
}
void InGameScene::Load()
{
	for( int i = 0; i < GRAPH_MAX; i++ )
	{
		switch( i )
		{
		case 0:		m_Graph[i] = { LoadGraph( "Data/Player/player_00.png" ) };	break;
		case 1:		m_Graph[i] = { LoadGraph( "Data/Player/player_01.png" ) };	break;
		case 2:		m_Graph[i] = { LoadGraph( "Data/Player/player_02.png" ) };	break;
		case 3:		m_Graph[i] = { LoadGraph( "Data/Player/player_03.png" ) };	break;
		case 4:		m_Graph[i] = { LoadGraph( "Data/Player/player_04.png" ) };	break;
		case 5:		m_Graph[i] = { LoadGraph( "Data/Player/player_05.png" ) };	break;
		case 6:		m_Graph[i] = { LoadGraph( "Data/Player/player_06.png" ) };	break;
		case 7:		m_Graph[i] = { LoadGraph( "Data/Player/player_07.png" ) };	break;
		case 8:		m_Graph[i] = { LoadGraph( "Data/Player/player_08.png" ) };	break;
		case 9:		m_Graph[i] = { LoadGraph( "Data/Player/player_09.png" ) };	break;
		case 10:	m_Graph[i] = { LoadGraph( "Data/Player/player_10.png" ) };	break;
		case 11:	m_Graph[i] = { LoadGraph( "Data/Player/player_11.png" ) };	break;
		case 12:	m_Graph[i] = { LoadGraph( "Data/Crate/crate_00.png" ) };	break;
		case 13:	m_Graph[i] = { LoadGraph( "Data/Crate/crate_01.png" ) };	break;
		case 14:	m_Graph[i] = { LoadGraph( "Data/Crate/crate_02.png" ) };	break;
		case 15:	m_Graph[i] = { LoadGraph( "Data/Ground/block.png" ) };		break;
		case 16:	m_Graph[i] = { LoadGraph( "Data/Ground/ground.png" )};		break;
		case 17:	m_Graph[i] = { LoadGraph( "Data/Clear.png" )};				break;
		}
	}
}
// 移動処理
void InGameScene::Move( DirType dir_ )
{
	// DirTupeが範囲外だったら処理終了
	if( dir_ < DirType_Up && dir_ >= DirType_Max )
	{
		return;
	}

	// 判定用の一時変数
	int next_x  = m_PlayerX;	//次の移動先X
	int next_y  = m_PlayerY;	//次の移動先Y
	int next2_x  = m_PlayerX;	//次の次X
	int next2_y  = m_PlayerY;	//次の次Y

	// 移動方向に応じて座標を設定
	// next_x(y),next2_(y)の値をそれぞれ設定する
	switch( dir_ )
	{
	case DirType_Up:
		next_y -= 1;
		next2_y -= 2;
		m_Dir = DirType_Up;
		break;
	case DirType_Down:
		next_y += 1;
		next2_y += 2;
		m_Dir = DirType_Down;
		break;
	case DirType_Left:
		next_x -= 1;
		next2_x -= 2;
		m_Dir = DirType_Left;
		break;
	case DirType_Right:
		next_x += 1;
		next2_x += 2;
		m_Dir = DirType_Right;
		break;

	}

	// 移動先が画面外なら、関数を抜ける
	if( next_x < 0 ||
		next_y < 0 || 
		next_x >= ( STAGE_WIDTH ) || 
		next_y >= ( STAGE_HEIGHT ) )
	{
		return;
	}

	// 通常移動
	if( m_StageData[next_y][next_x] == ObjectType_Ground ||
		m_StageData[next_y][next_x] == ObjectType_Target )
	{ 
		m_PlayerX = next_x;
		m_PlayerY = next_y;
		m_MoveCount++;
	}
	// 移動先に箱(クレート)がある場合
	else if( m_StageData[next_y][next_x] == ObjectType_UnsetCrate ||
		m_StageData[next_y][next_x] == ObjectType_SetCrate )
	{
		// 2つ先が画面外かチェック
		if( next2_x < 0 ||
			next2_y < 0 ||
			next2_x >= ( STAGE_WIDTH ) ||
			next2_y >= ( STAGE_HEIGHT ) )
		{
			return;
		}

		if( m_StageData[next2_y][next2_x] != ObjectType_Ground &&
			m_StageData[next2_y][next2_x] != ObjectType_Target )
		{
			return;
		}
		if( m_StageData[next_y][next_x] == ObjectType_UnsetCrate )
		{
			m_StageData[next_y][next_x] = ObjectType_Ground;
		}
		else
		{
			m_StageData[next_y][next_x] = ObjectType_Target;
		}

		// 2つ先に箱を配置する
		if( m_StageData[next2_y][next2_x] == ObjectType_Ground )
		{
			m_StageData[next2_y][next2_x] = ObjectType_UnsetCrate;
		}
		else
		{
			m_StageData[next2_y][next2_x] = ObjectType_SetCrate;
		}

		// プレイヤーを移動させる
		m_PlayerX = next_x;
		m_PlayerY = next_y;

		m_MoveCount++;
	}
}

int InGameScene::GetMoveCount() const
{
	return m_MoveCount; 
}
