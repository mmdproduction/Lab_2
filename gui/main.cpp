#include"GL/glew.h"

#include"GLFW/glfw3.h"
#include"glm/glm.hpp"

#include"Sequence.hpp"
#include"BitSequence.hpp"
#include"TestPanel.hpp"
#include<iostream>


int main(){

    Window window(1028, 720, "Test GUI");
    window.windowInit();
    window.makeContextCurrent();
    window.setFramebufferSizeCallback();

    if(glewInit()) return -1;
    Renderer render = Renderer(window.getWidth(), window.getHeight(), "shaders/vert.glsl", "shaders/frag.glsl");
    TextRenderer textRender = TextRenderer(window.getWidth(), window.getHeight(), "shaders/text_vert.glsl", "shaders/text_frag.glsl");

    if(!textRender.loadFont("C:/Windows/Fonts/arial.ttf", 24)){
        std::cerr << "ERROR::FONT::BUILD_FAIL";
    }

    EventSystem events;

    setKeyCallback(window.getWindow());
    setCharCallback(window.getWindow());
    setMouseButtonCallback(window.getWindow());
    setCursorPosCallback(window.getWindow());
    setScrollCallback(window.getWindow());



    TestPanel* testPanel = new TestPanel(20, 90, window.getWidth() - 40, window.getHeight() - 110);

    float lastTime = glfwGetTime();
    while(!window.isWindowShouldClose()){
        events.update();

        testPanel->onEvent(events);

        double now = glfwGetTime();
        float dt = now - lastTime;
        lastTime = now;

        glClear(GL_COLOR_BUFFER_BIT);

        testPanel->draw(render, textRender);
        
        window.swapBuffers();

        testPanel->update();

    }

    glfwTerminate();
    return 0;
}


