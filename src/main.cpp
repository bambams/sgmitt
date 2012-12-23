#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <map>
#include <string>

#include "al5poly/altypedef.hpp"
#include "al5poly/Animation.hpp"
#include "al5poly/AssetManager.hpp"
#include "al5poly/Camera.hpp"
#include "al5poly/Clock.hpp"
#include "al5poly/IAnimation.hpp"
#include "al5poly/IException.hpp"
#include "al5poly/IGameTime.hpp"
#include "al5poly/InputManager.hpp"
#include "al5poly/Player.hpp"
#include "al5poly/Renderer.hpp"

#include "ground.hpp"
#include "JumpHandler.hpp"
#include "make_ptr.hpp"
#include "RunHandler.hpp"
#include "sun.hpp"

#define GROUND_COLOR (al_map_rgb(100, 255, 100))
#define SUN_COLOR (al_map_rgb(255, 255, 100))

const char * const GROUND_BITMAP_NAME = "ground";
const char * const PLAYER_BITMAP_NAME = "reindeer";
const char * const PLAYER_SPRITE_PATH = "reindeer.png";
const char * const PLAYER_ANIMATION_NAME = "default";
const char * const SUN_BITMAP_NAME = "sun";

const int GROUND_H = 5;
const int H4X_GRAVITY_STEP = 10;
const int H4X_JUMP_STEP = 40;
const int PLAYER_START_X = 300;
const int PLAYER_START_Y = 395;
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int SUN_W = 100;
const int SUN_H = 100;
const int SUN_Y = 100;

const int GROUND_START_X = -SCREEN_W / 2;
const int GROUND_W = SCREEN_W * 2;
const int GROUND_START_Y = SCREEN_H - GROUND_H;
const int SUN_RADIUS = SUN_W / 2;
const int SUN_X = SCREEN_W - SUN_Y;

al5poly::ALLEGRO_BITMAP_Ptr createGroundSprite(void);
al5poly::ALLEGRO_BITMAP_Ptr createSunSprite(void);

al5poly::Player createPlayer(const al5poly::AssetManager &);

void h4xGravity(al5poly::Player &);
void h4xJump(const al5poly::IGameTime &, al5poly::Player &);

void initializeAllegro5(
        al5poly::ALLEGRO_DISPLAY_Ptr &,
        al5poly::ALLEGRO_TIMER_Ptr &,
        al5poly::ALLEGRO_EVENT_QUEUE_Ptr &);

