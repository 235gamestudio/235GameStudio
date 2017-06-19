#pragma once

#include <vector>
#include <unordered_map>

#include "Macros.h"
#include "GuiInput.h"
#include "GuiRendererSDL.h"
#include "GuiLayout.h"
#include "GuiWindow.h"
#include "GuiButton.h"
#include "GuiText.h"
#include "GuiEditBox.h"
#include "GuiTreeView.h"
#include "GuiTreeViewNode.h"
#include "GuiTreeViewLayout.h"
#include "GuiFactory.h"
#include "GuiRefButton.h"
#include "GuiEditor.h"
#include "GuiFileDialog.h"
#include "GuIScrollBar.h"

#include "GuiImage.h"
#include "GuiBar.h"

#include "GuiLayoutFactory.h"

#pragma comment(lib, "SDL2")
#pragma comment(lib, "FreeImage")

/* Enables layout editing mode */
#define SGUI_MODE_EDIT_MODE 0x1
/* Enables drawing layout size */
#define SGUI_MODE_SHOW_SIZE 0x2

/*
	Layout IDs
	0x01 - GuiLayout
	0x02 - GuiWindow
	0x03 - GuiButton
	0x04 - GuiText
	0x05 - GuiRefButton
	0x06 - GuiEditBox
	0x07 - GuiTreeView
	0x11 - GuiShopDialog
*/

class GuiManager
{
	GuiLayout *root, *focus;
	std::unordered_map<std::string, GuiTexture*>textures;
	std::unordered_map<std::string, GuiFont*>fonts;
	std::unordered_map<int, GuiFactory*>factories;

	int mode;

	GuiRenderer *renderer = NULL;
	GuiEditor *editor;

	void saveLayout(GuiLayout *layout, FILE *file);
	GuiLayout *loadLayout(FILE *file);

	GuiManager();
	GuiManager(const GuiManager&) : GuiManager() {}
	GuiManager &operator=(const GuiManager&) {}
	~GuiManager();
	
public:
	static GuiManager &get();

	void init(GuiRenderer *renderer);

	GuiLayout *getRootLayout();
	GuiLayout *getFocusLayout();

	GuiLayout *addLayout(GuiLayout *layout);
	GuiLayout *getLayout(int i);
	unsigned int getNumLayouts();
	void addTexture(std::string path);
	GuiTexture *getTexture(std::string path);
	std::string getTexturePath(GuiTexture *texture);
	void addFont(std::string path);
	GuiFont *getFont(std::string path);
	std::string getFontPath(GuiFont *font);
	void registerFactory(int chunk, GuiFactory *factory);
	GuiFactory *getFactory(int chunk);
	GuiLayout *load(std::string path);
	void save(std::string path, GuiLayout *layout);

	void moveAtForeground(GuiLayout *layout);
	bool inputLayout(GuiLayout *layout, bool handled = false);
	void updateLayout(GuiLayout *layout, float dt);
	void drawLayout(GuiLayout *layout);

	void setMode(int mode);
	void enableMode(int mode);
	void disableMode(int mode);
	int getMode();

	void setRenderer(GuiRenderer *r);
	GuiRenderer *getRenderer();
	void setEditor(GuiEditor *e);
	GuiEditor *getEditor();
	void resize(glm::vec2 s);

	/* Helpers */
	bool isPointInRect(glm::vec2 p, glm::vec2 r1, glm::vec2 r2);
	//void draw

	void onInput();
	void onUpdate(float dt);
	void onDraw();


	void print(GuiLayout *layout, int i = 0);
};