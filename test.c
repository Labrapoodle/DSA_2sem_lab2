#include <stdio.h>
#include <string.h>

int main()
{
    char s[] = "Hana";
    printf("%d\n", strlen(s));
    s[3] = '\0';
    printf("%d\n", strlen(s));
    printf("%c\n", *s);

    return 0;
}
