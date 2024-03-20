#include "Includes.h"

// Define a structure to hold RGB color values
struct ColorRGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// Function to get smoothly transitioning rainbow color
ColorRGB GetSmoothRainbowColor() {
    static float hue = 0.0f;
    hue += 0.001f;  // Adjust the increment for a slightly slower color change

    // Ensure hue stays within the valid range [0, 1]
    if (hue > 1.0f) {
        hue -= 1.0f;
    }

    // Convert HSV to RGB
    float h = hue * 360.0f;
    float s = 1.0f;
    float v = 1.0f;

    int hi = static_cast<int>(h / 60.0) % 6;
    float f = h / 60.0 - hi;
    float p = v * (1.0 - s);
    float q = v * (1.0 - f * s);
    float t = v * (1.0 - (1.0 - f) * s);

    ColorRGB rainbowColor;

    switch (hi) {
    case 0:
        rainbowColor.r = static_cast<uint8_t>(v * 255.0);
        rainbowColor.g = static_cast<uint8_t>(t * 255.0);
        rainbowColor.b = static_cast<uint8_t>(p * 255.0);
        break;
    case 1:
        rainbowColor.r = static_cast<uint8_t>(q * 255.0);
        rainbowColor.g = static_cast<uint8_t>(v * 255.0);
        rainbowColor.b = static_cast<uint8_t>(p * 255.0);
        break;
    case 2:
        rainbowColor.r = static_cast<uint8_t>(p * 255.0);
        rainbowColor.g = static_cast<uint8_t>(v * 255.0);
        rainbowColor.b = static_cast<uint8_t>(t * 255.0);
        break;
    case 3:
        rainbowColor.r = static_cast<uint8_t>(p * 255.0);
        rainbowColor.g = static_cast<uint8_t>(q * 255.0);
        rainbowColor.b = static_cast<uint8_t>(v * 255.0);
        break;
    case 4:
        rainbowColor.r = static_cast<uint8_t>(t * 255.0);
        rainbowColor.g = static_cast<uint8_t>(p * 255.0);
        rainbowColor.b = static_cast<uint8_t>(v * 255.0);
        break;
    case 5:
        rainbowColor.r = static_cast<uint8_t>(v * 255.0);
        rainbowColor.g = static_cast<uint8_t>(p * 255.0);
        rainbowColor.b = static_cast<uint8_t>(q * 255.0);
        break;
    }

    return rainbowColor;
}

pMenu_t* pMenu = (pMenu_t*)0x10089000;

void ScrollEffect() {
    // Set the selection color to the smoothly transitioning rainbow theme
    ColorRGB rainbowColor = GetSmoothRainbowColor();
    printf("Rainbow Color: R=%d, G=%d, B=%d\n", rainbowColor.r, rainbowColor.g, rainbowColor.b); // Add this line for debugging

    // Update the border color to rainbow color
    pMenu->lineColor = Color(rainbowColor.r / 255.0, rainbowColor.g / 255.0, rainbowColor.b / 255.0, 0.7);

    for (int i = 0; i < 9; i++) {
        pMenu->glowColor[i] = Color(0, 0, 0, 0);

        // Check if the current item is selected, then use rainbow color for text
        if (i == pMenu->ScrollIndex) {
            pMenu->textColor[i] = Color(rainbowColor.r / 255.0, rainbowColor.g / 255.0, rainbowColor.b / 255.0, 1.0);
        }
        else {
            // If not selected, keep the original text color
            pMenu->textColor[i] = Color(1, 1, 1, 0.2);
        }
    }
}


