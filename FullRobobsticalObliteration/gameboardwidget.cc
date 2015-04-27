#include "gameboardwidget.h"

const double GameBoardWidget::WALL_THICKNESS = 0.05; 
const double GameBoardWidget::WALL_HEIGHT = 0.25; 

GameBoardWidget::GameBoardWidget (GameStateManager* manager,
                                  WidgetLocation location) 
                                                                  {
  current_location_=location;
  game_state_manager_ = manager;
  atlas_=manager->TextureAtlas();
  player_=new RobotSprite(manager, manager->GetPlayerRobot());
  angle_ = 0.0;
  board_=new GameBoardController( NUMBER_OF_TILES_ACROSS );
}

GameBoardWidget::~GameBoardWidget (void){
  delete board_;
  delete player_;
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
  
  //glOrtho(-2.0,2.0,-2.0,2.0,5.0,11.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslated (0.0,-(NUMBER_OF_TILES_ACROSS/2.0),-18.5);
  //glTranslated (0.0,0.0,-16.5);
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
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  GameBoard::QUADRANT origin=OriginQuadrant();
  //draw the floor
  switch(origin) {
  case GameBoard::FAR_QUADRANT:
    for(Point tile=Point(0.0,0.0);tile.x<NUMBER_OF_TILES_ACROSS;++tile.x)
      for(tile.y=0.0;tile.y<NUMBER_OF_TILES_ACROSS;++tile.y) {
        GetTileColor(tile);
        RenderATile(tile,origin);
      }
     break;
  case GameBoard::RIGHT_QUADRANT:
    for(Point tile=Point(0.0,NUMBER_OF_TILES_ACROSS-1);
        tile.x<NUMBER_OF_TILES_ACROSS;++tile.x)
      for(tile.y=NUMBER_OF_TILES_ACROSS-1;tile.y>=0;--tile.y) {
        GetTileColor(tile);
        RenderATile(tile,origin);
      }
     break;
  case GameBoard::NEAR_QUADRANT:
    for(Point tile=Point(NUMBER_OF_TILES_ACROSS-1,NUMBER_OF_TILES_ACROSS-1);
        tile.x>=0;--tile.x)
      for(tile.y=NUMBER_OF_TILES_ACROSS-1;tile.y>=0;--tile.y) {
        GetTileColor(tile);
        RenderATile(tile,origin);
      }
     break;
  case GameBoard::LEFT_QUADRANT:
    for(Point tile=Point(NUMBER_OF_TILES_ACROSS-1,0.0);tile.x>=0;--tile.x)
      for(tile.y=0.0;tile.y<NUMBER_OF_TILES_ACROSS;++tile.y) {
        GetTileColor(tile);
        RenderATile(tile,origin);
      }
  }
  //now draw the walls
  switch(origin) {
  case GameBoard::FAR_QUADRANT:
    for(Point tile=Point(0.0,0.0);tile.x<NUMBER_OF_TILES_ACROSS;++tile.x) {
      for(tile.y=0.0;tile.y<NUMBER_OF_TILES_ACROSS;++tile.y) {
        GameBoard::Tile*floor_tile = board_->GetTile(tile);
        if(*(floor_tile->wall_north)==GameBoard::WALL_STANDARD)
          RenderAWall(tile,GameBoard::NORTH);
        if(*(floor_tile->wall_west)==GameBoard::WALL_STANDARD)
          RenderAWall(tile,GameBoard::WEST);
        if(player_->IsOverLocation(tile))
          player_->Draw(angle_);
      }
    }
    for(int x=0;x<NUMBER_OF_TILES_ACROSS;++x) {
      RenderAWall(Point(x,NUMBER_OF_TILES_ACROSS-1),GameBoard::SOUTH);
      RenderAWall(Point(NUMBER_OF_TILES_ACROSS-1,x),GameBoard::EAST);
    }
    break;
  case GameBoard::RIGHT_QUADRANT:
    for(Point tile=Point(0.0,NUMBER_OF_TILES_ACROSS-1);
        tile.x<NUMBER_OF_TILES_ACROSS;++tile.x) {
      for(tile.y=NUMBER_OF_TILES_ACROSS-1;tile.y>=0;--tile.y) {
        GameBoard::Tile*floor_tile = board_->GetTile(tile);
        if(*(floor_tile->wall_west)==GameBoard::WALL_STANDARD)
          RenderAWall(tile,GameBoard::WEST);
        if(*(floor_tile->wall_south)==GameBoard::WALL_STANDARD)
          RenderAWall(tile,GameBoard::SOUTH);
        if(player_->IsOverLocation(tile))
          player_->Draw(angle_);
      }
    }
    for(int x=0;x<NUMBER_OF_TILES_ACROSS;++x) {
      RenderAWall(Point(x,0),GameBoard::NORTH);
      RenderAWall(Point(NUMBER_OF_TILES_ACROSS-1,NUMBER_OF_TILES_ACROSS-x-1),GameBoard::EAST);
    }
    break;
  case GameBoard::NEAR_QUADRANT:
    for(Point tile=Point(NUMBER_OF_TILES_ACROSS-1,NUMBER_OF_TILES_ACROSS-1);
      tile.x>=0;--tile.x) {
      for(tile.y=NUMBER_OF_TILES_ACROSS-1;tile.y>=0;--tile.y) {
        GameBoard::Tile*floor_tile = board_->GetTile(tile);
        if(*(floor_tile->wall_south)==GameBoard::WALL_STANDARD)
          RenderAWall(tile,GameBoard::SOUTH);
        if(*(floor_tile->wall_east)==GameBoard::WALL_STANDARD)
          RenderAWall(tile,GameBoard::EAST);
        if(player_->IsOverLocation(tile))
          player_->Draw(angle_);
      }
    }
    for(int x=0;x<NUMBER_OF_TILES_ACROSS;++x) {
      RenderAWall(Point(NUMBER_OF_TILES_ACROSS-x-1,0),GameBoard::NORTH);
      RenderAWall(Point(0,NUMBER_OF_TILES_ACROSS-x-1),GameBoard::WEST);
    }
    break;
  case GameBoard::LEFT_QUADRANT:
    for(Point tile=Point(NUMBER_OF_TILES_ACROSS-1,0.0);tile.x>=0;--tile.x) {
      for(tile.y=0.0;tile.y<NUMBER_OF_TILES_ACROSS;++tile.y) {
        GameBoard::Tile*floor_tile = board_->GetTile(tile);
        if(*(floor_tile->wall_east)==GameBoard::WALL_STANDARD)
          RenderAWall(tile,GameBoard::EAST);
        if(*(floor_tile->wall_north)==GameBoard::WALL_STANDARD)
          RenderAWall(tile,GameBoard::NORTH);
        if(player_->IsOverLocation(tile))
          player_->Draw(angle_);
      }
    }
    for(int x=0;x<NUMBER_OF_TILES_ACROSS;++x) {
      RenderAWall(Point(NUMBER_OF_TILES_ACROSS-x-1,NUMBER_OF_TILES_ACROSS-1),GameBoard::SOUTH);
      RenderAWall(Point(0,x),GameBoard::WEST);
    }
    break;
  }

  glEnd();
  
  glDisable(GL_TEXTURE_2D);
}

