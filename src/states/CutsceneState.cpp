#include "states/CutsceneState.h"
#include "GameData.h"
#include <iostream>
#include "Text.h"

CutsceneState::CutsceneState() : State() {
    // always, dad is the first object, tuki is second and balloon is third, followed by the balloon text lines

    GameObject* bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "resources/img/blackBG.jpg"));
    AddObject(bg);

    stage = 0;
    if (GameData::intro){
        NewDialogue(0, "resources/img/cutscene/pai.png", "resources/img/cutscene/triste nao falando.png", "Tuki, minha querida, o destino das", "nossas receitas e doces esta em", "suas asas.", "A confeitaria e o coracao da nos-", "sa familia.");
    } else {
        NewDialogue(0, "resources/img/cutscene/pai-happy.png", "resources/img/cutscene/feliz nao falando.png", "Tuki, querida, como foi o dia", "na confeitaria?", " ", " ", " ");
    }

}

CutsceneState::~CutsceneState() {
    objectArray.clear();
}

void CutsceneState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();
    if (iM.KeyPress(Z_KEY)) NextStage();
    if (iM.KeyPress(ESCAPE_KEY) || iM.KeyPress(P_KEY)) popRequested = true;
}

void CutsceneState::Render() {
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void CutsceneState::Start() {
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}

void CutsceneState::Pause() {}

void CutsceneState::Resume() {}

void CutsceneState::LoadAssets() {}

void CutsceneState::NextStage() {
    stage++;
    objectArray.clear();
    if (GameData::intro && stage == 5) GameData::intro = false;

    GameObject* bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "resources/img/blackBG.jpg"));
    AddObject(bg);
    if (stage == 5) {
        popRequested = true;
        return;
    }
    
    if (GameData::intro){
        if (stage == 1){
            NewDialogue(1, "resources/img/cutscene/pai- nao falando.png", "resources/img/cutscene/triste.png", "Pai, sempre estou disposta a aju-", "dar. O que posso fazer?", " ", " ", " ");
        }
        if (stage == 2){
            NewDialogue(0, "resources/img/cutscene/pai.png", "resources/img/cutscene/triste nao falando.png", "Lembre-se, minha querida:", "explore o mundo, descubra os se-", "gredos dos ingredientes, encante", "os clientes com nossos doces e,", " ");
        }
        if (stage == 3){
            NewDialogue(0, "resources/img/cutscene/pai.png", "resources/img/cutscene/triste nao falando.png", "acima de tudo, encontre o doce", "que me curara e trata luz de vol-", "ta a esta confeitaria.", " ", " ");
        }
        if (stage == 4){
            NewDialogue(1, "resources/img/cutscene/pai- nao falando.png", "resources/img/cutscene/triste.png", "Eu farei de tudo para te curar e", "cuidar da confeitaria da nossa", "familia.", " ", " ");
            GameData::intro = 0;
        }
    } else {
        if (stage == 1){
            NewDialogue(1, "resources/img/cutscene/pai-happy nao falando.png", "resources/img/cutscene/feliz.png", "Foi um sucesso!", " ", " ", " ", " ");
        }
        if (stage == 2){   
            NewDialogue(1, "resources/img/cutscene/pai-happy nao falando.png", "resources/img/cutscene/choque.png", "Por mais que aquelas receitas", "me fizeram quebrar o bico para", "terminar...", " ", " ");       
        }
        if (stage == 3){
            NewDialogue(1, "resources/img/cutscene/pai- nao falando.png", "resources/img/cutscene/triste.png", "E... nao achei o ingrediente pra", "cura ainda, papai...", " ", " ", " ");
        }
        if (stage == 4){
            NewDialogue(0, "resources/img/cutscene/pai-happy.png", "resources/img/cutscene/triste nao falando.png", "Tudo bem, Tuki, a hora certa", "vai chegar... Mas venha dormir,", "ja esta tarde e amanha e um", "novo dia.", " ");
            GameData::completed = false;
        }
    }
}

void CutsceneState::NewDialogue(int type, std::string dad, std::string tuki, std::string text1, std::string text2, std::string text3, std::string text4, std::string text5){
        GameObject* dadI = new GameObject();
        dadI->AddComponent(new Sprite(*dadI, dad));
        dadI->box.SetCenter({180, 500});
        AddObject(dadI);

        GameObject* tukiI = new GameObject();
        tukiI->AddComponent(new Sprite(*tukiI, tuki));
        tukiI->box.SetCenter({1128,500});
        AddObject(tukiI);

        GameObject* balloon = new GameObject();
        if (type == 0){
            balloon->AddComponent(new Sprite(*balloon, "resources/img/cutscene/bolha esquerd.png"));
            balloon->box.SetCenter({550,600});
        } else if (type == 1){
            balloon->AddComponent(new Sprite(*balloon, "resources/img/cutscene/bolha.png"));
            balloon->box.SetCenter({750,600});
        }
        AddObject(balloon);


        GameObject* textLine1 = new GameObject();
        textLine1->AddComponent(new Text(*textLine1, "resources/font/Minecraft.ttf", 30, TextStyle::BLENDED, text1, {0,0,0,255}, {0,0,0,255}, false));
        GameObject* textLine2 = new GameObject();
        textLine2->AddComponent(new Text(*textLine2, "resources/font/Minecraft.ttf", 30, TextStyle::BLENDED, text2, {0,0,0,255}, {0,0,0,255}, false));
        GameObject* textLine3 = new GameObject();
        textLine3->AddComponent(new Text(*textLine3, "resources/font/Minecraft.ttf", 30, TextStyle::BLENDED, text3, {0,0,0,255}, {0,0,0,255}, false));
        GameObject* textLine4 = new GameObject();
        textLine4->AddComponent(new Text(*textLine4, "resources/font/Minecraft.ttf", 30, TextStyle::BLENDED, text4, {0,0,0,255}, {0,0,0,255}, false));
        GameObject* textLine5 = new GameObject();
        textLine5->AddComponent(new Text(*textLine5, "resources/font/Minecraft.ttf", 30, TextStyle::BLENDED, text5, {0,0,0,255}, {0,0,0,255}, false));


        textLine1->box.y = 550;
        textLine2->box.y = 575;
        textLine3->box.y = 600;
        textLine4->box.y = 625;
        textLine5->box.y = 650;
        if (type == 0){
            textLine1->box.x = 300;
            textLine2->box.x = 300;
            textLine3->box.x = 300;
            textLine4->box.x = 300;
            textLine5->box.x = 300;
        } else if (type == 1){
            textLine1->box.x = 500;
            textLine2->box.x = 500;
            textLine3->box.x = 500;
            textLine4->box.x = 500;
            textLine5->box.x = 500;
        }


        AddObject(textLine1);
        AddObject(textLine2);
        AddObject(textLine3);
        AddObject(textLine4);
        AddObject(textLine5);
}