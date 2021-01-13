﻿
#ifndef SCENE_BASE_H
#define SCENE_BASE_H

// シーン基底クラス
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	// 処理内容は派生クラス毎に違うので、
	// 純粋仮想関数として宣言しておく
	virtual void Exec() = 0;	// 処理を行う
	virtual void Draw() = 0;	// 描画を行う

	virtual bool IsEnd()const = 0;	// シーンが終了したかどうかを返す

protected:
	int		m_Stem;		// 処理内容を管理する変数
};


#endif //SCENE_BASE_H
