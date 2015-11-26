#include "hud.h"

FlashScreen::FlashScreen()
{
    frames = 0;
    current_frame = 0;
    is_running = false;
}

void FlashScreen::Set(Color _color, int _frames)
{
    color.r = _color.r;
    color.g = _color.g;
    color.b = _color.b;
    color.a = 0;
    frames = _frames;
    rect.setPosition(Vector2f(0.0, 0.0));
    rect.setSize(Vector2f((double)DEFAULT_SCREEN_W, (double)DEFAULT_SCREEN_H));
}

void FlashScreen::Flash(RenderWindow* window)
{
    if(is_running)
    {
        if(current_frame < frames)
        {
            if(current_frame < (frames / 2))
            {
                rect.setFillColor(Color(color.r, color.g, color.b, 255 - (255 - (frames / 2) * (current_frame - (frames / 2)))));
            }
            else
            {
                rect.setFillColor(Color(color.r, color.g, color.b, (255 / (frames / 2)) * current_frame));
            }
        }
        else
        {
            is_running = false;
        }
        if(is_running)
        {
            window->draw(rect);
            current_frame++;
        }
    }
}

void FlashScreen::Start()
{
    is_running = true;
    current_frame = 0;
}

Button::Button()
{
    is_active = false;
    position.Set(0, 0);
    lenght = 0;
    height = 0;
    is_pressed = false;
    color_thick.r = 0;
    color_thick.g = 0;
    color_thick.b = 0;
    color_thick.a = 0;
}

void Button::Set(Vector<int> _position, int _lenght, int _height, const char *_title, Color _color_thick)
{
    position = _position;
    lenght = _lenght;
    height = _height;
    text.setString(_title);
    text.setCharacterSize(24);
    text.setColor(_color_thick);
    text.setPosition((double)position.x + 5.0, (double)position.y);
    color_thick.r = _color_thick.r;
    color_thick.g = _color_thick.g;
    color_thick.b = _color_thick.b;
    color_thick.a = _color_thick.a;
}

void Button::Draw(RenderWindow *window)
{
    static RectangleShape shape;
    shape.setPosition((double)position.x, (double)position.y);
    shape.setSize(Vector2f((double)lenght, (double)height));
    shape.setFillColor(Color(0, 0, 0, 0));
    shape.setOutlineThickness(3.0);
    shape.setOutlineColor(color_thick);

    window->draw(shape);
    window->draw(text);
}

LineIndicator::LineIndicator()
{
    data[MAX] = 0.0;
    data[CURRENT] = 0.0;
    position.x = 0.0;
    position.y = 0.0;
    autocolor = false;
    length = 0;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0;
    color_thick.r = 255;
    color_thick.g = 255;
    color_thick.b = 255;
    color_thick.a = 0;
}

void LineIndicator::Draw(RenderWindow *window)
{
    static RectangleShape shape_ind;
    static RectangleShape shape_thick;
    static double length_ind;

    shape_ind.setPosition(position);
    shape_thick.setPosition(position);
    length_ind = (double)data[CURRENT] / (double)data[MAX] * length;

    shape_thick.setSize(Vector2f(length, HUD_DEFAULT_LINEIND_H));
    shape_ind.setSize(Vector2f(length_ind, HUD_DEFAULT_LINEIND_H));

    shape_thick.setFillColor(Color(0, 0, 0, 0));
    shape_thick.setOutlineColor(color_thick);
    if(autocolor)
    {

        color.r = 255 - 255 * ((double)data[CURRENT] / (double)data[MAX]);
        color.g = 255 * ((double)data[CURRENT] / (double)data[MAX]);
        color.b = 0;
        color.a = DEFAULT_ALPHA;
        shape_ind.setFillColor(color);
    }
    else
    {
        shape_ind.setFillColor(color);
    }

    shape_thick.setOutlineThickness(HUD_DEFAULT_THICK);

    window->draw(shape_ind);
    window->draw(shape_thick);

}

void LineIndicator::SetPosition(Vector2f pos)
{
    position = pos;
}

void LineIndicator::SetData(int current, int max)
{
    data[CURRENT] = current;
    data[MAX] = max;
}

void LineIndicator::SetLength(double _length)
{
    length = _length;
}

void LineIndicator::SetColor(Color _color, Color _color_t)
{
    color.r = _color.r;
    color.g = _color.g;
    color.b = _color.b;
    color.a = _color.a;

    color_thick.r = _color_t.r;
    color_thick.g = _color_t.g;
    color_thick.b = _color_t.b;
    color_thick.a = _color_t.a;
}

void LineIndicator::SetColor(int _r, int _g, int _b, int _a,
                             int _t_r, int _t_g, int _t_b, int _t_a)
{
    color.r = _r;
    color.g = _g;
    color.b = _b;
    color.a = _a;

    color_thick.r = _t_r;
    color_thick.g = _t_g;
    color_thick.b = _t_b;
    color_thick.a = _t_a;
}

JumpText::JumpText()
{
    is_active = false;
    inertia.Set(0.0, 0.0);
}

void JumpText::Set(Color _color, const char *data, Vector<double> _position, Vector<double> _inertia)
{
    is_active = true;
    text.setString(data);
    text.setColor(_color);
    position = _position;
    inertia = _inertia;

    frame = JT_LIVETIME;
}

void JumpText::Move()
{
    if(is_active)
    {
        if(frame > 0)
        {
            position = position + inertia;
            if(inertia.x > 0.0)
            {
                if(inertia.x < JT_DECELERATION) inertia.x = 0.0;
                else inertia.x -= JT_DECELERATION;
            }
            else
            {
                if(inertia.x > -JT_DECELERATION) inertia.x = 0.0;
                else inertia.x += JT_DECELERATION;
            }

            if(inertia.y > 0.0)
            {
                if(inertia.y < JT_DECELERATION) inertia.y = 0.0;
                else inertia.y -= JT_DECELERATION;
            }
            else
            {
                if(inertia.y > -JT_DECELERATION) inertia.y = 0.0;
                else inertia.y += JT_DECELERATION;
            }
            frame--;
            text.setPosition(position.x, position.y);
        }
        else
        {
            is_active = false;
        }
    }
}
