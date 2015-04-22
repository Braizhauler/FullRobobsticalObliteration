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

/*struct Texture_Data {
  std::string name;
  double top, left, right, bottom;
};*/
}

class SpriteAtlas {
public:
  //Constructors, Init, and Destructor
  SpriteAtlas();
  ~SpriteAtlas(void);
  //Methods
  void SpriteAtlas::loadImage(std::string filename=
                                               "../Graphics/fro_fullsheet.png");
  void getCoordinates(std::string tartgetTexture,
                      Texture::TEXTURE_CORNER corner); 
  void ActivateTexture(std::string texture_name);
  void LoadCoordinates(Texture::TEXTURE_CORNER corner);
private:
  Jzon::Object root_node_;
  GLuint texture_gl_name_;

  unsigned int sheet_width_;
  unsigned int sheet_height_;

  std::string active_texture_name_;
  double active_texture_top_;
  double active_texture_left_;
  double active_texture_bottom_;
  double active_texture_right_;
};


#endif SPRITE_ATLAS_H