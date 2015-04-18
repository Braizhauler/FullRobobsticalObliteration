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

using std::ios;

/*******************************
* Constructors and Destructor */
std::string type;

SpriteAtlas::SpriteAtlas(std::string filename){
	is_file_loaded_ = false;
	if(filename!=""){
		loadImage(filename);
	}

}


SpriteAtlas::~SpriteAtlas(void) {
	glDeleteBuffers(1, &gl_texture_name_);
}

/*******************************
* Methods                     */
void SpriteAtlas::loadImage(std::string filename){
  std::vector<unsigned char> image; 
  unsigned int width, height;
  lodepng::decode(image,width,height,filename);

	std::cout << "IMAGE LOADED!";

	/*CImg<unsigned char> src("../Graphics/fro_fullsheet.png");
	std::cout << "IMAGE LOADED!";
  CImg<unsigned char> interleaved = src.get_permute_axes("xyzc");
  src.data();
  */
	glGenTextures(1, &gl_texture_name_);
	glBindTexture(GL_TEXTURE_2D, gl_texture_name_);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, image.data());
}

void displayTexture(std::string targetTexture, char*** memoryImage){

}

void loadCoordinates(std::string filename) {

}

int * SpriteAtlas::getCoordinates(std::string targetTexture){

	Jzon::Object rootNode;
	Jzon::FileReader::ReadFile("../Graphics/sprite_map.json", rootNode);
	
	const Jzon::Array &stuff = rootNode.Get(targetTexture).AsArray();

	for (Jzon::Array::const_iterator it = stuff.begin(); it != stuff.end(); ++it)
	{
		std::cout << (*it).ToString() << std::endl;
	}
	return 0;
}


void SetTextureCorner(int texture, Texture::TEXTURE_CORNER corner) {
  using namespace Texture;
  if(corner == UPPER_LEFT) {
    //glTexCoord2d();
  }
}
