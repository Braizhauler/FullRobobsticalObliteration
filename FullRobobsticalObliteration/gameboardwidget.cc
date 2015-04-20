#include "gameboardwidget.h"

const double GameBoardWidget::WALL_THICKNESS = 0.05; 
const double GameBoardWidget::WALL_HEIGHT = 0.25; 

GameBoardWidget::GameBoardWidget (void) {
  current_location_=WidgetLocation(60.0,30.0,0.0,0.0,0.0);
  game_state_manager_ = nullptr;
  angle_ = 00.0;
  board_=nullptr;

  robot_=2;
  direction_=0;
  step_=0;
  wait_=0;
}

GameBoardWidget::GameBoardWidget (GameStateManager* manager,
                                  WidgetLocation location) {
  current_location_=location;
  game_state_manager_ = manager;
  angle_ = 0.0;
  board_=new GameBoardController( NUMBER_OF_TILES_ACROSS );
  robot_=2;
  direction_=0;
  step_=0;
  wait_=0;
}

GameBoardWidget::~GameBoardWidget (void){
  delete board_;
}

  //returns true if:
  //x is between left and right
  //y is between top and bottom
const bool GameBoardWidget::ContainPoint(const double x, const double y) const{
  if( (current_location_.left() <= x) && (x <= current_location_.right()) )
    if( (current_location_.top() <= y) && (y <= current_location_.bottom()) )
      return true;
  return false;
}
const bool GameBoardWidget::ContainPoint(const Point upper_left) const{
  return ContainPoint(upper_left.x, upper_left.y);
}

void GameBoardWidget::MoveTo(const Point upper_left){
  current_location_.MoveTo(upper_left);
}
void GameBoardWidget::MoveTo(const double x, const double y){
  current_location_.setLeft(x);
  current_location_.setTop(y);
}

void GameBoardWidget::SizeTo(const Widget *){}
void GameBoardWidget::SizeTo(const double width, const double height){}
  
FrameWidget* GameBoardWidget::parent() const {
  return nullptr;
}
void GameBoardWidget::setParent(FrameWidget*){}

void GameBoardWidget::Draw(){
  glColor3f(0.1f,0.0f,0.2f);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(current_location_.left(),
               current_location_.top(),
               current_location_.depth());
    glVertex3d(current_location_.right(),
               current_location_.top(),
               current_location_.depth());
    glVertex3d(current_location_.right(),
               current_location_.bottom(),
               current_location_.depth());
    glVertex3d(current_location_.left(),
               current_location_.bottom(),
               current_location_.depth());
  glEnd();
  Setup3dRendering();
  /* from
    0<angle_<90 --> (0,0) far 
    90<angle_<180 --> (0,0) right 
    180<angle_<270 --> (0,0) near 
    270<angle_<360 --> (0,0) left
 */
  RenderTiles();
  Setup2dRendering();
}

