#include <iostream>
#include <graphics.h>
#include <math.h>

#define NUM_VERTICES 6
#define scale_factor 0.08

void rotate(double coords[], double origin[], double theta){
    double c = cos(theta), s = sin(theta);
    double ox = origin[0], oy = origin[1];
    for(int i = 0; i < NUM_VERTICES + 1; i++){
        double x = coords[2 * i], y = coords[2 * i + 1];
        double tmp_x = c*(x - ox) - s*(y - oy) + ox;
        double tmp_y = s*(x - ox) + c*(y - oy) + oy;
        coords[2 * i] = tmp_x, coords[2 * i + 1] = tmp_y;
    }
}

void scale(double coords[], double origin[], int dir){
    double ox = origin[0], oy = origin[1];
    for(int i = 0; i < NUM_VERTICES + 1; i++){
        double x = coords[2 * i], y = coords[2 * i + 1];
        double v[2] = {(x - ox) * (1 - scale_factor * -dir),
                       (y - oy) * (1 - scale_factor * -dir)};
        coords[2 * i] = v[0] + ox;
        coords[2 * i + 1] = v[1] + oy;
    }
}

void draw_polygon(double coords[]){
    for(int i = 0; i < NUM_VERTICES; i++){
        int x1 = (int)round(coords[2 * i]);
        int y1 = (int)round(coords[2 * i + 1]);
        int x2 = (int)round(coords[2 * (i + 1)]);
        int y2 = (int)round(coords[2 * (i + 1) + 1]);
        line(x1, y1, x2, y2);
    }
}

void move(double coords[], double origin[], double dx, double dy){
    for(int i = 0; i < NUM_VERTICES + 1; i++){
        coords[2 * i] += dx;
        coords[2 * i + 1] += dy;
    }
    origin[0] += dx;
    origin[1] += dy;
}

void process_keyboard(double coords[], double origin[]){
    char c = (char)getch();
    if(c == 49){
        rotate(coords, origin, 0.256);
    }else if(c == 50){
        rotate(coords, origin, -0.256);
    }else if(c == 97){
        move(coords, origin, -10.0, 0.0);
    }else if(c == 115){
        move(coords, origin, 0.0, 10.0);
    }else if(c == 100){
        move(coords, origin, 10.0, 0.0);
    }else if(c == 119){
        move(coords, origin, 0.0, -10.0);
    }else if(c == 43){
        scale(coords, origin, 1);
    }else if(c == 45){
        scale(coords, origin, -1);
    }
}

int main(){
    int win = initwindow(620, 480);
    double coords[] = {150.0, 350.0, 200.0, 300.0, 
                       250.0, 300.0, 300.0, 350.0,
                       250.0, 400.0, 200.0, 400.0,
                       150.0, 350.0};
    double origin[] = {0.0, 0.0};
    for(int i = 0; i < NUM_VERTICES; i++){
        origin[0] += coords[2 * i];
        origin[1] += coords[2 * i + 1];
    }
    origin[0] /= NUM_VERTICES; origin[1] /= NUM_VERTICES;
    while(1){
        draw_polygon(coords);
        if(kbhit()){
            process_keyboard(coords, origin);
        }
        swapbuffers();
        clearviewport();
        Sleep(1);

    }
    return 0;
}