
#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "SceneBase.h"


class TitleScene : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Exec();	// 処理を行う
	virtual void Draw();	// 描画を行う

	virtual bool IsEnd()const;	// シーンが終了したかどうかを返す

protected:
	int m_Step;

private:
	void step_LogoIn();
	void step_Input();

	int m_AnimationCounter;
	int m_SpriteNumber;

};

#endif //TITLE_SCENE_H
