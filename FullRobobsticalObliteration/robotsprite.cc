#include "robotsprite.h"


RobotSprite::RobotSprite(GameStateManager* manager,const int robot) {
  manager_=manager;
  atlas_=manager_->TextureAtlas();
  sprite_prefix_;
  SetSpritePrefix(robot);
  animation_frame_=0;
}


RobotSprite::~RobotSprite(void) {
}

void RobotSprite::SetSpritePrefix(const int robot_number) {
  sprite_prefix_ = "r";
  sprite_prefix_.append(std::to_string(robot_number));
  sprite_prefix_.append("_");

}


void RobotSprite::Draw(const double camera_angle) {
  using namespace Robot;
  glColor3f(1.00f, 1.00f, 1.00f);
  Robot::RELATIVE_POSITION_8_WAY origin_position = OriginPosition();
  int image_number_ = (2*facing_+origin_position)%8;
  image_number_+=8*animation_frame_+1;
  std::string sprite_name;
  sprite_name.append(std::to_string(image_number_) );
  if(origin_position==FAR){
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(tile.x,  tile.y+1, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(tile.x,  tile.y+1, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(tile.x+1,  tile.y, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(tile.x+1,  tile.y, 1.0);
  }
  if(origin_position==FAR_LEFT){
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(tile.x-0.2,  tile.y+0.5, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(tile.x-0.2,  tile.y+0.5, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(tile.x+1.2,  tile.y+0.5, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(tile.x+1.2,  tile.y+0.5, 1.0);
  }
  if(origin_position==LEFT){
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(tile.x,  tile.y, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(tile.x,  tile.y, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(tile.x+1,  tile.y+1, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(tile.x+1,  tile.y+1, 1.0);
  }
  if(origin_position==NEAR_LEFT){
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(tile.x+0.5,  tile.y-0.2, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(tile.x+0.5,  tile.y-0.2, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(tile.x+0.5,  tile.y+1.2, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(tile.x+0.5,  tile.y+1.2, 1.0);
  }
  if(origin_position==NEAR){
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(tile.x+1,  tile.y, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(tile.x+1,  tile.y, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(tile.x,  tile.y+1, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(tile.x,  tile.y+1, 1.0);
  }
  if(origin_position==NEAR_RIGHT){
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(tile.x+1.2,  tile.y+0.5, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(tile.x+1.2,  tile.y+0.5, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(tile.x-0.2,  tile.y+0.5, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(tile.x-0.2,  tile.y+0.5, 1.0);
  }
  if(origin_position==RIGHT){
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(tile.x+1,  tile.y+1, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(tile.x+1,  tile.y+1, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(tile.x,  tile.y, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(tile.x,  tile.y, 1.0);
  }
  if(origin_position==FAR_RIGHT){
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(tile.x+.5,  tile.y+1.2, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(tile.x+.5,  tile.y+1.2, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(tile.x+.5,  tile.y-0.2, -0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(tile.x+.5,  tile.y-0.2, 1.0);
  }
}

Robot::RELATIVE_POSITION_8_WAY RobotSprite::OriginPosition() const {
  int offset_angle = (angle_+22.5);
  if(offset_angle>=360) offset_angle-=360;
    Robot::RELATIVE_POSITION_8_WAY position=
      Robot::RELATIVE_POSITION_8_WAY((offset_angle/45));
  if(position==INVALID)position=FAR_LEFT;
  return position;
}