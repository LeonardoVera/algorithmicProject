#pragma once
#include <Windows.h>

// Función para mover el cursor a una posición específica en la consola
inline void gotoxy(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

// Función para ocultar el cursor en la consola
inline void ocultarCursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 50;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

// Función para obtener la posición actual del cursor en el eje X (columna) dentro de la consola
inline int whereX() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int column;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    column = csbi.dwCursorPosition.X;
    return column;
}

// Función para obtener la posición actual del cursor en el eje Y (fila) dentro de la consola
inline int whereY() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int row;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    row = csbi.dwCursorPosition.Y;
    return row;
}

/*
    Función que cambia el color de la consola
    @param x: color a cambiar
    0: Negro
    1: Azul
    2: Verde
    3: Aguamarina
    4: Rojo
    5: Púrpura
    6: Amarillo (marrón en sistemas antiguos)
    7: Blanco (gris en sistemas antiguos)
    8: Gris
    9: Azul claro
    10: Verde claro
    11: Aguamarina claro
    12: Rojo claro
    13: Púrpura claro
    14: Amarillo claro
    15: Blanco brillante
*/
inline void color(int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
