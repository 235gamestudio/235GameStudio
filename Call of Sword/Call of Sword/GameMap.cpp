#include "GameMap.h"

GameMap::GameMap()
{
	//if (!map.load("map/Maps/map2.tmx"))
	if (!map.load("map/zzz.tmx"))
		throw std::string("Couldn't open map file!");

	else
	{
		radiusX = 64;
		radiusY = 32;
		tileAmount = map.getTileCount().x;
		tileH = map.getTileSize().y;
		tileW = map.getTileSize().x;
		mapW = tileW * tileAmount;
		mapH = tileH * tileAmount;

		const auto& tileset = map.getTilesets()[0];
		const auto& tiles = tileset.getTiles();

		for (int i = 0; i < tiles.size(); i++)
		{
			const auto& objectGroup = tiles[i].objectGroup;
			const auto& object = objectGroup.getObjects();
			const auto& objectPoints = object[0].getPoints();

			for (const auto& objectPoint : objectPoints)
				polygon[tiles[i].ID].push_back(glm::ivec2(objectPoint.x, objectPoint.y));
		}

		const auto& layers = map.getLayers();
		for (const auto& layer : layers)
		{
			if (layer->getType() == tmx::Layer::Type::Object)
			{
				auto objects_s = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();

				std::sort(&objects_s[0], &objects_s[0] + objects_s.size(), isSmaller);


				const auto& objects = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();

				for (const auto& object : objects)
				{
					std::string wkt;
					wkt += "POLYGON((";
					if (object.getTileID() - 1 == 64)
					{
						for (int i = 0; i< polygon[object.getTileID() - 1].size(); i++)
						{
							std::string tmp;
							tmp = std::to_string((int)polygon[object.getTileID() - 1][i].x + (int)object.getPosition().x);
							wkt += tmp;
							wkt += " ";
							tmp = std::to_string((int)polygon[object.getTileID() - 1][i].y + (int)object.getPosition().y);
							wkt += tmp;

							if (i + 1 < polygon[object.getTileID() - 1].size())
								wkt += ",";
							else
								wkt += "))";
						}
						printf("%s\n", wkt.c_str());
						poly_wkt.push_back(wkt);
					}

				}

			}
		}

	}
}

GameMap::~GameMap()
{
	sceneTiles.clear();
	sceneTiles.shrink_to_fit();
}

int GameMap::getMapW()
{
	return mapW;
}

int GameMap::getMapH()
{
	return mapH;
}

void GameMap::setMapW(int w)
{
	mapW = w;
}

void GameMap::setMapH(int h)
{
	mapH = h;
}

int GameMap::getTileW()
{
	return tileW;
}

int GameMap::getTileH()
{
	return tileH;
}

int GameMap::getTileAmount()
{
	return tileAmount;
}

