#include <print>

import Engine.WindowContext;

int main()
{
  WindowContext ctx;
  auto result = ctx.init("WindowContext test",800,600);
  if(!result.has_value())
  {
    std::println("{}",result.error().message);
  }else
  {
    ctx.run();
  }
  ctx.shutdown();
}
