/*******************************************************************************
* File: spriteatlas.cc
* Author: Robert Smith
* Created: 2015 FEB 3
* Version: 0
* Revised: 2015 FEB 3
*
* 
*******************************************************************************/

#include "spriteatlas.h"
#include <string>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>


/*******************************
* Constructors and Destructor */
std::string type;

SpriteAtlas::SpriteAtlas(std::string tstType, int iWidthOfSpriteInPixels, int iHeightOfSpriteInPixels, int iMaxNumberOfSprites=0, std::string filename="spritesheet.jpg"){
	this->type = tstType;
	 
	this->spriteHeight = iHeightOfSpriteInPixels;
	this->spriteWidth = iWidthOfSpriteInPixels;
	this->numberOfSprites = iMaxNumberOfSprites;

	iTextureName;
	   
	//GH: By default, we haven't loaded a texture
	this->bTexturesCurrentlyLoaded = false;
	this->sheetWidth = 0;
	this->sheetHeight = 0;
	this->spritesPerRow = 0;
	
	if(filename!=""){
		this->loadImage(filename);
	}
}


SpriteAtlas::~SpriteAtlas(void) {
}

bool SpriteAtlas::Init(void) {
  return false;
}

/*******************************
* Methods                     */
void SpriteAtlas::loadImage(std::string filename){

}

void SpriteAtlas::del(){
	glDeleteBuffers(1, &iTextureName);
}

std::string SpriteAtlas::SheetType(){
	return type;
}

void SpriteAtlas::bindTexture(){
	glBindTexture(GL_TEXTURE_2D, iTextureName);
}

float * SpriteAtlas::getTextureCoordinates(int index){
	if((index < 0) && (index >=numberOfSprites)){
		std::cout << "Loading out of bound texture on sprite sheet";
	}
	float edges[4];

	edges[0] = float(spriteHeight*(index/spritesPerRow))/sheetHeight;
	edges[1] = float(spriteHeight*(index/spritesPerRow)+spriteHeight)/sheetHeight;
	edges[2] = float(spriteWidth*(index % spritesPerRow))/sheetWidth;
	edges[3] = float(spriteWidth*(index % spritesPerRow)+sheetWidth)/sheetWidth;
	return edges;
}

/*******************************
* Accessors and Mutators      */