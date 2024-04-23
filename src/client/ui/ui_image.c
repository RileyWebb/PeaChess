#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "debug.h"

#include "client/ui.h"

unsigned int ui_image_wbishop;
unsigned int ui_image_wking;
unsigned int ui_image_wknight;
unsigned int ui_image_wpawn;
unsigned int ui_image_wqueen;
unsigned int ui_image_wrook;

unsigned int ui_image_bbishop;
unsigned int ui_image_bking;
unsigned int ui_image_bknight;
unsigned int ui_image_bpawn;
unsigned int ui_image_bqueen;
unsigned int ui_image_brook;

/*
unsigned int UI_ImageFromPiece(piece_t piece) 
{
    if (!piece)
        return 0;

    piece_color color = PieceGetColor(piece);

    switch (PieceGetType(piece))
    {
        case PIECE_TYPE_BISHOP:
            if (color == PIECE_COLOR_WHITE)
                return ui_image_wbishop;
            else
                return ui_image_bbishop;
        case PIECE_TYPE_KING:
            if (color == PIECE_COLOR_WHITE)
                return ui_image_wking;
            else
                return ui_image_bking;
        case PIECE_TYPE_KNIGHT:
            if (color == PIECE_COLOR_WHITE)
                return ui_image_wknight;
            else
                return ui_image_bknight;
        case PIECE_TYPE_PAWN:
            if (color == PIECE_COLOR_WHITE)
                return ui_image_wpawn;
            else
                return ui_image_bpawn;
        case PIECE_TYPE_QUEEN:
            if (color == PIECE_COLOR_WHITE)
                return ui_image_wqueen;
            else
                return ui_image_bqueen;
        case PIECE_TYPE_ROOK:
            if (color == PIECE_COLOR_WHITE)
                return ui_image_wrook;
            else
                return ui_image_brook;
    }

    return 0;
}
*/
void UI_ImageLoadPieces() 
{
    ui_image_wbishop = UI_ImageLoad("data/white_bishop.png");
    ui_image_wking   = UI_ImageLoad("data/white_king.png");
    ui_image_wknight = UI_ImageLoad("data/white_knight.png");
    ui_image_wpawn   = UI_ImageLoad("data/white_pawn.png");
    ui_image_wqueen  = UI_ImageLoad("data/white_queen.png");
    ui_image_wrook   = UI_ImageLoad("data/white_rook.png");

    ui_image_bbishop = UI_ImageLoad("data/black_bishop.png");
    ui_image_bking   = UI_ImageLoad("data/black_king.png");
    ui_image_bknight = UI_ImageLoad("data/black_knight.png");
    ui_image_bpawn   = UI_ImageLoad("data/black_pawn.png");
    ui_image_bqueen  = UI_ImageLoad("data/black_queen.png");
    ui_image_brook   = UI_ImageLoad("data/black_rook.png");
}

unsigned int UI_ImageLoad(char *filename)
{
    unsigned int texture;

    int width, height;
    unsigned char *data = stbi_load(filename, &width, &height, NULL, STBI_rgb_alpha);

    if (!data)
    {
        DEBUG_ERROR("Unable to load image: %s", filename);
        return 0;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return texture;
}