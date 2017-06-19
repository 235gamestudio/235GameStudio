#pragma once

#include <stdio.h>
#include <glm.hpp>
#include <string>

class GuiLayout;

class GuiFactory
{
public:
	virtual ~GuiFactory() {}
	virtual GuiLayout *create() = 0;
	virtual GuiLayout *copy(GuiLayout *c) = 0;

	void write(FILE *file, void *v, int s, int c);
	void write(FILE *file, int v);
	void write(FILE *file, float v);
	void write(FILE *file, glm::vec2 v);
	void write(FILE *file, std::string v);

	void read(FILE *file, void *v, int s, int c);
	void read(FILE *file, int &v);
	void read(FILE *file, float &v);
	void read(FILE *file, glm::vec2 &v);
	void read(FILE *file, std::string &v);
};