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
SpriteAtlas::SpriteAtlas(){
	
	/*std::string filename = targetfile;*/
	/*if(filename!=""){*/
	Jzon::FileReader::ReadFile("../Graphics/sprite_map.json", root_node_);
  loadImage();
	/*}*/
  active_texture_name_="";

}


SpriteAtlas::~SpriteAtlas(void) {
	glDeleteBuffers(1, &texture_gl_name_);
}

/*******************************
* Methods                     */
void SpriteAtlas::loadImage(std::string filename){
  std::vector<unsigned char> image; 
  
  lodepng::decode(image,sheet_width_,sheet_height_,filename);
  
	glGenTextures(1, &texture_gl_name_);
	glBindTexture(GL_TEXTURE_2D, texture_gl_name_);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			sheet_width_, sheet_height_, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, image.data());
}

void SpriteAtlas::getCoordinates(std::string targetTexture,
                                 Texture::TEXTURE_CORNER corner){
	const Jzon::Array &stuff = SpriteAtlas::root_node_.Get(targetTexture).AsArray();

	Jzon::Array::const_iterator it = stuff.begin(); 
	//it != stuff.end(); ++it
	   
	// std::cout << (*it).ToString() << std::endl;
	std::string left = (*it).ToString();
	double toppercent = atof(left.c_str());
	toppercent = toppercent/sheet_width_;
	++it;
	std::string top = (*it).ToString();
	double rightpercent = atof(top.c_str());
	rightpercent = rightpercent/sheet_height_;
	++it;
	std::string right = (*it).ToString();
	double bottompercent = atof(right.c_str());
	bottompercent = bottompercent/sheet_width_;
	++it;
	std::string bottom = (*it).ToString();
	double leftpercent = atof(bottom.c_str());
	leftpercent = leftpercent/sheet_height_;
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



void SpriteAtlas::ActivateTexture(std::string texture_name) {
  //if it's already active, don't bother reloading it
  if(active_texture_name_==texture_name) return;
  //if we don't have the texture in the file, quit befor we error
  if(!root_node_.Has(texture_name)) return;
	const Jzon::Array &active_texture = root_node_.Get(texture_name).AsArray();
  active_texture_name_ = texture_name;
	Jzon::Array::const_iterator it = active_texture.begin(); 
  //somehow we ended up sideways, but this is where we're fixing it.
  //Using int to string to double because the Json has "" in it.
	active_texture_top_= std::stod((*it).ToString()) /sheet_width_;
	active_texture_right_= std::stod((*(++it)).ToString())/sheet_height_;
	active_texture_bottom_= std::stod((*(++it)).ToString())/sheet_width_;
	active_texture_left_= std::stod((*(++it)).ToString())/sheet_height_;

}
void SpriteAtlas::LoadCoordinates(Texture::TEXTURE_CORNER corner) {
  if (corner == LOWER_LEFT)
    glTexCoord2d(active_texture_top_,active_texture_left_);
  if (corner == UPPER_LEFT)
    glTexCoord2d(active_texture_top_,active_texture_right_);
  if (corner == LOWER_RIGHT)
    glTexCoord2d(active_texture_bottom_,active_texture_left_);
  if (corner == UPPER_RIGHT)
    glTexCoord2d(active_texture_bottom_,active_texture_right_);
}