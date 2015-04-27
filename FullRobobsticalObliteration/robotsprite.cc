#include "robotsprite.h"

const double RobotSprite::ANIMATION_SPEED=0.02;

RobotSprite::RobotSprite(GameStateManager* manager,RobotController*robot) {
  manager_=manager;
  atlas_=manager_->TextureAtlas();
  logical_robot_=robot;
  SetSpritePrefix(robot->GetRobotNumber());
  animation_frame_=0;
  time_at_current_frame_=0;
  animating_fraction_=1.0;
  UpdateLocation();
  current_location_=logical_robot_->GetLocation();
  target_location_=current_location_;
}


RobotSprite::~RobotSprite(void) {
}

void RobotSprite::SetSpritePrefix(const int robot_number) {
  sprite_prefix_ = "r";
  sprite_prefix_.append(std::to_string(robot_number));
  sprite_prefix_.append("_");

}


bool RobotSprite::IsOverLocation(Point location) {
  if(location==current_location_||location==target_location_)
    return true;
  return false;
}


void RobotSprite::Draw(const double camera_angle) {
  using namespace Robot;
  if(animating_fraction_<1.0) {
    animating_fraction_+=ANIMATION_SPEED;
    drawn_center_.x=(1.0-animating_fraction_)*current_location_.x+
                    animating_fraction_*target_location_.x+0.5;
    drawn_center_.y=(1.0-animating_fraction_)*current_location_.y+
                    animating_fraction_*target_location_.y+0.5;
    if(++time_at_current_frame_>FRAME_DELAY) {
      animation_frame_=(animation_frame_+1)%2;
      time_at_current_frame_=0;
    }
    if(animating_fraction_>1.0) {
      animating_fraction_=1.0;
      logical_robot_->PopQueue();
      if(!logical_robot_->QueueComplete())
        Animate();
    }
  }
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

bool RobotSprite::IsAnimating(void) {
  return (animating_fraction_>=1.0);
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

void RobotSprite::Animate() {
  current_location_=logical_robot_->GetLocation();
  target_location_=logical_robot_->GetNextLocation();
  drawn_center_.x=current_location_.x+0.5;
  drawn_center_.y=current_location_.y+0.5;
  if(!logical_robot_->QueueComplete()) {
    animating_fraction_=0.0;
    if(logical_robot_->GetFacing()!=logical_robot_->GetNextFacing())
     animating_fraction_=0.5; //if turning, half the animation time.
  }
}