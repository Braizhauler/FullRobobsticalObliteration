/*******************************************************************************
* File: spriteatlas.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 19
* Version: 0
* Revised: 2015 JAN 22
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "MyWindowWrapper.h"


/*******************************
* Constructors and Destructor */

//Constructor DOES NOT CREATE A WINDOW, call Init() after the object is created.
MyWindowWrapper::MyWindowWrapper() {
  window_ = nullptr;
	initialized_ = false;
  finished_ = false;
  window_width_ = 0;
  window_height_ = 0;
  title_ = nullptr;
}
 
MyWindowWrapper::~MyWindowWrapper(void) {
  delete [] title_;
  title_ = nullptr;
  initialized_ = false;
}

const bool MyWindowWrapper::Init(int width, int height, const char * title)  {
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  //glfwWindowHint(GLFW_DECORATED, GL_FALSE);//Remove title bar, acting wierd

  window_width_ = width;
  window_height_ = height;
  size_t title_length = strlen(title);
  title_ = new char[title_length+1];
  for (size_t i = 0;i<=title_length;++i) {
    title_[i] = title[i];
  }
  //The last two parameters of glfwCreateWindow are:
  //  GLFWmonitor * monitorUsedByFullScreen
  //  GLFWwindow * share
  window_ = glfwCreateWindow( window_width_, window_height_, title_, nullptr, nullptr);
	if( window_ == NULL ){
		glfwTerminate();
	} else {
    initialized_ = true;
  }
  //make that OpenGL context the active context
  glfwMakeContextCurrent(window_);
  RegisterResize(MyWindowControl::ResizeWindow);
  Resize(window_width_,window_height_);
  return initialized_;
}

//sets the finished to true
void MyWindowWrapper::Exit(void) {
  finished_=true;
}

// Terminate tells GLFW to close it's window and clean up
void MyWindowWrapper::Terminate(void) {
  finished_=true;
  glfwTerminate();
}


/*******************************
* Methods                     */

// ProccessOSEvents() makes sure the operating system isn't blocking our window,
// and invokes our input_handler_
void MyWindowWrapper::ProccessOSEvents()  {
  glfwPollEvents();
}


void MyWindowWrapper::SwapBuffers() {
  glfwSwapBuffers(window_);
}


void MyWindowWrapper::Resize(const int width,const int height)  {
  
  int window_width_ = width;
  int window_height_ = height;
  glViewport(0,0,width,height);

  double field_of_view_y = 45;
  double aspect_ratio_x_to_y = window_width_/window_height_;
  double near_clip_distance= .5;
  double far_clip_distance = 5;
  
  double depth_sum(near_clip_distance+far_clip_distance);
  double depth_range(near_clip_distance-far_clip_distance);
  double f_y = tan(M_PI_2 - field_of_view_y) / 2;
  double f_x = f_y / aspect_ratio_x_to_y;

	double projection_matrix[16] = {
    f_x,            0.0,            0.0,            0.0,
    0.0,            f_y,            0.0,            0.0,
    0.0,            0.0,  depth_sum/depth_range,   2*depth_sum/depth_range,
    0.0,            0.0,           -1.0,            0.0
  };
  
  glMatrixMode(GL_PROJECTION);//changing perspective rather then drawing
	
  glLoadIdentity();

  glMultMatrixd(projection_matrix);
  //glTranslated(0.0,0.0,-0.5);
  
  glOrtho(0, window_width_, window_height_, 0, -1, 10);
}

void MyWindowWrapper::RegisterResize(GLFWwindowsizefun)  {
  MyWindowControl::glfw_to_mywindowwrapper.emplace(window_, this);
  glfwSetWindowSizeCallback(window_,MyWindowControl::ResizeWindow);
}

void MyWindowWrapper::RegisterKeyboard(GLFWkeyfun keyboard) {
  glfwSetKeyCallback(window_,keyboard);
}

void MyWindowWrapper::RegisterMouse(GLFWcursorenterfun cursorenterFunc,
                                    GLFWcursorposfun positionFunc,
                                    GLFWmousebuttonfun buttonFunc,
                                    GLFWscrollfun scrollwheelFunc) {
  glfwSetCursorPosCallback(window_, positionFunc);
  glfwSetMouseButtonCallback(window_, buttonFunc);
  glfwSetScrollCallback(window_, scrollwheelFunc);
  glfwSetCursorEnterCallback(window_, cursorenterFunc);
}

/*******************************
* Accessors and Mutators      */
const bool MyWindowWrapper::initialized() {
  return initialized_;
}

const bool MyWindowWrapper::done() {
  return finished_;
}

GLFWwindow * MyWindowWrapper::context(void) {
  return window_;
}

char const* MyWindowWrapper::title() {
  return title_;
}
  
void MyWindowWrapper::set_title(const char * title) {
  size_t title_length = strlen(title);
  for (size_t i = 0;i<title_length;++i) {
    title_[i] = title[i];
  }
  glfwSetWindowTitle(window_, title_);
}

namespace MyWindowControl {

void ResizeWindow(GLFWwindow* window, int width, int height) {
  glfw_to_mywindowwrapper.at(window)->Resize(width, height);
}

}