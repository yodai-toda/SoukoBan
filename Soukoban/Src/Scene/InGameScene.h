
#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

// 継承する、基底クラスのヘッダー
#include "SceneBase.h"
// 定義ヘッダー
#include "../Definition.h"

const int GRAPH_MAX = 18;

class InGameScene : public SceneBase
{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Exec();	// 処理を行う
	virtual void Draw();	// 描画を行う

	virtual bool IsEnd()const;	// シーンが終了したかどうかを返す

protected:
	int		m_Step;

private:
	// スタートジングル待ち
	void step_StartJingle();
	// 入力待ち
	void step_Input();
	// クリアジングル待ち
	void step_ClearJingle();

// 倉庫番に関する関数群
private:
	// ゲームのクリア判定
	bool IsClear() const;
	// 初期化状態にリセット
	void Reset();
	// 画像をロード
	void Load();
	// 移動処理
	void Move( DirType dir_ );
	
public:
	// クリア手数の取得
	int GetMoveCount() const;

private:
	int m_StageData[STAGE_HEIGHT][STAGE_WIDTH];
	int m_PlayerX;	// 配列上のX
	int m_PlayerY;	// 配列上のY
	int m_Dir;		// 方向
	int m_SpriteNumber;		// 描画する画像の番号
	int m_AnimationCounter;	// アニメーションの切り替えカウント
	
	int m_Graph[GRAPH_MAX];	// 画像の配列
	
public:
	static int m_MoveCount;	// 移動数

	
};

#endif //IN_GAME_SCENE_H
