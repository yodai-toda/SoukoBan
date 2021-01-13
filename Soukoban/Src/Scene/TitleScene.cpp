
#include "TitleScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

// 実行ステップ定義
enum
{
	STEP_LOGO_IN,	// ロゴイン
	STEP_INPUT,		// 入力待ち
	STEP_END,		// シーン終了
};


TitleScene::TitleScene()
{
	m_Step = STEP_LOGO_IN;
	m_AnimationCounter = 0;
	m_SpriteNumber = 0;
}

TitleScene::~TitleScene()
{

}

void TitleScene::Exec()
{
	switch( m_Step )
	{
	case STEP_LOGO_IN:	step_LogoIn();	break;
	case STEP_INPUT:	step_Input();	break;
	default:							break;
	}
}

void TitleScene::Draw()
{
	LoadGraphScreen( 0, 0, "Data/Title.png", FALSE );
	if( m_SpriteNumber == 0 )
	{
		LoadGraphScreen( 0, 20, "Data/White.png", TRUE );
	}
	else if( m_SpriteNumber == 1 )
	{
		LoadGraphScreen( 0, 20, "Data/Black.png", TRUE );
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

bool TitleScene::IsEnd() const
{
	return ( m_Step == STEP_END );
}

void TitleScene::step_LogoIn()
{
	m_Step = STEP_INPUT;
}

void TitleScene::step_Input()
{
	
	InputManager* pInputMng = InputManager::GetInstance();
	if( pInputMng->IsPush( KeyType_Enter ) )
	{
		m_Step = STEP_END;
		SceneManager::GetInstance()->SetNextScene( SceneID_InGame );
	}
}