void GameMap::draw(int x, int y, int w, int h, SDL_Renderer *renderer, std::vector<SDL_Texture*>tilesets)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = tileW;
	src.h = tileH;
	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = tileW;
	dst.h = tileH;

	int xStart, yStart;
	int limitX, limitY, limit;
	int startIndexX, startIndexY;
	int startIndex;
	bool p;
	int tilesetAmountW, tilesetAmountH, tilesetCount;
	tilesetCount = map.getTilesets()[0].getTileCount();
	tilesetAmountW = map.getTilesets()[0].getColumnCount();
	tilesetAmountH = tilesetCount / tilesetAmountW;

	int actualID;
	int row, col;

	limitX = w / tileW + 4;

	if (w % tileW == 0)
		limitX++;

	limitY = h / (tileH / 2) + 3;

	if (h % (tileH / 2) == 0)
		limitY++;

	limit = limitX * limitY;

	startIndexX = x / tileW - 1;
	startIndexY = y / (tileH/2) - 2;

	if (startIndexX < 0)
		startIndexX = 0;
	if (startIndexY < 0)
		startIndexY = 0;
	if (startIndexX > (mapW / tileW) - limitX)
		startIndexX = (mapW / tileW) - limitX - 1;
	if (startIndexY >(mapH / (tileH / 2)) - limitY)
		startIndexY = (mapH / (tileH / 2) - limitY) - 1;

	startIndex = (startIndexY) * map.getTileCount().x + startIndexX;

	xStart = -(x - startIndexX * tileW);
	yStart = -(y - startIndexY * (tileH/2));

	if (startIndexY % 2 == 0)
		p = true;
	else
		p = false;

	if (p == false)
		dst.x += (tileW/2);

	const auto& layers = map.getLayers();
	for (const auto& layer : layers)
	{
		dst.x = xStart;
		dst.y = yStart;

		if (layer->getType() == tmx::Layer::Type::Tile)
		{
			const auto& tiles = dynamic_cast<tmx::TileLayer*>(layer.get())->getTiles();

			for (int i = startIndex, k = 0; k < limit; i++, k++)
			{
				if (k % limitX == 0 && k != 0)
				{
					if (p == true)
					{
						p = false;
						dst.x = xStart + (tileW/2);
					}
					else
					{
						p = true;
						dst.x = xStart;
					}

					dst.y += (tileH/2);

					i += (map.getTileCount().x - limitX);
				}
				if (i >= map.getTileCount().x * map.getTileCount().y)
					return;
				else
				{
					actualID = tiles[i].ID - 1;
					row = actualID / (tilesetAmountW);
					col = actualID - (tilesetAmountW * row);

					src.x = col * src.w;
					src.y = row * src.h;

					SDL_RenderCopy(renderer, tilesets[0], &src, &dst);
					dst.x += tileW;
				}
			}
		}
		else if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objects = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();

			// zoptymalizowaæ - nie moga sie wyswietlac wszystkie obiekty tylko te widoczne

			for (const auto& object : objects)
			{
				dst.x = object.getPosition().x - x;
				dst.y = object.getPosition().y - y;
				//SDL_Texture *tmp2 = NULL;
				actualID = object.getTileID() - 1;

				//for (const auto& tileset : map.getTilesets())
				//{
					//if (actualID > tileset.getLastGID())
					//{
						//for (int i = 0; i<tileset.getTiles().size() ; i++)
						//{
						//	if (tileset.getTiles()[i].ID == actualID - tileset.getTileCount())
							//{
								//SDL_Surface * tmp = IMG_Load(tilesets[0]);
								//printf("%s\n", tile.imagePath.c_str());
								//tmp2 = SDL_CreateTextureFromSurface(renderer, tilesets[0]);
								//SDL_FreeSurface(tmp);
						//	}
						//}
					//}
					row = actualID / (tilesetAmountW);
					col = actualID % tilesetAmountW;

					src.x = col * src.w;
					src.y = row * src.h;

					SDL_RenderCopy(renderer, tilesets[0], &src, &dst);
					//break;
			//	}
			}

		}
	}

}

bool GameMap::isCollision(int x, int y)
{
	p.x(x);
	p.y(y);
	const auto& layers = map.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objects = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();
			int i = 0;
			for (const auto& object : objects)
			{
				poly.clear();
				std::string wkt;
				//wkt += "POLYGON((";
				if (object.getTileID() - 1 == 64)
				{
					if (!(abs(object.getPosition().x - x) < radiusX && abs(object.getPosition().y - y) < radiusY))
					{
						i++;
						continue;
					}

					wkt = poly_wkt[i];
					boost::geometry::read_wkt(wkt.c_str(), poly);

					if (boost::geometry::within(p, poly))
						return true;
					else
					{
						i++;
						continue;
					}

				}

			}

		}
	}
	//return false;
	return false;
}

bool GameMap::isSmaller(const tmx::Object &i,const tmx::Object &j)
{
	return (i.getPosition().y < j.getPosition().y);
}