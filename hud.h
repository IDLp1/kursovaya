#ifndef HUD
#define HUD
#include "main.h"
#include "vector.h"

#define HUD_DEFAULT_LINEIND_W   256.0
#define HUD_DEFAULT_LINEIND_H   12.0
#define HUD_DEFAULT_THICK       5.0

#define LINEIND_HEALTH_POS  Vector2f(5.0, 5.0)
#define LINEIND_SHIELD_POS  Vector2f(5.0, 45.0)
#define LINEIND_ENERGY_POS  Vector2f(5.0, 85.0)

#define DEFAULT_ALPHA       175

#define JT_LIVETIME         75
#define JT_RANDOMINERTION   random(-8.0, 8.0)
#define JT_DECELERATION     0.5
#define JT_SIZE             20

class FlashScreen
{
public:
    bool is_running;
    FlashScreen();
    RectangleShape rect;
    Color color;
    int frames;
    int current_frame;
    void Set(Color _color, int _frames);
    void Flash(RenderWindow* window);
    void Start();
};

class Button
{
public:
    Button();
    bool    is_active;
    Vector<int> position;
    int lenght;
    int height;
    bool is_pressed;
    Text   text;
    Color   color_thick;

    void Set(Vector<int> _position, int _lenght, int _height, const char* _title, Color _color_thick);
    void Draw(RenderWindow* window);
};


class LineIndicator
{
public:

    LineIndicator();
    void        Draw(RenderWindow* window);
    void        SetPosition(Vector2f pos);
    void        SetData(int current, int max);
    void        SetLength(double _length);

    Color       color;
    Color       color_thick;
    bool        autocolor;

    void        SetColor(int _r, int _g, int _b, int _a,
                         int _t_r, int _t_g, int _t_b, int _t_a);
    void        SetColor(Color _color, Color _color_t);

private:

    int         data[2];
    double         length;
    Vector2f    position;


};

class JumpText
{
public:
    JumpText();
    bool    is_active;
    Text    text;
    Vector<double>  position;
    Vector<double>  inertia;
    int     frame;

    void    Set(Color _color, const char* data, Vector<double> _position, Vector<double> _inertia);
    void    Move();

};

#endif // HUD

