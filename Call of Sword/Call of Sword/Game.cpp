#include "Game.h"
#include <math.h>

Game::Game()
{
	try
	{
		if (!WindowInit())
			throw std::string("Failed to initialize window!");
		else
		{
			if (!MediaInit())
				throw std::string("Failed to initialize media!");
			else
			{
				isOpened = true;
				countedFrames = 0;
				fpsTimer = new GameTimer();
				fpsTimer->start();
				capTimer = new GameTimer();

				if (fpsTimer == NULL || capTimer == NULL)
					std::cout << "Warning! Failed to initialize fps counter!" << std::endl;

				mainCamera = new Camera(player->getPosX() - gameWindow->getWidth() / 2, player->getPosY() - gameWindow->getHeight() / 2, gameWindow->getWidth(), gameWindow->getHeight());

				if (mainCamera == NULL)
					throw std::string("Failed to initialize main camera!");

				if (!guiInit())
					throw std::string("Failed to initialize gui!");

				key = 0;
				GameLoop();
			}
		}
	}
	catch(std::string capturedError)
	{
		std::cout << capturedError << std::endl;
		return;
	}
}

Game::~Game()
{
	SDL_DestroyTexture(sceneTexture);
	delete player;
	delete steward;
	delete mainCamera;
	delete gameWindow;
	delete gameMap;
	fpsTimer->stop();
	delete fpsTimer;
	capTimer->stop();
	delete capTimer;
}

GameWindow* Game::getWindow()
{
	return gameWindow;
}

bool Game::WindowInit()
{
	gameWindow = new GameWindow("Call of Sword", 1600, 900);
	if (gameWindow->opened() == true)
		return true;
	else
		return false;
}

bool Game::guiInit()
{
	gui.init(new GuiRendererSDL(gameWindow->getWindow(), gameWindow->getRenderer()));

	gui.resize(glm::vec2(gameWindow->getWidth(), gameWindow->getHeight()));

	if (gui.getRenderer() == NULL)
		throw std::string("Failed to initialize ingame GUI manager!");

	gui.addLayout(rootLayout = new GuiLayout(glm::vec2(0.0f, 0.0f), gui.getRootLayout()->getSize() - glm::vec2(0.0f, 0.0f)));

	if (rootLayout == NULL)
		throw std::string("Failed to initialize root layout!");

	rootLayout->setLabel("root_layout");
	rootLayout->setFocusable(false);

	gui.addLayout(guiLayout["sidebar_left"] = new GuiBar(NULL,glm::vec2(0.0f, -gameWindow->getHeight() / 12), glm::vec2(100.0f, 370.0f)));

	guiLayout["sidebar_left"]->setFocusable(false);
	guiLayout["sidebar_left"]->setAlign(GuiLayout::AlignLeft, GuiLayout::AlignCenter);

	int maph = 225;
	int mapw = 250;

	gui.addLayout(guiLayout["minimap"] = new GuiLayout(glm::vec2(), glm::vec2(mapw, maph)));
	guiLayout["minimap"]->setFocusable(false);
	guiLayout["minimap"]->setAlign(GuiLayout::AlignRight, GuiLayout::AlignTop);
	guiLayout["minimap"]->addLayout(guiLayout["minimap_border"] = new GuiImage(gui.getTexture("images/other/minimap_border.png"), glm::vec2(), glm::vec2(250.0f, 225.0f)));
	guiLayout["minimap"]->addLayout(guiLayout["minimap_button_arrow"] = new GuiButton("", glm::vec2(20.0f, -15.0f)));
	((GuiButton*)guiLayout["minimap_button_arrow"])->setAlign(GuiLayout::AlignLeft, GuiLayout::AlignBottom);
	((GuiButton*)guiLayout["minimap_button_arrow"])->setTexture(gui.getTexture("images/other/minimap_arrow_up.png"));

	gui.addLayout(guiLayout["downbar_mana"] = new GuiLayout(glm::vec2(), glm::vec2(398.0f, 173.0f)));
	guiLayout["downbar_mana"]->setFocusable(false);
	guiLayout["downbar_mana"]->setAlign(GuiLayout::AlignRight, GuiLayout::AlignBottom);
	guiLayout["downbar_mana"]->addLayout(guiLayout["panel_mana"] = new GuiButton("", glm::vec2()));
	((GuiButton*)guiLayout["panel_mana"])->setTexture(gui.getTexture("images/other/downbar_mana_panel.png"));

	gui.addLayout(guiLayout["downbar_health"] = new GuiLayout(glm::vec2(), glm::vec2(398.0f, 173.0f)));
	guiLayout["downbar_health"]->setFocusable(false);
	guiLayout["downbar_health"]->setAlign(GuiLayout::AlignLeft, GuiLayout::AlignBottom);
	guiLayout["downbar_health"]->addLayout(guiLayout["panel_health"] = new GuiButton("", glm::vec2()));
	((GuiButton*)guiLayout["panel_health"])->setTexture(gui.getTexture("images/other/downbar_health_panel.png"));

	gui.print(gui.getRootLayout());

#ifdef _DEBUG
	//gui.setMode(SGUI_MODE_EDIT_MODE | SGUI_MODE_SHOW_SIZE);
#else
	gui.setMode(SGUI_MODE_EDIT_MODE/* | SGUI_MODE_SHOW_SIZE*/);
#endif

	return true;
}

