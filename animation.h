#ifndef ANIMATION_H
#define ANIMATION_H

#include "main.h"
#include "vector.h"

class Animation
{
public:
    Animation();

    int    current_frame;
    int    number_of_frame;
    int    lenght;
    int    height;
    Vector<int>     size_frame;


    Sprite  sprite;

    bool    repeat;
    bool    is_running;
    bool    mirror;
    bool    mirror_motion;
    int     ping[2];

    void Set(int _number_of_frame,
             int _lenght, int _height, Vector<int> _size_frame, int _ping, bool _repeat = false, bool _mirror = false);
    void Play();
    void Start();
    void Reload();
    void Stop();

};

#endif // ANIMATION_H


