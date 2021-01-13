
#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include "SceneBase.h"
#include "InGameScene.h"

class ResultScene : public SceneBase
{
public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Exec();	// 処理を行う
	virtual void Draw();	// 描画を行う

	virtual bool IsEnd()const;	// シーンが終了したかどうかを返す

	int m_MoveCount;

protected:
	int		m_Step;

private:
	// 入力受付
	void step_Input();

	int m_AnimationCounter;
	int m_SpriteNumber;
};

#endif //RESULT_SCENE_H
