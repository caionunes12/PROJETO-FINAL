#ifndef _FONT_H_
#define _FONT_H_

// Fontes para A-Z e 0-9. Os caracteres tem 8x8 pixels


static const uint8_t font[] = {
    // Espaço e caracteres especiais (ASCII 32-47)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Space (32)
    0x00, 0x00, 0x5F, 0x5F, 0x00, 0x00, 0x00, 0x00, // ! (33)
    0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, // " (34)
    0x14, 0x7F, 0x14, 0x14, 0x7F, 0x14, 0x00, 0x00, // # (35)
    0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00, 0x00, 0x00, // $ (36)
    0x23, 0x13, 0x08, 0x64, 0x62, 0x00, 0x00, 0x00, // % (37)
    0x36, 0x49, 0x55, 0x22, 0x50, 0x00, 0x00, 0x00, // & (38)
    0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, // ' (39)
    0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, 0x00, 0x00, // ( (40)
    0x00, 0x41, 0x22, 0x1C, 0x00, 0x00, 0x00, 0x00, // ) (41)
    0x14, 0x08, 0x3E, 0x08, 0x14, 0x00, 0x00, 0x00, // * (42)
    0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00, 0x00, // + (43)
    0x00, 0x50, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, // , (44)
    0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // - (45)
    0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, // . (46)
    0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00, // / (47)

    // Números (ASCII 48-57)
    0x3e, 0x41, 0x41, 0x49, 0x41, 0x41, 0x3e, 0x00, // 0
    0x00, 0x00, 0x42, 0x7f, 0x40, 0x00, 0x00, 0x00, // 1
    0x30, 0x49, 0x49, 0x49, 0x49, 0x46, 0x00, 0x00, // 2
    0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x36, 0x00, // 3
    0x3f, 0x20, 0x20, 0x78, 0x20, 0x20, 0x00, 0x00, // 4
    0x4f, 0x49, 0x49, 0x49, 0x49, 0x30, 0x00, 0x00, // 5
    0x3f, 0x48, 0x48, 0x48, 0x48, 0x48, 0x30, 0x00, // 6
    0x01, 0x01, 0x01, 0x61, 0x31, 0x0d, 0x03, 0x00, // 7
    0x36, 0x49, 0x49, 0x49, 0x49, 0x49, 0x36, 0x00, // 8
    0x06, 0x09, 0x09, 0x09, 0x09, 0x09, 0x7f, 0x00, // 9

    // Caracteres especiais (ASCII 58-64)
    0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, // : (58)
    0x00, 0x56, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, // ; (59)
    0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00, 0x00, // < (60)
    0x14, 0x14, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, // = (61)
    0x00, 0x41, 0x22, 0x14, 0x08, 0x00, 0x00, 0x00, // > (62)
    0x02, 0x01, 0x51, 0x09, 0x06, 0x00, 0x00, 0x00, // ? (63)
    0x32, 0x49, 0x79, 0x41, 0x3E, 0x00, 0x00, 0x00, // @ (64)

    // Letras maiúsculas (ASCII 65-90)
    0x78, 0x14, 0x12, 0x11, 0x12, 0x14, 0x78, 0x00, // A
    0x7f, 0x49, 0x49, 0x49, 0x49, 0x49, 0x7f, 0x00, // B
    0x7e, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x00, // C
    0x7f, 0x41, 0x41, 0x41, 0x41, 0x41, 0x7e, 0x00, // D
    0x7f, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x00, // E
    0x7f, 0x09, 0x09, 0x09, 0x09, 0x01, 0x01, 0x00, // F
    0x7f, 0x41, 0x41, 0x41, 0x51, 0x51, 0x73, 0x00, // G
    0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7f, 0x00, // H
    0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, // I
    0x21, 0x41, 0x41, 0x3f, 0x01, 0x01, 0x01, 0x00, // J
    0x00, 0x7f, 0x08, 0x08, 0x14, 0x22, 0x41, 0x00, // K
    0x7f, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, // L
    0x7f, 0x02, 0x04, 0x08, 0x04, 0x02, 0x7f, 0x00, // M
    0x7f, 0x02, 0x04, 0x08, 0x10, 0x20, 0x7f, 0x00, // N
    0x3e, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, 0x00, // O
    0x7f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e, 0x00, // P
    0x3e, 0x41, 0x41, 0x49, 0x51, 0x61, 0x7e, 0x00, // Q
    0x7f, 0x11, 0x11, 0x11, 0x31, 0x51, 0x0e, 0x00, // R
    0x46, 0x49, 0x49, 0x49, 0x49, 0x30, 0x00, 0x00, // S
    0x01, 0x01, 0x01, 0x7f, 0x01, 0x01, 0x01, 0x00, // T
    0x3f, 0x40, 0x40, 0x40, 0x40, 0x40, 0x3f, 0x00, // U
    0x0f, 0x10, 0x20, 0x40, 0x20, 0x10, 0x0f, 0x00, // V
    0x7f, 0x20, 0x10, 0x08, 0x10, 0x20, 0x7f, 0x00, // W
    0x00, 0x41, 0x22, 0x14, 0x14, 0x22, 0x41, 0x00, // X
    0x01, 0x02, 0x04, 0x78, 0x04, 0x02, 0x01, 0x00, // Y
    0x41, 0x61, 0x59, 0x45, 0x43, 0x41, 0x00, 0x00, // Z

    // Caracteres especiais (ASCII 91-96)
    0x00, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x00, 0x00, // [ (91)
    0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00, // \ (92)
    0x00, 0x41, 0x41, 0x7F, 0x00, 0x00, 0x00, 0x00, // ] (93)
    0x04, 0x02, 0x01, 0x02, 0x04, 0x00, 0x00, 0x00, // ^ (94)
    0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, // _ (95)
    0x00, 0x01, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, // ` (96)

    // Letras minúsculas (ASCII 97-122)
    0x20, 0x54, 0x54, 0x54, 0x78, 0x40, 0x00, 0x00, // a
    0x7F, 0x48, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00, // b
    0x38, 0x44, 0x44, 0x44, 0x20, 0x00, 0x00, 0x00, // c
    0x38, 0x44, 0x44, 0x48, 0x7F, 0x00, 0x00, 0x00, // d
    0x38, 0x54, 0x54, 0x54, 0x18, 0x00, 0x00, 0x00, // e
    0x08, 0x7E, 0x09, 0x01, 0x02, 0x00, 0x00, 0x00, // f
    0x0C, 0x52, 0x52, 0x52, 0x3E, 0x00, 0x00, 0x00, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, 0x00, 0x00, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, 0x00, 0x00, 0x00, // i
    0x20, 0x40, 0x44, 0x3D, 0x00, 0x00, 0x00, 0x00, // j
    0x7F, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, 0x00, 0x00, 0x00, // l
    0x7C, 0x04, 0x18, 0x04, 0x78, 0x00, 0x00, 0x00, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, 0x00, 0x00, 0x00, // n
    0x38, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00, // o
    0x7C, 0x14, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00, // p
    0x08, 0x14, 0x14, 0x18, 0x7C, 0x00, 0x00, 0x00, // q
    0x7C, 0x08, 0x04, 0x04, 0x08, 0x00, 0x00, 0x00, // r
    0x48, 0x54, 0x54, 0x54, 0x20, 0x00, 0x00, 0x00, // s
    0x04, 0x3F, 0x44, 0x40, 0x20, 0x00, 0x00, 0x00, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00, 0x00, 0x00, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00, 0x00, 0x00, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00, 0x00, 0x00, // w
    0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00, // x
    0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00, 0x00, 0x00, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, 0x00, 0x00, // z

    // Caracteres especiais (ASCII 123-127)
    0x00, 0x08, 0x36, 0x41, 0x00, 0x00, 0x00, 0x00, // { (123)
    0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, // | (124)
    0x00, 0x41, 0x36, 0x08, 0x00, 0x00, 0x00, 0x00, // } (125)
    0x10, 0x08, 0x08, 0x10, 0x08, 0x00, 0x00, 0x00, // ~ (126)
    0x78, 0x46, 0x41, 0x46, 0x78, 0x00, 0x00, 0x00  // DEL (127)
};

#endif // _FONT_H_





