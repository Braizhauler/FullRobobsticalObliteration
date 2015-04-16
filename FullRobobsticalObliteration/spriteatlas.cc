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



#define cimg_plugin "plugins/jpeg_buffer.h"


using std::ios;
using namespace cimg_library; 

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

	CImg<unsigned char> src("../Graphics/fro_fullsheet.png");
	std::cout << "IMAGE LOADED!";

	GLuint froTexture = 0;

	/*glGenTextures(1, &froTexture);*/
	glBindTexture(GL_TEXTURE_2D, froTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, src.width(), src.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, src);
}

void displayTexture(std::string targetTexture, char*** memoryImage){

}

int * getCoordinates(std::string targetTexture){
	
	Jzon::Object rootNode;
	Jzon::FileReader::ReadFile("Graphics/sprite_map.json", rootNode);
	
	const Jzon::Array &stuff = rootNode.Get(targetTexture).AsArray();
	   for (Jzon::Array::const_iterator it = stuff.begin(); it != stuff.end(); ++it)
	   {
			 std::cout << (*it).ToString() << std::endl;
	   }
	return 0;
}



