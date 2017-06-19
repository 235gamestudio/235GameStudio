#include "GuiFactory.h"

void GuiFactory::write(FILE *file, void *v, int s, int c)
{
	fwrite(v, s, c, file);
}
void GuiFactory::write(FILE *file, int v)
{
	fwrite(&v, sizeof(int), 1, file);
}
void GuiFactory::write(FILE *file, float v)
{
	fwrite(&v, sizeof(float), 1, file);
}
void GuiFactory::write(FILE *file, glm::vec2 v)
{
	fwrite(&v, sizeof(glm::vec2), 1, file);
}
void GuiFactory::write(FILE *file, std::string v)
{
	fwrite(&(v._Mysize()), sizeof(int), 1, file);
	fwrite(&v[0], sizeof(char), v.size(), file);
}

void GuiFactory::read(FILE *file, void *v, int s, int c)
{
	fread(v, s, c, file);
}
void GuiFactory::read(FILE *file, int &v)
{
	fread(&v, sizeof(int), 1, file);
}
void GuiFactory::read(FILE *file, float &v)
{
	fread(&v, sizeof(float), 1, file);
}
void GuiFactory::read(FILE *file, glm::vec2 &v)
{
	fread(&v, sizeof(glm::vec2), 1, file);
}
void GuiFactory::read(FILE *file, std::string &v)
{
	int len;
	fread(&len, sizeof(int), 1, file);
	v.reserve(len);
	fread(&v[0], sizeof(char), len, file);
}