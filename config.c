#include "config.h"
#include "raylib.h"

#define RINI_IMPLEMENTATION
#include "external/rini.h"

static unsigned int pending_config = 0;
static unsigned int pending_state = 0;
static unsigned int pending_state_clear = 0;

void LoadConfig()
{
    rini_data data = rini_load("config.ini");
    
    pending_config |= rini_get_value(data, "FLAG_WINDOW_TRANSPARENT") ? FLAG_WINDOW_TRANSPARENT : 0;
    pending_config |= rini_get_value(data, "FLAG_WINDOW_HIGHDPI") ? FLAG_WINDOW_HIGHDPI : 0;
    pending_config |= rini_get_value(data, "FLAG_MSAA_4X_HINT") ? FLAG_MSAA_4X_HINT : 0;
    pending_config |= rini_get_value(data, "FLAG_INTERLACED_HINT") ? FLAG_INTERLACED_HINT : 0;
    
    if (pending_config != 0)
    {
        SetConfigFlags(pending_config);
    }
    
    rini_unload(&data);
}

void SaveConfig()
{
    rini_data data = rini_load("config.ini");
    
    rini_set_value(&data, "FLAG_WINDOW_TRANSPARENT", (pending_config & FLAG_WINDOW_TRANSPARENT) > 0, NULL);
    rini_set_value(&data, "FLAG_WINDOW_HIGHDPI", (pending_config & FLAG_WINDOW_HIGHDPI) > 0, NULL);
    rini_set_value(&data, "FLAG_MSAA_4X_HINT", (pending_config & FLAG_MSAA_4X_HINT) > 0, NULL);
    rini_set_value(&data, "FLAG_INTERLACED_HINT", (pending_config & FLAG_INTERLACED_HINT) > 0, NULL);
    
    rini_save(data, "config.ini");
    
    rini_unload(&data);
}

void UpdateConfig()
{
    if (pending_state != 0)
    {
        SetWindowState(pending_state);
        pending_state = 0;
    }
    
    if (pending_state_clear != 0)
    {
        ClearWindowState(pending_state_clear);
        pending_state_clear = 0;
    }
}

void SetPendingFlag(unsigned int flag)
{
    bool isEnabled = IsWindowState(flag);
    
    switch(flag)
    {
    case FLAG_VSYNC_HINT:
    case FLAG_FULLSCREEN_MODE:
    case FLAG_WINDOW_RESIZABLE:
    case FLAG_WINDOW_UNDECORATED:
    case FLAG_WINDOW_HIDDEN:
    case FLAG_WINDOW_MINIMIZED:
    case FLAG_WINDOW_MAXIMIZED:
    case FLAG_WINDOW_UNFOCUSED:
    case FLAG_WINDOW_TOPMOST:
    case FLAG_WINDOW_ALWAYS_RUN:
    case FLAG_WINDOW_MOUSE_PASSTHROUGH:
    case FLAG_BORDERLESS_WINDOWED_MODE:
        if (isEnabled)
            pending_state_clear |= flag;
        else
            pending_state |= flag;
        break;
    case FLAG_WINDOW_TRANSPARENT:
    case FLAG_WINDOW_HIGHDPI:
    case FLAG_MSAA_4X_HINT:
    case FLAG_INTERLACED_HINT:
        if (pending_config & flag)
            pending_config &= ~flag;
        else
            pending_config |= flag;
        break;
    }
}

void DrawPendingConfig()
{
    if (pending_config > 0)
    {
        int X = 400;
        int Y = 10;
        DrawText("Will apply on restart:", X, Y, 32, MAROON);
        X += 32;
        Y += 42;
        
        if (pending_config & FLAG_WINDOW_TRANSPARENT)
        {
            DrawText("Window Transparency", X, Y, 32, MAROON);
            Y += 42;
        }
        if (pending_config & FLAG_WINDOW_HIGHDPI)
        {
            DrawText("High DPI Mode", X, Y, 32, MAROON);
            Y += 42;
        }
        if (pending_config & FLAG_MSAA_4X_HINT)
        {
            DrawText("4x Multi-Sample Anti-Aliasing", X, Y, 32, MAROON);
            Y += 42;
        }
        if (pending_config & FLAG_INTERLACED_HINT)
        {
            DrawText("Interlaced Video", X, Y, 32, MAROON);
            Y += 42;
        }
    }
}