void GameBoardWidget::Setup3dRendering() {
  //glEnable(GL_DEPTH);
  glPushMatrix();
  glTranslated((current_location_.left()+current_location_.width())/2.0,
                current_location_.top()+current_location_.height()/2.2,0.0);
  glFrustum(-1.0,1.0,-1.0,1.0,10.0,11.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslated (0.0,-(NUMBER_OF_TILES_ACROSS/2.0),-18.5);
  double scale = current_location_.width()/(NUMBER_OF_TILES_ACROSS);
  glScaled(scale,scale,1.0);
  glRotatef(60.0, 1.0, 0.0, 0.0);
  glRotatef(angle_, 0.0, 0.0, 1.0);
  glTranslated(-(NUMBER_OF_TILES_ACROSS/2.0),-(NUMBER_OF_TILES_ACROSS/2.0),0);
  //glClear(GL_DEPTH_BUFFER_BIT);
  //glEnable(GL_TEXTURE_2D);
}

void GameBoardWidget::Setup2dRendering() {
  //glDisable(GL_TEXTURE_2D);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  //glDisable(GL_DEPTH);
}

void GameBoardWidget::RenderTiles() {
  glBegin(GL_QUADS);
  QUADRENT origin=OriginQuadrant();
  if( origin == FAR_QUADRENT) {
    for(Point tile=Point(0.0,0.0);tile.x<NUMBER_OF_TILES_ACROSS;++tile.x)
      for(tile.y=0.0;tile.y<NUMBER_OF_TILES_ACROSS;++tile.y) {
        GetTileColor(tile);
        RenderATile(tile,origin);
        if(tile.x==1.0 && tile.y==1.0) RenderRobot (tile);
      }
    for(int x=0;x<NUMBER_OF_TILES_ACROSS;++x) {
      RenderAWall(Point(x,NUMBER_OF_TILES_ACROSS-1),SOUTH);
      RenderAWall(Point(NUMBER_OF_TILES_ACROSS-1,x),EAST);
    }
  } else if( origin == RIGHT_QUADRENT) {
    for(Point tile=Point(0.0,NUMBER_OF_TILES_ACROSS-1);
        tile.x<NUMBER_OF_TILES_ACROSS;++tile.x)
      for(tile.y=NUMBER_OF_TILES_ACROSS-1;tile.y>=0;--tile.y) {
        GetTileColor(tile);
        RenderATile(tile,origin);
      }
    for(int x=0;x<NUMBER_OF_TILES_ACROSS;++x) {
      RenderAWall(Point(x,0),NORTH);
      RenderAWall(Point(NUMBER_OF_TILES_ACROSS-1,NUMBER_OF_TILES_ACROSS-x-1),EAST);
    }
  } else if( origin == NEAR_QUADRENT) {
    for(Point tile=Point(NUMBER_OF_TILES_ACROSS-1,NUMBER_OF_TILES_ACROSS-1);
        tile.x>=0;--tile.x)
      for(tile.y=NUMBER_OF_TILES_ACROSS-1;tile.y>=0;--tile.y) {
        GetTileColor(tile);
        RenderATile(tile,origin);
      }
    for(int x=0;x<NUMBER_OF_TILES_ACROSS;++x) {
      RenderAWall(Point(NUMBER_OF_TILES_ACROSS-x-1,0),NORTH);
      RenderAWall(Point(0,NUMBER_OF_TILES_ACROSS-x-1),WEST);
    }
  } else if(origin == LEFT_QUADRENT) {
    for(Point tile=Point(NUMBER_OF_TILES_ACROSS-1,0.0);tile.x>=0;--tile.x)
      for(tile.y=0.0;tile.y<NUMBER_OF_TILES_ACROSS;++tile.y) {
        GetTileColor(tile);
        RenderATile(tile,origin);
      }
    for(int x=0;x<NUMBER_OF_TILES_ACROSS;++x) {
      RenderAWall(Point(NUMBER_OF_TILES_ACROSS-x-1,NUMBER_OF_TILES_ACROSS-1),SOUTH);
      RenderAWall(Point(0,x),WEST);
    }
  }
  glEnd();
}
void GameBoardWidget::RenderRobot (Point tile) {
  if(++wait_>7) {
    wait_=0;
    if(++step_>3) {
      step_=0;
      if(++direction_>7) direction_=0;
    }
  }
  glColor3f(1.00f, 1.00f, 1.00f);
  glTexCoord2d( 0.2505+0.0625*direction_,0.00005+0.03125*(step_%2)+0.0625*robot_);
  glVertex3d(tile.x+1,  tile.y, 0.0);
  glTexCoord2d( 0.3120+0.0625*direction_,0.00005+0.03125*(step_%2)+0.0625*robot_);
  glVertex3d(tile.x+1,  tile.y, 1.0);
  glTexCoord2d( 0.3120+0.0625*direction_,0.03115+0.03125*(step_%2)+0.0625*robot_);
  glVertex3d(tile.x,  tile.y+1, 1.0);
  glTexCoord2d( 0.2505+0.0625*direction_,0.03115+0.03125*(step_%2)+0.0625*robot_);
  glVertex3d(tile.x,  tile.y+1, 0.0);
}


void GameBoardWidget::GetTileColor(Point tile) {

  if(tile.x+tile.y==0)
    glColor3f(1.0f,0.3f,0.3f);
  else if(tile.x==0&&tile.y==7)
    glColor3f(0.5f,1.0f,0.5f);
  else if(((int)(tile.x+tile.y))%2==0)
    glColor3f(0.3f,0.3f,0.7f);
  else
    glColor3f(0.6f,0.6f,0.4f);
  
  FLOOR_MATERIAL floor_type = board_->GetTile(tile)->floor_type ;
  if(floor_type==FLOOR_EMPTY)
    glColor3d(0.3+0.08*tile.x,0.0,0.1+0.1*tile.y);
}

void GameBoardWidget::RenderATile(Point tile,gameboard::QUADRENT quadrent) {
  using namespace gameboard;
    glVertex3d(tile.x    ,tile.y    ,0.0);
    glVertex3d(tile.x+1.0,tile.y    ,0.0);
    glVertex3d(tile.x+1.0,tile.y+1.0,0.0);
    glVertex3d(tile.x    ,tile.y+1.0,0.0);
    
    Tile*floor_tile = board_->GetTile(tile);
    if(quadrent == FAR_QUADRENT) {
      if(*(floor_tile->wall_north)==WALL_STANDARD)
        RenderAWall(tile,NORTH);
      if(*(floor_tile->wall_west)==WALL_STANDARD)
        RenderAWall(tile,WEST);
    } else if (quadrent == RIGHT_QUADRENT) {
      if(*(floor_tile->wall_west)==WALL_STANDARD)
        RenderAWall(tile,WEST);
      if(*(floor_tile->wall_south)==WALL_STANDARD)
        RenderAWall(tile,SOUTH);
    } else if (quadrent == NEAR_QUADRENT) {
      if(*(floor_tile->wall_south)==WALL_STANDARD)
        RenderAWall(tile,SOUTH);
      if(*(floor_tile->wall_east)==WALL_STANDARD)
        RenderAWall(tile,EAST);
    } else if (quadrent == LEFT_QUADRENT) {
      if(*(floor_tile->wall_east)==WALL_STANDARD)
        RenderAWall(tile,EAST);
      if(*(floor_tile->wall_north)==WALL_STANDARD)
        RenderAWall(tile,NORTH);
    }
}

void GameBoardWidget::RenderAWall(Point tile, DIRECTION direction) {
  using namespace gameboard;
  if(direction==NORTH)
    RenderNorthWall(tile);
  if(direction==WEST)
    RenderWestWall(tile);
  if(direction==SOUTH)
    RenderSouthWall(tile);
  if(direction==EAST)
    RenderEastWall(tile);
}

void GameBoardWidget::RenderNorthWall(Point tile) {
  glColor3f(0.5f,0.5f,0.5f); //face color
  if(angle_<100 || angle_>260) { //North face
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,0.0);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,0.0);
  }
  if(angle_>80 && angle_ < 280) { //South face
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,0.0);
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,0.0);
  }
  glColor3f(0.4f,0.4f,0.4f); //Cap color
  if(angle_<2 || angle_>178) { //West cap
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,0.0);
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,0.0);
  }
  if(angle_<182 || angle_>358) { //East cap
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,0.0);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,0.0);
  }
  glColor3f(0.7f,0.7f,0.7f); //wall top
  glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,WALL_HEIGHT);
  glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,WALL_HEIGHT);
  glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,WALL_HEIGHT);
  glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,WALL_HEIGHT);
}
void GameBoardWidget::RenderEastWall(Point tile) {
  tile.x+=1.0;
  glColor3f(0.6f,0.6f,0.6f); //face color
  if(angle_<10 || angle_>170) { //West Face
    glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,0.0);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,0.0);
  }
  if(angle_<190 || angle_>350) { //East Face
    glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,0.0);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,0.0);
  }
  glColor3f(0.4f,0.4f,0.4f); //Cap color
  if(angle_<92 || angle_>268) { //North cap
    glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,0.0);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,0.0);
  }
  if(angle_>88 && angle_ < 272) { //South cap
    glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,0.0);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,0.0);
  }
  glColor3f(0.7f,0.7f,0.7f); //wall top
  glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
  glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
  glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
  glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
}
void GameBoardWidget::RenderSouthWall(Point tile) {
  tile.y+=1.0;
  glColor3f(0.5f,0.5f,0.5f); //face color
  if(angle_<100 || angle_>260) { //North face
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,0.0);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,0.0);
  }
  if(angle_>80 && angle_ < 280) { //South face
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,0.0);
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,0.0);
  }
  glColor3f(0.4f,0.4f,0.4f); //Cap color
  if(angle_<2 || angle_>178) { //West cap
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,0.0);
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,0.0);
  }
  if(angle_<182 || angle_>358) { //East cap
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,0.0);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,0.0);
  }
  glColor3f(0.7f,0.7f,0.7f); //wall top
  glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,WALL_HEIGHT);
  glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,WALL_HEIGHT);
  glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,WALL_HEIGHT);
  glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,WALL_HEIGHT);
}
void GameBoardWidget::RenderWestWall(Point tile) {
    glColor3f(0.6f,0.6f,0.6f); //face color
     if(angle_<10 || angle_>170) { //West Face
      glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,0.0);
      glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
      glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
      glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,0.0);
    }
    if(angle_<190 || angle_>350) { //East Face
      glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,0.0);
      glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
      glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
      glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,0.0);
    }
    glColor3f(0.4f,0.4f,0.4f); //Cap color
    if(angle_<92 || angle_>268) { //North cap
      glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,0.0);
      glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
      glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
      glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,0.0);
    }
    if(angle_>88 && angle_ < 272) { //South cap
      glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,0.0);
      glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
      glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
      glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,0.0);
    }
    glColor3f(0.7f,0.7f,0.7f); //wall top
    glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
}

