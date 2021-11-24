#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
using namespace std;

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

struct GameState
{
	int score = 0;
};

GameState gamestate;

enum GameObjectType
{
	TYPE_NULL = -1,
	TYPE_AGENT8,
	TYPE_FAN,
	TYPE_TOOL,
	TYPE_COIN,
	TYPE_STAR,
	TYPE_LASER,
	TYPE_DESTROIED,
};

void HandlePlayerControl();
void UppdateFan();
void UppdateTools();


// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	/*char j[5] = {,,,,};
	j[5] = "test";*/
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground("Data\\Backgrounds\\background.png");
	Play::StartAudioLoop("music");
	Play::CreateGameObject(TYPE_AGENT8, { 115, 100 }, 50, "agent8");//kolla denna
	int fanId = Play::CreateGameObject(TYPE_FAN, { 1140, 217 }, 0, "fan");//varför spara id?
	Play::GetGameObject(fanId).velocity = { 0,3 };//FORTSÄTT HÄRRRRRRRRRRRRRRRRRRRRRRRRRRR
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::DrawBackground();//kolla denna
	HandlePlayerControl();
	Play::DrawDebugText({ 100, 100 }, "type is: ");
	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}


void HandlePlayerControl()
{
	GameObject& gubben = Play::GetGameObjectByType(TYPE_AGENT8);//kolla denna

	if (Play::KeyDown(VK_UP))
	{
		gubben.velocity = { 0, -4 };
		Play::SetSprite(gubben, "agent8_climb", 0.25f);
	}
	else if (Play::KeyDown(VK_DOWN))
	{
		gubben.acceleration = { 0, 1 };
		Play::SetSprite(gubben, "agent8_fall", 0);
	}
	else
	{
		Play::SetSprite(gubben, "agent8_hang", 0.02f);
		gubben.velocity *= 0.5f;
		gubben.acceleration = { 0, 0 };
	}

	Play::UpdateGameObject(gubben);

	if (Play::IsLeavingDisplayArea(gubben))
	{
		gubben.pos = gubben.oldPos;
	}

	Play::DrawLine({ gubben.pos.x, 0 }, { gubben.pos.x, gubben.pos.y }, Play::cWhite);
	Play::DrawObjectRotated(gubben);

}
