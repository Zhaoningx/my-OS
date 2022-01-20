#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Univariate Polynomial Solve
 * 
 * ADT mylist {
 * data: D = {n1,n2,n3..., m1,m2,m3...}
 * data relationship R = {<n1, m1>, <n2, m2>...|n1,n2,n3,...-> R, m1,m2,m3,...->N}
 * data operation:
 *      initCoordinateSystem(ElemSet x, ElemSet y);
 *      parse_expression(&string, &mylist);
 *      get_sequence_pair(&mylist);
 *      show_sequence_pair();
 * }
 * 
 */

/*********************Set xy system**************************/
#define SYS_SIZE_X 25
#define SYS_SIZE_Y 30

typedef struct {
    int x;
    int y;
    char value;
} xy;

xy xy_system[SYS_SIZE_X * SYS_SIZE_Y]; 

void initCoordinateSystem(xy *x_y)
{
    int index = 0;
    for (int i = 0; i < SYS_SIZE_Y; i++) {
        for (int j = 0; j < SYS_SIZE_X; j++, index++) {
            x_y[index].x = j;
            x_y[index].y = i;
            x_y[index].value = ' ';
            if (x_y[index].x == 0) {
                x_y[index].value = '|';
            }
            if (x_y[index].y == 0) {
                x_y[index].value = '-';
            }
            if (x_y[index].x == (SYS_SIZE_X - 2) && x_y[index].y == 0) {
                x_y[index].value = '>';
            }
            if (x_y[index].x == (SYS_SIZE_X - 1) && x_y[index].y == 0) {
                x_y[index].value = 'x';
            }
            if (x_y[index].y == (SYS_SIZE_Y - 2) && x_y[index].x == 0) {
                x_y[index].value = '^';
            }
            if (x_y[index].y == (SYS_SIZE_Y - 1) && x_y[index].x == 0) {
                x_y[index].value = 'y';
            }
        }
    }
}

void show_xy_system(xy *x_y)
{
    for (int i = SYS_SIZE_Y - 1; i >= 0; i--) {
        for (int j = 0; j < SYS_SIZE_X; j++) {
            //printf("(%d, %d)", x_y[SYS_SIZE_X * i + j].x, x_y[SYS_SIZE_X * i + j].y);
            if ( x_y[SYS_SIZE_X * i + j].y == 0 && x_y[SYS_SIZE_X * i + j].x < (SYS_SIZE_X -2)) {
                printf("%c--", x_y[SYS_SIZE_X * i + j].value);
            } else {
                printf("%c  ", x_y[SYS_SIZE_X * i + j].value);
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool modify_xy(xy *x_y, int x, int y)
{
    if (x > (SYS_SIZE_X - 1) || y > (SYS_SIZE_Y - 1)) {
        return false;
    }
    for (int i = 0; i < SYS_SIZE_Y * SYS_SIZE_X; i++) {
        if (x_y[i].x == x && x_y[i].y == y) {
            x_y[i].value = 'o';
        }
    }
    return true;
}
/**************************set static link-list*************************************/
#define STATIC_LIST_SIZE 10
typedef struct{
    int data;
    int ex;
    int next;
} mylist;

mylist polynomial[STATIC_LIST_SIZE];

void init_static_list(mylist *slist)
{
    for (int i = 0; i < STATIC_LIST_SIZE; i++) {
        slist[i].next = i + 1;
    }

    slist[0].next = slist[1].next;
    slist[1].next = 0;
    slist[STATIC_LIST_SIZE - 1].next = 0;
}

bool insert_mylist(mylist * slist, int data, int ex)
{
    int space = 0;
    int temp = 1;

    if (slist[0].next == 0) {
        return false;
    }
    space = slist[0].next;
    slist[0].next = slist[space].next;

    slist[space].data = data;
    slist[space].ex = ex;
    slist[space].next = 0;

    while (slist[temp].next) {
        temp = slist[temp].next;
    }

    slist[temp].next = space;


}

void show_mylist(mylist * slist)
{
    for (int i = 0; i < STATIC_LIST_SIZE; i++) {
        printf("data ->%d ex ->%d next ->%d - %d\n", slist[i].data, slist[i].ex, slist[i].next, i);
    }
}

int char_to_int(char *p)
{
    int ret = 0;
    switch (*p)
    {
        case '0': ret = 0; break;
        case '1': ret = 1; break;
        case '2': ret = 2; break;
        case '3': ret = 3; break;
        case '4': ret = 4; break;
        case '5': ret = 5; break;
        case '6': ret = 6; break;
        case '7': ret = 7; break;
        case '8': ret = 8; break;
        case '9': ret = 9; break;
        default: ret = 1; break;
    }
    return ret;
}

void parse_expression(char *str, mylist * slist)
{
    int data = 0, ex = 0;
    char *p = str;
    int i = 0;
    int temp = 1;

    while (*str != '\0') {
        //printf("%c", *str);
        p = str;
        if (*p == 'x') {
            i = 0;
            data = 0;
            temp = 1;
            ex = char_to_int(p + 1);
            p--;
            if (*p == ' ' || *p == '=' || *p == '+' || *p == '-') {
                if (*p == '-') {
                    data = -1;
                } else {
                    data = 1;
                }
            } else {
                while (*p != ' ' && *p != '=') {
                    for (int j = 0; j < i; j++) {
                        temp = temp * 10;
                    }
                    data += char_to_int(p) * temp;
                    i++;
                    p--;
                    if (*p == '+') {
                        data = data;
                        break;
                    }
                    if (*p == '-') {
                        data = -data;
                        break;
                    }
                }
            }
            insert_mylist(slist, data, ex);
        }
        str++;
    }
}

void set_function_to_xy(xy *x_y, mylist * slist)
{
    int i = 1;
    int x = 0, y = 0, temp = 1;
    for (x = 0; x < SYS_SIZE_X; x++) {
        y = 0;
        i = 1;
        while (slist[i].next != 0) {
            i = slist[i].next;
            temp = 1;
            for (int j = 0; j < slist[i].ex; j++) {
                temp = (temp * x);
            }
            //printf("temp = %d, data = %d\n", temp, slist[i].data);
            y += (temp * (slist[i].data));
        }
        printf("(%d, %d)\n", x, y);
        modify_xy(x_y, x, y);
    }
    
    
}

void main(void)
{
    char function[] = "y=-x2+10x";
    printf("\n");
    printf("The function %s graph is:\n", function);
    initCoordinateSystem(xy_system);
    init_static_list(polynomial);

    parse_expression(function, polynomial);
    set_function_to_xy(xy_system, polynomial);

    modify_xy(xy_system, 0, 0); //(0, 0)

    show_xy_system(xy_system);
    show_mylist(polynomial);
}

