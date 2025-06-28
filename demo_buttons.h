#pragma once

typedef void (*IntDelegate)(unsigned int);

typedef struct DemoButton
{
    char label[64];
    unsigned int flag;
} DemoButton;

void SetDemoButtonDelegate(IntDelegate delegate);
void AddDemoButton(const char* label, unsigned int flag);
void DrawDemoButtons();