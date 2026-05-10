#include<locale>
#include"GL/glew.h"

#include"GLFW/glfw3.h"
#include"glm/glm.hpp"

#include"Sequence.hpp"
#include"BitSequence.hpp"
#include"TestPanel.hpp"
#include"TabsPanel.hpp"
#include<iostream>


int main(){
    setlocale(LC_ALL, ".UTF8");


    if (!Window::windowInit()) return -1;
    
    Window window(1028, 720, "Test GUI");


    window.makeContextCurrent();
    window.setFramebufferSizeCallback();

    if(glewInit()) return -1;
    Renderer render = Renderer(window.getWidth(), window.getHeight(), "shaders/vert.glsl", "shaders/frag.glsl");
    TextRenderer textRender = TextRenderer(window.getWidth(), window.getHeight(), "shaders/text_vert.glsl", "shaders/text_frag.glsl");

    if(!textRender.loadFont("C:/Windows/Fonts/arial.ttf", 24)){
        std::cerr << "ERROR::FONT::BUILD_FAIL";
    }

    EventSystem events;

    events.setKeyCallback(window.getWindow());
    events.setCharCallback(window.getWindow());
    events.setMouseButtonCallback(window.getWindow());
    events.setCursorPosCallback(window.getWindow());
    events.setScrollCallback(window.getWindow());

    ListSequence<int> list;
    int k = list.get(5);

    TestPanel* testPanel = new TestPanel(0, 0, window.getWidth(), window.getHeight() - 40);
    TabsPanel* tabsPanel = new TabsPanel(0, window.getHeight() - 40, window.getWidth(), 40);
    tabsPanel->addTab("Тесты");
    float lastTime = glfwGetTime();
    while(!window.isWindowShouldClose()){

        events.update();
        testPanel->onEvent(events);
        tabsPanel->onEvent(events);

        double now = glfwGetTime();
        float dt = now - lastTime;
        lastTime = now;

        glClear(GL_COLOR_BUFFER_BIT);


        tabsPanel->draw(render, textRender);
        testPanel->draw(render, textRender);
        
        
        window.swapBuffers();
        testPanel->update(dt);
        tabsPanel->update(dt);

    }

    delete testPanel;
    delete tabsPanel;

    glfwTerminate();
    return 0;
}


