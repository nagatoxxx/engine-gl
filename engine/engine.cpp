#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../gpu/shader.h"
#include "engine.h"

using namespace eng;

Engine::Engine(int windowWidth, int windowHeight, const std::string& windowTitle)
: m_window(std::make_unique<eng::Window>(windowWidth, windowHeight, windowTitle)),
  m_keyboard(std::make_shared<Keyboard>(Keyboard())),
  m_mouse(std::make_shared<Mouse>(Mouse(static_cast<double>(windowWidth) / 2, static_cast<double>(windowHeight) / 2))),
  m_timer(std::make_unique<Timer>(Timer())),
  m_shader("resources/shaders/shader.vs", "resources/shaders/shader.frag"),
  m_camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
  m_world()
{
    glEnable(GL_DEPTH_TEST);

    m_window->setKeyboardPtr(m_keyboard);
    m_window->setMousePtr(m_mouse);


    Logger::log("Engine created");
}

/* virtual */ Engine::~Engine()
{
    Logger::log("Engine destroyed");
}

void Engine::run()
{
    m_timer->start();

    Object cube("cube", "resources/objects/cube.obj");
    m_world.addObject(std::move(cube));

    while (!m_window->shouldClose()) {
        m_window->pollEvents();
        EventSystem::pollEvents();

        this->update();

        m_window->swapBuffers();
    }
}

/* virtual */ void Engine::update()
{
    // clear color and depth buffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.2f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float dtime = m_timer->reset();

    // input processing
    if (m_keyboard->isKeyPressed(GLFW_KEY_W)) {
        m_camera.position() += m_camera.front() * 10.0f * dtime;
    }
    else if (m_keyboard->isKeyPressed(GLFW_KEY_S)) {
        m_camera.position() -= m_camera.front() * 10.0f * dtime;
    }
    if (m_keyboard->isKeyPressed(GLFW_KEY_D)) {
        m_camera.position() += m_camera.right() * 10.0f * dtime;
    }
    else if (m_keyboard->isKeyPressed(GLFW_KEY_A)) {
        m_camera.position() -= m_camera.right() * 10.0f * dtime;
    }
    if (m_keyboard->isKeyPressed(GLFW_KEY_SPACE)) {
        m_camera.position() += glm::vec3(0.0f, 1.0f, 0.0f) * 10.0f * dtime;
    }
    else if (m_keyboard->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        m_camera.position() -= glm::vec3(0.0f, 1.0f, 0.0f) * 10.0f * dtime;
    }

    // mouse movement processing
    glm::vec2 mouseDelta = m_mouse->getDelta();
    m_camera.incAngles(mouseDelta.x, -mouseDelta.y);

    // cube rendering
    m_shader.use();

    auto cube = m_world.getObject("cube");

    GLuint modelLoc = glGetUniformLocation(m_shader.getProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cube->model().getModelMatrix()));

    // view (camera) transformation
    GLuint viewLoc = glGetUniformLocation(m_shader.getProgram(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera.getViewMatrix()));

    // perspective projection transformation
    glm::mat4 projection = glm::perspective(m_camera.getFov(), m_window->getAspectRatio(), 0.1f, 100.0f);

    GLuint projectionLoc = glGetUniformLocation(m_shader.getProgram(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // lighting
    GLint objectColorLoc = glGetUniformLocation(m_shader.getProgram(), "objectColor");
    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);

    GLint lightColorLoc = glGetUniformLocation(m_shader.getProgram(), "lightColor");
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos(0.0f, 10.0f, 0.0f);
    GLuint    lightPosLoc = glGetUniformLocation(m_shader.getProgram(), "lightPos");
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

    cube->render();
}
