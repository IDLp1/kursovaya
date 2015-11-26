#ifndef MAIN_H
#define MAIN_H

#define DEFAULT_SCREEN_W 1280
#define DEFAULT_SCREEN_H 1024
#define DEFAULT_SCREEN_FLASH 24
#define SPAWN_ENEMY_MIN_COORD   50

#define DEFAULT_TIME_SPAWN_ENEMY_MIN    1000
#define DEFAULT_TIME_SPAWN_ENEMY_MAX    10000

#define FPS 60

#define MAX         1
#define CURRENT     0
#define MIN         0

#define TEXTURE_PLAYER          0
#define TEXTURE_ENEMY           1
#define TEXTURE_EXPLOSION       2
#define TEXTURE_SPARK           3
#define TEXTURE_SPARK_SHIELD    4
#define TEXTURE_BACKGROUND      5
#define TEXTURE_LASER           6
#define TEXTURE_ENEMY_BIG       7
#define TEXTURE_ENEMY_BOX       8
#define TEXTURE_BACKGROUND2     9
#define TEXTURE_BACKGROUND3     10
#define TEXTURE_BOX             11

#define SOUND_DEFAULT_WEAPON    0
#define SOUND_HIT               1
#define SOUND_EXPLOSION         2
#define SOUND_SHUTDOWN          3
#define SOUND_HIT_SHIELD        4
#define SOUND_BREAK_SHIELD      5
#define SOUND_DOUBLE_KILL       6
#define SOUND_MULTI_KILL        7
#define SOUND_ULTRA_KILL        8
#define SOUND_MEGA_KILL         9
#define SOUND_MONSTER_KILL      10
#define SOUND_PICKUP            11

#define MUSIC_LEVEL01           0
#define MUSIC_LEVEL02           1
#define MUSIC_LEVEL03           2


#define BUTTON_RETRY            0
#define BUTTON_EXIT             1

#define SOUND_Z     0.5

#define HIT 0
#define HIT_SHIELD 1

#define MAX_BULLET  512
#define MAX_ENEMY   16
#define MAX_TEXTURE 12
#define MAX_ANIMATION   32
#define MAX_JIMPTEXT    96
#define MAX_SOUNDBUFFER 16
#define MAX_MUSIC   3
#define MAX_BUTTONS 8
#define MAX_FLASHSCREEN 4
#define MAX_BOX 64

#define SPARK 0
#define SPARK_SHIELD 1

#define DEFAULT_FONT_SIZE 18

#define FLASHSCREEN_LEVELUP 0





#define GAMEPLAY_TICK_MLS   200

#include <iostream>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <stdio.h>

using namespace std;
using namespace sf;

int random(int min, int max);
double random(double min, double max);

const char texture_list[MAX_TEXTURE][128]
{
    "sprites/player_ship.png",
    "sprites/enemy.png",
    "sprites/explosion.png",
    "sprites/spark.png",
    "sprites/spark_shield.png",
    "sprites/background00.png",
    "sprites/laser.png",
    "sprites/enemy_big.png",
    "sprites/enemy_box.png",
    "sprites/background01.png",
    "sprites/background02.png",
    "sprites/box.png"

};

const char soundbuffer_list[MAX_SOUNDBUFFER][128]
{
    "sounds/default.wav",
    "sounds/hit.ogg",
    "sounds/explosion.ogg",
    "sounds/shutdown.wav",
    "sounds/hit_shield.wav",
    "sounds/break_shield.wav",
    "sounds/double_kill.wav", //6
    "sounds/multi_kill.wav",
    "sounds/ultra_kill.wav",
    "sounds/mega_kill.wav",
    "sounds/monster_kill.wav", //10
    "sounds/pickup.wav"
};

const char music_list[MAX_MUSIC][128]
{
    "music/03.ogg",
    "music/02.ogg",
    "music/01.ogg"
};

const char bonus_text_list[6][128]
{
    "kill", //0
    "Double kill", //1
    "Multi kill!", //2
    "Ultra kill!!", //3
    "Mega kill!!!", //4
    "MONSTER!!!!!" //5
};

const char button_list[2][128]
{
    "Restart",
    "Exit"
};

#endif // MAIN
