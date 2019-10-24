// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <SDL/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
//#include "Renderer.h"

//Gameクラスのヘッダファイル　関数及びメンバ変数の宣言
class Game
{
public:
	Game();
	bool Initialize();
    //ゲームループのメソッド
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
    int GetHoge(){return hoge;}

	class Renderer* GetRenderer() { return mRenderer; }
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	
	// All the actors in the game
	std::vector<class Actor*> mActors;
    std::vector<class Actor*> mBalls;
    std::vector<class Actor*> mOther_thing;
    
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;

	Uint32 mTicksCount;
	volatile bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;
    
    int hoge = 0;

	// Game-specific code
	class CameraActor* mCameraActor;
};

extern Game *_gameInstance;
//extern Renderer *_rendererInstance;
