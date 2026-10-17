#include <stdio.h>

int main() {
    double result = 1.0, x = 1/3.0, PI = 3.141592653589793, num_term = 4.0 * x * x, pi_squared = PI * PI, s_val = 0.0;
    int i = 1, n, op_count;

    printf("Введіть значення n: ");
    scanf("%d", &n);

    op_count = 12; 
    
    if (n > 0) {
        while (i <= n) {
            s_val += (4.0 * i - 1.0);
            result *= (1.0 - num_term / (pi_squared * s_val));
            i++;
            op_count += 11;
        }
        op_count += 1;
        
        printf("Значення P:  %.7f\n", result);
        printf("Кількість виконаних операцій: %d\n", op_count);
    }
    else {
        printf("n is invalid\n");
    }
    
    return 0;
}