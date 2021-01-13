
#include "SceneManager.h"
#include "../Scene/SceneBase.h"
#include "../Scene/TitleScene.h"
#include "../Scene/InGameScene.h"
#include "../Scene/ResultScene.h"

// staticなメンバ変数を初期化
SceneID SceneManager::m_NextSceneID = SceneID_Invalid;
int SceneManager::m_MoveCount = 0;

SceneManager::SceneManager()
	: m_pScene( nullptr )
{
	// 最初に実行するシーンを作成
	SetNextScene( SceneID_Title );
	m_pScene = create_NextScene();
}

SceneManager::~SceneManager()
{
	delete m_pScene;
	m_pScene = nullptr;
}

void SceneManager::Exec()
{
	if( m_pScene == nullptr ) { return; }

	m_pScene->Exec();
	if( m_pScene->IsEnd() )
	{
		m_MoveCount = InGameScene::m_MoveCount;
		delete m_pScene;
		m_pScene = create_NextScene();
	}
}

void SceneManager::Draw()
{
	if( m_pScene == nullptr ) { return; }

	m_pScene->Draw();
}

void SceneManager::SetNextScene( SceneID next_ )
{
	m_NextSceneID = next_;
}

SceneBase* SceneManager::create_NextScene()
{
	SceneBase* next = nullptr;
	switch( m_NextSceneID )
	{
		// 
		// 
	case SceneID_Title:		next = new TitleScene();	break;
	case SceneID_InGame:	next = new InGameScene();	break;
	case SceneID_Result:	next = new ResultScene();	break;
	default:				break;
	}
	return next;
}

