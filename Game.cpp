#include "Engine.h"
#include <stdlib.h>
#include <map>
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
    Game.Initialize();
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    static Keys key_map = { std::pair(InputKey::ESCAPE, KeyState(VK_ESCAPE)),
                            std::pair(InputKey::LEFT, KeyState(VK_LEFT)),
                            std::pair(InputKey::RIGHT, KeyState(VK_RIGHT)),
                            std::pair(InputKey::UP, KeyState(VK_UP)),
                            std::pair(InputKey::DOWN, KeyState(VK_DOWN)),
                            std::pair(InputKey::SPACE, KeyState(VK_SPACE)),
                            std::pair(InputKey::RETURN, KeyState(VK_RETURN))};

    for (auto& key : key_map)
    {
        key.second.OldState = key.second.State;
        key.second.State = is_key_pressed(key.second.OsKey);
    }

  Game.Input(key_map);
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

