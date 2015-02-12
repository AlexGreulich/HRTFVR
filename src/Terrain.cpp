#ifndef HRTFVR_TERRAIN_CPP
#define HRTFVR_TERRAIN_CPP

#include "Terrain.h"

Terrain::Terrain(){

}

void Terrain::Generate(){
	/*int count = VERTEX_COUNT * VERTEX_COUNT;
	float vertices[count * 3];
	float normals[count * 3];
	float textureCoords[count * 2];
	int indices[6 * (VERTEX_COUNT-1) * (VERTEX_COUNT*1) ];
	int vertexPointer = 0;

	for(int i = 0; i < VERTEX_COUNT; i++){
		for(int j = 0; j < VERTEX_COUNT; j++){
			vertices[vertexPointer * 3] = j / (VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer * 3+1] = 0;
			vertices[vertexPointer * 3+2] = i / (VERTEX_COUNT - 1) * SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3+1] = 1;
			normals[vertexPointer * 3+2] = 0;
			textureCoords[vertexPointer * 2] = j / (VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2+1] = i / (VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}

	int pointer = 0;

	for(int gz=0;gz<VERTEX_COUNT-1;gz++){
		for(int gx=0;gx<VERTEX_COUNT-1;gx++){
			int topLeft = (gz*VERTEX_COUNT)+gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}*/

}

Terrain::~Terrain(){

}

#endif