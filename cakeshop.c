#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CAKES 100
#define MAX_NAME 50

struct Cake {
    int id;
    char name[MAX_NAME];
    int price;
};

struct Cake cakes[MAX_CAKES] = {
    {1, "Chocolate Cake", 500},
    {2, "Vanilla Cake", 400},
    {3, "Black Forest Cake", 600},
    {4, "Red Velvet Cake", 700},
    {5, "Pineapple Cake", 450},
    {6, "Dutch Truffel", 750},
    {7, "Chocolava Cake", 100}
};

int cake_count = 7;

void viewCakes();
void addCake();
void searchCake();
void updateCake();
void deleteCake();
void generateBill();

int findCake(int id);

int main()
{
    int choice;

    while (1)
    {
        printf("\n===================================\n");
        printf("             WELCOME\n");
        printf("                TO\n");
        printf("         MR.RAJ CAKE SHOP\n");
        printf("===================================\n");

        printf("\n========== MAIN MENU ==========\n");
        printf("1. View Cake Menu\n");
        printf("2. Add New Cake\n");
        printf("3. Search Cake\n");
        printf("4. Update Cake Details\n");
        printf("5. Delete Cake\n");
        printf("6. Generate Customer Bill\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                viewCakes();
                break;

            case 2:
                addCake();
                break;

            case 3:
                searchCake();
                break;

            case 4:
                updateCake();
                break;

            case 5:
                deleteCake();
                break;

            case 6:
                generateBill();
                break;

            case 7:
                printf("\nThank You for Visiting Cake Shop!\n");
                printf("Application Closed.\n");
                return 0;

            default:
                printf("\nInvalid Choice! Please Try Again.\n");
        }
    }
}

// Find cake using ID
int findCake(int id)
{
    int i;

    for (i = 0; i < cake_count; i++)
    {
        if (cakes[i].id == id)
            return i;
    }

    return -1;
}

// 1. View Cake Menu
void viewCakes()
{
    int i;

    printf("\n========== CAKE MENU ==========\n");
    printf("-----------------------------------\n");

    for (i = 0; i < cake_count; i++)
    {
        printf("Cake ID: %d\n", cakes[i].id);
        printf("Cake Name: %s\n", cakes[i].name);
        printf("Price: Rs. %d\n", cakes[i].price);
        printf("-----------------------------------\n");
    }
}

void addCake()
{
    int id, price;
    char name[MAX_NAME];

    printf("\n========== ADD NEW CAKE ==========\n");

    if (cake_count >= MAX_CAKES)
    {
        printf("Cake storage is full!\n");
        return;
    }

    id = 1;

    while (findCake(id) != -1)
        id++;

    printf("Enter Cake Name: ");
    scanf(" %49[^\n]", name);

    printf("Enter Cake Price: ");
    if (scanf("%d", &price) != 1)
    {
        printf("Please enter a valid price!\n");
        return;
    }

    if (strlen(name) == 0 || price <= 0)
    {
        printf("Please enter a valid name and price!\n");
        return;
    }

    cakes[cake_count].id = id;
    strcpy(cakes[cake_count].name, name);
    cakes[cake_count].price = price;

    cake_count++;

    printf("\nCake Added Successfully!\n");
    printf("Cake ID: %d\n", id);
}

