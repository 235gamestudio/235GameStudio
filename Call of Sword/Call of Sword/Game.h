#pragma once
#include "GameWindow.h"
#include "GameTimer.h"
#include "NPC.h"
#include "Player.h"
#include "Camera.h"
#include "GameMap.h"
#include "gui\GuiManager.h"
#include <map>

#define GuiButtonCast(a)			((GuiButton*)a)
#define GuiWindowCast(a)			((GuiWindow*)a)
#define GuiTextCast(a)				((GuiText*)a)
#define GuiTreeViewCast(a)			((GuiTreeView*)a)
#define GuiTreeViewNodeCast(a)		((GuiTreeViewNode*)a)
#define GuiTreeViewLayoutCast(a)	((GuiTreeViewLayout*)a)
#define GuiEditBoxCast(a)			((GuiEditBox*)a)

const int SCREEN_FPS = 100;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

class Game
{
private:
	GameWindow *gameWindow = NULL;
	std::vector<SDL_Texture*>tilesets;
	SDL_Texture* orbFill = NULL;
	SDL_Texture* minimapFill = NULL;
	Camera *mainCamera = NULL;
	bool isOpened = false;
	GameTimer *fpsTimer = NULL;
	GameTimer *capTimer = NULL;
	int countedFrames;
	GameMap *gameMap = NULL;
	Player *player = NULL;
	NPC *steward = NULL;

	std::map<char*, GuiLayout*> guiLayout;
	GuiLayout *rootLayout = NULL;

	enum E_EditMode
	{
		eEditSelect = 0,
		eEditMove,
		eEditResize,
		eEditCreate
	};

	E_EditMode editMode;
	GuiLayout *newLayout;

public:
	Game();
	~Game();

	// this function is loading texture from current path
	SDL_Texture* loadTexture(std::string path);

	// this function is initializing all media
	bool MediaInit();

	// this function is initializing window
	bool WindowInit();

	// this function is initializing GUI
	bool guiInit();
	GameWindow *getWindow();

	// this function is a game loop, which is running while program is opened
	void GameLoop();

	// this function is updating all informations in game every frame
	void Update(SDL_Event *event);
	void RenderUpdate();

	// this function is drawing all visable objects (such as f.e. gui, map, player, npc's etc.) ever7 frame
	void Draw();

	// this function is an additional function which helps to render gui objects every frame
	void RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, glm::ivec2 src_pos, glm::ivec2 src_size, glm::ivec2 dst_pos, glm::ivec2 dst_size);

	// this function is reading and handing all events that have occured
	void Input(SDL_Event *event);

	// this function is checking if GUI was clicked
	bool guiClick();
	SDL_Texture* sceneTexture = NULL;
	int key;
};