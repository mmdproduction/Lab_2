#pragma once
#include "TestRunner.hpp"
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
        float btnW = 120, btnH = 35;
        
        btnRunAll = new UIButton(x + 20, y + 10, btnW, btnH, {0.3f, 0.7f, 0.3f, 1.0f},  "Run All Tests", {1, 1, 1});
        btnRunSelected = new UIButton(x + 150, y + 10, btnW, btnH, {0.3f, 0.6f, 0.8f, 1.0f}, "Run Selected", {1, 1, 1});
        btnClear = new UIButton(x + w - btnW - 20, y + 10, btnW, btnH, {0.6f, 0.3f, 0.3f, 1.0f}, "Clear", {1, 1, 1});
        
        inputFilter = new UIInputText(x + 350, y + 12, 200, btnH - 4, "Filter tests...");

        resultList = new UIList(x + 20, y + 60, w - 40, h - 80);
        resultList->setShowScrollbar(true);
    }

    void update(float dt) {
        btnRunAll->update(dt);
        btnRunSelected->update(dt);
        btnClear->update(dt);
        inputFilter->update(dt);

        if (btnRunAll->isClicked() && !runner.getIsRunning()) {
            runner.run();
            refreshList();
        }
        
        if (btnRunSelected->isClicked() && !runner.getIsRunning()) {
            const char* filter = inputFilter->getText();
            runner.run(filter);
            refreshList();
        }

        if (btnClear->isClicked()) {
            runner.run();
        }
    }

    void refreshList() {
        for(size_t i = 0; i < resultList->getItemCount; ++i){
            resultList->removeItem();
        }
        const auto& res = runner.getResults();
        for(const auto& test : res){
            char[512] line;
            if(test.pass) sprintf(line, "[PASS] %s : %0.1f ms", test.name, test.time_ms)
            else std::sprintf(line, "[FAIL] %s: %s", r.name, r.message);
            resultList->addItem(std::string(line));
        }
        
    }

    void draw(Renderer& renderer, TextRenderer& textRenderer) const {
        renderer.begin();
        textRenderer.begin();

        renderer.draw(x, y, w, h, COLOR_BG);
        textRenderer.drawText("Unit Tests", x + 20, y - 25, 1, glm::vec3(0.9f));

        btnRunAll->draw(renderer, textRenderer);
        btnRunSelected->draw(renderer, textRenderer);
        btnClear->draw(renderer, textRenderer);
        inputFilter->draw(renderer, textRenderer);
        renderer.end();
        textRenderer.end();

        resultList->draw(renderer, textRenderer);
    }

    void onEvent(EventSystem& events){
        btnRunAll->onEvent(events);
        btnRunSelected->onEvent(events);
        btnClear->onEvent(events);
        inputFilter->onEvent(events);

        resultList->onEvent(events);
    }
};