#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "double_stack.h"

#define OPERATOR "+-*/^~"
#define UNARY_OPERATOR "sctgql"
#define PI 3.141592

int priority(char chr);
void create_postfix(char* input, char* output);
double execute(double a, double b, char op);
double calculate(char* postfix);
void switch_x(char* postfix, double x, char* result);
void graph(char* postfix);

int main() {
    char input[50];
    fgets(input, 50, stdin);
    int k = 0;
    while (input[k] != '\n')
        k++;
    input[k] = '\0';
    char output[50];
    create_postfix(input, output);
    puts(input);
    puts(output);
    graph(output);
    return 0;
}
void graph(char* postfix) { // Процедура отрисовки графика
    double dx = (PI * 4) / 79;
    double x = 0;
    double dy = 2.0 / 24;
    double y = 1;
    for (int i = 0; i < 25; i++) {
        dx = (PI * 4) / 80;
        x = 0;
        for (int j = 0; j < 85; j++) {
            char res[20];
            switch_x(postfix, x, res); // Замена Х на число в строке
            double X = calculate(res); // Подсчер значения в точке
            if ((X <= (y + dy)) && X >= (y - dy))
                printf("*");
            else
                printf(".");
            x += dx;
        }
        printf("\n");
        y -= dy;
    }
}
void switch_x(char* postfix, double x, char* result) { // Процедура меняет Х на число в строке
    int k = 0;
    for (unsigned long i = 0; i < strlen(postfix); i++) {
        if (postfix[i] == 'x') {
            char num[20];
            sprintf(num, "%.5f", x);
            for (unsigned long j = 0; j < strlen(num); j++) {
                result[k] = num[j];
                k++;
            }
        } else {
            result[k] = postfix[i];
            k++;
        }
    }
    result[k] = '\0';
}
void create_postfix(char* input, char* output) { // Создание постфиксной записи
    int k = 0;
    node* root = init(0);
    for (unsigned long i = 0; i < strlen(input); i++) {
        if (input[i] == 'x' || (input[i] <= '9' && input[i] >= '0')) { // Если операнд
            while (input[i] == 'x' || (input[i] <= '9' && input[i] >= '0')) {
                output[k] = input[i];
                i++;
                k++;
            }
            output[k] = ' ';
            k++;
        }
        if (input[i] == '(')
            root = push(root, input[i]);
        if (input[i] == ')') {
            while(root) {
                if (root->num == '(')
                    break;
                output[k] = root->num;
                root = pop(root);
                k++;
            }
            root = pop(root);
        }
        if (strchr(OPERATOR, input[i])) { // Если простой оператор
            if (input[i] == '-' && i == 0)
                input[i] = '~';
            if (input[i] == '-' && input[i - 1] == '(')
                input[i] = '~';
            while (priority(input[i]) < priority(root->num)) {
                output[k] = root->num;
                root = pop(root);
                k++;
            }
            root = push(root, input[i]);
            continue;
        }
        if (strchr(UNARY_OPERATOR, input[i])) { // Если сложный оператор
            if (input[i] == 's' && input[i + 1] == 'i') { // Если синус
                while (priority('s') < priority(root->num)) {
                    output[k] = root->num;
                    root = pop(root);
                    k++;
                }
                root = push(root, 's');
            }
            if (input[i] == 'c' && input[i + 1] == 'o') {  // Если косинус
                while (priority('c') < priority(root->num)) {
                    output[k] = root->num;
                    root = pop(root);
                    k++;
                }
                root = push(root, 'c');
            }
            if (input[i] == 't') { // Если таннгентс
                while (priority('t') < priority(root->num)) {
                    output[k] = root->num;
                    root = pop(root);
                    k++;
                }
                root = push(root, 't');
            }
            if (input[i] == 'c' && input[i + 1] == 't') { // Если котангентс
                while (priority('g') < priority(root->num)) {
                    output[k] = root->num;
                    root = pop(root);
                    k++;
                }
                root = push(root, 'g');
            }
            if (input[i] == 's' && input[i + 1] == 'q') { // Если квадратный корень
                while (priority('q') < priority(root->num)) {
                    output[k] = root->num;
                    root = pop(root);
                    k++;
                }
                root = push(root, 'q');
            }
            if (input[i] == 'l') { // Если натуральный логарифм
                while (priority('l') < priority(root->num)) {
                    output[k] = root->num;
                    root = pop(root);
                    k++;
                }
                root = push(root, 'l');
            }
            while (input[i] <= 122 && input[i] >= 97)
                i++;
            i--;
        }
    }
    while (root) {
        output[k] = root->num;
        root = pop(root);
        k++;
    }
    output[k] = '\0';
    destroy(root);
}

int priority(char chr) { // Функция возвращает приоритет операции
    int result = 0;
    switch (chr) {
        case '(':
            result = 0;
            break;
        case '+':
            result = 1;
            break;
        case '-':
            result = 1;
            break;
        case '~':
            result = 1;
            break;
        case '*':
            result = 2;
            break;
        case '/':
            result = 2;
            break;
        case '^':
            result = 2;
            break;
        case 's':
            result = 3;
            break;
        case 'c':
            result = 3;
            break;
        case 't':
            result = 3;
            break;
        case 'g':
            result = 3;
            break;
        case 'q':
            result = 3;
            break;
        case 'l':
            result = 3;
            break;
        default:
            break;
    }
    return result;
}
double execute(double a, double b, char op) { // Функция считает
    double result = 0;
    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '^':
            result = pow(a, b);
            break;
        case 's':
            result = sin(a);
            break;
        case 'c':
            result = cos(a);
            break;
        case 't':
            result = tan(a);
            break;
        case 'g':
            result = (tan((PI / 2 - a)) * (-1));
            break;
        case 'q':
            result = sqrt(a);
            break;
        case 'l':
            result = log(a);
            break;
        default:
            break;
    }
    return result;
}
double calculate(char* postfix) { // Подсчет выражения
    d_node* root = d_init(0);
    for (unsigned long i = 0; i < strlen(postfix); i++) {
        if ((postfix[i] <= '9' && postfix[i] >= '0') || postfix[i] == '.') { // Если операнд
            char num[20];
            int k = 0;
            while ((postfix[i] <= '9' && postfix[i] >= '0') || postfix[i] == '.') {
                num[k] = postfix[i];
                k++;
                i++;
            }
            double d_num = atof(num);
            root = d_push(root, d_num);
            continue;
        }
        if (postfix[i] == '~') { // Если унарный минус
            double a = root->num;
            root = d_pop(root);
            root = d_push(root, execute(0, a, '-'));
        }
        if (strchr(UNARY_OPERATOR, postfix[i])) { // Если сложный оператор
            double a = root->num;
            root = d_pop(root);
            root = d_push(root, execute(a, 0, postfix[i]));
        }
        if (strchr(OPERATOR, postfix[i])) { // Если оператор
            double a = root->num;
            root = d_pop(root);
            double b = root->num;
            root = d_pop(root);
            root = d_push(root, execute(b, a, postfix[i]));
        }
        
    }
    double result = 0;
    result = root->num;
    d_destroy(root);
    return result;
}
