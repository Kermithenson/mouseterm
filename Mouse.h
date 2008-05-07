// Possible mouse modes
typedef enum
{
    NO_MODE = -1,
    NORMAL_MODE,
    HILITE_MODE,
    BUTTON_MODE,
    ALL_MODE
} MouseMode;

// Control codes

// Normal control codes
#define UP_ARROW "\033[A"
#define DOWN_ARROW "\033[B"
// Control codes for application keypad mode
#define UP_ARROW_APP "\033OA"
#define DOWN_ARROW_APP "\033OB"
#define ARROW_LEN (sizeof(UP_ARROW) - 1)

#define TOGGLE_MOUSE "\033[?100" // Excludes mode and toggle flag
#define TOGGLE_MOUSE_LEN (sizeof(TOGGLE_MOUSE) - 1)

// X11 mouse button values
typedef enum
{
    MOUSE_BUTTON1 = 0,
    MOUSE_BUTTON2,
    MOUSE_BUTTON3,
    MOUSE_RELEASE,
    MOUSE_WHEEL_UP,
    MOUSE_WHEEL_DOWN
} MouseButton;

// X11 mouse reporting responses
#define MOUSE_RESPONSE "\033[M%c%c%c"
#define MOUSE_RESPONSE_LEN (sizeof(MOUSE_RESPONSE) - 1)

// Returns a control code for a mouse movement (from iTerm)
inline NSData* mousePress(MouseButton button, unsigned int modflag, int x, int y)
{
    char buf[MOUSE_RESPONSE_LEN];
    char cb;

    cb = button % 3;
    if (button > MOUSE_RELEASE) // Wheel movement
        cb += 64;
    if (modflag & NSControlKeyMask)
        cb += 16;
    if (modflag & NSShiftKeyMask)
        cb += 4;
    if (modflag & NSAlternateKeyMask) // Alt/option
        cb += 8;

    snprintf(buf, MOUSE_RESPONSE_LEN, MOUSE_RESPONSE, 32 + cb, 32 + x + 1,
             32 + y + 1);
    return [NSData dataWithBytes: buf length: MOUSE_RESPONSE_LEN];
}