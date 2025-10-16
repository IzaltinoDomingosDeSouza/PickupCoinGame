#include <print>
#include <expected>

import Engine.WindowContext;

struct GameApplicationError
{
    enum class Code
    {
        WINDOW_CONTEXT_FAILED,
    } code;
    std::string message;
};

class Game
{
public:
  std::expected<void, GameApplicationError> init()
  {
    auto result = ctx.init("WindowContext test",800,600);
    
    if(!result.has_value())
      return std::unexpected(GameApplicationError{GameApplicationError::Code::WINDOW_CONTEXT_FAILED,"Failed to initialize window context"});
    
    return {};
  }
  
  void shutdown()
  {
    ctx.shutdown();
  }
  void update()
  {
    
  }
  std::expected<void, GameApplicationError> run()
  {
    auto result = init();
    
    if(result.has_value())
    {
      while(!ctx.should_close())
      {
        update();
        ctx.start_frame();
        ctx.end_frame();
      }
    }
    
    shutdown();
    
    return result;
  }
private:
  WindowContext ctx;
};

int main()
{
  Game game;
  auto result = game.run();
  
  if(!result.has_value())
    std::println("{}",result.error().message);
}
