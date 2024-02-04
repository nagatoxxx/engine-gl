#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../gpu/ibo.h"
#include "../gpu/shader.h"
#include "../gpu/texture.h"
#include "../gpu/vao.h"
#include "../gpu/vbo.h"
#include "camera.h"
#include "engine.h"

using namespace eng;

Engine::Engine()
: m_window(std::make_unique<eng::Window>(800, 600, "engine")),
  m_keyboard(std::make_shared<Keyboard>(Keyboard())),
  m_mouse(std::make_shared<Mouse>(Mouse(400.0f, 300.0f))),
  m_timer(std::make_unique<Timer>(Timer()))
{
    m_window->setKeyboardPtr(m_keyboard);
    m_window->setMousePtr(m_mouse);

    Logger::log("Logging started");
    Logger::log("Engine created");
}

/* virtual */ Engine::~Engine()
{
    Logger::log("Engine destroyed");
}

void Engine::run()
{
    // shaders
    Shader shader("shaders/shader.vs", "shaders/shader.frag");

    float vertices[] =
        {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
         0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

         -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

         -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
         0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

         -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

    VBO vbo;
    vbo.bind();
    vbo.bufferData(vertices, sizeof(vertices));

    VAO vao;
    vao.bind();

    // IBO ibo;
    // ibo.bind();
    // ibo.bufferData(indices, sizeof(indices));

    // position attribute
    vao.attribPointer(0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (GLvoid*)(0));
    // texture attribute
    vao.attribPointer(2, 2, GL_FLOAT, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    // unbind VAO
    vao.unbind();

    // texture load
    Texture t1("textures/container.jpg", GL_TEXTURE_2D, GL_RGB, GL_UNSIGNED_BYTE);

    glEnable(GL_DEPTH_TEST);


    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    m_timer->start();

    while (!m_window->shouldClose()) {
        m_window->pollEvents();

        float dt = m_timer->reset();

        // input processing
        if (m_keyboard->isKeyPressed(GLFW_KEY_W)) {
            camera.position() += camera.front() * 10.0f * dt;
        }
        else if (m_keyboard->isKeyPressed(GLFW_KEY_S)) {
            camera.position() -= camera.front() * 10.0f * dt;
        }
        if (m_keyboard->isKeyPressed(GLFW_KEY_D)) {
            camera.position() += camera.right() * 10.0f * dt;
        }
        else if (m_keyboard->isKeyPressed(GLFW_KEY_A)) {
            camera.position() -= camera.right() * 10.0f * dt;
        }

        glm::vec2 mouseDelta = m_mouse->getDelta();

        camera.incAngles(mouseDelta.x, -mouseDelta.y);

        // clear color buffer
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

        glm::mat4 model(1.0f);
        model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 1.0f));

        glm::mat4 view(1.0f);
        view = camera.getViewMatrix();

        glm::mat4 projection(1.0f);
        projection = glm::perspective(camera.getFov(), 4.0f / 3.0f, 0.1f, 100.0f);

        GLuint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        GLuint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLuint projLoc = glGetUniformLocation(shader.getProgram(), "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        glActiveTexture(GL_TEXTURE0);
        t1.bind();
        t1.setTextureUnit(shader.getProgram(), "sampler", 0);

        // draw container
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        vao.unbind();

        m_window->swapBuffers();
    }
}
