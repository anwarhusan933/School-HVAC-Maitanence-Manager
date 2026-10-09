#include<stdio.h>
#include "Input_validation.h"
void show_menu();
void menu_operator();
int main()
{
    show_menu();
    return 0;
}
void show_menu()
{
    int choice;
    printf("\n--------------------------------------------------\n");
    printf("%40s","Welcome School Maintenance Manager");
    printf("\n--------------------------------------------------\n");
    printf("1.Add Record\n");
    printf("2.Display Record\n");
    printf("3.Delete Record\n");
    printf("4.Update Record\n");
    printf("5.Search Record\n");
    choice = read_integer("Enter your choice : ");
    printf("You have enter %d.",choice);
}

void menu_operator();