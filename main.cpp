#include "main.h"
#include "vector.h"
#include "player.h"
#include "bullet.h"
#include "weapon.h"
#include "enemy.h"
#include "hud.h"
#include "animation.h"


Player* player = new Player;
Enemy*  p_enemy = new Enemy[MAX_ENEMY];
EnemyPrototype* p_enemy_prot = new EnemyPrototype[3];
Bullet* p_bullet = new Bullet[MAX_BULLET];
Box*    p_box = new Box[MAX_BOX];

WeaponTemp* p_default_weapon = new WeaponTemp;
WeaponTemp* p_default_weapon2 = new WeaponTemp;
WeaponTemp* p_big_enemy_weapon = new WeaponTemp;
WeaponTemp* p_box_enemy_weapon = new WeaponTemp;
WeaponTemp* p_minigan = new WeaponTemp;

Engine* p_default_engine = new Engine;
Texture* texture = new Texture[MAX_TEXTURE];

Animation* p_animation = new Animation[MAX_ANIMATION];

Sprite* s_explosion = new Sprite;
Sprite* s_spark = new Sprite[2];
Sprite* s_enemy = new Sprite[MAX_ENEMY_PROT];
Sprite* rs_background = new Sprite[3];
Sprite* s_default_bullet = new Sprite;
Sprite* s_box = new Sprite;

SoundBuffer* p_soundbuffer = new SoundBuffer[MAX_SOUNDBUFFER];
SoundBuffer* sb_music = new SoundBuffer[MAX_MUSIC];

Sound* sn_blaster = new Sound;
Sound* sn_hit = new Sound[2];
Sound* sn_explosion = new Sound;
Sound* sn_shutdown = new Sound;
Sound* sn_break_shield = new Sound;
Sound* sn_bonus = new Sound[5];
Sound* sn_music = new Sound[MAX_MUSIC];
Sound* sn_pickup = new Sound;


LineIndicator* p_lineindicator_health = new LineIndicator;
LineIndicator* p_lineindicator_shield = new LineIndicator;
LineIndicator* p_lineindicator_energy = new LineIndicator;

JumpText* p_jumptext = new JumpText[MAX_JIMPTEXT];

Button* p_button = new Button[MAX_BUTTONS];

FlashScreen* p_flashscreen = new FlashScreen[MAX_FLASHSCREEN];

Music* music = new Music[3];

Clock timer_spawn_enemy;

bool key_control;
int random_music;

double _abs(double a)
{
    if(a > 0.0) a = a * -1.0;
    return a;
}

double GetLenght(Vector2f a, Vector2f b)
{
    return sqrt(pow(b.x - a.x, 2.0) + pow(b.y - a.y, 2.0));
}

double GetSoundBalance(double x)
{
    static double dw = (double)DEFAULT_SCREEN_W / 2.0;
    return (x - dw) / dw;
}

int random(int min, int max)
{
    max++;
    return min + rand() % (max - min);
}