void SelectOption() {
    switch (pMenu->ScrollIndex) {
    case 0:
        DrawKeyboard("Change your name", "", 32, CELL_OSKDIALOG_PANELMODE_ALPHABET, KeyboardCallback);
        pMenu->setName = true;
        break;
    case 1:
        doLevels();
        break;
    case 2:
        doPrestige();
        break;
    case 3:
        memcpy((void*)0x01FFA0C7, &UnlockAll, 3120);
        for (int i = 0; i < 9; i++)
            *(char*)(0x1FF9E47 + (0x40 * i)) = 0x01;
        break;
    case 4:
        Cbuf_AddText(0, "defaultStatsInit;uploadStats;");
        break;
    case 5:
        DrawKeyboard("Custom Command", "", 100, CELL_OSKDIALOG_PANELMODE_ALPHABET, KeyboardCallback);
        pMenu->customCmd = true;
        break;
    case 6:
        pMenu->forceHost ^= true;
        toggleFFAFH();
        break;
    case 7:
        pMenu->teamForceHost ^= true;
        if (!pMenu->teamForceHost)
            teamBasedForceHost(true);
        break;
    case 8:
        int value = *(int*)0x1F96708;
        value = value == 1 ? 3 : 1;
        *(int*)0x1F96708 = value;
        break;
    }
}

void pregameThread(uint64_t arg) {
    for (int i = 0; i < 9; i++) {
        pMenu->textColor[i] = Color(1, 1, 1, 0);
        pMenu->glowColor[i] = Color(1, 0, 0, 0);
    }

    pMenu->titleColor = Color(1, 1, 1, 0);  // White color with full intensity on the red, green, and blue components
    pMenu->titleGlow = Color(1, 0, 0, 0.0); // No longer in use
    pMenu->lineColor = Color(0.7, 0, 0, 0);
    pMenu->currentLevel = 1;
    int nop[] = { 0x60000000 };
    WriteProcessMemory(0x2383A8, nop, 4);

    for (;;) {
        if (!cl_ingame->current.enabled) {
            updateButtons();
            sleep(1);
        }
        else {
            sleep(1000);
        }
    }
}

void Menu_PaintAll_s(...) {
    __asm("li %r3, 5;");
}

void Menu_PaintAll_h(uint64_t a1, uint64_t a2) {
    if (!cl_ingame->current.enabled) {
        if (pMenu->isOpen) {
            DrawMenu();

            if (pMenu->R3) {
                SelectOption();
            }
            if (pMenu->Square) {
                pMenu->bgColor.rgba[3] = 0;
                pMenu->lineColor.rgba[3] = 0;
                pMenu->titleColor.rgba[3] = 0;
                for (int i = 0; i < 9; i++)
                    pMenu->textColor[i].rgba[3] = 0;
                pMenu->isOpen = false;
                if (!pMenu->DisabledControlText)
                    pMenu->DisabledControlText = true;
            }

            if (pMenu->L2 || pMenu->R2) {
                if (pMenu->ScrollIndex == 1) {
                    pMenu->currentLevel += pMenu->R2;
                    pMenu->currentLevel -= pMenu->L2;
                    if (pMenu->currentLevel > 70)
                        pMenu->currentLevel = 1;
                    if (pMenu->currentLevel < 1)
                        pMenu->currentLevel = 70;
                }
                else if (pMenu->ScrollIndex == 2) {
                    pMenu->currentPrestige += pMenu->R2;
                    pMenu->currentPrestige -= pMenu->L2;
                    if (pMenu->currentPrestige > 11)
                        pMenu->currentPrestige = 0;
                    if (pMenu->currentPrestige < 0)
                        pMenu->currentPrestige = 11;
                }
            }

            if (pMenu->L1 || pMenu->R1) {
                pMenu->ScrollIndex += pMenu->R1;
                pMenu->ScrollIndex -= pMenu->L1;
                if (pMenu->ScrollIndex > 8)
                    pMenu->ScrollIndex = 0;
                if (pMenu->ScrollIndex < 0)
                    pMenu->ScrollIndex = 8;
                ScrollEffect();
            }

            // Continuous update of rainbow color
            ScrollEffect();
        }
        else {
            if (pMenu->L3) {
                pMenu->bgColor.rgba[3] = .5;
                pMenu->lineColor.rgba[3] = 1;
                pMenu->titleColor.rgba[3] = 1;
                ScrollEffect();
                pMenu->isOpen = true;
                UI_PlayLocalSoundAliasByName(0, "mp_suitcase_pickup");
            }
        }

        updateButtons(true);
    }
    Menu_PaintAll_s(a1, a2);
}