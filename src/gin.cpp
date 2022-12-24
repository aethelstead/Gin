#include "gin.h"
#include "game.h"
#include "keyboard.h"

Gin::Gin* Gin::Gin::instance = nullptr;

bool Gin::Gin::start()
{
    instance = new Gin();
    if (!instance->init())
    {
        return false;
    }

    instance->run();

    instance->quit();

    return true;
}

bool Gin::Gin::init()
{
    Logger::logLevel = Logger::LogLevel::Info;

    if (!Platform::init())
    {
        Logger::log_error("Failed to init platform.");
        return false;
    }
    Logger::log_info("Platform started.");

    window = Platform::open_window("Gin Game", 640, 480);
    if (!window)
    {
        Logger::log_error("Failed to open window.");
        return false;
    }
    Logger::log_info("Window open.");

    renderContext = new RenderContext(window->backBuffer->dimensions);
    Logger::log_info("Render context created.");
    renderContext->font = open_font("assets/fonts/DrawnOldEnglish.ttf", 16);

    // @TODO: Static start method?
    game = new Game();
    game->init();

    return true;
}

void Gin::Gin::quit()
{
    delete game;
    delete renderContext;
    
    Platform::close_window(window);
    Platform::quit();
}

void Gin::Gin::run()
{
    Logger::log_info("Gin started running.");
    running = true;

    while(running)
    {
       update();
       render();
    }

    quit();
}

void Gin::Gin::handle_keyboard()
{
    // Check for key pressed
    if (Keyboard::key_pressed(KeyCode::Escape))
    {
        Logger::log_info("Should quit!");
    }
}

void Gin::Gin::update()
{
    uint startTicks = ticks();
    uint endTicks = 0;
    Event e;

    while (next_event(&e))
    {
        if (e.type == EventType::Quit)
        {
            running = false;
        }
        else if (e.type == EventType::Keydown)
        {
            Keyboard::keydownMap[e.keyboard.code] = true;
        }
        else if (e.type == EventType::Keyup)
        {
            Keyboard::keydownMap[e.keyboard.code] = false;
        }
    }

    handle_keyboard();
    game->update();
    Keyboard::prevKeydownMap = Keyboard::keydownMap;

    // Calculate how long to delay til next frame.
    endTicks = ticks();
    int deltaTicks = endTicks - startTicks;
    const int MAX_DELAY = (1000 / TARGET_FPS);
    int delay = MAX_DELAY - deltaTicks;
    if (delay < 0)
        delay = 0;

    // Increment frame counter and set the FPS
    ++frames;
    //fps = frames / deltaTicks;

    sleep(delay);
}

void Gin::Gin::render()
{
    Renderer::clear(renderContext);

    if (game->player->attacking)
    {
        renderContext->drawColor = (uint)Color::Red;
    }
    else
    {   
        renderContext->drawColor = (uint)Color::White;
    }

    Renderer::draw_point(renderContext, game->player->pos);
    Rect r(0, 0, 400, 400);
    Renderer::draw_text(renderContext, "Gin", r);
    blit(renderContext->buffer, window->backBuffer);
    window->swap_buffers();
}
