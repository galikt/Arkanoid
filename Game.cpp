#include "Engine.h"
#include <stdlib.h>
#include <list>
#include "Arcanoid.h"
//#include "Input.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

static Arcanoid Game;

// initialize game data in this function
void initialize()
{
    Game.Initialize(1, 150);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  static std::list<InputKey> key_list;

  if (is_key_pressed(VK_ESCAPE))
  {
    key_list.push_back(InputKey::ESCAPE);
    schedule_quit_game();
  }

  if (is_key_pressed(VK_SPACE))
      key_list.push_back(InputKey::SPACE);

  if (is_key_pressed(VK_LEFT))
      key_list.push_back(InputKey::LEFT);

  if (is_key_pressed(VK_UP))
      key_list.push_back(InputKey::UP);

  if (is_key_pressed(VK_RIGHT))
      key_list.push_back(InputKey::RIGHT);

  if (is_key_pressed(VK_DOWN))
      key_list.push_back(InputKey::DOWN);

  if (is_key_pressed(VK_RETURN))
      key_list.push_back(InputKey::RETURN);

  Game.Input(key_list);
  Game.Process(dt);
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
  // clear backbuffer
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
  Game.Draw(*buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

// free game data in this function
void finalize()
{
}

