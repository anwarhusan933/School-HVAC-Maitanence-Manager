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
    char gander[12];
} school_data;

void show_menu();
void menu_operator(int menu, int min, int max);
void add_records();
void display();
void delete();
int load_records();
void update();
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
        update();
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
    int gander_selection;
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
        return;
    }
    if (!get_phone_number("Enter Watchman number : ", var.mobile_number, sizeof(var.mobile_number)))
    {
        printf("Reading watchman phone number failed!\n");
        return;
    }
    // gander selection
    if (!get_integer("1.Boys\n2.Girls\n3.Unknown\nEnter your choice : ", &gander_selection))
    {
        printf("Reading Selection failed!\n");
        return;
    }
    switch (gander_selection)
    {
    case 1:
        strcpy(var.gander, "Boys");
        break;
    case 2:
        strcpy(var.gander, "Girls");
        break;
    case 3:
        strcpy(var.gander, "Unknown");
        break;
    default:
        printf("Invalid choice. Please enter 1 to 3.\n");
    }

    FILE *fp;
    fp = fopen(RECORD_FILE, "a");
    if (fp == NULL)
    {
        printf("File can't open!\n");
        fclose(fp);
        return;
    }
    fprintf(fp, "%d|%s|%s|%s|%s|%s\n", var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
    printf("Record added Successfully.\n");
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
    if ((fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander)) == EOF)
    {
        printf("File is empty. Please add data befor display.\n");
        return;
    }
    rewind(fp);
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-2c%-7s%-50s%-20s%-20s%-20s%-10s\n", ' ', "SR.NO", "SCHOOL NAME", "MOE ID", "AREA", "PHONE NUMBER", "Gender");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander) == 6)
    {
        printf("%-4c%-5d%-50s%-20s%-20s%-20s%-10s\n", ' ', var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(fp);
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
    if ((fscanf(fp, "%d|%[^|]%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander)) == EOF)
    {
        printf("File is empty. Please add records.\n");
        fclose(fp);
        return 0;
    }
    rewind(fp);
    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander) == 6)
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

    while ((fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander)) == 6)
    {

        if (search_serial == var.serial_number)
        {
            found_status = 1;
            printf("************Founded records************\n");
            printf("%-4c%-5d%-50s%-20s%-20s%-20s%-10s\n", ' ', var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
            printf("Are sure you want to delete?\n");
            printf("1.Confirm\n");
            printf("0.Decline\n");
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
            fprintf(fp1, "%d|%s|%s|%s|%s|%s\n", serial, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
        }
    }
    if (!found_status)
    {
        printf("Records not founded.\n");
    }
    fclose(fp);
    fclose(fp1);
    remove(RECORD_FILE);
    rename(TEMP_FILE, RECORD_FILE);
}
// udate record function
void update()
{
    int serial_number;
    int choice;
    int found_status = 0;
    school_data var;
    printf("1.School name\n");
    printf("2.MOE-ID\n");
    printf("3.Area\n");
    printf("4.Phone Number\n");
    printf("5.Gender\n");
    if (!get_integer("Choose your choice from above list : ", &choice))
    {
        printf("Reading choice failed!\n");
        return;
    }
    FILE *fp, *fp1;
    fp = fopen(RECORD_FILE, "r");
    fp1 = fopen(TEMP_FILE, "w");
    if (fp == NULL || fp1 == NULL)
    {
        printf("File can't open!\n");
        return;
    }

    switch (choice)
    {
        // update school name
    case 1:

        if (!get_integer("Enter Serial number whose you want to change school name : ", &serial_number))
        {
            printf("Reading serial number failed!\n");
            fclose(fp);
            fclose(fp1);
            remove(TEMP_FILE);
            return;
        }

        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander) == 6)
        {
            if (serial_number == var.serial_number)
            {
                found_status = 1;

                printf("\n\n----------Founded records----------\n");
                printf("%-2c%-7s%-50s%-20s%-20s%-20s%-10s\n", ' ', "SR.NO", "SCHOOL NAME", "MOE ID", "AREA", "PHONE NUMBER", "Gender");
                printf("%-4c%-5d%-50s%-20s%-20s%-20s%-10s\n\n", ' ', var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
                if (!get_string("Enter new School name : ", var.school_name, sizeof(var.school_name)))
                {
                    printf("Reading new school name failed.\n");
                    fclose(fp1);
                    fclose(fp);
                    remove(TEMP_FILE);
                    return;
                }
            }
            fprintf(fp1, "%d|%s|%s|%s|%s|%s\n", var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
        }
        fclose(fp);
        fclose(fp1);
        if (!found_status)
        {
            printf("Entered serial not matched to change school name!\n");
            remove(TEMP_FILE);
        }
        else
        {
            remove(RECORD_FILE);
            rename(TEMP_FILE, RECORD_FILE);
            printf("Changed school name successfully.\n");
        }
        break;
        // update moe-id
    case 2:

        if (!get_integer("Enter serial number to change MOE-ID : ", &serial_number))
        {
            printf("Reading serial number failed to change MOE-ID!\n");
            fclose(fp);
            fclose(fp1);
            remove(TEMP_FILE);
            return;
        }
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander) == 6)
        {
            if (serial_number == var.serial_number)
            {
                found_status = 1;
                printf("\n\n----------Founded records----------\n");
                printf("%-2c%-7s%-50s%-20s%-20s%-20s%-10s\n", ' ', "SR.NO", "SCHOOL NAME", "MOE ID", "AREA", "PHONE NUMBER", "Gender");
                printf("%-4c%-5d%-50s%-20s%-20s%-20s%-10s\n\n", ' ', var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
                if (!get_string("Enter new MOE-ID number : ", var.moe_id, sizeof(var.moe_id)))
                {

                    printf("Reading new MOE-ID failed!\n");
                    fclose(fp);
                    fclose(fp1);
                    remove(TEMP_FILE);
                    return;
                }
            }
            fprintf(fp1, "%d|%s|%s|%s|%s|%s\n", var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
        }

        fclose(fp);
        fclose(fp1);
        if (!found_status)
        {
            printf("Entered serial number not matched to change MOE-ID!\n");
            remove(TEMP_FILE);
        }
        else
        {
            remove(RECORD_FILE);
            rename(TEMP_FILE, RECORD_FILE);
            printf("Changed MEO-ID Successfully.\n");
        }
        break;
        // update area name
    case 3:

        if (!get_integer("Enter serial number whose you want to change area name: ", &serial_number))
        {
            printf("Reading area name failed!\n");
            fclose(fp);
            fclose(fp1);
            remove(TEMP_FILE);
            return;
        }
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander) == 6)
        {
            if (serial_number == var.serial_number)
            {
                found_status = 1;
                printf("\n\n----------Founded records----------\n");
                printf("%-2c%-7s%-50s%-20s%-20s%-20s%-10s\n", ' ', "SR.NO", "SCHOOL NAME", "MOE ID", "AREA", "PHONE NUMBER", "Gender");
                printf("%-4c%-5d%-50s%-20s%-20s%-20s%-10s\n\n", ' ', var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
                if (!get_string("Enter new Area name : ", var.area, sizeof(var.area)))
                {
                    printf("Reading new area name failed!\n");
                    fclose(fp);
                    fclose(fp1);
                    remove(TEMP_FILE);
                    return;
                }
            }
            fprintf(fp1, "%d|%s|%s|%s|%s|%s\n", var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
        }
        fclose(fp);
        fclose(fp1);
        if (!found_status)
        {
            printf("Entered serial number not matched to upadate!\n");
            remove(TEMP_FILE);
        }
        else
        {
            remove(RECORD_FILE);
            rename(TEMP_FILE, RECORD_FILE);
            printf("Changed area name Successfully.\n");
        }

        break;
        // update Phone number
    case 4:

        if (!get_integer("Enter serial number whose you want to change mobile number : ", &serial_number))
        {
            printf("Reading mobile number failed!\n");
            fclose(fp);
            fclose(fp1);
            remove(TEMP_FILE);
            return;
        }
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander) == 6)
        {
            if (serial_number == var.serial_number)
            {
                found_status = 1;
                printf("\n\n----------Founded records----------\n");
                printf("%-2c%-7s%-50s%-20s%-20s%-20s%-10s\n", ' ', "SR.NO", "SCHOOL NAME", "MOE ID", "AREA", "PHONE NUMBER", "Gender");
                printf("%-4c%-5d%-50s%-20s%-20s%-20s%-10s\n\n", ' ', var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
                if (!get_string("Enter new phone number : ", var.mobile_number, sizeof(var.mobile_number)))
                {
                    printf("Reading new phone number failed!\n");
                    fclose(fp);
                    fclose(fp1);
                    remove(TEMP_FILE);
                    return;
                }
            }
            fprintf(fp1, "%d|%s|%s|%s|%s|%s\n", var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
        }
        fclose(fp);
        fclose(fp1);
        if (!found_status)
        {
            printf("Entered serial number not matched to upadate phone number!\n");
            remove(TEMP_FILE);
        }
        else
        {
            remove(RECORD_FILE);
            rename(TEMP_FILE, RECORD_FILE);
            printf("Changed phone number Successfully.\n");
        }

        break;
        // update gender
    case 5:

        if (!get_integer("Enter serial number whose you want to change gender : ", &serial_number))
        {
            printf("Reading mobile number failed!\n");
            fclose(fp);
            fclose(fp1);
            remove(TEMP_FILE);
            return;
        }
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", &var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander) == 6)
        {
            if (serial_number == var.serial_number)
            {
                found_status = 1;
                int choice;
                printf("\n\n----------Founded records----------\n");
                printf("%-2c%-7s%-50s%-20s%-20s%-20s%-10s\n", ' ', "SR.NO", "SCHOOL NAME", "MOE ID", "AREA", "PHONE NUMBER", "Gender");
                printf("%-4c%-5d%-50s%-20s%-20s%-20s%-10s\n\n", ' ', var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
                printf("\n\nSelect new gender\n");
                printf("1.Boys\n2.Girls\n3.Unknown\n");
                if (!get_integer("Enter your selection from above list : ", &choice))
                {
                    printf("Gender selection failed!\n");
                    fclose(fp);
                    fclose(fp1);
                    remove(TEMP_FILE);
                    return;
                }
                switch (choice)
                {
                case 1:
                    strcpy(var.gander, "Boys");
                    break;
                case 2:
                    strcpy(var.gander, "Girls");
                    break;
                case 3:
                    strcpy(var.gander, "Unknown");
                    break;
                default:
                    printf("Invalid Choice. Please enter from 1 to 3.\n");
                }
            }
            fprintf(fp1, "%d|%s|%s|%s|%s|%s\n", var.serial_number, var.school_name, var.moe_id, var.area, var.mobile_number, var.gander);
        }
        fclose(fp);
        fclose(fp1);

        if (!found_status)
        {
            printf("Entered serial number not matched to change Gender type!\n");
            remove(TEMP_FILE);
        }
        else
        {
            remove(RECORD_FILE);
            rename(TEMP_FILE, RECORD_FILE);
            printf("Changed gender Successfully.\n");
        }

        break;
    }
}
