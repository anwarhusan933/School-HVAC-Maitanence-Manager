#include <stdio.h>
#include "validator.h"
#define SCHOOL_NAME_LEN 200
#define MOE_ID_LEN 15
#define AREA_LEN 127
#define WATCH_MAN_NUMBER 14
#define MOBILE_NUMBER_LEN 14
#define START_MENU_NUMBER 0
#define END_MENU_NUMBER 5
#define RECORD_FILE "record.txt"
#define TEMP_FILE "temp_file.txt"
typedef struct school_record
{
    int serial_number;
    char school_name[SCHOOL_NAME_LEN];
    char moe_id[MOE_ID_LEN];
    char area[AREA_LEN];
    char mobile_number[MOBILE_NUMBER_LEN];
} school_data;

void show_menu();
void menu_operator(int menu, int min, int max);
void add_records();
void display();
void delete();
int load_records();
int main()
{
    show_menu();
    return 0;
}
void show_menu()
{
    int choice, min, max;
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
        get_integer("Please enter your choice : ", &choice);
        menu_operator(choice, START_MENU_NUMBER, END_MENU_NUMBER);
    } while (choice != 0);
}

void menu_operator(int menue_choice, int min, int max)
{
    switch (menue_choice)
    {
    case 1:
        add_records();
        break;
    case 2:
        display();
        break;
    case 3:
        delete();
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
        printf("Invalid input. Please enter between %d to %d.\n", min, max);
    }
}

void add_records()
{
    school_data var;
    // if(!get_integer("Enter serial number : ",&var.serial_number))
    // {
    //     printf("Reading failed serial numbe!\n");
    //     return;
    // }
    var.serial_number = load_records();
    var.serial_number++;
    if (!get_string("Enter school name : ", var.school_name, sizeof(var.school_name)))
    {
        printf("Reading school name failed!\n");
        return;
    }
    if (!get_string("Enter MOE id : ", var.moe_id, sizeof(var.moe_id)))
    {
        printf("Reading MOE id failed!\n");
        return;
    }
    if (!get_string("Enter Area name : ", var.area, sizeof(var.area)))
    {
        printf("Reading area name failed!\n");
    }
    if (!get_phone_number("Enter Watchman number : ", var.mobile_number, sizeof(var.mobile_number)))
    {
        printf("Reading watchman phone number failed!\n");
    }
    FILE *fp;
    fp = fopen(RECORD_FILE, "a");
    if (fp == NULL)
    {
        printf("File can't open!\n");
        fclose(fp);
        return;
    }
    fprintf(fp, "%d|%s|%s|%s|%s\n", var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number);
    fclose(fp);
}

// display function
void display()
{

    school_data var;
    FILE *fp;
    fp = fopen(RECORD_FILE, "r");
    if (fp == NULL)
    {
        printf("File can't open!\n");
        fclose(fp);
        return;
    }
    if ((fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number)) == EOF)
    {
        printf("File is empty. Please add data befor display.\n");
        return;
    }
    rewind(fp);
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("%-2c%-7s%-50s%-20s%-20s%-20s\n", ' ', "SR.NO", "SCHOOL NAME", "MOE ID", "AREA", "PHONE NUMBER");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number) == 5)
    {
        printf("%-4c%-5d%-50s%-20s%-20s%-20s\n", ' ', var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number);
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");
    fclose(fp);
    int total_records = load_records();
    printf("Total records : %d", total_records);
}

int load_records()
{
    int record_count = 0;
    school_data var;
    FILE *fp;
    fp = fopen(RECORD_FILE, "r");
    if (fp == NULL)
    {
        printf("File opening failed!\n");
        fclose(fp);
        return 0;
    }
    if ((fscanf(fp, "%d|%[^|]%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number)) == EOF)
    {
        printf("File is empty. Please add records.\n");
        fclose(fp);
        return 0;
    }
    rewind(fp);
    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number) == 5)
    {
        record_count++;
    }
    fclose(fp);
    return record_count;
}

// delete function
void delete()
{
    school_data var;
    if (load_records() == 0)
    {
        printf("File is empty.\n");
        return;
    }
    int serial = 0;
    int search_serial;
    int found_status = 0;
    FILE *fp = fopen(RECORD_FILE, "r");
    if (fp == NULL)
    {
        printf("File opening failed!\n");
        return;
    }
    if (!get_integer("Enter serial number you want to delete : ", &search_serial))
    {
        printf("Reading serial number failed!\n");
        fclose(fp);
        return;
    }

    FILE *fp1;
    fp1 = fopen(TEMP_FILE, "w");
    if (fp1 == NULL)
    {
        printf("File opening failed!\n");
        fclose(fp);
        remove(TEMP_FILE);
        return;
    }

    while ((fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number)) == 5)
    {

        // printf("I am in reading data from file\n");
        if (search_serial == var.serial_number)
        {
            found_status = 1;
            printf("Founded records.\n");
            printf("%-4c%-5d%-50s%-20s%-20s%-20s\n", ' ', var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number);
            printf("Are sure you want to delete?\n");
            printf("1.Confirm\n");
            printf("0.Decline");
            int choice;
            if (!get_integer("Please enter your choice : ", &choice))
            {
                printf("Reading choice failed!\n");
                fclose(fp);
                fclose(fp1);
                remove(TEMP_FILE);
                return;
            }
            if (choice == 1)
            {
                printf("Record deleted successfully.\n");
                continue;
            }
            else
            {

                printf("Declined.\n");
                fclose(fp1);
                fclose(fp);
                remove(TEMP_FILE);
                return;
            }
        }
        else
        {
            serial++;
            fprintf(fp1, "%d|%s|%s|%s|%s\n", serial, var.school_name, var.moe_id, var.area, var.mobile_number);
        }
    }
    if(!found_status)
    {
        printf("Records not founded.\n");
    }
    fclose(fp);
    fclose(fp1);
    remove(RECORD_FILE);
    rename(TEMP_FILE, RECORD_FILE);
}