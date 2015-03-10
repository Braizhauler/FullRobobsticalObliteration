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
	glDeleteBuffers(1, iTextureName);
}

std::string SpriteAtlas::SheetType(SpriteAtlas SA){
	return SA.type;
}

void SpriteAtlas::bindTexture(SpriteAtlas SA){
	glBindTexture(GL_TEXTURE_2D, iTextureName);
}

void SpriteAtlas::getTextureCoordinates(SpriteAtlas SA, int index){
	if(index < 0 & index >=SA.numberOfSprites){
		std::cout << "Loading out of bound texture on sprite sheet";
	}
	float edges;

	edges["top"] = float(SA.spriteHeight*(index/SA.spritesPerRow))/SA.sheetHeight;
	edges["bottom"] = float(SA.spriteHeight*(index/SA.spritesPerRow)+SA.spriteHeight)/SA.sheetHeight;
	edges["left"] = float(SA.spriteWidth*(index % SA.spritesPerRow))/SA.sheetWidth;
	edges["right"] = float(SA.spriteWidth*(index % SA.spritesPerRow)+SA.sheetWidth)/SA.sheetWidth;
	return edges;
}

void SpriteAtlas::loadImage(SpriteAtlas SA, std::string filename){

}


/*******************************
* Accessors and Mutators      */