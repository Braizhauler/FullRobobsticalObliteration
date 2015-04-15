#include "gameboardwidget.h"

GameBoardWidget::GameBoardWidget (void) {
  current_location_=WidgetLocation(60.0,30.0,0.0,0.0,0.0);
  game_state_manager_ = nullptr;
  angle_ = 00.0;
}
GameBoardWidget::GameBoardWidget (GameStateManager* manager,
                                  WidgetLocation location) {
  current_location_=location;
  game_state_manager_ = manager;
  angle_ = 0.0;
}
GameBoardWidget::~GameBoardWidget (void){
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
  /*glColor3f(0.3f,0.3f,0.7f);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(-1.0,1.0,-2.0);
    glVertex3d(-1.0,-1.0,-2.0);
    glVertex3d(1.0,-1.0,-2.0);
  glColor3f(0.6f,0.6f,0.9f);
    glVertex3d(1.0,1.0,-2.0);
  glEnd();*/
  /*Checkerboard*/
  for(int x=0;x<NUMBER_OF_TILES_ACROSS;++x)
    for(int y=0;y<NUMBER_OF_TILES_ACROSS;++y) {
      if((x+y)%2==0)
        glColor3f(0.3f,0.3f,0.7f);
      else
        glColor3f(0.5f,0.5f,0.5f);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3i(x,y, 0);
        glVertex3i(x+1,y, 0);
        glVertex3i(x+1,y+1,0);
        glVertex3i(x,y+1,0);
      glEnd();
    }
  Setup2dRendering();
  glColor3f(0.1f,0.0f,0.2f);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(current_location_.left()+29,
               current_location_.top(),
               current_location_.depth());
    glVertex3d(current_location_.right()-29,
               current_location_.top(),
               current_location_.depth());
    glVertex3d(current_location_.left()+current_location_.width()/2.0,
               current_location_.top()+current_location_.height()/2.0-6.0,
               current_location_.depth());
  glEnd();
}

void GameBoardWidget::Setup3dRendering() {
  glClear(GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glTranslated((current_location_.left()+current_location_.width())/2.0,
                current_location_.top()+current_location_.height()/2.0,0.0);
  glFrustum(-0.01,0.01,-0.01,0.01,0.1,1.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslated (0.0,-6.0,-10.0);
  //glTranslated (-(current_location_.left()+current_location_.width())/2.0,
  //             -current_location_.top()-current_location_.height()/2.0,0.0);
  double scale = current_location_.width()/(1.65*NUMBER_OF_TILES_ACROSS);
  glScaled(scale,scale,1.0);
  glRotatef(60.0, 1.0, 0.0, 0.0);
  glRotatef(angle_, 0.0, 0.0, 1.0);
  glTranslated(-4.0,-4.0,0);
}

void GameBoardWidget::Setup2dRendering() {
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

void GameBoardWidget::RenderTiles() {

}
void GameBoardWidget::RenderATile(Point corner, Point tile) {
}

double GameBoardWidget::angle() const {
  return angle_;
}
void GameBoardWidget::setAngle(const double new_angle) {
  angle_ = new_angle;
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
