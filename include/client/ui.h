#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
#include <cimgui_impl.h>
#include <cimplot.h>

#include "chess.h"

extern ImGuiIO *ioptr;
extern ImGuiContext *ui_context;
extern ImPlotContext *plot_context;

extern game_t *current_game;

void UI_Init();
void UI_Start(game_t *g);
void UI_Update();

// ui_window
extern SDL_Window *window;

extern unsigned int window_width, window_height;

extern int close;

void UI_WindowCreate();
void UI_WindowProcessEvents();

// ui_renderer
extern SDL_GLContext *gl_context;

void UI_RendererCreate();
void UI_NewFrame();
void UI_Render();

// ui_image
extern unsigned int ui_image_wbishop;
extern unsigned int ui_image_wking;
extern unsigned int ui_image_wknight;
extern unsigned int ui_image_wpawn;
extern unsigned int ui_image_wqueen;
extern unsigned int ui_image_wrook;

extern unsigned int ui_image_bbishop;
extern unsigned int ui_image_bking;
extern unsigned int ui_image_bknight;
extern unsigned int ui_image_bpawn;
extern unsigned int ui_image_bqueen;
extern unsigned int ui_image_brook;

unsigned int UI_ImageFromType(piece_t *piece);
void UI_ImageLoadPieces();
unsigned int UI_ImageLoad(char *filename);

// ui_board
void UI_DrawBoard(ImVec2 boardsize);

// ui_svg
typedef struct ui_svg_path_s
{
    enum 
    {
        UI_SVG_PATH_TYPE_LINE,
        UI_SVG_PATH_TYPE_CUBIC,
    } type;

    ImVec2 p1, p2, p3, p4;
    ImU32 color;
    float thickness
} ui_svg_path_t;


typedef struct ui_svg_s 
{
    float width, height;

    size_t path_count;
    ui_svg_path_t *paths;
} ui_svg_t;