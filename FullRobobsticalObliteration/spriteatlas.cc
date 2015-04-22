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
using namespace Texture;

/*******************************
* Constructors and Destructor */
Jzon::Object rootNode;
std::string type;
unsigned int width, height;


SpriteAtlas::SpriteAtlas(){
	
	/*std::string filename = targetfile;*/
	/*if(filename!=""){*/
	Jzon::FileReader::ReadFile("../Graphics/sprite_map.json", rootNode);
		loadImage(filename);
	/*}*/

}


SpriteAtlas::~SpriteAtlas(void) {
	glDeleteBuffers(1, &froTexture);
}

/*******************************
* Methods                     */
void SpriteAtlas::loadImage(std::string filename){
  std::vector<unsigned char> image; 
  
  lodepng::decode(image,width,height,"../Graphics/fro_fullsheet.png");

	std::cout << "IMAGE LOADED!";

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

void SpriteAtlas::getCoordinates(std::string targetTexture, Texture::TEXTURE_CORNER corner){

	

	const Jzon::Array &stuff = SpriteAtlas::rootNode.Get(targetTexture).AsArray();

	Jzon::Array::const_iterator it = stuff.begin(); 
	//it != stuff.end(); ++it
	   
			// std::cout << (*it).ToString() << std::endl;
			 std::string left = (*it).ToString();
			 double toppercent = atof(left.c_str());
			 toppercent = toppercent/width;
			 ++it;
			 std::string top = (*it).ToString();
			 double rightpercent = atof(top.c_str());
			 rightpercent = rightpercent/height;
			 ++it;
			 std::string right = (*it).ToString();
			 double bottompercent = atof(right.c_str());
			 bottompercent = bottompercent/width;
			 ++it;
			 std::string bottom = (*it).ToString();
			 double leftpercent = atof(bottom.c_str());
			 leftpercent = leftpercent/height;
			 ++it;
			 if (corner == LOWER_LEFT) {
				 glTexCoord2d(toppercent, leftpercent);
			 }
			 if (corner == UPPER_LEFT) {
				 glTexCoord2d(toppercent,rightpercent);
			 }
			 if (corner == LOWER_RIGHT) {
				 glTexCoord2d(bottompercent, leftpercent);
			 }
			 if (corner == UPPER_RIGHT) {
				 glTexCoord2d(bottompercent, rightpercent);
	   }
	   
}