void GameBoardWidget::GetTileColor(Point tile) {
  GameBoard::FLOOR_MATERIAL floor_type = board_->GetTile(tile)->floor_type ;
  if(floor_type==GameBoard::FLOOR_EMPTY)
    glColor3d(0.6+0.03*tile.x,0.8-0.04*abs(tile.x-tile.y),0.6+0.03*tile.y);
  glColor3d(0.6,0.6,0.6);
}

void GameBoardWidget::RenderATile(Point tile,GameBoard::QUADRANT quadrent) {
  using namespace GameBoard;
  using namespace Texture;
  atlas_->ActivateTexture("blank");
  atlas_->LoadCoordinates(UPPER_LEFT);
  glVertex3d(tile.x    ,tile.y    ,0.0);
  atlas_->LoadCoordinates(LOWER_LEFT);
  glVertex3d(tile.x    ,tile.y+1.0,0.0);
  atlas_->LoadCoordinates(LOWER_RIGHT);
  glVertex3d(tile.x+1.0,tile.y+1.0,0.0);
  atlas_->LoadCoordinates(UPPER_RIGHT);
  glVertex3d(tile.x+1.0,tile.y    ,0.0);
}

void GameBoardWidget::RenderAWall(Point tile, GameBoard::DIRECTION direction) {
  using namespace GameBoard;
  if(direction==NORTH)
    RenderNorthWall(tile);
  if(direction==WEST)
    RenderWestWall(tile);
  if(direction==SOUTH)
    RenderSouthWall(tile);
  if(direction==EAST)
    RenderEastWall(tile);
}

