#include "states/CutsceneState.h"
#include "GameData.h"
#include <iostream>
#include "Text.h"

CutsceneState::CutsceneState() : State() {
    // always, dad is the first object, tuki is second and balloon is third, followed by the balloon text lines
    stage = 0;
    if (GameData::intro){
        GameObject* dad = new GameObject();
        dad->AddComponent(new Sprite(*dad, "resources/img/cutscene/pai.png"));
        dad->box.SetCenter({180, 500});
        AddObject(dad);

        GameObject* tuki = new GameObject();
        tuki->AddComponent(new Sprite(*tuki, "resources/img/cutscene/triste nao falando.png"));
        tuki->box.SetCenter({1128,500});
        AddObject(tuki);

        GameObject* balloon = new GameObject();
        balloon->AddComponent(new Sprite(*balloon, "resources/img/cutscene/bolha esquerd.png"));
        balloon->box.SetCenter({550,600});
        AddObject(balloon);

        GameObject* textLine1 = new GameObject();
        textLine1->AddComponent(new Text(*textLine1, "resources/font/Base.ttf", 30, TextStyle::BLENDED, "Tuki, minha querida, o destino das", {0,0,0,255}, {0,0,0,255}, false));
        textLine1->box.x = 300;
        textLine1->box.y = 550;
        AddObject(textLine1);

        GameObject* textLine2 = new GameObject();
        textLine2->AddComponent(new Text(*textLine2, "resources/font/Base.ttf", 30, TextStyle::BLENDED, "nossas receitas e doces esta", {0,0,0,255}, {0,0,0,255}, false));
        textLine2->box.x = 300;
        textLine2->box.y = 575;
        AddObject(textLine2);

        GameObject* textLine3 = new GameObject();
        textLine3->AddComponent(new Text(*textLine3, "resources/font/Base.ttf", 30, TextStyle::BLENDED, "em suas asas.", {0,0,0,255}, {0,0,0,255}, false));
        textLine3->box.x = 300;
        textLine3->box.y = 600;
        AddObject(textLine3);

        GameObject* textLine4 = new GameObject();
        textLine4->AddComponent(new Text(*textLine4, "resources/font/Base.ttf", 30, TextStyle::BLENDED, "A confeitaria e o coracao", {0,0,0,255}, {0,0,0,255}, false));
        textLine4->box.x = 300;
        textLine4->box.y = 625;
        AddObject(textLine4);

        GameObject* textLine5 = new GameObject();
        textLine5->AddComponent(new Text(*textLine5, "resources/font/Base.ttf", 30, TextStyle::BLENDED, "da nossa familia.", {0,0,0,255}, {0,0,0,255}, false));
        textLine5->box.x = 300;
        textLine5->box.y = 650;
        AddObject(textLine5);
    } else {
        GameObject* dad = new GameObject();
        dad->AddComponent(new Sprite(*dad, "resources/img/cutscene/pai-happy.png"));
        dad->box.SetCenter({180, 500});
        AddObject(dad);

        GameObject* tuki = new GameObject();
        tuki->AddComponent(new Sprite(*tuki, "resources/img/cutscene/feliz nao falando.png"));
        tuki->box.SetCenter({1128,500});
        AddObject(tuki);

        GameObject* balloon = new GameObject();
        balloon->AddComponent(new Sprite(*balloon, "resources/img/cutscene/bolha esquerd.png"));
        balloon->box.SetCenter({550,600});
        AddObject(balloon);

        GameObject* textLine1 = new GameObject();
        textLine1->AddComponent(new Text(*textLine1, "resources/font/Base.ttf", 30, TextStyle::BLENDED, "Tuki, querida, como foi o dia", {0,0,0,255}, {0,0,0,255}, false));
        textLine1->box.x = 300;
        textLine1->box.y = 550;
        AddObject(textLine1);

        GameObject* textLine2 = new GameObject();
        textLine2->AddComponent(new Text(*textLine2, "resources/font/Base.ttf", 30, TextStyle::BLENDED, "na confeitaria?", {0,0,0,255}, {0,0,0,255}, false));
        textLine2->box.x = 300;
        textLine2->box.y = 575;
        AddObject(textLine2);

        GameObject* textLine3 = new GameObject();
        textLine3->AddComponent(new Text(*textLine3, "resources/font/Base.ttf", 30, TextStyle::BLENDED, " ", {0,0,0,255}, {0,0,0,255}, false));
        textLine3->box.x = 300;
        textLine3->box.y = 600;
        AddObject(textLine3);

        GameObject* textLine4 = new GameObject();
        textLine4->AddComponent(new Text(*textLine4, "resources/font/Base.ttf", 30, TextStyle::BLENDED, " ", {0,0,0,255}, {0,0,0,255}, false));
        textLine4->box.x = 300;
        textLine4->box.y = 625;
        AddObject(textLine4);

        GameObject* textLine5 = new GameObject();
        textLine5->AddComponent(new Text(*textLine5, "resources/font/Base.ttf", 30, TextStyle::BLENDED, " ", {0,0,0,255}, {0,0,0,255}, false));
        textLine5->box.x = 300;
        textLine5->box.y = 650;
        AddObject(textLine5);
    }

}

