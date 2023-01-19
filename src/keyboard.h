#include <map>

enum class KeyCode
{
    None = 0,
    Escape = 27,
    Space = 32,
    Q = 113,
    W = 119,
    A = 97,
    S = 115,
    D = 100
};

struct Keyboard
{
    // @TODO: Replace with unordered_map
    // Used to keep track of pressed keys.
    static std::map<KeyCode, bool> keydownMap;
    // Used to keep track of released keys.
    static std::map<KeyCode, bool> prevKeydownMap;

    static bool key_pressed(KeyCode keyCode);
    static bool key_released(KeyCode keyCode);
};
