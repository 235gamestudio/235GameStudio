#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <Map.hpp>
#include <TileLayer.hpp>
#include <ObjectGroup.hpp>
#include <Object.hpp>
#include <SDL.h>
#include <glm.hpp>
#include <SDL_image.h>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <algorithm>

class GameMap
{
	int tileW;
	int tileH;
	int mapW;
	int mapH;
	int tileAmount;
	std::map<int, std::vector<glm::ivec2>> polygon;
	std::vector<std::string>poly_wkt;

	typedef boost::geometry::model::d2::point_xy<int>point_type;
	typedef boost::geometry::model::polygon<point_type> polygon_type;
	polygon_type poly;
	point_type p;
	int radiusX, radiusY;

public:
	std::vector<int>sceneTiles;
	GameMap();
	~GameMap();
	
	int getMapW();
	int getMapH();
	void setMapW(int w);
	void setMapH(int h);
	int getTileW();
	int getTileH();
	int getTileAmount();

	// this function is calulating position of a camera and copying map to renderer
	void draw(int x, int y, int w, int h, SDL_Renderer *renderer, std::vector<SDL_Texture*>tilesets);

	//this function is checking if there was a collision with any object
	bool isCollision(int x, int y);

	// this function is a comparator for sort functions (it is using while sorting drawing order)
	static bool isSmaller(const tmx::Object &i, const tmx::Object &j);
	tmx::Map map;
};