gameboard::QUADRENT GameBoardWidget::OriginQuadrant() const {
  if(angle_<90)
    return gameboard::FAR_QUADRENT;
  else if(angle_<180)
    return gameboard::RIGHT_QUADRENT;
  else if(angle_<270)
    return gameboard::NEAR_QUADRENT;
  else
    return gameboard::LEFT_QUADRENT;
}

double GameBoardWidget::angle() const {
  return angle_;
}
void GameBoardWidget::setAngle(const double new_angle) {
  angle_ = new_angle;
  while (angle_<  0)angle_+=360.0;
  while (angle_>=360)angle_-=360.0;
}

double GameBoardWidget::width() const {
  return current_location_.width();
}
void GameBoardWidget::setWidth(double new_width) {
  current_location_.setWidth(new_width);
}

double GameBoardWidget::height() const {
  return current_location_.height();
}
void GameBoardWidget::setHeight(double new_height) {
  current_location_.setHeight(new_height);
}
  
double GameBoardWidget::left() const{
  return current_location_.left();
}
void GameBoardWidget::setLeft(double new_left) {
  current_location_.setLeft(new_left);
}
 
double GameBoardWidget::right() const{
  return current_location_.right();
}
void GameBoardWidget::setRight(double new_right) {
  current_location_.setRight(new_right);
}
 
double GameBoardWidget::top() const {
  return current_location_.top();
}
void GameBoardWidget::setTop(double new_top) {
  current_location_.setTop(new_top);
}
  
double GameBoardWidget::bottom() const {
  return current_location_.bottom();
}
void GameBoardWidget::setBottom(double new_bottom) {
  current_location_.setBottom(new_bottom);
}

double GameBoardWidget::depth() const {
  return current_location_.depth();
}
void GameBoardWidget::setDepth(double new_depth) {
 current_location_.setDepth(new_depth);
}


