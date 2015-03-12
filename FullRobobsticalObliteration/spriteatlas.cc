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
void SpriteAtlas::loadImage(std::string filename){

}

void SpriteAtlas::del(){
	glDeleteBuffers(1, &iTextureName);
}

<<<<<<< HEAD
std::string SpriteAtlas::SheetType(SpriteAtlas SA){
=======
std::string SpriteAtlas::SheetType(){
>>>>>>> origin/DisableSpriteAtlas
	return type;
}

void SpriteAtlas::bindTexture(){
	glBindTexture(GL_TEXTURE_2D, iTextureName);
}

<<<<<<< HEAD
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

void SpriteAtlas::loadImage(SpriteAtlas SA, std::string filename){
	if(bTexturesCurrentlyLoaded == true){
		glDeleteBuffers(1, SA.iTextureName);
		std::cout << "Loading texture into spritesheet with texture already loaded";
	}
	fileSeemsValid = false;
	colorMode = GL_RGB;
	databuffer;
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




			FILE f;
			f = fopen(filename, "rb");
			ing = IMGLIB.open(f);

			img.verify();
			fileSeemsValid = true;

			f.seek(0);
			img = IMGLIB.open(f);
			(SA.sheetWidth, SA.sheetHeight) = img.size;
			if(img.mode == "RGBA"){
				colorMode = GL_RGBA;
			}
			else if(img.mode == "RGB")
			{
				colorMode = GL_RGB;
			}
			img.getdata();
			databuffer = img.getdata();
		
		f.close()
	}
	if(fileSeemsValid){
		SA.iTextureName = glGenTextures(1, '');

		glPixelStorei(GL_UNPACK_ALIGNMENT,1);

		glBindTexture(GL_TEXTURE_2D, SA.iTextureName);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SA.sheetWidth, SA.sheetHeight, 0, colorMode, GL_UNSIGNED_BYTE, databuffer);

		SA.bTexturesCurrentlyLoaded = true;
		SA.spritesPerRow = SA.sheetWidth / SA.spriteWidth;
	}
}

bool SpriteAtlas::fileExists(std::string filename){
	std::ifstream iff(filename.c_str());  
	return iff.is_open(); 
}


=======
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

>>>>>>> origin/DisableSpriteAtlas
/*******************************
* Accessors and Mutators      */