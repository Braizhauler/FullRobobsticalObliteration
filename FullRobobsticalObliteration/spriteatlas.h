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

// Include GLEW
#include <GL/glew.h>

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
  //Constructors, Init, and Destructor
  SpriteAtlas(std::string filename = "../Graphics/fro_fullsheet.png");
  ~SpriteAtlas(void);

  //Methods
  void bindTexture();
  void loadImage(std::string filename);
  void loadCoordinates(std::string filename);
  bool fileExists(std::string filename);

  void SetTextureCorner(int texture, Texture::TEXTURE_CORNER);


  int * getCoordinates(std::string filename);
  float * getTextureCoordinates(int index);
private:
	
  Jzon::Object root_node_;

	int sheet_width_pixels_;
	int sheet_height_pixels_;
    
  GLuint gl_texture_name_;

	bool is_file_loaded_;

};


#endif SPRITE_ATLAS_H