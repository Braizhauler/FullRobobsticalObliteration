#include "robotsprite.h"


RobotSprite::RobotSprite(GameStateManager* manager,RobotController*robot) {
  manager_=manager;
  atlas_=manager_->TextureAtlas();
  logical_robot_=robot;
  SetSpritePrefix(robot->GetRobotNumber());
  animation_frame_=0;
  UpdateLocation();
}


RobotSprite::~RobotSprite(void) {
}

void RobotSprite::SetSpritePrefix(const int robot_number) {
  sprite_prefix_ = "r";
  sprite_prefix_.append(std::to_string(robot_number));
  sprite_prefix_.append("_");

}


bool RobotSprite::IsOverLocation(Point location) {
  if(location==logical_robot_->GetLocation()||location==target_location_)
    return true;
  return false;
}


void RobotSprite::Draw(const double camera_angle) {
  using namespace Robot;
  glColor3f(1.00f, 1.00f, 1.00f);
  std::string sprite_name = GetRobotTexture(camera_angle);
  Robot::RELATIVE_POSITION_8_WAY origin_position = OriginPosition(camera_angle);
  switch(origin_position) {
  case FAR:
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(drawn_center_.x-0.5,drawn_center_.y+0.5, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(drawn_center_.x-0.5,drawn_center_.y+0.5,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(drawn_center_.x+0.5,drawn_center_.y-0.5,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(drawn_center_.x+0.5,drawn_center_.y-0.5, 1.0);
    break;
  case FAR_LEFT:
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(drawn_center_.x-0.7,drawn_center_.y    , 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(drawn_center_.x-0.7,drawn_center_.y    ,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(drawn_center_.x+0.7,drawn_center_.y    ,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(drawn_center_.x+0.7,drawn_center_.y    , 1.0);
    break;
  case LEFT:
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(drawn_center_.x-0.5,drawn_center_.y-0.5, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(drawn_center_.x-0.5,drawn_center_.y-0.5,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(drawn_center_.x+0.5,drawn_center_.y+0.5,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(drawn_center_.x+0.5,drawn_center_.y+0.5, 1.0);
    break;
  case NEAR_LEFT:
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(drawn_center_.x    ,drawn_center_.y-0.7, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(drawn_center_.x    ,drawn_center_.y-0.7,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(drawn_center_.x    ,drawn_center_.y+0.7,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(drawn_center_.x    ,drawn_center_.y+0.7, 1.0);
    break;
  case NEAR:
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(drawn_center_.x+0.5,drawn_center_.y-0.5, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(drawn_center_.x+0.5,drawn_center_.y-0.5,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(drawn_center_.x-0.5,drawn_center_.y+0.5,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(drawn_center_.x-0.5,drawn_center_.y+0.5, 1.0);
    break;
  case NEAR_RIGHT:
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(drawn_center_.x+0.7,drawn_center_.y    , 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(drawn_center_.x+0.7,drawn_center_.y    ,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(drawn_center_.x-0.7,drawn_center_.y    ,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(drawn_center_.x-0.7,drawn_center_.y    , 1.0);
    break;
  case RIGHT:
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(drawn_center_.x+0.5,drawn_center_.y+0.5, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(drawn_center_.x+0.5,drawn_center_.y+0.5,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(drawn_center_.x-0.5,drawn_center_.y-0.5,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(drawn_center_.x-0.5,drawn_center_.y-0.5, 1.0);
    break;
  case FAR_RIGHT:
    atlas_->getCoordinates(sprite_name,Texture::UPPER_LEFT);
    glVertex3d(drawn_center_.x    ,drawn_center_.y+0.7, 1.0);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_LEFT);
    glVertex3d(drawn_center_.x    ,drawn_center_.y+0.7,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::LOWER_RIGHT);
    glVertex3d(drawn_center_.x    ,drawn_center_.y-0.7,-0.5);
    atlas_->getCoordinates(sprite_name,Texture::UPPER_RIGHT);
    glVertex3d(drawn_center_.x    ,drawn_center_.y-0.7, 1.0);
  }
}

Robot::RELATIVE_POSITION_8_WAY RobotSprite::OriginPosition(
                                                    double origin_angle) const {
  Robot::RELATIVE_POSITION_8_WAY position=
    Robot::RELATIVE_POSITION_8_WAY(OriginPositionIndex(origin_angle));
  return position;
}

int RobotSprite::OriginPositionIndex(double origin_angle) const {
  int offset_angle = (int)(origin_angle+22.5);
  if(offset_angle>=360) offset_angle-=360;
  int position=(offset_angle/45);
  if (position==0) position=8;
  return position;
}


void RobotSprite::SetAnimationCompleteCallback(
                                   void(*AnimationCompleteCallbackFunc)(void)) {
  animation_complete_callback_function_=AnimationCompleteCallbackFunc;
}

std::string RobotSprite::GetRobotTexture(double viewing_angle) {
  int image_number;
  switch(logical_robot_->GetFacing()) {
  case Robot::NORTH:
    image_number=0;
    break;
  case Robot::EAST:
    image_number=2;
    break;
  case Robot::SOUTH:
    image_number=4;
    break;
  case Robot::WEST:
    image_number=6;
    break;
  default:
    break;
  }
  image_number+=OriginPositionIndex(viewing_angle);
  image_number%=8;
  image_number+=8*animation_frame_+1;
  std::string sprite_name=sprite_prefix_;
  sprite_name.append(std::to_string(image_number));
  return sprite_name;
}

void RobotSprite::UpdateLocation(void) {
  drawn_center_ = logical_robot_->GetLocation();
  drawn_center_.x+=0.5;
  drawn_center_.y+=0.5;
}