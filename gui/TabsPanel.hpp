#pragma once

#include"UI.hpp"
#include "Window.hpp"
#include"EventSystem.hpp"
#include "Renderer.hpp"
#include "TextRenderer.hpp"
#include "glm/glm.hpp"
#include "Sequence.hpp"


class TabsPanel{
    private:

    ListSequence<UIButton*> buttons;

    float x, y, w, h;
    float btnW;

    const glm::vec4 COLOR_BG   = glm::vec4(0.15f, 0.15f, 0.18f, 1.0f);
    const glm::vec4 COLOR_PANEL = glm::vec4(0.4f, 0.4f, 0.45f, 1.0f);

    public:

    TabsPanel(float x_, float y_, float w_, float h_): x(x_), y(y_), w(w_), h(h_), btnW(w_ / 3) {}
    void addTab(std::string text){
        buttons.append(new UIButton(x + buttons.getLength() * btnW + btnW / 2, y + h/2, btnW, h, COLOR_PANEL, text, glm::vec3(1.0f)));
    }

    void onEvent(EventSystem& events){
        for(auto* button : buttons){
            button->onEvent(events);
        }
    }

    void update(float dt){
        for(auto* button : buttons){
            button->update(dt);
        }
    }

    void draw(Renderer& render, TextRenderer& textRender){
        render.begin();
        textRender.begin();

        render.draw({x, y}, {w, h}, COLOR_BG);
        for(auto* button : buttons){
            button->draw(render, textRender);
        }

        render.end();
        textRender.end();
    }

};
