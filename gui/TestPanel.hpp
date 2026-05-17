#pragma once
#include"TestRunner.hpp"
#include"UI.hpp"
#include "Window.hpp"
#include"EventSystem.hpp"
#include "Renderer.hpp"
#include "TextRenderer.hpp"
#include "glm/glm.hpp"

class TestPanel {
private:
    GTestManager runner;
    
    UIButton* btnRunAll;
    UIButton* btnRunSelected;
    UIButton* btnClear;
    UIInputText* inputFilter;
    UIList* resultList;

    float x, y, w, h;

    const glm::vec4 COLOR_PASS = glm::vec4(0.2f, 0.8f, 0.3f, 1.0f);
    const glm::vec4 COLOR_FAIL = glm::vec4(0.9f, 0.2f, 0.2f, 1.0f);
    const glm::vec4 COLOR_BG   = glm::vec4(0.15f, 0.15f, 0.18f, 1.0f);
    const glm::vec4 COLOR_PANEL = glm::vec4(0.2f, 0.2f, 0.25f, 1.0f);


public:
    TestPanel(float x_, float y_, float w_, float h_) : x(x_), y(y_), w(w_), h(h_) {
        initUI();
    }

void initUI() {
    float btnW = 160, btnH = 35;
    float pad = 20;              
    float topY = y + h - 10;     

    btnRunAll = new UIButton(
        x + pad + btnW / 2.0f,               
        topY - btnH / 2.0f,                      
        btnW, btnH, 
        {0.3f, 0.7f, 0.3f, 1.0f}, 
        "Запустить все", 
        {1, 1, 1}
    );


    btnClear = new UIButton(
        x + w - pad - btnW / 2.0f,    
        topY - btnH / 2.0f, 
        btnW, btnH, 
        {0.6f, 0.3f, 0.3f, 1.0f}, 
        "Очистить", 
        {1, 1, 1}
    );

    float listW = w - 40;
    float listH = h - 80;  
    float listBottomY = y + 20; 

    resultList = new UIList(
        x + 20 + listW / 2.0f,                  
        listBottomY + listH / 2.0f,
        listW, listH
    );
    resultList->setShowScrollbar(true);
}

    void update(float dt) {
        btnRunAll->update(dt);
        btnClear->update(dt);    
    }

    void refreshList() {
        size_t count = resultList->getItemCount();
        for (size_t i = count; i > 0; --i) {
            resultList->removeItem(i - 1);
        }
        auto& res = runner.getResults();
        if (res.getLength() == 0) return; 

        for(const auto& test : res){
            char line[512];
            if(test.passed) sprintf(line, "[OK] %s : %0.1f ms", test.name, test.time_ms);
            else std::sprintf(line, "[FAIL] %s: %s", test.name, test.message);
            resultList->addItem(std::string(line));
        }
        
    }

    void clearList(){
        size_t count = resultList->getItemCount();
        for (size_t i = count; i > 0; --i) {
            resultList->removeItem(i - 1);
        }
    }

    void draw(Renderer& renderer, TextRenderer& textRenderer) const {

        

        renderer.begin();
        textRenderer.begin();

        
        renderer.draw({x, y}, {w, h}, COLOR_BG);
        float titleY = y + h - 35;
        textRenderer.drawText("Модульные тесты", x + 350, titleY, 1, glm::vec3(0.9f));

        btnRunAll->draw(renderer, textRenderer);
        btnClear->draw(renderer, textRenderer);

        renderer.end();
        textRenderer.end();
        
        resultList->draw(renderer, textRenderer);
        

    }

    void onEvent(EventSystem& events){
        btnRunAll->onEvent(events);
        btnClear->onEvent(events);
        
        resultList->onEvent(events);

        if (btnRunAll->isPressed && !runner.getIsRunning()) {
            runner.run();
            refreshList();
        }
        

        if (btnClear->isPressed) {
            clearList();
        }
    }
};