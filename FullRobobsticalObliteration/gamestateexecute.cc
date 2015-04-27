#include "gamestateexecute.h"


GameStateExecute::GameStateExecute(GameStateManager* manager):
                              board_(manager,
                                     WidgetLocation(84.0, 42.0, 0.0, 0.0, 0.0)){
  manager_=manager;
  program_state_=nullptr;
  for(int index=0;index<5;++index)
    card_register_[index]=CardWidget(manager_,
                                     WidgetLocation(7.2, 10.8,
                                                    2.0,42.0-0.1*index,0.0));
}

GameStateExecute::~GameStateExecute(void) {
}
void GameStateExecute::Draw() {
  if(!ready_to_execute_)
    if(player_->QueueComplete())
      EnableInteractivity();
  board_.Draw();
  for(int index=5-1;index>=0;--index) {
    card_register_[index].Draw();
  }
}
bool GameStateExecute::Opaque() const {
  return true;
}
void GameStateExecute::Load() {
  for(int index=0;index<5;++index) {
    card_register_[index].MoveTo(2.0,42.0-0.2*index);
    card_register_[index].SetCard(manager_->GetRegister(index));
    card_register_[index].FaceDown();
  }
  board_.setAngle(manager_->GetBoardAngle());
  cards_played_=0;
  bool ready_to_execute_=true;
  player_=manager_->GetPlayerRobot();
}
void GameStateExecute::Cover() {
}
void GameStateExecute::Uncover() {
}
void GameStateExecute::Unload() {
}
//Mouse Input
void GameStateExecute::CursorMove(bool left_mouse_button_down,
                                  double x_position,
                                  double y_position) {
  if(left_mouse_button_down) {
    if(board_.ContainPoint(x_position,y_position)) {
        board_.setAngle(board_.angle()
                        +(0.2*(y_position-18.0)* 
                        (last_mouse_position_.x-x_position)));
        board_.setAngle(board_.angle()
                        +(0.2*(y_position-18.0)* 
                        (last_mouse_position_.x-x_position)));
    }
  }
  last_mouse_position_ = Point(x_position,y_position);
}
void GameStateExecute::MouseButtonPressed(int button,
                        double x_position,
                        double y_position) {
}
void GameStateExecute::MouseButtonReleased(int button,
                          double x_position,
                          double y_position) {
}
void GameStateExecute::MouseButtonClicked(int button,
                          double x_position,
                          double y_position) {
  if(ready_to_execute_) {
    if(cards_played_<5) {
      if(card_register_[cards_played_].ContainPoint(x_position,y_position)) {
        ready_to_execute_=false;
        player_->QueueCard(*(card_register_[cards_played_].GetCard()));
        card_register_[cards_played_].setLeft(12.0+9.0*cards_played_);
        card_register_[cards_played_].FlipStart();
        cards_played_++;
        board_.UpdateRobots();
      }
    } else {
      manager_->Pop();
    }
  }
}
//Key Actions
void GameStateExecute::Select_Next() {
}
void GameStateExecute::Select_Prev() {
}
void GameStateExecute::Hotkey(const int) {
}
void GameStateExecute::Activate_Selection() {
}
void GameStateExecute::LinkProgramState(GameState*program_state) {
  program_state_=program_state;
}

void GameStateExecute::EnableInteractivity() {
  ready_to_execute_=true;
}