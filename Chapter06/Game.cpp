// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include <algorithm>
#include "Renderer.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "CameraActor.h"
#include "PlaneActor.h"
#include "Block.hpp"
#include "Ball.hpp"
#include "Grid_obj.hpp"
#include "Bar.hpp"

Game *_gameInstance = nullptr;
Renderer *_rendererInstance = nullptr;

Game::Game():
mRenderer(nullptr)
,mIsRunning(true)
,mUpdatingActors(false)
{
    _gameInstance = this;
//    _rendererInstance = new Renderer(this);
}



bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create the renderer
	mRenderer = new Renderer(this);
//    _rendererInstance = new Renderer(this);
	if (!mRenderer->Initialize(1024.0f, 768.0f))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
        //シャットダウン判定
		ProcessInput();
        //ゲームアップデート
		UpdateGame();
        //レンダーラー　画面表示
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
                //シャットダウン
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
    //経過時間まで待つ
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    //経過時間ゲット
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    //処理が重くなり時間が経ち過ぎを防ぐ
	if (deltaTime > 0.05f){
		deltaTime = 0.05f;
	}
    //前フレームの時間をとる
	mTicksCount = SDL_GetTicks();

	// Update all actors
	mUpdatingActors = true;
    //全てのアクターのアップデートの処理
	for (auto actor : mActors){
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;
    
    //あたり判定
    for(auto actor : mBalls){
        actor -> Hit_Actor(deltaTime);
    }

	// Move any pending actors to mActors
    //追加されたオブジェクトの処理　その後アクターのリストに追加
	for (auto pending : mPendingActors){
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
        if(pending -> GetName() == "Ball"){
            mBalls.emplace_back(pending);
        }else{
            mOther_thing.emplace_back(pending);
        }
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
    //消すオブジェクトの処理
	std::vector<Actor*> deadActors;
	for (auto actor : mActors){
        //各オブジェクトの状態を取る
		if (actor->GetState() == Actor::EDead){
			deadActors.emplace_back(actor);
            
		}
	}

	// Delete dead actors (which removes them from mActors)
    //オブジェクトを消す
	for (auto actor : deadActors){
		delete actor;
	}
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::LoadData()
{
	// Create actors
    
    //デバッグ用グリッド
//    new Grid();
    
//    //キューブのオブジェクト制作
//    MeshComponent* mc;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            Block* block = new Block();
            block->SetPosition(Vector3(500 - (101.0f * i), 500 - (101.0f * j), 200.0f));
            block->SetScale(100.0f);
            Quaternion q(Vector3::UnitY, -Math::Pi);
            q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi));
            block->SetRotation(q);
//            mc = new MeshComponent(block);
//            mc->SetMesh(mRenderer->GetMesh("Assets/Cube.gpmesh"));
        }
    }
    

    //ボールのオブジェクト制作
	Ball* ball = new Ball();
	ball->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
	ball->SetScale(3.0f);
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
//    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
//    ball->SetRotation(q);
//    mc = new MeshComponent(ball);
//	mc->SetMesh(mRenderer->GetMesh("Assets/Sphere.gpmesh"));
    
    //バー作成
    Bar *bar = new Bar();
    bar->SetPosition(Vector3(-200.0f, -100.0f, -200.0f));
    bar->SetScale(50.0f);
//
	// Setup floor 床の作成
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Actor* a = new PlaneActor();
			a->SetPosition(Vector3(start + i * size, start + j * size, -(float)(GetFieldHeight())));
		}
	}

//	 Left/right walls 左右の壁制作
	/*Quaternion*/ q = Quaternion(Vector3::UnitX, Math::PiOver2);
	for (int i = 0; i < 10; i++)
	{
		Actor* a = new PlaneActor();
		a->SetPosition(Vector3(start + i * size, start - size/*(float)GetFieldWidth()*/, 0.0f));
		a->SetRotation(q);

		a = new PlaneActor();
		a->SetPosition(Vector3(start + i * size, -start + size/*-(float)GetFieldWidth()*/, 0.0f));
		a->SetRotation(q);
	}

	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
	// Forward/back walls 上下の壁作成
	for (int i = 0; i < 10; i++)
	{
		Actor* a = new PlaneActor();
		a->SetPosition(Vector3(start - size/*(float)GetFieldWidth()*/, start + i * size, 0.0f));
		a->SetRotation(q);

		a = new PlaneActor();
        a->SetPosition(Vector3(-start + size/*-(float)GetFieldWidth()*/, start + i * size, 0.0f));
		a->SetRotation(q);
	}

	// Setup lights
	mRenderer->SetAmbientLight(Vector3(1.2f, 1.2f, 1.2f));
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

	// Camera actor
	mCameraActor = new CameraActor();

//	// UI elements
//	a = new Actor(this);
//	a->SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
//	SpriteComponent* sc = new SpriteComponent(a);
//	sc->SetTexture(mRenderer->GetTexture("Assets/HealthBar.png"));
//
//	a = new Actor(this);
//	a->SetPosition(Vector3(375.0f, -275.0f, 0.0f));
//	a->SetScale(0.75f);
//	sc = new SpriteComponent(a);
//	sc->SetTexture(mRenderer->GetTexture("Assets/Radar.png"));
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty()){
		delete mActors.back();
	}

	if (mRenderer){
		mRenderer->UnloadData();
	}
}

void Game::Shutdown()
{
	UnloadData();
	if (mRenderer){
		mRenderer->Shutdown();
	}
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors){
		mPendingActors.emplace_back(actor);
	}else{
		mActors.emplace_back(actor);
        if(actor -> GetName() == "Ball"){
            mBalls.emplace_back(actor);
        }else{
            mOther_thing.emplace_back(actor);
        }
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()){
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()){
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
    
    // Is it in Balls?
    if(actor -> GetName() == "Ball"){
        iter = std::find(mBalls.begin(), mBalls.end(), actor);
        if(iter != mBalls.end()){
            std::iter_swap(iter, mBalls.end() - 1);
            mBalls.pop_back();
        }
    
    }else{ // Or is it in Other_actors?
        iter = std::find(mOther_thing.begin(), mOther_thing.end(), actor);
        if(iter != mOther_thing.end()){
            std::iter_swap(iter, mOther_thing.end() - 1);
            mOther_thing.pop_back();
        }
    }
}
