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

class SpriteAtlas
{
public:
  //Constructors, Init, and Destructor
  SpriteAtlas(void);
  bool Init(void);
  ~SpriteAtlas(void);

  //Methods

  //Accessors and Mutators
private:
  int _imageBufferName;
};


#endif SPRITE_ATLAS_H