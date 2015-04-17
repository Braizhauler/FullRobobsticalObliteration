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


SpriteAtlas::SpriteAtlas(){
	
	/*std::string filename = targetfile;*/
	/*if(filename!=""){*/
		loadImage(filename);
	/*}*/

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

void SpriteAtlas::loadImage(std::string filename){
  std::vector<unsigned char> image; 
  unsigned int width, height;
  lodepng::decode(image,width,height,"../Graphics/fro_fullsheet.png");

	std::cout << "IMAGE LOADED!";

	/*CImg<unsigned char> src("../Graphics/fro_fullsheet.png");
	std::cout << "IMAGE LOADED!";
  CImg<unsigned char> interleaved = src.get_permute_axes("xyzc");
  src.data();
  */
	GLuint froTexture = 0;
	glGenTextures(1, &froTexture);
	glBindTexture(GL_TEXTURE_2D, froTexture);
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



