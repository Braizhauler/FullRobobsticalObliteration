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


SpriteAtlas::SpriteAtlas(std::string targetfile="spritesheet.jpg"){
	
	std::string filename = targetfile;
	if(filename!=""){
		loadImage(filename);
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

void loadImage(std::string filename){

	CImg<unsigned char> src("Graphics/fro_fullsheet.png");
	int width = src.width();
	int height = src.height();
	unsigned char* allPixels[1792][4096];
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			allPixels[j][i]= src.data(j,i);
		}
	}
	
	//return 0; 
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



