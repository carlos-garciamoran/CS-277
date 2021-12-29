#include <stdio.h>


int main()
{
    unsigned char uc = 0b00000101U;
    char sc = 0b00000101;
    unsigned char uc2 = 0b11111111U;
    char sc2 = 0b11111111;
    char sc3 = 0b01100001;

    char *p1 = 1000;    char *pp1 = p1+1;

    long *p2 = 1000;    long *pp2 = p2+1;

    char s[10] = "abcdefghij";
    char *sp1 = s;      char *sp2 = s;

    char c1 = 0xCC;     char c2 = 0x7E;


    printf("h = %d\n", 0x80108AB0);
    puts("");

    printf("b1 = 0x%x\n", 0b10110100010011000000111011010101);
    printf("b2 = 0x%x\n", 0b11101101110000100000000011111101);
    puts("");

    printf("uc = %d\n", uc);
    printf("sc = %d\n", sc);

    printf("uc2 = %d\n", uc2);
    printf("sc2 = %d\n", sc2);
    puts("");

    printf("sc3 = %c\n", sc3);
    puts("");

    printf("%d -> %d\n", p1, pp1);
    printf("%ld -> %ld\n", p2, pp2);
    puts("");

    printf("%s -> %d\n", s, *sp1++);
    printf("%s -> %d\n", s, *++sp2);
    puts("");

    printf("0x%x ^ 0x%x -> %d\n", c1, c1, c1^c1);
    printf("0x%x ^ 0x%x -> %d\n", c2, c2, c2^c2);
    puts("");

    printf("0x%x\n", ~0X7EDCBA98);
    printf("0x%x\n", (0X55234555 >> 12) & 0X1FFF);
    printf("0x%x\n", 0X55234555 & ~0X01FFF000);
    printf("0x%x\n", (0X55555555 & (~(0XFFFF << 8))) | (0X9889 << 8));

    return 0;
}