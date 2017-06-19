#pragma once

#include <glm.hpp>
#include <string>
#include <vector>

#include "GuiRenderer.h"
#include "GuiFactory.h"

#include "Macros.h"

/**
 * \class GuiLayout
 *
 * \brief Base class of each GUI component.
 */
class GuiLayout
{
protected:
	std::string label; ///< ID of layout.
	GuiLayout *parent; ///< Parent layout.
	std::vector<GuiLayout*>childs; ///< Array of layout's childrens.
	glm::vec2 position; ///< Position relative to parent's position.
	glm::vec2 size; ///< Size of layout.
	glm::vec2 align; ///< Position offset relative to parent's size and position.
	glm::vec4 viewport; ///< Layout's viewport (optional).
	bool
		enabled, ///< This flag is set if layout is enabled. Default value = true
		selected, ///< This flag is set when layout is selected (see also EditMode). Default value = false
		removed, ///< This flag is set if layout is to be removed. Default value = false
		destroyed; ///< This flag is set if layout is to be destroyed. Default value = false
	bool savable; ///< This flag is set if layout should be automaticly saved by GuiManager. Default value = true
	bool editable; ///< This flag is set if layout can be editable when editing mode is enabled. Default value = false
	bool focusable; //< This flag is set if layout can be focues by clicking on it. Default value = true

public:
	int id; ///< Unique ID of class (for factory). Necessary, if needed saving and loading layout
	static const float AlignLeft; ///< Left edge of parent.
	static const float AlignRight; ///< Right edge of parent.
	static const float AlignTop; ///< Top edge of parent.
	static const float AlignBottom; ///< Bottom edge of parent.
	static const float AlignCenter; ///< Center of parent.

	/**
	 * Constructor.
	 * @param p Layout's position.
	 * @param s Layout's size.
	 */
	GuiLayout(glm::vec2 p, glm::vec2 s);
	GuiLayout();
	/**
	 * Copy constructor. Necessary, when needed copying layouts with an other layouts as a member of class.
	 * @param c layout to copy.
	 */
	GuiLayout(const GuiLayout& c);
	virtual ~GuiLayout();

	virtual void setLabel(std::string label);
	virtual std::string getLabel();
	virtual void setPosition(glm::vec2 p);
	virtual glm::vec2 getPosition();
	/**
	 * Adds vector d to the position vector.
	 * @param d Translation vector.
	 */
	virtual void move(glm::vec2 d);
	virtual void setSize(glm::vec2 s);
	virtual glm::vec2 getSize();
	virtual void setAlign(float h, float v);
	virtual glm::vec2 getAlign();
	virtual void setParent(GuiLayout *p);
	virtual GuiLayout *getParent();
	virtual void setViewport(glm::vec4 v);
	virtual glm::vec4 getViewport();
	virtual void setEnabled(bool s);
	virtual bool isEnabled();
	virtual bool isDisabled();
	virtual void setSelected(bool s);
	virtual bool isSelected();
	virtual void setRemoved(bool s);
	virtual void remove();
	virtual bool isRemoved();
	virtual void setDestroyed(bool s);
	virtual void destroy();
	virtual bool isDestroyed();
	virtual void setSavable(bool s);
	virtual bool isSavable();
	virtual void setEditable(bool s);
	virtual bool isEditable();
	virtual void setFocusable(bool s);
	virtual bool isFocusable();

	virtual bool layoutClick();

	/**
	 * Returns absolute position relative to window, instead of parent layout.
	 * @return Absolute position.
	 */
	virtual glm::vec2 getAbsolutePosition();
	/**
	 * Sets position so that the p will be absolute position of this layout.
	 * Layout's position is still relative to its parent, so after changing parent's position, you need
	 * to set absolute position again.
	 * @param p Absolute position of layout.
	 */
	virtual void setAbsolutePosition(glm::vec2 p);

	/**
	 * Finds and returns first layout with a certain label.
	 * Searching is started from layout which calls the method and it's parents are not included.
	 * @param label Label of layout which you looking for.
	 */
	virtual GuiLayout *find(std::string label);

	/**
	 * Add layout as a children of layout which calls the method.
	 * Parent of added layout is set to layout which calls the method.
	 * @param layout Layout to be added to hierarchy.
	 */
	virtual GuiLayout *addLayout(GuiLayout *layout);
	/**
	 * Returns children with specified index.
	 * Index isn't assigned to a specific object and may change.
	 * @param i Children's index.
	 */
	virtual GuiLayout *getChildren(int i);
	/**
	 * Removes children with specified index.
	 * Sets 'removed' flag as 'true', so layout will be removed in the next GuiManager update;
	 * Remember that index isn't assigned to a specific object and may change.
	 * @param i Children's index.
	 */
	virtual void removeChildren(int i);
	virtual void removeAllChildrens();
	virtual unsigned int getNumChildrens();

	/**
	 * Method called for each events (mouse, keyboard, window change...), if layout is focused.
	 * Can be called more than once during one frame.
	 */
	virtual void onInput();
	/**
	 * Method called every frame before rendering.
	 * @param dt Length of last frame in seconds (Delta time).
	 */
	virtual void onUpdate(float dt);
	/**
	 * Method called every frame after update.
	 */
	virtual void onDraw();

	/**
	 * Sets ID of the layout class. Each class must have unique ID to allow proper saving and loading layout.
	 * @param i ID of layout class.
	 */
	virtual void setID(int i);
	virtual int getID();

	/**
	 * Called by GuiManager to load the layout.
	 * Childrens are loaded automaticly by GuiManager.
	 */
	virtual void load(FILE *file);
	/**
	 * Called by GuiManager to save the layout.
	 * Childrens are saved automaticly by GuiManager.
	 */
	virtual void save(FILE *file);
};