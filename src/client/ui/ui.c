#include "client/ui.h"

int close;

ImGuiIO *ioptr;
ImGuiContext *ui_context;
ImPlotContext *plot_context;

game_t *current_game;

void UI_Init()
{
	UI_WindowCreate();
	UI_RendererCreate();

	ui_context = igCreateContext(NULL);
	plot_context = ImPlot_CreateContext();

	ioptr = igGetIO();

	ioptr->ConfigFlags |= ImGuiConfigFlags_None;
    ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	// ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
	// Gamepad Controls
	ioptr->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	//ioptr->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform

	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init("#version 150");

	igStyleColorsDark(NULL);

	SDL_GL_SetSwapInterval(1);

	UI_ImageLoadPieces();
}

void UI_Start(game_t *g)
{
	current_game = g;
	while (!close)
		UI_Update();
}

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void UI_Update()
{
	UI_WindowProcessEvents();

	igSetCurrentContext(ui_context);
	ImPlot_SetCurrentContext(plot_context);

	UI_NewFrame();



	ImVec2 boardsize; //= (ImVec2){1024,1024};

	int a = 1;

	//igShowDemoWindow(&a);

	if (current_game)
	{
        //ImGuiViewport* viewport = igGetMainViewport();
        //igSetNextWindowPos(viewport->WorkPos, ImGuiCond_Always, (ImVec2){0,0});
        //igSetNextWindowSize(viewport->WorkSize, ImGuiCond_Always);
        //igSetNextWindowViewport(viewport->ID);

		//igPushStyleVar_Vec2(ImGuiStyleVar_ItemSpacing, (ImVec2){0.0f, 0.0f});
		//igPushStyleVar_Vec2(ImGuiStyleVar_FramePadding, (ImVec2){0.0f, 0.0f});
		//igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0.0f, 0.0f});
        //igPushStyleVar_Vec2(ImGuiStyleVar_ItemInnerSpacing, (ImVec2){0.0f, 0.0f});
        //igPushStyleVar_Vec2(ImGuiStyleVar_ItemInnerSpacing, (ImVec2){0.0f, 0.0f});

		igBegin("Board", &a, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse); //ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | 
        //igPopStyleVar(5);

		ImVec2 window_min;
		ImVec2 window_max;
		ImVec2 window_size;

		//igGetWindowContentRegionMin(&window_min);
		//igGetWindowContentRegionMax(&window_max);
		// igGetItemRectSize(&window_size);
		igGetContentRegionAvail(&window_size);

		boardsize.x =
			MIN(window_size.x, window_size.y);
		boardsize.y =
			MIN(window_size.x, window_size.y);
		//tab bar
		UI_DrawBoard(boardsize);
		igEnd();
	}

	UI_Render();
}

/* COLORSCHEMES
   PEACH ICON
*/