void GameBoardWidget::RenderSouthWall(Point tile) {
  tile.y+=1.0;
  RenderNorthWall(tile);
}
void GameBoardWidget::RenderNorthWall(Point tile) {
  atlas_->ActivateTexture("wall");
  glColor3f(0.5f,0.5f,0.5f); //face color
  if(angle_<100 || angle_>260) { //North face
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,0.0);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,0.0);
  }
  if(angle_>80 && angle_ < 280) { //South face
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,0.0);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,0.0);
  }
  atlas_->ActivateTexture("background");
  glColor3f(0.4f,0.4f,0.4f); //Cap color
  if(angle_<2 || angle_>178) { //West cap
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,0.0);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,0.0);
  }
  if(angle_<182 || angle_>358) { //East cap
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,0.0);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,0.0);
  }
  glColor3f(0.7f,0.7f,0.7f); //wall top
  atlas_->LoadCoordinates(Texture::LOWER_LEFT);
  glVertex3d(tile.x    ,tile.y-WALL_THICKNESS,WALL_HEIGHT);
  atlas_->LoadCoordinates(Texture::UPPER_LEFT);
  glVertex3d(tile.x+1.0,tile.y-WALL_THICKNESS,WALL_HEIGHT);
  atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
  glVertex3d(tile.x+1.0,tile.y+WALL_THICKNESS,WALL_HEIGHT);
  atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
  glVertex3d(tile.x    ,tile.y+WALL_THICKNESS,WALL_HEIGHT);
}
void GameBoardWidget::RenderEastWall(Point tile) {
  tile.x+=1.0;
  RenderWestWall(tile);
}

void GameBoardWidget::RenderWestWall(Point tile) {
  atlas_->ActivateTexture("wall");
  glColor3f(0.6f,0.6f,0.6f); //face color
    if(angle_<10 || angle_>170) { //West Face
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,0.0);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,0.0);
  }
  if(angle_<190 || angle_>350) { //East Face
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,0.0);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,0.0);
  }
  atlas_->ActivateTexture("background");
  glColor3f(0.4f,0.4f,0.4f); //Cap color
  if(angle_<92 || angle_>268) { //North cap
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,0.0);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,0.0);
  }
  if(angle_>88 && angle_ < 272) { //South cap
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,0.0);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,0.0);
  }
  glColor3f(0.7f,0.7f,0.7f); //wall top
  atlas_->LoadCoordinates(Texture::LOWER_LEFT);
  glVertex3d(tile.x-WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
  atlas_->LoadCoordinates(Texture::UPPER_LEFT);
  glVertex3d(tile.x-WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
  atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
  glVertex3d(tile.x+WALL_THICKNESS,tile.y+1.0,WALL_HEIGHT);
  atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
  glVertex3d(tile.x+WALL_THICKNESS,tile.y    ,WALL_HEIGHT);
}

GameBoard::QUADRANT GameBoardWidget::OriginQuadrant() const {
  if(angle_<90)
    return GameBoard::FAR_QUADRANT;
  else if(angle_<180)
    return GameBoard::RIGHT_QUADRANT;
  else if(angle_<270)
    return GameBoard::NEAR_QUADRANT;
  else
    return GameBoard::LEFT_QUADRANT;
}

void GameBoardWidget::UpdateRobots() {
  player_->Animate();
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


