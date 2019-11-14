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
#include "CreateField.hpp"

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
       // printf("up");
	}
	
    
    //あたり判定
    Vector3 temp_ball_pos;
    Vector3 temp_pos;
    for(auto ball : mBalls){
//        printf("hoge");
        temp_ball_pos = ball -> GetPosition();
        //ブロックの当たり判定
        if(temp_ball_pos.z > (block_height-50)){
            for(auto block : mBlocks){
//                printf("kore");
                temp_pos = block -> GetPosition();
                if((temp_ball_pos.x > temp_pos.x - block_scale.x) && (temp_ball_pos.x < temp_pos.x + block_scale.x)){
                    if((temp_ball_pos.y > temp_pos.y - block_scale.y) && (temp_ball_pos.y < temp_pos.y + block_scale.y)){
                        if((temp_ball_pos.y > temp_pos.y - block_scale.y) && (temp_ball_pos.y < temp_pos.y + block_scale.y)){
                            block -> Hit_Actor(0);
                            ball -> Hit_Actor(1);
//                            printf("\nbreak_block");
                            break;
                        }
                    }
                }
            }
        }else if(temp_ball_pos.z < bar_under + 50.0f){
            for(auto bar : mBars){
                temp_pos = bar -> GetPosition();
                if((temp_ball_pos.x > temp_pos.x - bar_scale.x) && (temp_ball_pos.x < temp_pos.x + bar_scale.x)){
                    if((temp_ball_pos.y > temp_pos.y - bar_scale.y) && (temp_ball_pos.y < temp_pos.y + bar_scale.y)){
                        if((temp_ball_pos.z > temp_pos.z - bar_scale.z) && (temp_ball_pos.z < temp_pos.z + bar_scale.z)){
                            bar -> Hit_Actor(0);
                            ball -> Hit_Actor(1);
//                            printf("hit_bar");
                        }
                    }
                }
            }

        }
    }
    
    mUpdatingActors = false;

	// Move any pending actors to mActors
    //追加されたオブジェクトの処理　その後アクターのリストに追加
	for (auto pending : mPendingActors){
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
        mOther_thing.emplace_back(pending);
	}
	mPendingActors.clear();
    
    //継承先ではメンバ変数を変更できなかったので、ここでブロックとボールをリストに追加 さらにバー追加
    for (auto pending : mOther_thing){
        if(pending -> GetName() == "Block"){
            mBlocks.emplace_back(pending);
//            printf("hogehogehogoe");
        }else if(pending -> GetName() == "Ball"){
            mBalls.emplace_back(pending);
//            printf("add_ball");
        }else if(pending -> GetName() == "Bar"){
            mBars.emplace_back(pending);
        }
    }
    mOther_thing.clear();

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
    
//    new CreateField();
    
    //デバッグ用グリッド
//    new Grid();
    
    //キューブのオブジェクト制作
    for(int y = 0; y < 3; y++){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                Block* block = new Block();
                block->SetPosition(Vector3(500 - (101.0f * i), 500 - (101.0f * j), block_height + (100 * y)));
                block->SetScale(100.0f);
                Quaternion q(Vector3::UnitY, -Math::Pi);
                q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi));
                block->SetRotation(q);
            }
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
    
//    バー作成
    Bar *bar = new Bar();
    bar->SetPosition(Vector3(-200.0f, -100, bar_under));
    bar->SetScale(50.0f);

	// Setup floor 床の作成
//	const float start = 0.0f;
//	const float size = 1000.0f;
//	for (int i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < 2; j++)
//		{
//			Actor* a = new PlaneActor();
//			a->SetPosition(Vector3(start + i * size, start + j * size, -(GetFieldHeight())));
//            
//            a = new PlaneActor();
//            a->SetPosition(Vector3(start + i * size, start + j * size, (GetFieldHeight())));
//		}
//	}

//	 Left/right walls 左右の壁制作
//	/*Quaternion*/ q = Quaternion(Vector3::UnitX, Math::PiOver2);
//	for (int i = 0; i < 1; i++)
//	{
//		Actor* a = new PlaneActor();
//		a->SetPosition(Vector3(start + i * size, /*start - size*/GetFieldWidth(), 0.0f));
//		a->SetRotation(q);
//
//		a = new PlaneActor();
//		a->SetPosition(Vector3(start + i * size, /*-start + size*/-GetFieldWidth(), 0.0f));
//		a->SetRotation(q);
//	}

//	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
	// Forward/back walls 上下の壁作成
//	for (int i = 0; i < 1; i++)
//	{
//		Actor* a = new PlaneActor();
//		a->SetPosition(Vector3(/*start - size*/GetFieldWidth(), start + i * size, 0.0f));
//		a->SetRotation(q);
//
//		a = new PlaneActor();
//        a->SetPosition(Vector3(/*-start + size*/-GetFieldWidth(), start + i * size, 0.0f));
//		a->SetRotation(q);
//	}

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
//    printf("%s",actor -> GetName());
	if (mUpdatingActors){
		mPendingActors.emplace_back(actor);
	}else{
		mActors.emplace_back(actor);
        mOther_thing.emplace_back(actor);
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
    }else if(actor -> GetName() == "Block"){//Or is it in Block?
        iter = std::find(mBlocks.begin(), mBlocks.end(), actor);
        if(iter != mBlocks.end()){
            std::iter_swap(iter, mBlocks.end() - 1);
            mBlocks.pop_back();
        }
    }else if(actor -> GetName() == "Bar"){
        iter = std::find(mBars.begin(), mBars.end(), actor);
        if(iter != mBars.end()){
            std::iter_swap(iter, mBars.end() - 1);
            mBars.pop_back();
        }
    }
    else{ // Or is it in Other_actors?
        iter = std::find(mOther_thing.begin(), mOther_thing.end(), actor);
        if(iter != mOther_thing.end()){
            std::iter_swap(iter, mOther_thing.end() - 1);
            mOther_thing.pop_back();
        }
    }
}
