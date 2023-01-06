#include <iostream> 
#include <cstdio>
#include <unistd.h>

using namespace std;
int width = 45, height = 35;
char buffer[45*30];

// heart bombing times
int bomb_times = 20;

// heart bombing speed
int speed = 1000*1000*0.05;

// heart bombing maxmiem and miniem
float k_max = 0.4, k_min = 0.2;

// function -> (x^2 + y^2 - k)^3 - x^2*y^3 <= 0 , ratio controls k
float math_function (float x, float y, float ratio) {
    float tmp, result;
    tmp = x*x + y*y - ratio;
    result = tmp*tmp*tmp - x*x*y*y*y;
    return result;
}

void heart_body(float ratio, std::string ch) {
    float r, x, y;
    int count = 0, chr = 0;
    for (y = 1.5f; y > -1.5f; y -= 0.1f) {
        for (x = -1.5f; x < 1.5f; x += 0.05f) {
            r = math_function(x, y, ratio);
            if (r <= 0.0f) buffer[count] = ch[chr % 5];
            else buffer[count] = ' ';
            count += 1;
            chr += 1;
            //usleep(100);
        }
        buffer[count] = '\n';
        count += 1;
    }
}

void outside(float ratio, char ch) {
    int count = 0;
    float r;
    for (float y = 1.5f; y > -1.5f; y -= 0.1f) {
        for (float x = -1.5f; x < 1.5f; x += 0.05f) {
            r = math_function(x, y, ratio);
            if (r <= 0.075f && r >= 0.0f) buffer[count] = ch;
            count += 1;
        }
        buffer[count] = '\n';
        count += 1;
    }
}

void explosion(std::string ch) {
    float explo_ratio = 0.2;
    for (int i = 0; i < 6; i++) {
        heart_body(explo_ratio, ch);
        printf("\x1b[H");
        for (int j = 0; j < width*height; j++) {
            putchar(buffer[j]);
        }
        explo_ratio += 0.2;
        usleep(speed/5);
    }
    for (float i = 0.2f; i < 1.5f; i += 0.1f) {
        outside(i, '*');
        printf("\x1b[H");
        printf("\x1b[1;31m");
        for (int j = 0; j < width*height; j++) {
                putchar(buffer[j]);
        }
        usleep(speed);
        outside(i, ' ');
    }
}

void text() {
    for (int i = 0; i < width*height*2; i++) {
        if (i % width == 0) buffer[i] = '\n';
        else buffer[i] = ' ';
    }
    printf("\x1b[H");
    for (int i = 0; i < width*height*2; i++) {
        putchar(buffer[i]);
    }
    printf("\x1b[H");
    printf("\x1b[1;31m");
    printf("**********           *****       *****              **           **\n    **             ********** **********            **           **\n    **            ***********************           **           **\n    **            ***********************           **           **\n    **             *********************            **           **\n    **             *********************            **           **\n    **               *****************              **           **\n    **                ***************               **           **\n    **                  ***********                 **           **\n    **                    *******                    **         **\n***********                  *                         *********");
}

int main (int argc, char** argv) {
    float x,y,k,r, o = 0.5;
    int c = 0;

    // bombing part
    while(c <= bomb_times) {
        if (c % 2 == 1) k = k_max;
        else k = k_min;
        heart_body(k, "IluvU");
        for (int i = 0; i < 13; i++) {
            if (c % 2 == 1) outside(o, '*');
            printf("\x1b[H");
            printf("\x1b[1;31m");
            for (int j = 0; j < width*height; j++) {
                putchar(buffer[j]);
            }
            usleep(speed);
            if (c % 2 == 1) {
                outside(o, ' ');
                o += 0.3f;
            }
        }
        o = 0.5f;
        c += 1;
    }

    // explosion part
    explosion("IluvU");
    text();

    return 0;
}