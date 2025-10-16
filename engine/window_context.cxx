module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <expected>
#include <string>
#include <format>

export module Engine.WindowContext;

struct WindowContextError
{
    enum class Code
    {
        GLFW_INIT_FAILED,
        WINDOW_CREATION_FAILED,
        GLAD_INIT_FAILED
    } code;
    std::string message;
};

export class WindowContext
{
public:
  std::expected<void, WindowContextError> init(const char * title, int width,int height)
  {
    if (!glfwInit())
    {
        return std::unexpected(WindowContextError{WindowContextError::Code::GLFW_INIT_FAILED,"Failed to initialize GLFW"});
    }
    
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
   
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!m_window)
    {
      return std::unexpected(WindowContextError{WindowContextError::Code::WINDOW_CREATION_FAILED,"Failed to create GLFW window"});
    }
    
    glfwMakeContextCurrent(m_window);
    
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow * window, int width, int height)
    {
      glViewport(0, 0, width, height);
    });
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return std::unexpected(WindowContextError{WindowContextError::Code::GLAD_INIT_FAILED,"Failed to initialize GLAD"});
    }
    
    glViewport(0, 0, width, height);
    
    return {};
  }
  void shutdown()
  {
    if (m_window)
    {
      glfwDestroyWindow(m_window);
      m_window = nullptr;
    }
    glfwTerminate();
  }
  bool should_close()
  {
    return glfwWindowShouldClose(m_window);
  }
  void start_frame()
  {
    glfwPollEvents();
    glClearColor(0.13, 0.09, 0.20, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }
  void end_frame()
  {
    glfwSwapBuffers(m_window);
  }
private:
   GLFWwindow * m_window{nullptr};
};
