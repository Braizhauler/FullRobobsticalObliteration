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

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

using std::ios;

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
	float edges [4];

	edges[0] = float(spriteHeight*(index/spritesPerRow))/sheetHeight; //TOP
	edges[1] = float(spriteHeight*(index/spritesPerRow)+spriteHeight)/sheetHeight; //BOTTOM
	edges[2] = float(spriteWidth*(index % spritesPerRow))/sheetWidth; //LEFT
	edges[3] = float(spriteWidth*(index % spritesPerRow)+sheetWidth)/sheetWidth; //RIGHT
	return edges;
}

void SpriteAtlas::loadImage(std::string filename){
	if(bTexturesCurrentlyLoaded == true){
		glDeleteBuffers(1, &iTextureName);
		std::cout << "Loading texture into spritesheet with texture already loaded";
	}
	bool fileSeemsValid = false;
	int colorMode = GL_RGB;
	char * databuffer = nullptr;
  //TODO: check for file exisitance
	if(fileExists(filename)){
			
		std::ifstream image;
		image.open("C:\\bbb.bmp", std::ios_base::binary);

		image.seekg (0, ios::end);
		int n = image.tellg();
		image.seekg (0, ios::beg);

		char* res = new char[n];
		for(int i = 0; i < n; i++)
			res[i] = '5';

		bool bit = image.eof();

		image.read(res, n);

			std::fstream f;
			f.open(filename, std::fstream::in);
			
      //TODO: Open the image
      //img = IMGLIB.open(f);

      //TODO: Validate Header
			//img.verify();
			fileSeemsValid = true;

      //TODO: READ HEADER DATA
			//std::fseek(f,0);
			//img = IMGLIB.open(f);  //Move file pointer to begining of file
			//(sheetWidth, sheetHeight) = img.size;
			//if(img.mode == "RGBA"){
			//	colorMode = GL_RGBA;
			//}
			//else if(img.mode == "RGB")
			//{
			//	colorMode = GL_RGB;
			//}
			//img.getdata();
      //TODO: Fix this to the size of the file data
			databuffer = new char[20];
		  f.read(databuffer,20);
		f.close();
	}
	if(fileSeemsValid){
		glGenTextures(1,&iTextureName);

		glPixelStorei(GL_UNPACK_ALIGNMENT,1);

		glBindTexture(GL_TEXTURE_2D, iTextureName);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if(databuffer != nullptr)
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sheetWidth, sheetHeight, 0, colorMode, GL_UNSIGNED_BYTE, databuffer);

		bTexturesCurrentlyLoaded = true;
		spritesPerRow = sheetWidth / spriteWidth;
	}
  delete [] databuffer;
}

bool SpriteAtlas::fileExists(std::string filename){
	std::ifstream iff(filename.c_str());  
	return iff.is_open(); 
}
;
/*******************************
* Accessors and Mutators      */