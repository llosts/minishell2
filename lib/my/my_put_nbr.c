/*
** EPITECH PROJECT, 2024
** my_put_nbr
** File description:
** print a number
*/

#include <unistd.h>

#include "my.h"

int my_put_nbr(int nb)
{
    if (nb == -2147483648) {
        write(1, "-2147483648", 11);
        return 0;
    }
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb > 9) {
        my_put_nbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
    return 0;
}