CutsceneState::~CutsceneState() {
    objectArray.clear();
}

void CutsceneState::Update(float dt) {
    InputManager& iM = InputManager::GetInstance();
    if (iM.KeyPress(ESCAPE_KEY) || iM.QuitRequested()) {
        popRequested = true; 
    }
    if (iM.KeyPress(Z_KEY)) NextStage();
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
    if (GameData::intro && stage == 5){
        GameData::intro = false;
        popRequested = true;
    }
    if (!GameData::intro && stage == 5) popRequested = true;

    if (GameData::intro){
        if (stage == 1){
            objectArray[0]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[0]->AddComponent(new Sprite(*objectArray[0], "resources/img/cutscene/pai- nao falando.png"));
            
            objectArray[1]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[1]->AddComponent(new Sprite(*objectArray[1], "resources/img/cutscene/triste.png"));

            objectArray[2]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[2]->AddComponent(new Sprite(*objectArray[2], "resources/img/cutscene/bolha.png"));
            objectArray[2]->box.SetCenter({750,600});

            ((Text*)(objectArray[3]->GetComponent("Text").lock().get()))->SetText("Pai, sempre estou disposta a aju-");
            objectArray[3]->box.x = 500;
            ((Text*)(objectArray[4]->GetComponent("Text").lock().get()))->SetText("dar. O que posso fazer?");
            objectArray[4]->box.x = 500;
            ((Text*)(objectArray[5]->GetComponent("Text").lock().get()))->SetText(" ");
            ((Text*)(objectArray[6]->GetComponent("Text").lock().get()))->SetText(" ");
            ((Text*)(objectArray[7]->GetComponent("Text").lock().get()))->SetText(" ");
        }
        if (stage == 2){
            objectArray[0]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[0]->AddComponent(new Sprite(*objectArray[0], "resources/img/cutscene/pai.png"));
            
            objectArray[1]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[1]->AddComponent(new Sprite(*objectArray[1], "resources/img/cutscene/triste nao falando.png"));

            objectArray[2]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[2]->AddComponent(new Sprite(*objectArray[2], "resources/img/cutscene/bolha esquerd.png"));
            objectArray[2]->box.SetCenter({550,600});

            ((Text*)(objectArray[3]->GetComponent("Text").lock().get()))->SetText("Lembre-se, minha querida:");
            objectArray[3]->box.x = 300;
            ((Text*)(objectArray[4]->GetComponent("Text").lock().get()))->SetText("explore o mundo, descubra os se-");
            objectArray[4]->box.x = 300;
            ((Text*)(objectArray[5]->GetComponent("Text").lock().get()))->SetText("gredos dos ingredientes, encante");
            ((Text*)(objectArray[6]->GetComponent("Text").lock().get()))->SetText("os clientes com nossos doces e,");
        }
        if (stage == 3){
            ((Text*)(objectArray[3]->GetComponent("Text").lock().get()))->SetText("acima de tudo, encontre o doce");
            ((Text*)(objectArray[4]->GetComponent("Text").lock().get()))->SetText("que me curara e trata luz de vol-");
            ((Text*)(objectArray[5]->GetComponent("Text").lock().get()))->SetText("ta a esta confeitaria.");
            ((Text*)(objectArray[6]->GetComponent("Text").lock().get()))->SetText(" ");
        }
        if (stage == 4){
            objectArray[0]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[0]->AddComponent(new Sprite(*objectArray[0], "resources/img/cutscene/pai- nao falando.png"));
            
            objectArray[1]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[1]->AddComponent(new Sprite(*objectArray[1], "resources/img/cutscene/triste.png"));

            objectArray[2]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[2]->AddComponent(new Sprite(*objectArray[2], "resources/img/cutscene/bolha.png"));
            objectArray[2]->box.SetCenter({750,600});

            ((Text*)(objectArray[3]->GetComponent("Text").lock().get()))->SetText("Eu farei de tudo para te curar e");
            objectArray[3]->box.x = 500;
            ((Text*)(objectArray[4]->GetComponent("Text").lock().get()))->SetText("cuidar da confeitaria da nossa");
            objectArray[4]->box.x = 500;
            ((Text*)(objectArray[5]->GetComponent("Text").lock().get()))->SetText("familia.");
            objectArray[5]->box.x = 500;
            ((Text*)(objectArray[6]->GetComponent("Text").lock().get()))->SetText(" ");
            ((Text*)(objectArray[7]->GetComponent("Text").lock().get()))->SetText(" ");
        }
    } else {
        if (stage == 1){
            objectArray[0]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[0]->AddComponent(new Sprite(*objectArray[0], "resources/img/cutscene/pai-happy nao falando.png"));
            
            objectArray[1]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[1]->AddComponent(new Sprite(*objectArray[1], "resources/img/cutscene/feliz.png"));

            objectArray[2]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[2]->AddComponent(new Sprite(*objectArray[2], "resources/img/cutscene/bolha.png"));
            objectArray[2]->box.SetCenter({750,600});

            ((Text*)(objectArray[3]->GetComponent("Text").lock().get()))->SetText("Foi um sucesso!");
            objectArray[3]->box.x = 500;
            ((Text*)(objectArray[4]->GetComponent("Text").lock().get()))->SetText(" ");
            ((Text*)(objectArray[5]->GetComponent("Text").lock().get()))->SetText(" ");
            ((Text*)(objectArray[6]->GetComponent("Text").lock().get()))->SetText(" ");
            ((Text*)(objectArray[7]->GetComponent("Text").lock().get()))->SetText(" ");
        }
        if (stage == 2){            
            objectArray[1]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[1]->AddComponent(new Sprite(*objectArray[1], "resources/img/cutscene/choque.png"));

            ((Text*)(objectArray[3]->GetComponent("Text").lock().get()))->SetText("Por mais que aquelas receitas");
            ((Text*)(objectArray[4]->GetComponent("Text").lock().get()))->SetText("me fizeram quebrar o bico para");
            objectArray[4]->box.x = 500;
            ((Text*)(objectArray[5]->GetComponent("Text").lock().get()))->SetText("terminar...");
            objectArray[5]->box.x = 500;
            ((Text*)(objectArray[6]->GetComponent("Text").lock().get()))->SetText(" ");
            ((Text*)(objectArray[7]->GetComponent("Text").lock().get()))->SetText(" ");
        }
        if (stage == 3){
            objectArray[0]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[0]->AddComponent(new Sprite(*objectArray[0], "resources/img/cutscene/pai- nao falando.png"));
            
            objectArray[1]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[1]->AddComponent(new Sprite(*objectArray[1], "resources/img/cutscene/triste.png"));

            ((Text*)(objectArray[3]->GetComponent("Text").lock().get()))->SetText("E... nao achei o ingrediente pra");
            ((Text*)(objectArray[4]->GetComponent("Text").lock().get()))->SetText("cura ainda, papai...");
            ((Text*)(objectArray[5]->GetComponent("Text").lock().get()))->SetText(" ");
            ((Text*)(objectArray[6]->GetComponent("Text").lock().get()))->SetText(" ");
            ((Text*)(objectArray[7]->GetComponent("Text").lock().get()))->SetText(" ");
        }
        if (stage == 4){
            objectArray[0]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[0]->AddComponent(new Sprite(*objectArray[0], "resources/img/cutscene/pai-happy.png"));
            
            objectArray[1]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[1]->AddComponent(new Sprite(*objectArray[1], "resources/img/cutscene/triste nao falando.png"));

            objectArray[2]->RemoveComponent(objectArray[0]->GetComponent("Sprite").lock().get());
            objectArray[2]->AddComponent(new Sprite(*objectArray[2], "resources/img/cutscene/bolha esquerd.png"));
            objectArray[2]->box.SetCenter({550,600});

            ((Text*)(objectArray[3]->GetComponent("Text").lock().get()))->SetText("Tudo bem, Tuki, a hora certa");
            objectArray[3]->box.x = 300;
            ((Text*)(objectArray[4]->GetComponent("Text").lock().get()))->SetText("vai chegar... Mas venha dormir,");
            objectArray[4]->box.x = 300;
            ((Text*)(objectArray[5]->GetComponent("Text").lock().get()))->SetText("já está tarde e amanhã é um");
            objectArray[5]->box.x = 300;
            ((Text*)(objectArray[6]->GetComponent("Text").lock().get()))->SetText("novo dia.");  
        }
    }
}