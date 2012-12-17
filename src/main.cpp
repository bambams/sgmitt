#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <map>
#include <string>

#include "al5poly/altypedef.hpp"
#include "al5poly/Animation.hpp"
#include "al5poly/Camera.hpp"
#include "al5poly/Clock.hpp"
#include "al5poly/IAnimation.hpp"
#include "al5poly/IException.hpp"
#include "al5poly/IGameTime.hpp"
#include "al5poly/Player.hpp"
#include "al5poly/Renderer.hpp"

al5poly::Player createPlayer(const std::string &);

std::string getRootDir(const std::string &);

void initializeAllegro5(
        al5poly::ALLEGRO_DISPLAY_Ptr &,
        al5poly::ALLEGRO_TIMER_Ptr &,
        al5poly::ALLEGRO_EVENT_QUEUE_Ptr &);

int main(int argc, char * argv[]) try
{
    std::string root = getRootDir(argv[0]);

    const int player_start_x = 300;
    const int player_start_y = 400;

    al5poly::ALLEGRO_DISPLAY_Ptr display;
    al5poly::ALLEGRO_TIMER_Ptr timer;
    al5poly::ALLEGRO_EVENT_QUEUE_Ptr eventQueue;

    initializeAllegro5(display, timer, eventQueue);

    al_set_target_bitmap(al_get_backbuffer(display.get()));

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al5poly::Camera camera;
    al5poly::Clock clock;
    al5poly::Player player(createPlayer(root));
    al5poly::Renderer renderer(display);

    player.setCurrentAnimation("default");
    player.beginAnimation(1, *clock.getGameTime());
    player.setX(player_start_x);
    player.setY(player_start_y);

    al_start_timer(timer.get());

    while(true)
    {
        ALLEGRO_EVENT event;
        bool redraw = false;
        al_wait_for_event(eventQueue.get(), &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            clock.tick();
            redraw = true;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN &&
                event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            break;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if(redraw)
        {
            try
            {
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

al5poly::Player createPlayer(const std::string & root)
{
    std::string path = root + "assets/reindeer.png";
    al5poly::ALLEGRO_BITMAP_Ptr reindeer(
            al_load_bitmap(path.c_str()),
            al_destroy_bitmap);

    if(reindeer.get() == 0)
    {
        al5poly::Exception("Failed to load reindeer sprite!").raise();
    }

    al_convert_mask_to_alpha(
            reindeer.get(),
            al_map_rgb(255, 0, 255));

    al5poly::ALLEGRO_BITMAP_Ptr_Vector sprites;

    sprites.push_back(reindeer);

    al5poly::IAnimation::Ptr animation(new al5poly::Animation(sprites));

    al5poly::IAnimation::StringMap animations;

    animations.insert(std::make_pair("default", animation));

    al5poly::Player player(animations);

    return player;
}

std::string getRootDir(const std::string & command)
{
    std::string root(command);

    boost::algorithm::replace_all(root, "\\", "/");
    boost::algorithm::replace_all(root, "bin/game.exe", "");

    return root;
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
            al_create_display(800, 600),
            al_destroy_display);

    if(!d)
        al5poly::Exception("Failed to create Allegro 5 display!").raise();

    display = d;

    if(!al_install_keyboard())
        al5poly::Exception("Failed to install Allegro 5 keyboard!").raise();

    if(!al_init_image_addon())
        al5poly::Exception("Failed to initialize image addon.").raise();

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