int main(int argc, char * argv[]) try
{
    const char * const TITLE = "Santa's Gotta Make It To Town";

    al5poly::ALLEGRO_DISPLAY_Ptr display;
    al5poly::ALLEGRO_TIMER_Ptr timer;
    al5poly::ALLEGRO_EVENT_QUEUE_Ptr eventQueue;

    initializeAllegro5(display, timer, eventQueue);

    al_set_window_title(display.get(), TITLE);

    al5poly::AssetManager assMan;
    al5poly::Camera camera;
    al5poly::Clock clock;
    al5poly::InputManager inputMan;
    al5poly::Renderer renderer(display);

    assMan.addBitmap(GROUND_BITMAP_NAME, createGroundSprite());
    assMan.addBitmap(SUN_BITMAP_NAME, createSunSprite());
    assMan.loadBitmap(PLAYER_BITMAP_NAME, PLAYER_SPRITE_PATH, true);
    assMan.loadAnimation(PLAYER_ANIMATION_NAME, 1, PLAYER_BITMAP_NAME);

    al5poly::Player player(createPlayer(assMan));

    inputMan.addActionHandler("jump",
            make_ptr<JumpHandler>(new JumpHandler(player)));

    RunHandler::Ptr runner(new RunHandler(player));
    H4xSun sun(SUN_X, SUN_Y, assMan.getBitmap(SUN_BITMAP_NAME));

    H4xGround ground(GROUND_START_X, GROUND_START_Y,
            assMan.getBitmap(GROUND_BITMAP_NAME));

    inputMan.addActionHandler("run-left", runner);
    inputMan.addActionHandler("run-right", runner);

    inputMan.setKeyAction(ALLEGRO_KEY_SPACE, "jump");
    inputMan.setKeyAction(ALLEGRO_KEY_UP, "jump");
    inputMan.setKeyAction(ALLEGRO_KEY_LEFT, "run-left");
    inputMan.setKeyAction(ALLEGRO_KEY_RIGHT, "run-right");

    player.setCurrentAnimation(PLAYER_ANIMATION_NAME);
    player.beginAnimation(1, *clock.getGameTime());
    player.setX(PLAYER_START_X);
    player.setY(PLAYER_START_Y);

    al_start_timer(timer.get());

    al_set_target_bitmap(al_get_backbuffer(display.get()));
    al_clear_to_color(al_map_rgb(0, 0, 0));

    while(true)
    {
        ALLEGRO_EVENT event;
        bool tick = false;

        al_wait_for_event(eventQueue.get(), &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            clock.tick();
            tick = true;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            int keycode = event.keyboard.keycode;

            if(keycode == ALLEGRO_KEY_ESCAPE)
            {
                break;
            }

            inputMan.keyPress(keycode);
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP)
        {
            inputMan.keyRelease(event.keyboard.keycode);
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        // Logic.
        if(tick)
        {
            inputMan.sendEvents(*clock.getGameTime());

            if(player.isJumping())
            {
                h4xJump(*clock.getGameTime(), player);
            }

            // h4x.
            h4xGravity(player);
        }

        // Drawing.
        if(tick)
        {
            try
            {
                renderer.render(*clock.getGameTime(), camera, ground);
                renderer.render(*clock.getGameTime(), camera, sun);
                renderer.render(*clock.getGameTime(), camera, player);
                renderer.paint();
            }
            catch(al5poly::IException & ex)
            {
                std::cerr << ex.getMessage() << std::endl;
            }
        }
    }

    return 0;
}
catch(std::exception & ex)
{
    std::cerr << ex.what() << std::endl;

    return 1;
}

al5poly::ALLEGRO_BITMAP_Ptr createGroundSprite(void)
{
    ALLEGRO_BITMAP * sprite = al_create_bitmap(GROUND_W, GROUND_H);

    if(sprite == 0)
    {
        throw std::runtime_error("Failed to create ground sprite.");
    }

    al_set_target_bitmap(sprite);
    al_draw_filled_rectangle(0, 0, GROUND_W, GROUND_H, GROUND_COLOR);

    return make_ptr(sprite, al_destroy_bitmap);
}

al5poly::ALLEGRO_BITMAP_Ptr createSunSprite(void)
{
    ALLEGRO_BITMAP * sprite = al_create_bitmap(SUN_W, SUN_H);

    if(sprite == 0)
    {
        throw std::runtime_error("Failed to create Sun sprite.");
    }

    al_set_target_bitmap(sprite);
    al_draw_filled_circle(SUN_W / 2, SUN_H / 2, SUN_RADIUS, SUN_COLOR);

    return make_ptr(sprite, al_destroy_bitmap);
}

al5poly::Player createPlayer(const al5poly::AssetManager & assMan)
{
    al5poly::IAnimation::StringMap animations;

    animations.insert(std::make_pair(PLAYER_ANIMATION_NAME,
            assMan.getAnimation(PLAYER_ANIMATION_NAME)));

    al5poly::Player player(animations);

    return player;
}

void h4xGravity(al5poly::Player & player)
{
    int y = player.getY();

    if(y < PLAYER_START_Y)
    {
        y += H4X_GRAVITY_STEP;
    }

    // h4x.
    if(y > PLAYER_START_Y)
    {
        y = PLAYER_START_Y;
    }

    player.setY(y);

    // h4x.
    if(y == PLAYER_START_Y)
    {
        player.land();
    }
}

void h4xJump(
        const al5poly::IGameTime & time,
        al5poly::Player & player) try
{
    int delta;

    player.updateJump(time, &delta);

    int dy = H4X_JUMP_STEP * delta;
    int y = player.getY();

    y -= dy;

    player.setY(y);
}
catch(std::exception & ex)
{
    std::cerr << "Failed jump: " << ex.what() << std::endl;
}

void initializeAllegro5(
        al5poly::ALLEGRO_DISPLAY_Ptr & display,
        al5poly::ALLEGRO_TIMER_Ptr & timer,
        al5poly::ALLEGRO_EVENT_QUEUE_Ptr & eventQueue)
{
    const int FPS = 30;

    if(!al_init())
        al5poly::Exception("Failed to initialize Allegro 5!").raise();

    al_set_new_display_flags(ALLEGRO_WINDOWED);

    al5poly::ALLEGRO_DISPLAY_Ptr d(
            al_create_display(SCREEN_W, SCREEN_H),
            al_destroy_display);

    if(!d)
        al5poly::Exception("Failed to create Allegro 5 display!").raise();

    display = d;

    if(!al_install_keyboard())
        al5poly::Exception("Failed to install Allegro 5 keyboard!").raise();

    if(!al_init_image_addon())
        al5poly::Exception("Failed to initialize image addon.").raise();

    if(!al_init_primitives_addon())
        al5poly::Exception("Failed to initialize primitives addon.").raise();

    al5poly::ALLEGRO_TIMER_Ptr t(
            al_create_timer(1.0 / FPS),
            al_destroy_timer);

    if(!t)
        al5poly::Exception("Failed to create Allegro 5 timer!").raise();

    timer = t;

    al5poly::ALLEGRO_EVENT_QUEUE_Ptr eQ(
            al_create_event_queue(),
            al_destroy_event_queue);

    if(!eQ)
        al5poly::Exception("Failed to create Allegro 5 event queue!").raise();

    eventQueue = eQ;

    al_register_event_source(
            eventQueue.get(),
            al_get_display_event_source(display.get()));

    al_register_event_source(
            eventQueue.get(),
            al_get_keyboard_event_source());

    al_register_event_source(
            eventQueue.get(),
            al_get_timer_event_source(timer.get()));
}
