#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include "TileMap.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	map = new int[mapSize.x * mapSize.y];
	for (int j = 0; j<mapSize.y; j++)
	{
		getline(fin, line);
		sstream.str(line);
		string delimiter = " ";
		for (int i = 0; i<mapSize.x; i++)
		{
			string tile = line.substr(0, line.find(delimiter));
			if (stoi(tile) == 0)
				map[j*mapSize.x + i] = 0;
			else
				map[j*mapSize.x + i] = stoi(tile);
			line.erase(0, line.find(delimiter) + delimiter.length());
		}
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	//halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	halfTexel = glm::vec2(0.0625f / tilesheet.width(), 0.0625f / tilesheet.height());
	for (int j = 0; j<mapSize.y; j++)
	{
		for (int i = 0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				//texCoordTile[0] = glm::vec2(float((tile-1)%2) / tilesheetSize.x, float((tile-1)/2) / tilesheetSize.y);
				texCoordTile[0] = glm::vec2(float((tile - 1) % 16) / tilesheetSize.x, float((tile - 1) / 16) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
}


// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		/*if(map[y*mapSize.x+x] == 0)
			return true;*/
		if (map[y*mapSize.x + x] == 112 || map[y*mapSize.x + x] == 113) {
			return true;
		}
	}
	
	return false;
}

bool TileMap::isTerrainAhead(const glm::ivec2 &pos, const glm::ivec2 &size, string dir) const
{
	int x, y0, y1;

	x = (pos.x / tileSize) + 1;
	y0 = (pos.y + size.y - 1) / tileSize;
	y1 = (pos.y + size.y + 1) / tileSize;
	if (dir == "LEFT") {
		for (int y = y0; y <= y1; ++y)
		{
			if (map[y*mapSize.x + x] == 112 || map[y*mapSize.x + x] == 113
				|| map[y*mapSize.x + x] == 7 || map[y*mapSize.x + x] == 8) {
				return true;
			}
		}
		return false;
	}
	else {

	}

}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		/*if(map[y*mapSize.x+x] == 0)
			return true;*/
		if (map[y*mapSize.x + x] == 112 || map[y*mapSize.x + x] == 113) {
			return true;
		}

		else if (map[y*mapSize.x + x] == 58 || map[y*mapSize.x + x] == 63
			|| map[y*mapSize.x + x] == 68 || map[y*mapSize.x + x] == 72
			|| map[y*mapSize.x + x] == 76 || map[y*mapSize.x + x] == 80
			|| map[y*mapSize.x + x] == 84 || map[y*mapSize.x + x] == 88
			|| map[y*mapSize.x + x] == 92 || map[y*mapSize.x + x] == 96) {
			return true;
		}
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y*mapSize.x + x] != 0)
		{
			/*if(*posY - tileSize * y + size.y <= -112)
			{
				*posY = tileSize * y - size.y;
				return true;
			}*/
			// special case. We need to ensure that the main character collides 
			// with the last water tile, not the first one as it would cause unrealistic efect
			if (map[y*mapSize.x + x] == 1 && y == 14) {
				*posY = tileSize * y - size.y;
				return true;
			}
			else if (map[y*mapSize.x + x] == 7 || map[y*mapSize.x + x] == 8 ||
				map[y*mapSize.x + x] == 112 || map[y*mapSize.x + x] == 113) {
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}

	return false;
}


bool TileMap::collisionMoveDownLv2(const glm::ivec2 &pos, const bool canMove, int *posY) const
{
	if (!canMove && pos.y >= 9 * 32) {
		*posY -= 4;
		return true;
	}
	else if (canMove) {
		*posY -= 4;
		return true;
	}
	else return false;
}

























