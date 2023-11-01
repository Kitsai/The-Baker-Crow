#ifndef Text_h_
#define Text_h_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <memory>
#include <iostream>
#include "defines/DefinesInclude.h"

#include "GameObject.h"
#include "Resources.h"

/// @brief A text component.
class Text: public Component {
    public:
        /// @brief Enum with diferent text types. SOLID - direct text. SHADED - Retangula com outra cor no fundo. BLENDED - Bordas suavisadas para adaptar ao fundo.
        enum TextStyle {SOLID,SHADED,BLENDED};

        /// @brief Constructor for the Text component initializes all members. And makes the texture.
        /// @param associated Object the component is part of.
        /// @param fontFile realtive path to font file.
        /// @param fontSize size of the font
        /// @param style Qual o estilo de renderizacao da fonte.
        /// @param text Texto que deve ser escrito na tela.
        /// @param colorA Cor do texto.
        /// @param colorB Cor do fundo.
        Text(GameObject& associated,std::string fontFile, int fontSize,TextStyle style,std::string text,SDL_Color colorA, SDL_Color colorB = COLOR_BLACK);
        /// @brief Frees the texture.
        ~Text();

        /// @brief Updates the component. 
        /// @param dt Delta Time.
        void Update(float dt);
        /// @brief Renders the component. 
        void Render();
        /// @brief Returns whether the object is of a certain type.
        /// @param type Type to be checked.
        /// @return True if type matches with the passed argument.
        bool Is(std::string type);

        /// @brief Setter for the text. Remakes the texture.
        /// @param text texture to be written.
        void SetText(std::string text);
        /// @brief Setter for the text color. Remakes the texture.
        /// @param color text color.
        void SetColorA(SDL_Color color);
        /// @brief Setter for the backgropund color. Remakes the texture.
        /// @param color background color.
        void SetColorB(SDL_Color color);
        /// @brief Setter for the text style. Remakes the texture.
        /// @param style style of the text.
        void SetStyle(TextStyle style);
        /// @brief Setter for the font file. Remakes the texture.
        /// @param fontFile relative path to the font file.
        void SetFontFile(std::string fontFile);
        /// @brief Setter for the font size. Remakes the texture.
        /// @param fontSize size of the font.
        void SetFontSize(int fontSize);

    private:
        /// @brief Remakes the texture with current data.
        void RemakeTexture();

        /// @brief shared pointer to the font.
        std::shared_ptr<TTF_Font> font;
        /// @brief raw pointer to the texture created from the font.
        SDL_Texture* texture;

        /// @brief Text that is written on the screen.
        std::string text;
        /// @brief Text style.
        TextStyle style;
        /// @brief relative path to the font file.
        std::string fontFile;
        /// @brief Size of the font.
        int fontSize;
        /// @brief color of the text.
        SDL_Color colorA;
        /// @brief color of the background.
        SDL_Color colorB;
};

#endif