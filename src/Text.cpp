#include <Text.h>

#include <Camera.h>
#include <Game.h>
#include <defines/DefinesInclude.h>

Text::Text(GameObject& associated,std::string fontFile,int fontSize,TextStyle style, std::string text,SDL_Color color): Component(associated) {
    this->text = text;
    this->style = style;
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->color = color;

    RemakeTexture();
}

Text::~Text() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }   
}

void Text::Update(float dt) {

}

void Text::Render() {
    if(texture != nullptr) {
        SDL_Rect src = {0,0,associated.box.w,associated.box.h};
        SDL_Rect dst = {associated.box.x - Camera::pos.x,associated.box.y - Camera::pos.y,src.w,src.h};

        if(SDL_RenderCopyEx(
            Game::GetInstance().GetRenderer(), texture, &src, &dst,0,nullptr,SDL_FLIP_NONE) != 0) {
                std::cerr << "Error - " << SDL_GetError() << std::endl;
                exit(-1);
        }
    }
}

bool Text::Is(std::string type) {
    return type == "Text";
}

void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this-> color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    font = Resources::GetFont(fontFile,fontSize);
    SDL_Surface* surface;

    switch (style) {
    case SOLID:
        surface = TTF_RenderText_Solid(font.get(),text.data(),color);
        break;
    
    case SHADED:
        surface = TTF_RenderText_Shaded(font.get(),text.data(),color,COLOR_BLACK);
        break;
    
    case BLENDED:
        surface = TTF_RenderText_Blended(font.get(),text.data(),color);
        break;

    default:
        break;
    }

    associated.box.w = surface->w;
    associated.box.h = surface->h;

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(),surface);

    SDL_FreeSurface(surface);
}