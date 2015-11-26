#include "animation.h"

Animation::Animation()
{
    is_running = false;
    repeat = false;
    mirror = false;
    mirror_motion = false;
    current_frame = 0;
    number_of_frame = 0;
    lenght = 0;
    height = 0;
    size_frame = Vector<int>(0, 0);
    ping[MAX] = 0;
    ping[CURRENT] = ping[MAX];
}


void Animation::Set(int _number_of_frame,
                    int _lenght, int _height, Vector<int> _size_frame, int _ping, bool _repeat, bool _mirror)
{
    current_frame = 0;

    number_of_frame = _number_of_frame;
    lenght = _lenght;
    height = _height;
    size_frame = _size_frame;
    repeat = _repeat;
    mirror = _mirror;
    mirror_motion = false;
    ping[MAX] = _ping;
    ping[CURRENT] = ping[MAX];
}

void Animation::Play()
{
    Vector<int> pointer;
    if(mirror_motion) pointer.Set(lenght - 1, height - 1);
    else pointer.Set(0, 0);
    int counter(0);
    counter = current_frame;
    if(current_frame >= number_of_frame)
    {
        if(repeat)
        {
            current_frame = 0;
        }
        if(mirror)
        {
            if(mirror_motion)
            {
                mirror_motion = false;
                is_running = false;
            }
            else
            {
                mirror_motion = true;
                current_frame = 0;
            }
        }
        else
        {
            is_running = false;
            return;
        }
    }
    while(counter > 0)
    {
        if(!mirror_motion)
        {
            if(pointer.x >= (lenght - 1))
            {
                pointer.x = 0;
                if(pointer.y < height)
                {
                    pointer.y++;
                }
                else
                {
                    pointer.y = 0;
                }
            }
            else
            {
                pointer.x++;
            }
            counter--;
        }
        else
        {
            if(pointer.x <= 0)
            {
                pointer.x = lenght - 1;
                if(pointer.y < 0)
                {
                    pointer.y = 0;
                }
                else pointer.y--;
            }
            else
            {
                pointer.x--;
            }
            counter--;
            // зеркальный расчет
        }
    }
    if(!mirror_motion) sprite.setTextureRect(IntRect(
                               size_frame.x * pointer.x,
                           size_frame.y * pointer.y,
                           size_frame.x,
                           size_frame.y));

    else sprite.setTextureRect(IntRect(
                                   (size_frame.x * (pointer.x + 1)) - 1,
                               size_frame.y * pointer.y,
                               -size_frame.x,
                               size_frame.y));
    if(ping[CURRENT] <= 0)
    {
        current_frame++;
        ping[CURRENT] = ping[MAX];
    }
    else ping[CURRENT]--;
}

void Animation::Start()
{
    is_running = true;
}

void Animation::Reload()
{
    current_frame = 0;
}

void Animation::Stop()
{

    current_frame = 0;
    number_of_frame = 0;
    lenght = 0;
    height = 0;
    size_frame = Vector<int>(0, 0);
    repeat = false;
}
