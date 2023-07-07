#include "VectorPCH.h"
#include "WindowsWindow.h"


namespace Vector {
    
    static bool s_GLFWInitialized = false;

    Window* Window::create(const WindowProperties& properties)
    {
        return new WindowsWindow(properties);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& properties)
    {
        m_data.title = properties.title;
        m_data.width = properties.width;
        m_data.height = properties.height;

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            if (!success)
            {
                glfwTerminate();
                return;
            }
            s_GLFWInitialized = true;
        }

        m_window = glfwCreateWindow((int)properties.width, (int)properties.height, m_data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        
        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    WindowsWindow::~WindowsWindow()
    {
        glViewport(0, 0, m_data.width, m_data.height);
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void WindowsWindow::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    unsigned int WindowsWindow::getWidth() const
    {
        return m_data.width;
    }

    unsigned int WindowsWindow::getHeight() const
    {
        return m_data.height;
    }

    void WindowsWindow::setVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_data.vSync = enabled;
    }

    bool WindowsWindow::isVSync() const
    {
        return m_data.vSync;
    }
}

