#include "demo_buttons.h"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "external/raygui.h"

#define MIN(x,y) (x < y ? x : y)

DemoButton* buttons = NULL;
int buttons_count = 0;
IntDelegate on_clicked;

void SetDemoButtonDelegate(IntDelegate delegate)
{
    on_clicked = delegate;
}

void AddDemoButton(const char* label, unsigned int flag)
{
    DemoButton button = (DemoButton){ .flag = flag };
    strncpy(button.label, label, MIN(strlen(label), 64));
    
    void* mem = MemRealloc(buttons, sizeof(DemoButton) * (buttons_count + 1));
    if (mem == NULL)
    {
        TraceLog(LOG_ERROR, "Failed to add new button in AddDemoButton.");
        return;
    }
    
    buttons = mem;
    buttons[buttons_count] = button;
    buttons_count++;
}

void SetStyle(unsigned int flag)
{
    if (flag == FLAG_WINDOW_HIDDEN)
    {
        GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0x878787ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x2c2c2cff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xc3c3c3ff);
        GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, 0xe1e1e1ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, 0x848484ff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, 0x181818ff);
        GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, 0x000000ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, 0xEFEFEFff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, 0x202020ff);
    }
    else if (flag == FLAG_WINDOW_TRANSPARENT ||
        flag == FLAG_WINDOW_HIGHDPI ||
        flag == FLAG_MSAA_4X_HINT ||
        flag == FLAG_INTERLACED_HINT)
    {
        GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0xffaccdff);
        GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0xffe4ffff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x000000ff);
        GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, 0xffc3e8ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, 0xffeeffff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, 0x000000ff);
        GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, 0xffd3f8ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, 0xfff3ffff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, 0x000000ff);
    }
    else if (IsWindowState(flag))
    {
        GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0x71ACCEff);
        GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0x9CC8FEff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x000000ff);
        GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, 0x187DB1ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, 0x60A7FDff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, 0x000000ff);
        GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, 0x171D72ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, 0x2C89FCff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, 0x000000ff);
    }
    else
    {
        GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0x838383ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0xc9c9c9ff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x686868ff);
        GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, 0x5bb2d9ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, 0xc9effeff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, 0x6c9bbcff);
        GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, 0x0492c7ff);
        GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, 0x97e8ffff);
        GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, 0x368bafff);
    }
}

void DrawDemoButtons()
{
    Rectangle button_rec = { 10, 10, 200, 40};
    
    int i = 0;
    while (i < buttons_count)
    {
        DemoButton* b = buttons + i;
        
        SetStyle(b->flag);
        if (GuiButton(button_rec, b->label))
        {
            on_clicked(b->flag);
        }
        
        button_rec.y += button_rec.height + 10;
        i++;
    }
}