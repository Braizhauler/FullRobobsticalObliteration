/*******************************************************************************
* File: gamestatemanager.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2014 DEC 22
* Version: 0
* Revised: 2015 APR 08
*
* GameStateManager:
*   A file for keeping track of current state, and redirecting calls to
*   all active game states/logic.
*
* � [2014] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <stack>
#include <vector>
#include <glfw3.h>


#include <ft2build.h>
#include FT_FREETYPE_H

#include "mywindowwrapper.h"
#include "gamestate.h"
#include "renderable.h"
#include "updateable.h"

extern FT_Face face;

void render_text(const std::string &str, FT_Face face, float x, float y, float sx, float sy);

struct GameTime;

class GameStateManager: public Renderable {
public:
  //Constructors and Destructor
  GameStateManager(MyWindowWrapper*);
  ~GameStateManager(void);
  //Methods
  GameState* Pop();
  GameState* Peek(); 
  void Push(GameState* new_state);

  //Mouse Input
  void CursorMove(bool left_mouse_button_down, double x_position, double y_position);
  void MouseButtonPressed(int button, double x_position, double y_position);
  void MouseButtonReleased(int button, double x_position, double  y_position);
  void MouseButtonClicked(int button, double cursor_x_, double cursor_y_);
  //Key Actions
  void Select_Next();
  void Select_Prev();
  void Hotkey(const int);
  void Activate_Selection();

  void Draw();
  void Update(GameTime frameNumber);

  void Exit();
private:
  void RestackRenderables();

  //Member Variables
  std::vector<GameState*> active_state_;
  std::vector<Renderable*> active_renderable_;
  std::vector<Updateable*> active_updatable_;
  MyWindowWrapper* window_;
};

#endif //GAME_STATE_MANAGER_H