double random(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

void LoadTexture()
{
    for(int i(0); i < MAX_TEXTURE; i++)
    {
        if(texture_list[i][0] != '\0')
        {
            if(!texture[i].loadFromFile(texture_list[i]))
            {
                cout << "Can't load : " << texture_list[i] << endl;
            }
            else
            {
                cout << "Loaded : " << texture_list[i] << endl;
            }
        }
    }
}

void LoadSoundBuffer()
{
    for(int i(0); i < MAX_SOUNDBUFFER; i++)
    {
        if(soundbuffer_list[i][0] != '\0')
        {
            if(!p_soundbuffer[i].loadFromFile(soundbuffer_list[i]))
            {
                cout << "Can't load : " << soundbuffer_list[i] << endl;
            }
            else
            {
                cout << "Loaded : " << soundbuffer_list[i] << endl;
            }
        }
    }
}

void LoadMusic()
{
    for(int i(0); i < MAX_MUSIC; i++)
    {
        if(music_list[i][0] != '\0')
        {
            if(!sb_music[i].loadFromFile(music_list[i]))
            {
                cout << "Can't load : " << music_list[i] << endl;
            }
            else
            {
                cout << "Loaded : " << music_list[i] << endl;
            }
        }
    }
}

void DrawFlashScreen(RenderWindow* window)
{
    for(int i(0); i < MAX_FLASHSCREEN; i++)
    {
        if(p_flashscreen[i].is_running)
        {
            p_flashscreen[i].Flash(window);
        }
    }
}

void DrawAnimation(RenderWindow* window)
{
    for(int i(0); i < MAX_ANIMATION; i++)
    {
        if(p_animation[i].is_running)
        {
            p_animation[i].Play();
            window->draw(p_animation[i].sprite);
        }
    }
}

void DrawBox(RenderWindow* window)
{
    for(int i(0); i < MAX_BOX; i++)
    {
        if(p_box[i].is_active)
        {
            p_box[i].sprite->setPosition(p_box[i].position.x, p_box[i].position.y);
            window->draw(*p_box[i].sprite);
        }
    }
    s_box->setRotation(s_box->getRotation() + 1.0);
}

void DrawJimpText(RenderWindow* window)
{
    for(int i(0); i < MAX_JIMPTEXT; i++)
    {
        if(p_jumptext[i].is_active)
        {
            p_jumptext[i].Move();
            window->draw(p_jumptext[i].text);
        }
    }
}

void PlayJimpText(Vector<double> _position, Color _color, char* data, Vector<double> _inertia)
{
    for(int i(0); i < MAX_JIMPTEXT; i++)
    {
        if(!p_jumptext[i].is_active)
        {
            p_jumptext[i].Set(_color, data, _position, _inertia);
            break;
        }
    }
}


void PlayAnimation(Vector2f pos, Sprite* _sprite, int _number_of_frame,
                   int _lenght, int _height, Vector<int> _size_frame, int _ping, bool _repeat = false, bool _mirror = false)
{

    for(int i(0); i < MAX_ANIMATION; i++)
    {
        if(!p_animation[i].is_running)
        {
            p_animation[i].sprite = *_sprite;
            p_animation[i].sprite.setPosition(pos);
            p_animation[i].Set(_number_of_frame, _lenght, _height, _size_frame, _ping,  _repeat, _mirror);
            p_animation[i].is_running = true;
            break;
        }
    }
}

void DrawButtons(RenderWindow* window)
{
    for(int i(0); i < MAX_BUTTONS; i++)
    {
        if(p_button[i].is_active)
        {
            p_button[i].Draw(window);
        }
    }
}

void CheckButtons(RenderWindow* window)
{
    for(int i(0); i < MAX_BUTTONS; i++)
    {
        if(p_button[i].is_active)
        {
            if(Mouse::getPosition(*window).x > p_button[i].position.x && Mouse::getPosition(*window).x < p_button[i].position.x + p_button[i].lenght)
            {
                if(Mouse::getPosition(*window).y > p_button[i].position.y && Mouse::getPosition(*window).y < p_button[i].position.y + p_button[i].height)
                {
                    if(Mouse::isButtonPressed(Mouse::Left))
                    {
                        p_button[i].is_pressed = true;
                    }
                }
            }
        }
        else
        {
            if(p_button[i].is_pressed)
            {
                p_button[i].is_pressed = false;
            }
        }
    }
}

void Attack(Player* player)
{
    if(player->is_alive)
    {
        if(!player->is_empty)
        {
            if(!player->weapon[player->weapon_selected].is_reload)
            {
                player->weapon[player->weapon_selected].is_reload = true;
                player->energy[CURRENT] -= player->weapon[player->weapon_selected].expense;
                player->weapon[player->weapon_selected].clock_reload.restart();
                for(int i(0); i < MAX_BULLET; i++)
                {
                    if(!p_bullet[i].is_exist)
                    {
                        p_bullet[i].SetActive(player);
                        player->weapon[player->weapon_selected].sound->setRelativeToListener(true);
                        player->weapon[player->weapon_selected].sound->setPosition(GetSoundBalance(player->GetPosition().x), 0.f, SOUND_Z);
                        player->weapon[player->weapon_selected].sound->play();
                        //cout << "dmg = " << p_bullet[i].damage << endl;
                        break;
                    }
                }
            }
        }
    }
}

void Attack(Enemy* enemy)
{
    if(enemy->is_alive)
    {
        if(!enemy->weapon.is_reload)
        {
            enemy->weapon.is_reload = true;
            enemy->weapon.clock_reload.restart();
            for(int i(0); i < MAX_BULLET; i++)
            {
                if(!p_bullet[i].is_exist)
                {
                    p_bullet[i].SetActive(enemy);
                    enemy->weapon.sound->setRelativeToListener(true);
                    enemy->weapon.sound->setPosition(GetSoundBalance(enemy->GetPosition().x), 0.f, SOUND_Z);
                    enemy->weapon.sound->play();
                    //cout << "dmg = " << p_bullet[i].damage << endl;
                    break;
                }
            }
        }
    }
}

void Drop(Enemy* enemy)
{
    for(int i(0); i < MAX_BOX; i++)
    {
        if(!p_box[i].is_active)
        {
            p_box[i].Spawn(Vector<double>(enemy->GetPosition().x, enemy->GetPosition().y), DEFAULT_BOX_ENERGY);
            break;
        }
    }
}


int main()
{
    char name_game[] = "name";
    srand(time(NULL));

    const double acceleration = 0.5;
    //cout << "Using WASD to moving ship, and press Ctrl to activate shield" << endl;

    Font font;
    if(!font.loadFromFile("DejaVuSans.ttf")) return 0;
    Text fps_text;
    fps_text.setFont(font);
    fps_text.setCharacterSize(DEFAULT_FONT_SIZE);
    fps_text.setPosition(Vector2f(100.0, 100.0));
    char char_fps_text[16];
    Text text_score;

    CircleShape shape(3.0);
    CircleShape bullet_shape(3.0);//пули
    CircleShape circle_enemy (3.0);//враг
    circle_enemy.setOrigin(1.5, 1.5);
    CircleShape circle_shield(SHIELD_R);//щит
    circle_shield.setFillColor(sf::Color(0,255,255,50));

    shape.setFillColor(sf::Color(255, 0, 0));

    Vertex dev_vector_inertia[2];
    Vertex dev_vector_view[2];

    p_lineindicator_health->SetPosition(LINEIND_HEALTH_POS);
    p_lineindicator_health->SetLength(HUD_DEFAULT_LINEIND_W);
    p_lineindicator_health->SetColor(Color(0, 0, 0, 0), Color(255, 255, 255, DEFAULT_ALPHA));
    p_lineindicator_health->autocolor = true;

    p_lineindicator_shield->SetPosition(LINEIND_SHIELD_POS);
    p_lineindicator_shield->SetLength(HUD_DEFAULT_LINEIND_W);
    p_lineindicator_shield->SetColor(Color(0, 50, 255, DEFAULT_ALPHA), Color(255, 255, 255, DEFAULT_ALPHA));

    p_lineindicator_energy->SetPosition(LINEIND_ENERGY_POS);
    p_lineindicator_energy->SetLength(HUD_DEFAULT_LINEIND_W);
    p_lineindicator_energy->SetColor(Color(255, 0, 255, DEFAULT_ALPHA), Color(0, 255, 0, DEFAULT_ALPHA));
    p_button[BUTTON_RETRY].Set(Vector<int>(DEFAULT_SCREEN_W / 2, DEFAULT_SCREEN_H / 2), 100, 30, button_list[BUTTON_RETRY],  Color(255, 0, 0, 255));
    p_button[BUTTON_RETRY].text.setFont(font);
    p_button[BUTTON_EXIT].Set(Vector<int>(DEFAULT_SCREEN_W - 150, DEFAULT_SCREEN_H - 300), 100, 30, button_list[BUTTON_EXIT], Color(255, 0, 0, 255));
    p_button[BUTTON_EXIT].text.setFont(font);

    p_flashscreen[FLASHSCREEN_LEVELUP].Set(Color::White, 24);



    text_score.setFont(font);
    text_score.setCharacterSize(16);
    text_score.setPosition(Vector2f(25.0, 100.0));
    text_score.setColor(Color(255, 220, 0, DEFAULT_ALPHA));
    char char_text_score[16];
    //String string_fps_text();

    Clock clock_fps;
    Clock gameplay_tick;
    Clock time_bonus;
    double _clock_fps = 0.0;
    unsigned int fps = 0;

    //Текстуры, спрайты
    LoadTexture();

    player->sprite.setTexture(texture[0]);
    player->sprite.setTextureRect(IntRect(0, 0, 64, 64));
    player->sprite.setOrigin(PLAYER_DIM/2, PLAYER_DIM/2);

    s_box->setTexture(texture[TEXTURE_BOX]);
    s_box->setOrigin(SIZE_BOX / 2, SIZE_BOX / 2);

    for(int i(0); i < MAX_BOX; i++)
    {
        p_box[i].sprite = s_box;
    }

    s_enemy[ENEMY_PROT_SOLDIER].setTexture(texture[TEXTURE_ENEMY]);
    s_enemy[ENEMY_PROT_BIG].setTexture(texture[TEXTURE_ENEMY_BIG]);
    s_enemy[ENEMY_PROT_BOX].setTexture(texture[TEXTURE_ENEMY_BOX]);

    s_explosion->setTexture(texture[TEXTURE_EXPLOSION]);
    s_explosion->setOrigin(Vector2f(32.0, 32.0));
    s_explosion->setScale(Vector2f(2.0, 2.0));

    s_spark[SPARK].setTexture(texture[TEXTURE_SPARK]);
    s_spark[SPARK].setOrigin(Vector2f(16.0, 16.0));

    s_spark[SPARK_SHIELD].setTexture(texture[TEXTURE_SPARK_SHIELD]);
    s_spark[SPARK_SHIELD].setOrigin(Vector2f(16.0, 16.0));

    rs_background[0].setTexture(texture[TEXTURE_BACKGROUND]);
    rs_background[0].setPosition(0.0, 0.0);
    rs_background[0].setColor(Color(150, 150, 150, 255));
    rs_background[1].setTexture(texture[TEXTURE_BACKGROUND2]);
    rs_background[1].setPosition(0.0, 0.0);
    rs_background[1].setColor(Color(150, 150, 150, 255));
    rs_background[2].setTexture(texture[TEXTURE_BACKGROUND3]);
    rs_background[2].setPosition(0.0, 0.0);
    rs_background[2].setColor(Color(150, 150, 150, 255));

    s_default_bullet->setTexture(texture[TEXTURE_LASER]);
    s_default_bullet->setOrigin(Vector2f(8.0, 8.0));

    shape.setOrigin(1.5, 1.5);

    for(int i(0); i < MAX_JIMPTEXT; i++)
    {
        p_jumptext[i].text.setFont(font);
        p_jumptext[i].text.setCharacterSize(JT_SIZE);
    }


    // Звуки
    LoadSoundBuffer();
    LoadMusic();

    sn_blaster->setBuffer(p_soundbuffer[SOUND_DEFAULT_WEAPON]);

    sn_hit[HIT].setBuffer(p_soundbuffer[SOUND_HIT]);
    sn_hit[HIT_SHIELD].setBuffer(p_soundbuffer[SOUND_HIT_SHIELD]);
    sn_explosion->setBuffer(p_soundbuffer[SOUND_EXPLOSION]);
    sn_explosion->setVolume(55.0);
    sn_shutdown->setBuffer(p_soundbuffer[SOUND_SHUTDOWN]);
    sn_break_shield->setBuffer(p_soundbuffer[SOUND_BREAK_SHIELD]);

    sn_bonus[0].setBuffer(p_soundbuffer[SOUND_DOUBLE_KILL]);
    sn_bonus[1].setBuffer(p_soundbuffer[SOUND_MULTI_KILL]);
    sn_bonus[2].setBuffer(p_soundbuffer[SOUND_ULTRA_KILL]);
    sn_bonus[3].setBuffer(p_soundbuffer[SOUND_MEGA_KILL]);
    sn_bonus[4].setBuffer(p_soundbuffer[SOUND_MONSTER_KILL]);

    sn_pickup->setBuffer(p_soundbuffer[SOUND_PICKUP]);
    sn_pickup->setVolume(65.0);

    sn_music[MUSIC_LEVEL01].setBuffer(sb_music[MUSIC_LEVEL01]);
    sn_music[MUSIC_LEVEL01].setVolume(45.0);
    sn_music[MUSIC_LEVEL02].setBuffer(sb_music[MUSIC_LEVEL02]);
    sn_music[MUSIC_LEVEL02].setVolume(65.0);
    sn_music[MUSIC_LEVEL03].setBuffer(sb_music[MUSIC_LEVEL03]);
    sn_music[MUSIC_LEVEL03].setVolume(85.0);

    random_music = random(0, 2);

    circle_shield.setOrigin(SHIELD_R, SHIELD_R);

    //p_default_weapon[1].SetWeapon(&enemy->weapon);

    ///
    ////////////////////////////Иницилизация окна

    RenderWindow window(sf::VideoMode(DEFAULT_SCREEN_W, DEFAULT_SCREEN_H), name_game); //"name"
    window.setKeyRepeatEnabled(false);
    //sf::Window window(sf::VideoMode(DEFAULT_SCREEN_W, DEFAULT_SCREEN_H), name_game); //"name"
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(FPS);
    Event window_event;
    int random_spawn_time = random(DEFAULT_TIME_SPAWN_ENEMY_MIN, DEFAULT_TIME_SPAWN_ENEMY_MAX);
    int level = 0;
    int score_for_level = 200;
    bool is_levelup = false;

    player->Alive();

    ////Дефолтные оружия
    ///
    p_default_weapon->SetParam(s_default_bullet, sn_blaster, Color(255, 255, 255, 255),  0,     0,     5.0,    2,    1000,   1000, 15.0, 5);
    p_default_weapon2->SetParam(s_default_bullet, sn_blaster, Color(255, 255, 255, 255), 10, 20, 5.0, 200, 1000, 2000, 15.0, 5);


    p_big_enemy_weapon->SetParam(s_default_bullet, sn_blaster,  Color(255, 0, 0, 255),  50,     100,    3.0,    800,    1000,   2500, 35.0, 30);
    p_box_enemy_weapon->SetParam(s_default_bullet, sn_blaster,  Color(100, 100, 255, 255),5,      10,     8.0,    175,    1000,   2500, 12.0, 5);
    p_minigan->         SetParam(s_default_bullet, sn_blaster,  Color(0, 255, 0, 255),3,      6,      10.0,   75,     1000,   1000, 13.0, 3);

    ////Враги
    ///

    p_enemy_prot[ENEMY_PROT_SOLDIER].SetParam(20, 10, p_default_weapon2, &s_enemy[ENEMY_PROT_SOLDIER], 64, 10, false);
    p_enemy_prot[ENEMY_PROT_BIG].SetParam(100, 15, p_big_enemy_weapon, &s_enemy[ENEMY_PROT_BIG], 96, 75, false);
    p_enemy_prot[ENEMY_PROT_BOX].SetParam(125, 15, p_box_enemy_weapon, &s_enemy[ENEMY_PROT_BOX], 96, 50, true);
    p_enemy_prot[ENEMY_PROT_SMALL].SetParam(10, 5, p_minigan, &s_enemy[ENEMY_PROT_SOLDIER], 64, 10, false);

    p_default_weapon2->SetWeapon(&player->weapon[0]);


    /////Дефольный движок
    ///
    p_default_engine->SetParam(0.5, 3, 5000, 5000);
    player->SetEngine(p_default_engine);

    sn_music[MUSIC_LEVEL01].play();
    player->score = 390;
    /////////////////////////////////Главный цикл
    ///
    while(window.isOpen())
    {
        while(window.pollEvent(window_event)) if(window_event.type == sf::Event::Closed) window.close();

        //fps
        _clock_fps = clock_fps.getElapsedTime().asSeconds();
        if(_clock_fps >= 1.0)
        {
            sprintf(char_fps_text, "fps = %d", fps);
            String string_fps_text(char_fps_text);
            fps_text.setString(string_fps_text);
            //cout << "fps = " << fps << endl;
            fps = 0;
            _clock_fps = 0;
            clock_fps.restart();

        }
        else fps++;
        //

        player->SetView(Mouse::getPosition(window));
        //cout << "X = " << player.GetPosition().x << " | Y = " << player.GetPosition().y << endl;
        if(!player->is_empty) player->sprite.setRotation(player->GetRotation());
        player->sprite.setPosition(player->GetPosition());
        circle_shield.setPosition(player->GetPosition());
        shape.setPosition(player->GetView());


        ////Обработка клавиатуры

        player->in_move = false;
        if(player->is_alive && player->engine.enabled && !player->is_empty)
        {
            static Vector<double> move_vector;
            if(Keyboard::isKeyPressed(Keyboard::W))
            {
                if(!(Keyboard::isKeyPressed(Keyboard::S)))
                {
                    move_vector.Set(0.0, -player->engine.power);
                    player->SetMove(move_vector, false);
                }
            }
            if(Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                if(!((Keyboard::isKeyPressed(sf::Keyboard::A))))
                {
                    move_vector.Set(player->engine.power, 0.0);
                    player->SetMove(move_vector, false);
                }
            }
            if(Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                if(!((Keyboard::isKeyPressed(Keyboard::W))))
                {
                    move_vector.Set(0.0, player->engine.power);
                    player->SetMove(move_vector, false);
                }
            }
            if(Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                if(!(Keyboard::isKeyPressed(Keyboard::D)))
                {
                    move_vector.Set(-player->engine.power, 0.0);
                    player->SetMove(move_vector, false);
                }
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))                 //Огонь
            {
                {
                    Attack(player);
                }
            }
            if(window_event.type == sf::Event::KeyPressed)
            {
                if(window_event.key.code == sf::Keyboard::LControl)
                {
                    if(!key_control) key_control = true;
                }

            }
            if(window_event.type == sf::Event::KeyReleased)
            {
                if(window_event.key.code == sf::Keyboard::LControl)
                {
                    if(key_control)
                    {
                        if(player->is_shield) player->is_shield = false;
                        else if(player->shield[CURRENT] > 0) player->is_shield = true;
                        key_control = false;
                    }
                }
            }
        }

        /////////ГРАНИЦЫ

        player->Move();

        if(player->GetPosition().x < SPAWN_ENEMY_MIN_COORD)
        {
            player->SetPosition(SPAWN_ENEMY_MIN_COORD, player->GetPosition().y);
            player->SetInertia(0.0, player->GetInertia().y);
        }
        if(player->GetPosition().x > DEFAULT_SCREEN_W - SPAWN_ENEMY_MIN_COORD)
        {
            player->SetPosition(DEFAULT_SCREEN_W - SPAWN_ENEMY_MIN_COORD, player->GetPosition().y);
            player->SetInertia(0.0, player->GetInertia().y);
        }

        if(player->GetPosition().y < SPAWN_ENEMY_MIN_COORD)
        {
            player->SetPosition(player->GetPosition().x, SPAWN_ENEMY_MIN_COORD);
            player->SetInertia(player->GetInertia().x, 0.0);
        }
        if(player->GetPosition().y > DEFAULT_SCREEN_H - SPAWN_ENEMY_MIN_COORD)
        {
            player->SetPosition(player->GetPosition().x, DEFAULT_SCREEN_H - SPAWN_ENEMY_MIN_COORD);
            player->SetInertia(player->GetInertia().x, 0.0);
        }

        ////////////////////Движение пуль

        for(int i(0); i < MAX_BULLET; i++)
        {
            if(p_bullet[i].is_exist)
            {
                p_bullet[i].Move();
            }
        }

        ///////Перезарядка

        for(int i(0); i < 4; i++)
        {
            if(player->weapon[i].is_exist)
            {
                if(player->weapon[i].is_reload)
                {
                    if(player->weapon[i].clock_reload.getElapsedTime().asMilliseconds() > player->weapon[i].time_reload)
                    {
                        player->weapon[i].is_reload = false;
                    }
                }
            }
        }
        for(int i(0); i < MAX_ENEMY; i++)
        {
            if(p_enemy[i].weapon.is_exist)
            {
                if(p_enemy[i].weapon.is_reload)
                {
                    if(p_enemy[i].weapon.clock_reload.getElapsedTime().asMilliseconds() > p_enemy[i].weapon.time_reload)
                    {
                        p_enemy[i].weapon.is_reload = false;
                    }
                }
            }
        }

        ///Проверка жизни пуль и хиты
        ///
        for(int i(0); i < MAX_BULLET; i++)
        {
            if(p_bullet[i].is_exist)
            {
                if(p_bullet[i].time_life.getElapsedTime().asMilliseconds() > p_bullet[i].max_time_life)
                {
                    p_bullet[i].SetDeactive();
                }
                else
                {
                    /*for(int j(0); j < MAX_BULLET; j++) //попадание по другой пуле
                    {
                        if(p_bullet[j].is_exist)
                        {
                            if(j != i)
                            {
                                if((GetLenght(p_bullet[i].GetPosition(), p_bullet[j].GetPosition()) < DEFAULT_BULLET_RADIUS))
                                {
                                    PlayAnimation(p_bullet[i].GetPosition(), &s_spark[SPARK], 4, 4, 1, Vector<int>(32, 32), 2, false);
                                    PlayAnimation(p_bullet[j].GetPosition(), &s_spark[SPARK], 4, 4, 1, Vector<int>(32, 32), 2, false);
                                    p_bullet[i].SetDeactive();
                                    p_bullet[j].SetDeactive();
                                }
                            }
                        }
                    }*/
                    if(player->is_alive)
                    {
                        if(player->is_shield && !p_bullet[i].in_shield)//если щит включен
                        {
                            if(player->GetPosition().x - SHIELD_R < p_bullet[i].GetPosition().x &&
                                                    player->GetPosition().x + SHIELD_R > p_bullet[i].GetPosition().x &&
                                                    player->GetPosition().y - SHIELD_R < p_bullet[i].GetPosition().y &&
                                                    player->GetPosition().y + SHIELD_R > p_bullet[i].GetPosition().y)
                            {
                                if(player->shield[CURRENT] < p_bullet[i].damage)
                                {
                                    p_bullet[i].damage -= player->shield[CURRENT];
                                    player->shield[CURRENT] = 0;
                                    player->is_shield = false;
                                    sn_break_shield->setRelativeToListener(true);
                                    sn_break_shield->setPosition(GetSoundBalance(player->GetPosition().x), 0.f, SOUND_Z);
                                    sn_break_shield->play();
                                }
                                else
                                {
                                    player->shield[CURRENT] -= p_bullet[i].damage;
                                    p_bullet[i].damage -= player->shield_prot;
                                    PlayAnimation(p_bullet[i].GetPosition(), &s_spark[SPARK_SHIELD], 4, 4, 1, Vector<int>(32, 32), 2, false);
                                    p_bullet[i].in_shield = true;
                                }
                                sn_hit[HIT_SHIELD].setRelativeToListener(true);
                                sn_hit[HIT_SHIELD].setPosition(GetSoundBalance(p_bullet[i].GetPosition().x), 0.f, SOUND_Z);
                                sn_hit[HIT_SHIELD].play();


                                if(p_bullet[i].damage <= 0)
                                {
                                    p_bullet[i].SetDeactive();
                                }
                            }
                        }
                        if(player->GetPosition().x - PLAYER_DIM/2 < p_bullet[i].GetPosition().x &&
                                                player->GetPosition().x + PLAYER_DIM/2 > p_bullet[i].GetPosition().x &&
                                                player->GetPosition().y - PLAYER_DIM/2 < p_bullet[i].GetPosition().y &&
                                                player->GetPosition().y + PLAYER_DIM/2 > p_bullet[i].GetPosition().y &&
                                                p_bullet[i].is_exist
                                                )
                        {
                            player->health[CURRENT] -= p_bullet[i].damage;
                            PlayAnimation(p_bullet[i].GetPosition(), &s_spark[SPARK], 4, 4, 1, Vector<int>(32, 32), 2, false);
                            char text[32];
                            sprintf(text, "-%d", p_bullet[i].damage);
                            PlayJimpText(Vector<double>(player->GetPosition().x, player->GetPosition().y), Color(Color::Red), text,
                                         Vector<double>(JT_RANDOMINERTION, JT_RANDOMINERTION));
                            sn_hit[HIT].setRelativeToListener(true);
                            sn_hit[HIT].setPosition(GetSoundBalance(p_bullet[i].GetPosition().x), 0.f, SOUND_Z);
                            sn_hit[HIT].play();
                            p_bullet[i].SetDeactive();
                        }
                    }
                    //попадание по врагу
                    for(int k(0); k < MAX_ENEMY; k++)
                    {
                        if(p_enemy[k].is_alive)
                        {
                            if(p_enemy[k].GetPosition().x - p_enemy[k].size/2 < p_bullet[i].GetPosition().x &&
                                    p_enemy[k].GetPosition().x + p_enemy[k].size/2 > p_bullet[i].GetPosition().x &&
                                    p_enemy[k].GetPosition().y - p_enemy[k].size/2 < p_bullet[i].GetPosition().y &&
                                    p_enemy[k].GetPosition().y + p_enemy[k].size/2 > p_bullet[i].GetPosition().y &&
                                    p_bullet[i].is_exist
                                                    )
                            {
                                p_enemy[k].health[CURRENT] -= p_bullet[i].damage;
                                /*sn_hit[HIT].setRelativeToListener(true);
                                sn_hit[HIT].setPosition(GetSoundBalance(p_bullet[i].GetPosition().x), 0.f, SOUND_Z);
                                sn_hit[HIT].play();*/
                                PlayAnimation(p_bullet[i].GetPosition(), &s_spark[SPARK], 4, 4, 1, Vector<int>(32, 32), 2, false);
                                if(p_enemy[k].health[CURRENT] <= 0)
                                {
                                    PlayAnimation(p_enemy[k].GetPosition(), s_explosion, 8, 4, 2, Vector<int>(64, 64), 3, false);
                                    sn_explosion->setRelativeToListener(true);
                                    sn_explosion->setPosition(GetSoundBalance(p_enemy[k].GetPosition().x), 0.f, SOUND_Z);
                                    sn_explosion->play();
                                    char text[32];
                                    sprintf(text, "+%d", p_enemy[k].reward + player->bonus * 10);
                                    PlayJimpText(Vector<double>(p_enemy[k].GetPosition().x, p_enemy[k].GetPosition().y), Color(Color::Yellow),
                                                 text, Vector<double>(JT_RANDOMINERTION, JT_RANDOMINERTION));
                                    player->score += p_enemy[k].reward + player->bonus*5;

                                    sprintf(text, "%s", &bonus_text_list[player->bonus]);
                                    PlayJimpText(Vector<double>(p_enemy[k].GetPosition().x, p_enemy[k].GetPosition().y), Color(Color::Red),
                                                 text, Vector<double>(JT_RANDOMINERTION, JT_RANDOMINERTION));

                                    if(player->bonus > 0)
                                    {
                                        sn_bonus[player->bonus - 1].play();
                                    }
                                    if(player->bonus <= 5) player->bonus++;
                                    time_bonus.restart();
                                    if(p_enemy[k].loot) Drop(&p_enemy[k]);
                                    p_enemy[k].Destruct();

                                }

                                p_bullet[i].SetDeactive();
                            }
                        }
                    }
                }
            }
        }
        /////Взятие лута
        for(int i(0); i < MAX_BOX; i++)
        {
            if(p_box[i].is_active)
            {
                if(GetLenght(player->GetPosition(), p_box[i].GetPosition()) < (double)SIZE_BOX + 48.0)
                {
                    player->energy[CURRENT] += p_box[i].energy;
                    if(player->energy[CURRENT] > player->energy[MAX]) player->energy[CURRENT] = player->energy[MAX];
                    p_box[i].Delete();
                    sn_pickup->setRelativeToListener(true);
                    sn_pickup->setPosition(GetSoundBalance(player->GetPosition().x), 0.f, SOUND_Z);
                    sn_pickup->play();
                }
            }
        }
        if(time_bonus.getElapsedTime().asMilliseconds() >= BONUS_TIME)
        {
            player->bonus = 0;
        }
        ////////////////////////////ИИ
        ///

        /////Спавн врага
        ///
        if(player->is_alive)
        {
            if(timer_spawn_enemy.getElapsedTime().asMilliseconds() > random_spawn_time)
            {
                random_spawn_time = random(DEFAULT_TIME_SPAWN_ENEMY_MIN, DEFAULT_TIME_SPAWN_ENEMY_MAX - 1500 * level);
                for(int i(0); i < MAX_ENEMY; i++)
                {
                    if(!p_enemy[i].is_alive)
                    {
                        Vector<int> pos;
                        double lenght(0.0);
                        while(lenght < DEFAULT_SPAWN_ENEMY_LENGHT)
                        {
                            pos.Set(random(SPAWN_ENEMY_MIN_COORD, DEFAULT_SCREEN_W - SPAWN_ENEMY_MIN_COORD),
                                    random(SPAWN_ENEMY_MIN_COORD, DEFAULT_SCREEN_H - SPAWN_ENEMY_MIN_COORD));
                            lenght = GetLenght(player->GetPosition(), Vector2f((double)pos.x, (double)pos.y));
                        }
                        int rnd[10];
                        if(level == 0) //вероятности спавна врага взависимости от текущего уровня
                        {
                            rnd[0] = ENEMY_PROT_SOLDIER;
                            rnd[1] = ENEMY_PROT_SOLDIER;
                            rnd[2] = ENEMY_PROT_SOLDIER;
                            rnd[3] = ENEMY_PROT_SOLDIER;
                            rnd[4] = ENEMY_PROT_BOX;
                            rnd[5] = ENEMY_PROT_BOX;
                            rnd[6] = ENEMY_PROT_SMALL;
                            rnd[7] = ENEMY_PROT_SMALL;
                            rnd[8] = ENEMY_PROT_SMALL;
                            rnd[9] = ENEMY_PROT_SMALL;
                        }
                        else if(level == 1)
                        {
                            rnd[0] = ENEMY_PROT_SOLDIER;
                            rnd[1] = ENEMY_PROT_SOLDIER;
                            rnd[2] = ENEMY_PROT_SOLDIER;
                            rnd[3] = ENEMY_PROT_SOLDIER;
                            rnd[4] = ENEMY_PROT_BIG;
                            rnd[5] = ENEMY_PROT_BOX;
                            rnd[6] = ENEMY_PROT_SMALL;
                            rnd[7] = ENEMY_PROT_SMALL;
                            rnd[8] = ENEMY_PROT_SMALL;
                            rnd[9] = ENEMY_PROT_SMALL;
                        }
                        else if(level == 2)
                        {
                            rnd[0] = ENEMY_PROT_SOLDIER;
                            rnd[1] = ENEMY_PROT_SOLDIER;
                            rnd[2] = ENEMY_PROT_SOLDIER;
                            rnd[3] = ENEMY_PROT_SOLDIER;
                            rnd[4] = ENEMY_PROT_BIG;
                            rnd[5] = ENEMY_PROT_BOX;
                            rnd[6] = ENEMY_PROT_BIG;
                            rnd[7] = ENEMY_PROT_SMALL;
                            rnd[8] = ENEMY_PROT_SMALL;
                            rnd[9] = ENEMY_PROT_SMALL;
                        }
                        else if(level == 3)
                        {
                            rnd[0] = ENEMY_PROT_SOLDIER;
                            rnd[1] = ENEMY_PROT_SOLDIER;
                            rnd[2] = ENEMY_PROT_SOLDIER;
                            rnd[3] = ENEMY_PROT_BIG;
                            rnd[4] = ENEMY_PROT_BIG;
                            rnd[5] = ENEMY_PROT_BOX;
                            rnd[6] = ENEMY_PROT_BIG;
                            rnd[7] = ENEMY_PROT_SMALL;
                            rnd[8] = ENEMY_PROT_SMALL;
                            rnd[9] = ENEMY_PROT_SMALL;
                        }
                        else if(level == 4)
                        {
                            rnd[0] = ENEMY_PROT_SOLDIER;
                            rnd[1] = ENEMY_PROT_SOLDIER;
                            rnd[2] = ENEMY_PROT_BIG;
                            rnd[3] = ENEMY_PROT_BIG;
                            rnd[4] = ENEMY_PROT_BIG;
                            rnd[5] = ENEMY_PROT_SMALL;
                            rnd[6] = ENEMY_PROT_BIG;
                            rnd[7] = ENEMY_PROT_BOX;
                            rnd[8] = ENEMY_PROT_SMALL;
                            rnd[9] = ENEMY_PROT_SMALL;
                        }
                        else
                        {
                            rnd[0] = ENEMY_PROT_SOLDIER;
                            rnd[1] = ENEMY_PROT_SOLDIER;
                            rnd[2] = ENEMY_PROT_BIG;
                            rnd[3] = ENEMY_PROT_BIG;
                            rnd[4] = ENEMY_PROT_BIG;
                            rnd[5] = ENEMY_PROT_SMALL;
                            rnd[6] = ENEMY_PROT_BIG;
                            rnd[7] = ENEMY_PROT_BIG;
                            rnd[8] = ENEMY_PROT_SMALL;
                            rnd[9] = ENEMY_PROT_BIG;
                        }
                        p_enemy[i].Spawn(&p_enemy_prot[rnd[random(0, 9)]], pos);
                        timer_spawn_enemy.restart();
                        break;
                    }
                }
            }
            for(int i(0); i < MAX_ENEMY; i++)//Атака врага
            {
                if(p_enemy[i].is_alive)
                {
                    p_enemy[i].SetView(player->GetPosition());
                    p_enemy[i].sprite.setRotation(p_enemy[i].GetRotation());
                    Attack(&p_enemy[i]);
                }
            }
        }

        //////////////////////Смерть игрока

        if(player->health[CURRENT] <= 0)
        {
            if(player->is_alive)
            {
                PlayAnimation(player->GetPosition(), s_explosion, 8, 4, 2, Vector<int>(64, 64), 5, false);
                sn_explosion->setRelativeToListener(true);
                sn_explosion->setPosition(GetSoundBalance(player->GetPosition().x), 0.f, SOUND_Z);
                sn_explosion->play();
                player->Death();
                p_button[BUTTON_RETRY].is_active = true;
                p_button[BUTTON_EXIT].is_active = true;
                for(int i(0); i < MAX_MUSIC; i++)
                {
                     sn_music[i].stop();
                }
            }
        }


        //////////////////////////ИГРОВОЙ "ТИК"
        ///

        if(gameplay_tick.getElapsedTime().asMilliseconds() > GAMEPLAY_TICK_MLS)
        {
            if(!player->is_empty)
            {
                if(player->energy[CURRENT] <= 0)
                {
                    player->is_empty = true;
                    player->is_shield = false;
                    player->sprite.setColor(Color(100, 100, 100));
                    sn_shutdown->setPosition(GetSoundBalance(player->GetPosition().x), 0.f, SOUND_Z);
                    sn_shutdown->play();
                    for(int i(0); i < MAX_MUSIC; i++)
                    {
                         sn_music[i].stop();
                    }
                }
                else
                {
                    if(player->in_move)//расход двигателя
                    {
                        player->energy[CURRENT] -= player->engine.expense;
                    }
                    if(player->shield[CURRENT] < player->shield[MAX] && !player->is_shield) //зарядка щита
                    {
                        player->energy[CURRENT] -= 2;
                        player->shield[CURRENT]++;
                    }
                    if(player->is_shield) //поддержка щита
                    {
                        player->energy[CURRENT] -= 1;
                    }
                }
            }
            if(player->score >= score_for_level)
            {
                if(level < 5)
                {
                    level++;
                    is_levelup = true;
                    score_for_level = score_for_level * 2;
                    if(level == 2)
                    {
                        for(int i(0); i < MAX_MUSIC; i++)
                        {
                             sn_music[i].stop();
                        }
                        sn_music[MUSIC_LEVEL02].play();
                        p_flashscreen[FLASHSCREEN_LEVELUP].Start();
                    }
                    if(level >= 4)
                    {
                        for(int i(0); i < MAX_MUSIC; i++)
                        {
                             sn_music[i].stop();
                        }
                        sn_music[MUSIC_LEVEL03].play();
                        p_flashscreen[FLASHSCREEN_LEVELUP].Start();
                    }
                }
            }
            gameplay_tick.restart();
        }
        CheckButtons(&window);
        if(p_button[BUTTON_RETRY].is_pressed)
        {
            p_button[BUTTON_EXIT].is_active = false;
            p_button[BUTTON_RETRY].is_active = false;
            player->Alive();
            level = 0;
            player->score = 0;
            p_default_weapon2->SetWeapon(&player->weapon[0]);
            sn_music[MUSIC_LEVEL01].play();
            for(int i(0); i < MAX_ENEMY; i++)
            {
                if(p_enemy[i].is_alive)
                {
                    p_enemy[i].Destruct();
                }
            }
            for(int i(0); i < MAX_BOX; i++)
            {
                if(p_box[i].is_active)
                {
                    p_box[i].Delete();
                }
            }

        }
        if(p_button[BUTTON_EXIT].is_pressed)
        {
            p_button[BUTTON_EXIT].is_active = false;
            window.close();
            break;
        }

        //////////////////////
        ///////////////////////Отрисовка
        ///

        window.clear(sf::Color::Black);
        window.draw(rs_background[level / 2]);
        //window.draw(fps_text);
        sprintf(char_text_score, "\n\nscore = %d\n\nWASD - move\nCtrl - shield", player->score, level + 1);

        DrawFlashScreen(&window);

        //анимация игрока
        if(player->is_alive)
        {
            if(!player->is_empty)
            {

                if(player->frame < 3)
                {
                    player->sprite.setTextureRect(IntRect(64*int(player->frame), 0, 64, 64));
                    player->frame = player->frame + 0.05;
                }
                else player->frame = 0.0;
                if(player->is_shield) window.draw(circle_shield);

            }
            else
            {
                player->sprite.setTextureRect(IntRect(128, 0, 64, 64));
            }
             window.draw(player->sprite);
        }

        //Отрисовка пуль
        for(int i(0); i < MAX_BULLET; i++)
        {
            if(p_bullet[i].is_exist)
            {
                p_bullet[i].sprite.setPosition(p_bullet[i].GetPosition());
                p_bullet[i].sprite.setRotation(p_bullet[i].GetRotation());
                window.draw(p_bullet[i].sprite);
            }
        }

        window.draw(shape);
        //Отрисовка врагов
        for(int i(0); i < MAX_ENEMY; i++)
        {
            if(p_enemy[i].is_alive)
            {
                p_enemy[i].sprite.setPosition(p_enemy[i].GetPosition());
                window.draw(p_enemy[i].sprite);
            }
        }

       // window.draw(dev_vector_inertia, 2, Lines);
        //window.draw(dev_vector_view, 2, Lines);

        //////HUD
        ///

        p_lineindicator_health->SetData(player->health[CURRENT], player->health[MAX]);
        p_lineindicator_health->Draw(&window);
        p_lineindicator_shield->SetData(player->shield[CURRENT], player->shield[MAX]);
        p_lineindicator_shield->Draw(&window);
        p_lineindicator_energy->SetData(player->energy[CURRENT], player->energy[MAX]);
        p_lineindicator_energy->Draw(&window);
        text_score.setString(char_text_score);
        window.draw(text_score);
        sprintf(char_text_score, "Level = %d", level + 1);
        if(level == 0) text_score.setColor(Color(0, 255, 0, DEFAULT_ALPHA));
        else if(level == 1) text_score.setColor(Color(50, 200, 0, DEFAULT_ALPHA));
        else if(level == 2) text_score.setColor(Color(100, 150, 0, DEFAULT_ALPHA));
        else if(level == 3) text_score.setColor(Color(150, 100, 0, DEFAULT_ALPHA));
        else if(level == 4) text_score.setColor(Color(200, 50, 0, DEFAULT_ALPHA));
        text_score.setString(char_text_score);
        text_score.setCharacterSize(DEFAULT_FONT_SIZE + 16);
        window.draw(text_score);
        text_score.setColor(Color(255, 220, 0, DEFAULT_ALPHA));
        text_score.setCharacterSize(DEFAULT_FONT_SIZE);
        ////
        ///

        DrawBox(&window);
        DrawAnimation(&window);
        DrawJimpText(&window);
        DrawButtons(&window);

        window.display();
    }
    ///
    /////////////////////////////////

    delete player;
    delete[] p_enemy;
    delete[] p_enemy_prot;
    delete[] p_bullet;
    delete[] p_box;

    delete p_default_weapon;
    delete p_default_weapon2;
    delete p_big_enemy_weapon;
    delete p_box_enemy_weapon;
    delete p_minigan;

    delete p_default_engine;
    delete[] texture;

    delete[] p_animation;

    delete s_explosion;
    delete[] s_spark;
    delete[] s_enemy;
    delete[] rs_background;
    delete s_default_bullet;
    delete s_box;

    delete[] p_soundbuffer;
    delete[] sb_music;

    delete sn_blaster;
    delete[] sn_hit;
    delete sn_explosion;
    delete sn_shutdown;
    delete sn_break_shield;
    delete[] sn_bonus;
    delete[] sn_music;
    delete sn_pickup;


    delete p_lineindicator_health;
    delete p_lineindicator_shield;
    delete p_lineindicator_energy;

    delete[] p_jumptext;

    delete[] p_button;

    delete[] p_flashscreen;

    return 0;
}
