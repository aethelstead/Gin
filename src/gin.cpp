#include "gin.h"
#include "game.h"

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

    // Init the keydown maps
    keydownMap = std::map<KeyCode, bool>();
    prevKeydownMap = std::map<KeyCode, bool>();

    // @TODO: Static start method?
    game = new Game();
    game->init();

    return true;
}

void Gin::Gin::quit()
{
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

void Gin::Gin::handle_keyboard(GameCommand& command)
{
    // Check for key released
    if (prevKeydownMap[KeyCode::Space] && !keydownMap[KeyCode::Space])
    {
        command = GameCommand::PLAYER_ATTACK_STOP;
    }
    if (prevKeydownMap[KeyCode::W] && !keydownMap[KeyCode::W])
    {
        command = GameCommand::PLAYER_MOVE_STOP;
    }
    if (prevKeydownMap[KeyCode::A] && !keydownMap[KeyCode::A])
    {
        command = GameCommand::PLAYER_MOVE_STOP;
    }
    if (prevKeydownMap[KeyCode::S] && !keydownMap[KeyCode::S])
    {
        command = GameCommand::PLAYER_MOVE_STOP;
    }
    if (prevKeydownMap[KeyCode::D] && !keydownMap[KeyCode::D])
    {
        command = GameCommand::PLAYER_MOVE_STOP;
    }

    // Check for key pressed
    if (keydownMap[KeyCode::Escape])
    {
        Logger::log_info("Should quit!");
    }
    if (keydownMap[KeyCode::Space])
    {
        command = GameCommand::PLAYER_ATTACK;
    }
    if (keydownMap[KeyCode::W])
    {
        command = GameCommand::PLAYER_MOVE_NORTH;
    }
    else if (keydownMap[KeyCode::A])
    { 
        command = GameCommand::PLAYER_MOVE_WEST;
    }
    else if (keydownMap[KeyCode::S])
    {
        command = GameCommand::PLAYER_MOVE_SOUTH;
    }
    else if (keydownMap[KeyCode::D])
    {
        command = GameCommand::PLAYER_MOVE_EAST;
    }
    
}

void Gin::Gin::update()
{
    Event e;

    while (next_event(&e))
    {
        if (e.type == EventType::Quit)
        {
            running = false;
        }
        else if (e.type == EventType::Keydown)
        {
            keydownMap[e.keyboard.code] = true;
        }
        else if (e.type == EventType::Keyup)
        {
            keydownMap[e.keyboard.code] = false;
        }
    }

    GameCommand command = GameCommand::NONE;
    handle_keyboard(command);
    prevKeydownMap = keydownMap;

    game->update(command);

    sleep(17);
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
    blit(renderContext->buffer, window->backBuffer);
    window->swap_buffers();
}
