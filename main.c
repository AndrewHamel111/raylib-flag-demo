#include "raylib.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024

#include "config.h"
#include "demo_buttons.h"

void InitButtons();

int main(void)
{
    LoadConfig();
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window Flag Overview");
    SetExitKey(-1);
    
    InitButtons();
    
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            ClearWindowState(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_MOUSE_PASSTHROUGH);
        }
        
        UpdateConfig();
        
        BeginDrawing();
        {
            Color background = IsWindowState(FLAG_WINDOW_TRANSPARENT) ? BLANK : WHITE;
            ClearBackground(background);
            
            DrawDemoButtons();
            DrawFPS(220, 5);
            
            DrawPendingConfig();
        }
        EndDrawing();
    }
    
    CloseWindow();
    
    SaveConfig();
}

void InitButtons()
{
    SetDemoButtonDelegate(&SetPendingFlag);
    
    AddDemoButton("VSync Hint", FLAG_VSYNC_HINT);
    AddDemoButton("Fullscreen Mode", FLAG_FULLSCREEN_MODE);
    AddDemoButton("Window Resizable", FLAG_WINDOW_RESIZABLE);
    AddDemoButton("Window Undecorated", FLAG_WINDOW_UNDECORATED);
    AddDemoButton("Window Hidden", FLAG_WINDOW_HIDDEN);
    AddDemoButton("Window Minimized", FLAG_WINDOW_MINIMIZED);
    AddDemoButton("Window Maximized", FLAG_WINDOW_MAXIMIZED);
    AddDemoButton("Window Unfocused", FLAG_WINDOW_UNFOCUSED);
    AddDemoButton("Window Topmost", FLAG_WINDOW_TOPMOST);
    AddDemoButton("Window Always Run", FLAG_WINDOW_ALWAYS_RUN);
    AddDemoButton("Window Transparent", FLAG_WINDOW_TRANSPARENT);
    AddDemoButton("Window High DPI", FLAG_WINDOW_HIGHDPI);
    AddDemoButton("Mouse Passthrough", FLAG_WINDOW_MOUSE_PASSTHROUGH);
    AddDemoButton("Borderless Windowed", FLAG_BORDERLESS_WINDOWED_MODE);
    AddDemoButton("MSAA 4X Hint", FLAG_MSAA_4X_HINT);
    AddDemoButton("Interlaced Hint", FLAG_INTERLACED_HINT);
}