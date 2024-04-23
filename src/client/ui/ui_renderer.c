#include <GL/glew.h>

#include "debug.h"

#include "client/ui.h"

SDL_GLContext *gl_context;

const char *r_requiredExtensions[] = {"GL_VERSION_3_3"};
size_t r_requiredExtensionCount = sizeof(r_requiredExtensions) / sizeof(const char*);

void UI_RendererCreate() 
{
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);

    if (!gl_context)
        DEBUG_FATAL("Unable to create OpenGL Context");

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err && err != GLEW_ERROR_NO_GLX_DISPLAY)
        DEBUG_FATAL("Unable to initialize OpenGL: %s", glewGetErrorString(glewInit()));

    for (size_t i = 0; i < r_requiredExtensionCount; ++i)
    {
        if (!glewIsSupported(r_requiredExtensions[i]))
            DEBUG_FATAL("Required OpenGL extension %s is not supported", r_requiredExtensions[i]);
    }

    DEBUG_INFO("Initialized OpenGL %s", glGetString(GL_VERSION));
    DEBUG_INFO("\tDevice: %s", glGetString(GL_RENDERER));
    DEBUG_INFO("\tVendor: %s", glGetString(GL_VENDOR));
}

void UI_NewFrame() 
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    igNewFrame();
}

void UI_Render() 
{
    SDL_GL_MakeCurrent(window, gl_context);
    glViewport(0, 0, (int)ioptr->DisplaySize.x, (int)ioptr->DisplaySize.y);

    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());

    if (ioptr->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        igUpdatePlatformWindows();
        igRenderPlatformWindowsDefault(NULL,NULL);
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
    
	SDL_GL_SwapWindow(window);
}