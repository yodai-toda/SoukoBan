
#include "ResultScene.h"
#include "DxLib.h"
#include "InGameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

// 実行ステップ定義
enum
{
	STEP_INPUT,		// 入力待ち
	STEP_END,		// シーン終了
};


ResultScene::ResultScene()
{
	m_Step = STEP_INPUT;
	m_MoveCount = SceneManager::m_MoveCount;
	m_AnimationCounter = 0;
	m_SpriteNumber = 0;
}

ResultScene::~ResultScene()
{

}

void ResultScene::Exec()
{
	switch( m_Step )
	{
	case STEP_INPUT: step_Input();	break;
	default:						break;
	}
}

void ResultScene::Draw()
{
	LoadGraphScreen( 0, 0, "Data/Result.png", FALSE );
	DrawFormatString( 50, 200, GetColor( 0, 0, 0 ), "クリア手数：%d", m_MoveCount );
	if( m_SpriteNumber == 0 )
	{
		LoadGraphScreen( 0, 120, "Data/White.png", TRUE );
	}
	else if( m_SpriteNumber == 1 )
	{
		LoadGraphScreen( 0, 120, "Data/Black.png", TRUE );
	}

	m_AnimationCounter++;
	if( m_AnimationCounter >= 24 )
	{
		m_AnimationCounter = 0;
		m_SpriteNumber++;
		if( m_SpriteNumber >= 2 )
		{
			m_SpriteNumber = 0;
		}
	}
}

bool ResultScene::IsEnd() const
{
	return ( m_Step == STEP_END );
}

void ResultScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if( pInputMng->IsPush( KeyType_Enter ) )
	{
		m_Step = STEP_END;
		SceneManager::GetInstance()->SetNextScene( SceneID_Title );
	}
}