SDL_Texture* Game::loadTexture(std::string path)
{
		SDL_Texture* newTexture = NULL;

		SDL_Surface * loadedSurface = IMG_Load(path.c_str());

		if (loadedSurface == NULL)
			throw std::string("Unable to load image: ") + std::string(path.c_str());

		else
		{
			newTexture = SDL_CreateTextureFromSurface(gameWindow->getRenderer(), loadedSurface);
			if (newTexture == NULL)
				throw std::string("Unable to create texture from: ") + std::string(path.c_str());

			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;

}

bool Game::MediaInit()
{
	bool initSuccess = true;
	
	player = new Player("images/player/player_walk.png", 1600, 950, 70 , 70, gameWindow->getRenderer());
	if (player->getTexture() == NULL)
	{
		initSuccess = false;
		throw std::string("Failed to load player texture!");
	}
	else
	{
		steward = new NPC("images/NPC/steward.png", 1000, 600, 70, 70, gameWindow->getRenderer());
		if (steward->getTexture() == NULL)
		{
			initSuccess = false;
			throw std::string("Failed to load player texture!");
		}

		else
		{
			orbFill = loadTexture("images/other/downbar_orb_fill.png");
			SDL_SetTextureBlendMode(orbFill, SDL_BLENDMODE_BLEND);

			minimapFill = loadTexture("images/other/minimap_fill.png");
			SDL_SetTextureBlendMode(minimapFill, SDL_BLENDMODE_BLEND);

				gameMap = new GameMap();
				
				SDL_Rect rendersrc;
				rendersrc.x = 0;
				rendersrc.y = 0;
				rendersrc.w = gameMap->getTileW();
				rendersrc.h = gameMap->getTileH();

				SDL_Rect renderpos;
				renderpos.x = 0;
				renderpos.y = 0;
				renderpos.w = gameMap->getTileW();
				renderpos.h = gameMap->getTileH();

				SDL_RenderClear(gameWindow->getRenderer());
				SDL_Surface *tmpSurface;
				for (const auto& tileset : gameMap->map.getTilesets())
				{
					tmpSurface = IMG_Load(tileset.getImagePath().c_str());
					printf("%s\n", tileset.getImagePath().c_str());

					tilesets.push_back(SDL_CreateTextureFromSurface(gameWindow->getRenderer(), tmpSurface));
					SDL_FreeSurface(tmpSurface);
				}
				if (tilesets.size() == 0)
				{
					initSuccess = false;
					throw std::string("Failed to load tilesets images!");
				}
			}
	}

	return initSuccess;
}

void Game::GameLoop()
{
	SDL_Event event;

	while (isOpened)
	{
		capTimer->start();

		while (SDL_PollEvent(&event) == 1)
		{
			Input(&event);
		}
		
		float avgFPS = countedFrames / (fpsTimer->getTicks() / 1000.f);
		
		if (fpsTimer->getTicks() > 1000)
		{
			fpsTimer->start();
			printf("Frames: %d\n", countedFrames);
			countedFrames = 0;
		}

		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		Update(&event);
		Draw();
		countedFrames++;
		int frameTicks = capTimer->getTicks();

		if (frameTicks < SCREEN_TICKS_PER_FRAME)
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
	}
}

void Game::Input(SDL_Event *event)
{
	input.onEvent(*event);
	gui.onInput();

	switch (event->type)
	{
		case SDL_QUIT:
		{
			isOpened = false;
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if (event->button.button == SDL_BUTTON_LEFT)
			{
				if (guiClick())
					break;

				if (player->getMouseOrder() == true)
					player->setMouseOrder(false);

				player->mouseEvent(event->button.clicks, (int)mainCamera->getPosX(), (int)mainCamera->getPosY());
				player->render.x = (int)player->getPosX() - mainCamera->cameraRect.x;
				player->render.y = (int)player->getPosY() - mainCamera->cameraRect.y;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{

			break;
		}
		case SDL_KEYDOWN:
		{
			if (player->getMouseOrder() == true)
				player->setMouseOrder(false);

			break;
		}
	}
}

void Game::Update(SDL_Event *event)
{
	gui.onUpdate(0.0f);

	if (player->getMouseOrder() == true)
		player->mouseEvent(event->button.clicks, (int)mainCamera->getPosX(), (int)mainCamera->getPosY());

	if(player->getMouseOrder() != true)
		player->move(event, key);

	if (gameMap->isCollision((int)player->getPosX(), (int)player->getPosY()))
	{
		if (player->getMouseOrder() == true)
			player->setMouseOrder(false);

		switch (player->moveDirection)
		{
			case e_east:
			{
				player->setPosX(player->getPosX() - player->getSpeed());
				break;
			}
			case e_north:
			{
				player->setPosY(player->getPosY() + player->getSpeed());
				break;
			}
			case e_west:
			{
				player->setPosX(player->getPosX() + player->getSpeed());
				break;
			}
			case e_south:
			{
				player->setPosY(player->getPosY() - player->getSpeed());
				break;
			}
			case e_northeast:
			{
				player->setPosX(player->getPosX() - player->getSpeed());
				player->setPosY(player->getPosY() + player->getSpeed());
				break;
			}
			case e_northwest:
			{
				player->setPosX(player->getPosX() + player->getSpeed());
				player->setPosY(player->getPosY() + player->getSpeed());
				break;
			}
			case e_southeast:
			{
				player->setPosX(player->getPosX() - player->getSpeed());
				player->setPosY(player->getPosY() - player->getSpeed());
				break;
			}
			case e_southwest:
			{
				player->setPosX(player->getPosX() + player->getSpeed());
				player->setPosY(player->getPosY() - player->getSpeed());
				break;
			}
		}
	}
	
	RenderUpdate();
}

void Game::RenderUpdate()
{
	player->render.x = (int)player->getPosX() - mainCamera->cameraRect.x;
	player->render.y = (int)player->getPosY() - mainCamera->cameraRect.y;
	steward->render.x = (int)steward->getPosX() - mainCamera->cameraRect.x;
	steward->render.y = (int)steward->getPosY() - mainCamera->cameraRect.y;

	if (player->render.x < mainCamera->cameraRect.w*0.25)
		mainCamera->cameraRect.x -= (int)player->getSpeed();

	if (player->render.x > mainCamera->cameraRect.w*0.75)
		mainCamera->cameraRect.x += (int)player->getSpeed();

	if (player->render.y < mainCamera->cameraRect.h*0.25)
		mainCamera->cameraRect.y -= (int)player->getSpeed();

	if (player->render.y > mainCamera->cameraRect.h*0.65)
		mainCamera->cameraRect.y += (int)player->getSpeed();

	player->setRenderHP(100 - (player->getActualHP() / player->getHP()) * 100);
	player->setRenderMP(100 - (player->getActualMP() / player->getMP()) * 100);
	player->render.x -= player->render.w / 2;
	player->render.y -= player->render.h / 2;
}

void Game::Draw()
{
	SDL_RenderClear(gameWindow->getRenderer());

	gameMap->draw(mainCamera->cameraRect.x, mainCamera->cameraRect.y, mainCamera->cameraRect.w, mainCamera->cameraRect.h, gameWindow->getRenderer(), tilesets);

	SDL_RenderCopy(gameWindow->getRenderer(), steward->getTexture(), &steward->walkingAnim,&steward->render);
	SDL_RenderCopy(gameWindow->getRenderer(), player->getTexture(), &player->walkingAnim, &player->render);
	
	SDL_SetTextureColorMod(orbFill, 0, 0, 255);
	RenderCopy(gameWindow->getRenderer(), orbFill, glm::ivec2(0, player->getRenderMP()), glm::ivec2(158, 158),
		glm::ivec2(guiLayout["downbar_mana"]->getAbsolutePosition().x + 232, guiLayout["downbar_mana"]->getAbsolutePosition().y + 8 + player->getRenderMP()),
		glm::ivec2(158, 158 - player->getRenderMP()));

	SDL_SetTextureColorMod(orbFill, 255, 0, 0);
	RenderCopy(gameWindow->getRenderer(), orbFill, glm::ivec2(0, player->getRenderHP()), glm::ivec2(158, 158),
		glm::ivec2(guiLayout["downbar_health"]->getAbsolutePosition().x + 8, guiLayout["downbar_health"]->getAbsolutePosition().y + 8 + player->getRenderHP()),
		glm::ivec2(158, 158 - player->getRenderHP()));

	RenderCopy(gameWindow->getRenderer(), minimapFill, glm::ivec2(-1, -1), glm::ivec2(-1, -1),
		glm::ivec2(guiLayout["minimap_border"]->getAbsolutePosition().x, guiLayout["minimap_border"]->getAbsolutePosition().y),
		glm::ivec2(250, 225));

	gui.onDraw();
	SDL_RenderPresent(gameWindow->getRenderer());
}

void Game::RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, glm::ivec2 src_pos, glm::ivec2 src_size, glm::ivec2 dst_pos, glm::ivec2 dst_size)
{
	SDL_Rect src;
	SDL_Rect dst;

	bool src_check = false;
	bool dst_check = false;

	if (src_pos.x == -1 || src_pos.y == -1 || src_size.x == -1 || src_size.y == -1)
		src_check = true;
	if (dst_pos.x == -1 || dst_pos.y == -1 || dst_pos.x == -1 || dst_pos.y == -1)
		dst_check = true;

	if (!src_check)
	{
		src.x = src_pos.x;
		src.y = src_pos.y;
		src.w = src_size.x;
		src.h = src_size.y;
	}

	if (!dst_check)
	{
		dst.x = dst_pos.x;
		dst.y = dst_pos.y;
		dst.w = dst_size.x;
		dst.h = dst_size.y;
	}

	if (src_check && dst_check)
	{
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		return;
	}
	if (src_check)
	{
		SDL_RenderCopy(renderer, texture, NULL, &dst);
		return;
	}
	if (dst_check)
	{
		SDL_RenderCopy(renderer, texture, &src, NULL);
		return;
	}

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

bool Game::guiClick()
{
	for (std::map<char *const, GuiLayout*>::iterator it = guiLayout.begin(); it != guiLayout.end(); ++it)
	{
		if (GuiLayout* guiLay = dynamic_cast<GuiLayout*>(it->second))
			if (guiLay->layoutClick())
				return true;
	}
	return false;
}