/*******************************************************************************
* File: gamestateexecute.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 APR 27
* Version: 0
* Revised: 2015 APR 27
*
* GameStateExecute:
*   A GameState in which the user . 
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/
#ifndef GAME_STATE_EXECUTE_H_
#define GAME_STATE_EXECUTE_H_
#include "gamestate.h"
#include "gameboardwidget.h"
#include "cardhandwidget.h"
#include "robotcontroller.h"
class GameStateExecute : public GameState {
public:
  GameStateExecute(GameStateManager* manager);
  ~GameStateExecute(void);

  //causes the GameState to draw all widgets
  void Draw();
  //returns true if nothing is no other states are to be drawn under this state.
  bool Opaque() const;
  //Loads the GameState onto the GameStateManager stack in active mode
  void Load();
  //Called when GameState when another GameState is preparing
  //to load over this State
  void Cover();
  //Called when GameState when another GameState is preparing
  //becomming the topmost active game state
  void Uncover();
  //Called when the Gamestate is unloaded from the GameStateManager
  void Unload();
  //Mouse Input
  void CursorMove(bool left_mouse_button_down,
                  double x_position,
                  double y_position);
  void MouseButtonPressed(int button,
                          double x_position,
                          double y_position);
  void MouseButtonReleased(int button,
                           double x_position,
                           double y_position);
  void MouseButtonClicked(int button,
                           double x_position,
                           double y_position);
  //Key Actions
  void Select_Next();
  void Select_Prev();
  void Hotkey(const int);
  void Activate_Selection();

  void EnableInteractivity();

  void LinkProgramState(GameState*program_state);
private:
  CardWidget card_register_[5];
  GameStateManager*manager_;
  GameState*program_state_;
  GameBoardWidget board_;
  Point last_mouse_position_;

  RobotController*player_;
  int cards_played_;
  bool ready_to_execute_;

};

#endif//GAME_STATE_PROGRAM_H_
