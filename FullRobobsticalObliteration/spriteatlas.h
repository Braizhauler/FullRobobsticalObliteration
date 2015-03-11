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

class SpriteAtlas
{
public:
  //Constructors, Init, and Destructor
  SpriteAtlas(std::string ststType, int iWidthOfSpriteInPixels, int iHeightOfSpriteInPixels, int iMaxNumberOfSprites, std::string filename);
  bool Init(void);
  ~SpriteAtlas(void);

  //Methods
  void loadImage(std::string filename);
  void del();
  //Accessors and Mutators
  std::string SheetType();
  void bindTexture();

  float * getTextureCoordinates(int index);
private:
	std::string filename;

	std::string type;
	 
	int spriteHeight;
	int spriteWidth;
	int numberOfSprites;
	   
	bool bTexturesCurrentlyLoaded;
	unsigned int iTextureName;
	int sheetWidth;
	int sheetHeight;
	int spritesPerRow;
};


#endif SPRITE_ATLAS_H