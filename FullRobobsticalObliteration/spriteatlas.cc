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
#include <fstream>

//Include CImg
#include "CImg.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

#define cimg_plugin "plugins/jpeg_buffer.h"

using std::ios;
using namespace cimg_library; 

/*******************************
* Constructors and Destructor */
std::string type;

SpriteAtlas::SpriteAtlas(std::string tstType, int iWidthOfSpriteInPixels, int iHeightOfSpriteInPixels, int iMaxNumberOfSprites=0, std::string filename="spritesheet.jpg"){
	type = tstType;
	 
	spriteHeight = iHeightOfSpriteInPixels;
	spriteWidth = iWidthOfSpriteInPixels;
	numberOfSprites = iMaxNumberOfSprites;

	iTextureName;
	   
	//GH: By default, we haven't loaded a texture
	bTexturesCurrentlyLoaded = false;
	sheetWidth = 0;
	sheetHeight = 0;
	spritesPerRow = 0;
	
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
void SpriteAtlas::del(){
	glDeleteBuffers(1, &iTextureName);
}

std::string SpriteAtlas::SheetType(SpriteAtlas SA){
	return type;
}
std::string SpriteAtlas::SheetType(){

	return type;
}

void SpriteAtlas::bindTexture(){
	glBindTexture(GL_TEXTURE_2D, iTextureName);
}

float SpriteAtlas::getTextureCoordinates(SpriteAtlas SA, int index){
	if(index < 0 & index >=SA.numberOfSprites){
		std::cout << "Loading out of bound texture on sprite sheet";
	}
	float edges [4];

	edges[0] = float(SA.spriteHeight*(index/SA.spritesPerRow))/SA.sheetHeight; //TOP
	edges[1] = float(SA.spriteHeight*(index/SA.spritesPerRow)+SA.spriteHeight)/SA.sheetHeight; //BOTTOM
	edges[2] = float(SA.spriteWidth*(index % SA.spritesPerRow))/SA.sheetWidth; //LEFT
	edges[3] = float(SA.spriteWidth*(index % SA.spritesPerRow)+SA.sheetWidth)/SA.sheetWidth; //RIGHT
	return edges [4];
}

void SpriteAtlas::loadImage(unsigned char filename){
	if(bTexturesCurrentlyLoaded == true){
		glDeleteBuffers(1, iTextureName);
		std::cout << "Loading texture into spritesheet with texture already loaded";
	}
	fileSeemsValid = false;
	colorMode = GL_RGB;
	databuffer;
	if(fileExists(filename)){
		const CImg<unsigned char> image = CImg<>(filename);
	}
	if(fileSeemsValid){
		glGenTextures(1, filename);

		glPixelStorei(GL_UNPACK_ALIGNMENT,1);

		glBindTexture(GL_TEXTURE_2D, iTextureName);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sheetWidth, sheetHeight, 0, colorMode, GL_UNSIGNED_BYTE, databuffer);

		bTexturesCurrentlyLoaded = true;
		spritesPerRow = sheetWidth / spriteWidth;
	}
}

bool SpriteAtlas::fileExists(unsigned char filename){
	std::ifstream iff(filename.c_str());  
	return iff.is_open(); 
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