void searchCake()
{
    char name[MAX_NAME];
    int i, found = 0;

    printf("\n========== SEARCH CAKE ==========\n");

    printf("Enter Cake Name: ");
    scanf(" %49[^\n]", name);

    for (i = 0; i < cake_count; i++)
    {
        if (strcmp(cakes[i].name, name) == 0)
        {
            printf("\nCake Found!\n");
            printf("Cake ID: %d\n", cakes[i].id);
            printf("Cake Name: %s\n", cakes[i].name);
            printf("Price: Rs. %d\n", cakes[i].price);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Cake Not Found!\n");
}

void updateCake()
{
    int id, index, price;
    char name[MAX_NAME];

    printf("\n========== UPDATE CAKE ==========\n");

    printf("Enter Cake ID: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Please enter valid details!\n");
        return;
    }

    index = findCake(id);

    if (index != -1)
    {
        printf("Current Name: %s\n", cakes[index].name);
        printf("Current Price: %d\n", cakes[index].price);

        printf("Enter New Cake Name: ");
        scanf(" %49[^\n]", name);

        printf("Enter New Price: ");

        if (scanf("%d", &price) != 1)
        {
            printf("Please enter valid details!\n");
            return;
        }

        if (strlen(name) > 0 && price > 0)
        {
            strcpy(cakes[index].name, name);
            cakes[index].price = price;

            printf("Cake Details Updated Successfully!\n");
        }
        else
        {
            printf("Invalid Name or Price!\n");
        }
    }
    else
    {
        printf("Cake ID Not Found!\n");
    }
}

void deleteCake()
{
    int id, index, i;
    char confirm[10];

    printf("\n========== DELETE CAKE ==========\n");

    printf("Enter Cake ID: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Please enter a valid Cake ID!\n");
        return;
    }

    index = findCake(id);

    if (index != -1)
    {
        printf("Cake Name: %s\n", cakes[index].name);

        printf("Are you sure? (yes/no): ");
        scanf("%9s", confirm);

        if (strcmp(confirm, "yes") == 0)
        {
            for (i = index; i < cake_count - 1; i++)
            {
                cakes[i] = cakes[i + 1];
            }

            cake_count--;

            printf("Cake Deleted Successfully!\n");
        }
        else
        {
            printf("Delete Cancelled!\n");
        }
    }
    else
    {
        printf("Cake ID Not Found!\n");
    }
}

void generateBill()
{
    char customer[MAX_NAME];
    char purchased_names[100][MAX_NAME];

    int purchased_prices[100];
    int quantities[100];
    int amounts[100];

    int cake_id, quantity;
    int index, count = 0;
    int i, bill = 0;

    printf("\n========== GENERATE CUSTOMER BILL ==========\n");

    printf("Enter Customer Name: ");
    scanf(" %49[^\n]", customer);

    while (1)
    {
        printf("\nEnter Cake ID (0 to finish): ");

        if (scanf("%d", &cake_id) != 1)
        {
            printf("Please enter valid numbers!\n");
            return;
        }

        if (cake_id == 0)
            break;

        index = findCake(cake_id);

        if (index != -1)
        {
            if (count >= 100)
            {
                printf("Bill item limit reached!\n");
                break;
            }

            printf("Enter Quantity: ");

            if (scanf("%d", &quantity) != 1)
            {
                printf("Please enter valid numbers!\n");
                return;
            }

            if (quantity <= 0)
            {
                printf("Invalid Quantity!\n");
                continue;
            }

            strcpy(purchased_names[count],
                   cakes[index].name);

            purchased_prices[count] =
                   cakes[index].price;

            quantities[count] = quantity;

            amounts[count] =
                   purchased_prices[count] * quantity;

            bill += amounts[count];

            count++;

            printf("Cake Added To Bill!\n");
        }
        else
        {
            printf("Invalid Cake ID!\n");
        }
    }

    printf("\n====================================================\n");
    printf("                  CUSTOMER BILL\n");
    printf("====================================================\n");

    printf("Customer Name: %s\n", customer);

    printf("----------------------------------------------------\n");

    printf("%-20s %-10s %-8s %-10s\n",
           "Cake Name", "Price", "Qty", "Amount");

    printf("----------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        printf("%-20s Rs.%-7d %-8d Rs.%-10d\n",
               purchased_names[i],
               purchased_prices[i],
               quantities[i],
               amounts[i]);
    }

    printf("----------------------------------------------------\n");

    printf("TOTAL AMOUNT: Rs. %d\n", bill);

    printf("====================================================\n");
    printf("             THANK YOU! VISIT AGAIN!\n");
    printf("====================================================\n");
}
