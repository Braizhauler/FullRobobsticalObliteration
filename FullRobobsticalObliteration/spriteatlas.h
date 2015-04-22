/******************************&************************************************
* File: spriteatlas.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 21
* Version: 0
* Revised: 2015 JAN 21
*
* SpriteAtlas:
* A GL texture loader with texture coordiate maps.
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef SPRITE_ATLAS_H
#define SPRITE_ATLAS_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

#include "lodepng.h"

//Include JZon
#include "Jzon.h"

namespace Texture {
enum TEXTURE_CORNER {
  UPPER_LEFT,
  UPPER_RIGHT,
  LOWER_LEFT,
  LOWER_RIGHT
};

struct Texture_Data {
  std::string name;
  double top, left, right, bottom;
};
}



class SpriteAtlas
{
public:

	Jzon::Object rootNode;
  //Constructors, Init, and Destructor
  SpriteAtlas();
  bool Init(void);
  ~SpriteAtlas(void);

  //Methods
  void del();
  std::string SheetType(SpriteAtlas SA);
  void bindTexture(SpriteAtlas SA);
  float getTextureCoordinates(SpriteAtlas SA, int index);
  void SpriteAtlas::loadImage(std::string filename);
  bool fileExists(std::string filename);
  void SpriteAtlas::bindTexture();
  void getCoordinates(std::string tartgetTexture, Texture::TEXTURE_CORNER corner);

  //Accessors and Mutators
  std::string SheetType();

  float * getTextureCoordinates(int index);
private:
	std::string filename;

	std::string type;

	GLuint froTexture;

	int spriteHeight;
	int spriteWidth;
	int numberOfSprites;
	   
	bool bTexturesCurrentlyLoaded;
	unsigned int iTextureName;
	int sheetWidth;
	int sheetHeight;
	int spritesPerRow;

	bool fileSeemsValid;

};


#endif SPRITE_ATLAS_H