#pragma once

#include"UI.hpp"
#include"Sequence.hpp"
#include "Window.hpp"
#include"EventSystem.hpp"
#include "Renderer.hpp"
#include "TextRenderer.hpp"
#include "glm/glm.hpp"
#include<string>
#include<codecvt>
#include<locale>



class SequencePanel{
    private:

    float x, y, w, h, topY;
    float btnW = 170, btnH = 35;
    float pad = 20; 
    size_t activeIndex = 0, secondIndex = 0;

    const glm::vec4 COLOR_PASS = glm::vec4(0.2f, 0.8f, 0.3f, 1.0f);
    const glm::vec4 COLOR_FAIL = glm::vec4(0.9f, 0.2f, 0.2f, 1.0f);
    const glm::vec4 COLOR_BG   = glm::vec4(0.15f, 0.15f, 0.18f, 1.0f);
    const glm::vec4 COLOR_PANEL = glm::vec4(0.2f, 0.2f, 0.25f, 1.0f);

    UICollapsibleList listSequence;
    UICollapsibleList listSecondSequence;
    UIButton btnAddSequence;
    UIButton btnConcat;
    UIButton btnMapX2;
    UIButton btnMax;
    UIButton btnMin;
    UIButton btnAppend;

    UIInputText inputSequence;
    UIList sequenceInfo;

    ArraySequence<Sequence<int>*> sequences;

    int mapX2(int x){ return x*2;}
    int mapMod2(int x){return x % 2; }
    int min(int avg, int x){return avg <= x ? avg : x; }
    int max(int avg, int x){return avg >= x ? avg : x; }

    

    
public:
    SequencePanel(float x_, float y_, float w_, float h_) :
        x(x_), y(y_), w(w_), h(h_),
        topY(y_ + h_ - 10),
        listSequence(x_ + pad + btnW/2, topY - 20, btnW, "1_Послед"),
        listSecondSequence(x_ + 2 * pad + btnW * 3 / 2 + 40, topY - 20, btnW, "2_Послед"),
        sequenceInfo(x_ + w_ * 3 / 4, y_ + h_ / 2, w_ / 2, h_, btnH),
        btnAddSequence(x_ + pad + (btnW + 40) / 2, topY - 20 - pad - btnH - 20, btnW + 40, btnH + 20, COLOR_PANEL, "Добавить послед.", glm::vec3(1.0f)),
        btnConcat(x_ + pad + (btnW + 20) / 2, topY - 320 - pad - btnH, btnW + 40, btnH + 20, COLOR_PANEL, "Объеденить", glm::vec3(1.0f)),
        btnMapX2(x_ + 3 * pad + (btnW + 20) * 3 / 2, topY - 320 - pad - btnH, btnW + 40, btnH + 20, COLOR_PANEL, "Умн. на 2", glm::vec3(1.0f)),
        btnMax(x_ + pad + (btnW + 20) / 2, topY - 320 - 3 * pad - 2 * btnH, btnW + 40, btnH + 20, COLOR_PANEL, "MAX", glm::vec3(1.0f)),
        btnAppend(x_ + pad + (btnW + 20) / 2, topY - 220 - 2 * pad - 1 * btnH, btnW + 40, btnH + 20, COLOR_PANEL, "Добавить", glm::vec3(1.0f)),
        btnMin(x_ + 3 * pad + (btnW + 20) * 3 / 2, topY - 320 - 3 * pad - 2 * btnH, btnW + 40, btnH + 20, COLOR_PANEL, "MIN", glm::vec3(1.0f)),
        inputSequence(x_ + pad + (btnW + 140) / 2, topY - 120 - pad - btnH, btnW + 140, btnH + 20, "Введите число: 1")
    {
       
        sequenceInfo.setShowScrollbar(true);
    }
    
    void refreshList(){
        listSecondSequence.clearItems();
        listSequence.clearItems();
        for(size_t i = 0; i < sequences.getLength(); ++i){
            listSequence.addItem(std::to_string(i));
            listSecondSequence.addItem(std::to_string(i));
        }
    }


    void draw(Renderer& render, TextRenderer& textRender){

        render.begin();
        textRender.begin();


        render.draw({x, y}, {w, h}, COLOR_BG);
        btnAddSequence.draw(render, textRender);
        btnConcat.draw(render, textRender);
        btnMapX2.draw(render, textRender);
        btnMin.draw(render, textRender);
        btnMax.draw(render, textRender);
        btnAppend.draw(render, textRender);


        render.end();
        textRender.end();

        inputSequence.draw(render, textRender);
        listSequence.draw(render, textRender);
        listSecondSequence.draw(render, textRender);
        sequenceInfo.draw(render, textRender);
        

        

    }
    void onEvent(EventSystem& events){

        btnAddSequence.onEvent(events);
        
        btnConcat.onEvent(events);
        btnMapX2.onEvent(events);
        btnMax.onEvent(events);
        btnMin.onEvent(events);
        btnAppend.onEvent(events);
        inputSequence.onEvent(events);


        activeIndex = listSequence.getSelectedItem();
        secondIndex = listSecondSequence.getSelectedItem();

        listSequence.onEvent(events);
        listSecondSequence.onEvent(events);

        sequenceInfo.onEvent(events);

        if(btnAddSequence.isPressed){
            sequences.append(new ArraySequence<int>());
            refreshList();
        }
        
        if(btnAppend.isPressed && !(inputSequence.getText().empty()) && sequences.getLength() != 0){
            if(activeIndex >= sequences.getLength()) {
                activeIndex = 0; 
            }
            std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
            auto text = inputSequence.getText();
            inputSequence.setText("");
            sequences[activeIndex]->append(std::stoi(convert.to_bytes(text)));
        }
    }

    void update(float dt){

        btnAddSequence.update(dt);
        btnConcat.update(dt);
        btnMapX2.update(dt);
        btnMin.update(dt);
        btnMax.update(dt);
        inputSequence.update(dt);
        btnAppend.update(dt);

        listSequence.update(dt);
        listSecondSequence.update(dt);

        sequenceInfo.update(dt);
        if(sequences.getLength() != 0){
            if(activeIndex >= sequences.getLength()) {
                activeIndex = 0; 
            }
            infoUpdate();
        }
    }

    void infoUpdate(){
        sequenceInfo.clearItems();
        auto* seq = sequences[activeIndex];
            if(seq != nullptr && seq->getLength() != 0){
            for(const auto& elem : *seq){
                sequenceInfo.addItem(std::to_string(elem));
            }
        }
    }


};
