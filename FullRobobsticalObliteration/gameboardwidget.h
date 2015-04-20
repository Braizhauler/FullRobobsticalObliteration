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
* � [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef GAME_BOARD_WIDGET_H
#define GAME_BOARD_WIDGET_H

#include "gamestatemanager.h"
#include "widget.h"
#include "gameboardcontroller.h"

namespace gameboard {
enum QUADRENT {
  FAR_QUADRENT = 0,
  RIGHT_QUADRENT,
  NEAR_QUADRENT,
  LEFT_QUADRENT
};

}
using namespace gameboard;
class GameBoardWidget : public Widget {
public:
  GameBoardWidget (void);
  GameBoardWidget (GameStateManager* manager,WidgetLocation location);
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
  void RenderATile(Point tile, QUADRENT);
  void RenderAWall(Point tile, DIRECTION direction);
  void RenderNorthWall(Point tile);
  void RenderEastWall(Point tile);
  void RenderSouthWall(Point tile);
  void RenderWestWall(Point tile);
  void RenderRobot(Point tile);
  QUADRENT OriginQuadrant() const;

  GameBoardController* board_;
  static const int NUMBER_OF_TILES_ACROSS = 12; 
  static const double WALL_HEIGHT; 
  static const double WALL_THICKNESS; 
  double angle_;
  WidgetLocation current_location_;
  GameStateManager* game_state_manager_;
  
  int robot_;
  int direction_;
  int step_;
  int wait_;
};

#endif//GAME_BOARD_WIDGET_H