/*******************************************************************************
* File: gameboardwidget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 APR 14
* Version: 0
* Revised: 2015 APR 14
*
* GameBoardWidget :
*   A gui widget which can contain a the gameboard
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef GAME_BOARD_WIDGET_H
#define GAME_BOARD_WIDGET_H

#include "gamestatemanager.h"
#include "widget.h"
#include "gameboardcontroller.h"

namespace GameBoard {
enum QUADRANT {
  FAR_QUADRANT = 0,
  RIGHT_QUADRANT,
  NEAR_QUADRANT,
  LEFT_QUADRANT
};

enum RELATIVE_POSITION_8_WAY {
  INVALID,
  FAR,
  FAR_RIGHT,
  RIGHT,
  NEAR_RIGHT,
  NEAR,
  NEAR_LEFT,
  LEFT,
  FAR_LEFT
};

}
using namespace GameBoard;
class GameBoardWidget : public Widget {
public:
  GameBoardWidget (GameStateManager* manager=nullptr,
                   WidgetLocation location=
                                  WidgetLocation(60.0,30.0,0.0,0.0,0.0));
  ~GameBoardWidget (void);

  //returns true if:
  //x is between left and right
  //y is between top and bottom
  const bool ContainPoint(const double x, const double y) const;
  const bool ContainPoint(const Point) const;

  void MoveTo(const Point);
  void MoveTo(const double x, const double y);

  void SizeTo(const Widget *);
  void SizeTo(const double width, const double height);
  
  FrameWidget* parent() const;
  void setParent(FrameWidget*);

  void Draw();
  
  double angle() const;
  void setAngle(const double);

  double width() const;
  double height() const;
  void setWidth(double);
  void setHeight(double);

  double left() const;
  double right() const;
  double top() const;
  double bottom() const;
  
  void setLeft(double);
  void setRight(double);
  void setTop(double);
  void setBottom(double);

  double depth() const;
  void setDepth(double);
private:
  void Setup3dRendering();
  void Setup2dRendering();
  void ResetRendering();
  void GetTileColor(Point tile);
  void RenderTiles();
  void RenderATile(Point tile, QUADRANT);
  void RenderAWall(Point tile, DIRECTION direction);
  void RenderNorthWall(Point tile);
  void RenderEastWall(Point tile);
  void RenderSouthWall(Point tile);
  void RenderWestWall(Point tile);
  void RenderRobot(Point tile);
  QUADRANT OriginQuadrant() const;
  RELATIVE_POSITION_8_WAY OriginPosition() const;
  

  GameBoardController* board_;
  static const int NUMBER_OF_TILES_ACROSS = 12; 
  static const double WALL_HEIGHT; 
  static const double WALL_THICKNESS; 
  double angle_;
  WidgetLocation current_location_;
  GameStateManager* game_state_manager_;

  SpriteAtlas* atlas_;
  
  int robot_;
  int times_;
  int direction_;
  int step_;
  int wait_;
};

#endif//GAME_BOARD_WIDGET_H