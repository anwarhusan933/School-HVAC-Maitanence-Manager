#include <stdio.h>
#include "Input_validation.h"
void show_menu();
void menu_operator(int menu,int min,int max);
int main()
{
    show_menu();
    return 0;
}
void show_menu()
{
    int choice,min,max;
    min = 0;
    max = 5;

    do
    {
        printf("\n--------------------------------------------------\n");
        printf("%40s", "Welcome School Maintenance Manager");
        printf("\n--------------------------------------------------\n");
        printf("1.Add Record\n");
        printf("2.Display Record\n");
        printf("3.Delete Record\n");
        printf("4.Update Record\n");
        printf("5.Search Record\n");
        printf("0.Exit\n");
        choice = get_integer("Enter your choice : ");
        if(choice == -1)
        {
            printf("Maximum number of input attempts reached.\n");
            continue;
        }
        else
        {
            menu_operator(choice,min,max);
        }

    } while (choice != 0);
}

void menu_operator(int menue_choice,int min,int max)
{
    switch (menue_choice)
    {
    case 1:
        printf("Add reocrd\n");
        break;
    case 2:
        printf("Display \n");
        break;
    case 3:
        printf("delete\n");
        break;
    case 4:
        printf("Update\n");
        break;
    case 5:
        printf("search\n");
        break;
    case 0:
        printf("Exiting....\n");
        break;
    default:
        printf("Invalid input. Please enter between %d to %d.\n",min,max);
    }
}