#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BLUE "\033[34m"

struct node {
    int data;
    char foodname[50];
    float price;
    struct node* next;
};
struct Developer {
    char name[50];
    int age;
    char edu[100];
    char info[100];
    char skill[100];
};
struct node* heada = NULL;
struct node* headc = NULL;
struct node* createAdmin(struct node* head, int data, char foodname[], float price);
struct node* deleteAdmin(struct node* head, int data);
struct node* createCustomer(struct node* head, int data, char foodname[], float price);
struct node* deleteCustomer(struct node* head, int data);
void adminMenu();
void customerMenu();
void logActivity(const char* activity, int clearLog);
void view(struct node* head);
void orderMenu();
void paymentMethod(float bill);
void viewActivities();
void freeMenu(struct node* head);
void mainMenu();
float calculateTotalBill();
float totalSales = 0.0;

void developerInfo() {
    clear();
    struct Developer m[4];


    strcpy(m[0].name, "Aritra Das");
    strcpy(m[0].edu, "BS.c in (SWE) at Daffodil International University.");
    strcpy(m[0].info, "ID : 232-35-444, Section : E, Batch: 41.");
    strcpy(m[0].skill, "Project Lead, Language : C, Java.");

    strcpy(m[1].name, "Ahammad Ullah");
    strcpy(m[1].edu, "BS.c in (SWE) at Daffodil International University.");
    strcpy(m[1].info, "ID : 232-35-386, Section : E, Batch: 41.");
    strcpy(m[1].skill, "Backend & Frontend Expert, Language : C, Java.");

    strcpy(m[2].name, "Rakib Hasan");
    strcpy(m[2].edu, "BS.c in (SWE) at Daffodil International University.");
    strcpy(m[2].info, "ID : 232-35-164, Section : E, Batch: 41.");
    strcpy(m[2].skill, "Resource Manager, Language : C, Java.");

    strcpy(m[3].name, "Rupok hossain");
    strcpy(m[3].edu, "BS.c in (SWE) at Daffodil International University.");
    strcpy(m[3].info, "ID : 232-35-143, Section : E, Batch: 41.");
    strcpy(m[3].skill, "Project Analyst, Language : C, Java.");

    const char *reset = "\033[0m";
    const char *headerColor = "\033[1;36m";
    const char *textColor = "\033[0;32m";
    const char *highlightColor = "\033[1;33m";

    for (int i = 0; i < 4; i++) {
        printf("\n\n\t\t\t\t\t\t\t%s+--------------------------------------------------------------+%s\n", headerColor, reset);
        printf("\t\t\t\t\t\t\t|%-24s %-36s |\n", " ", "Developer");
        printf("\t\t\t\t\t\t\t%s+--------------------------------------------------------------+%s\n", headerColor, reset);
        printf("\t\t\t\t\t\t\t%s+--------------------------------------------------------------+%s\n", headerColor, reset);
        printf("\t\t\t\t\t\t\t| %sName: %-54s%s |\n", highlightColor, m[i].name, reset);
        printf("\t\t\t\t\t\t\t| %s%-60s%s |\n", textColor, m[i].edu, reset);
        printf("\t\t\t\t\t\t\t| %s%-60s%s |\n", textColor, m[i].info, reset);
        printf("\t\t\t\t\t\t\t| %s%-60s%s |\n", textColor, m[i].skill, reset);

        printf("\t\t\t\t\t\t\t%s+--------------------------------------------------------------+%s\n", headerColor, reset);
        }
        printf("\n\n");
        printf("\t\t\t\t\t\t\t" CYAN "******** About This Project ********" RESET "\n\n");
        printf("\t\t\t\t\t\t\tWelcome to the Deowan Hotel & Restaurant Management System.\n");
        printf("\t\t\t\t\t\t\tThis software is designed to streamline the management\n");
        printf("\t\t\t\t\t\t\tof hotel and restaurant operations, providing features\n");
        printf("\t\t\t\t\t\t\tfor both administrators and customers.\n\n");

        printf("\t\t\t\t\t\t\t" YELLOW "Developed by:" RESET "\n");
        printf("\t\t\t\t\t\t\tCompany: WhichCol Ltd.\n");
        printf("\t\t\t\t\t\t\tContact: which.col@bd.org\n");
        printf("\t\t\t\t\t\t\tVersion: 1.1.3\n\n");

        printf("\t\t\t\t\t\t\t"CYAN"Special Features:"RESET"\n");
        printf("\t\t\t\t\t\t\t- Admin module for Restaurant management\n");
        printf("\t\t\t\t\t\t\t- Customer module for order and payment\n");
        printf("\t\t\t\t\t\t\t- Secure authentication system\n");
        printf("\t\t\t\t\t\t\t- Easy to track Log Activities\n\n");

        printf("\t\t\t\t\t\t\tThank you for choosing our software!\n\n");

}

void logActivity(const char* activity, int clearLog) {
    FILE* file = fopen("activities.log", "a");
    if (file == NULL) {
        perror("\n\t\t\t\t\t\t\t" RED "Failed to open activity log!" RESET);
        return;
    }
    if (clearLog) {
        if (freopen("activities.log", "w", file) == NULL) {
            printf("\n\t\t\t\t\t\t\t" RED "Failed to clear activity log!" RESET "\n");
            fclose(file);
            return;
        }
        printf("\n\t\t\t\t\t\t\t" YELLOW "Activity log cleared." RESET "\n");
    }
    time_t now = time(NULL);
    struct tm* local = localtime(&now);

    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", local);

    fprintf(file, "%s %s\n", timestamp, activity);

    fclose(file);

    if (clearLog) {
        printf("\n\t\t\t\t\t\t\t" MAGENTA "Log cleared at %s" RESET "\n", timestamp);
    }
}
void adminMenu() {
    clear();
    int choice;
    while (1) {
        printf("\n\t\t\t\t\t\t\t" MAGENTA "***** ADMIN MENU *****" RESET "\n\n");
        printf("\t\t\t\t\t\t\t1. Total Sales\n");
        printf("\t\t\t\t\t\t\t2. Add Item\n");
        printf("\t\t\t\t\t\t\t3. Delete Item\n");
        printf("\t\t\t\t\t\t\t4. View Items\n");
        printf("\t\t\t\t\t\t\t5. View Activity Log\n");
        printf("\t\t\t\t\t\t\t6. Exit\n\n");
        printf("\t\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clear();
                printf("\n\t\t\t\t\t\t\t" YELLOW "Total Sales: Tk. %.2f" RESET "\n", totalSales);
                break;
            case 2: {
                int id;
                char name[50];
                float price;

                printf("\n\t\t\t\t\t\t\tEnter food ID: ");
                scanf("%d", &id);
                printf("\t\t\t\t\t\t\tEnter food name: ");
                getchar();
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f", &price);
                heada = createAdmin(heada, id, name, price);
                printf("\n\t\t\t\t\t\t\t" GREEN "Item added successfully!" RESET "\n");
                break;
            }
            case 3: {
                int id;
                printf("\n\t\t\t\t\t\t\tEnter food ID to delete: ");
                scanf("%d", &id);
                heada = deleteAdmin(heada, id);
                break;
            }
            case 4:
                clear();
                view(heada);
                break;
            case 5:
                clear();
                viewActivities();
                break;
            case 6:
                clear();
                return;
            default:
                printf("\n\t\t\t\t\t\t\t" RED "Invalid choice! Please try again." RESET "\n");
        }
    }
}

void customerMenu() {
    clear();
    int choice;
    while (1) {
        printf("\n\t\t\t\t\t\t\t" CYAN "***** CUSTOMER MENU *****" RESET "\n\n");
        printf("\t\t\t\t\t\t\t1. Order Menu\n");
        printf("\t\t\t\t\t\t\t2. View Order\n");
        printf("\t\t\t\t\t\t\t3. Delete Item from Order\n");
        printf("\t\t\t\t\t\t\t4. Payment\n");
        printf("\t\t\t\t\t\t\t5. Exit\n\n");
        printf("\t\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                orderMenu();
                break;
            }
            case 2: {
                view(headc);
                break;
            }
            case 3: {
                int id;
                printf("\t\t\t\t\t\t\tEnter food ID to delete: ");
                scanf("%d", &id);
                headc = deleteCustomer(headc, id);
                break;
            }
            case 4: {
                float bill = calculateTotalBill();
                printf("\n\t\t\t\t\t\t\t" YELLOW "Total Bill: Tk. %.2f" RESET "\n", bill);
                paymentMethod(bill);
                break;
            }
            case 5:
                clear();
                return;
            default:
                printf("\n\t\t\t\t\t\t\t" RED "Invalid choice! Please try again." RESET "\n");
        }
    }
}
struct node* createAdmin(struct node* head, int data, char foodname[], float price) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));

    if (temp == NULL) {
        printf("\n\t\t\t\t\t\t\t" RED "Memory allocation failed! Item not added." RESET "\n");
        return head;
    }

    temp->data = data;
    strcpy(temp->foodname, foodname);
    temp->price = price;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        struct node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }
    char logMessage[100];
    snprintf(logMessage, sizeof(logMessage), "Added item: ID=%d, Name=%s, Price=%.2f", data, foodname, price);

    logActivity(logMessage, 0);

    return head;
}
struct node* deleteAdmin(struct node* head, int data) {
    if (head == NULL) {
        printf("\n\t\t\t\t\t\t\t" RED "No items found!" RESET "\n");
        return head;
    }

    struct node* prev = NULL;
    struct node* curr = head;

    while (curr != NULL && curr->data != data) {
        prev = curr;
        curr = curr->next;
    }
    if (curr != NULL) {
        if (prev == NULL) {
            head = curr->next;
        } else {
            prev->next = curr->next;
        }
        printf("\n\t\t\t\t\t\t\t" GREEN "Item deleted successfully!" RESET "\n");

        char logMessage[100];
        snprintf(logMessage, sizeof(logMessage), "Deleted item: ID=%d, Name=%s", curr->data, curr->foodname);
        logActivity(logMessage, 0);

        free(curr);
        curr = NULL;
    } else {
        printf("\n\t\t\t\t\t\t\t" RED "Item not found!" RESET "\n");
        char logMessage[100];
        snprintf(logMessage, sizeof(logMessage), "Failed to delete item: ID=%d (Item not found)", data);
        logActivity(logMessage, 0);
    }

    return head;
}
struct node* createCustomer(struct node* head, int data, char foodname[], float price) {

    struct node* temp = (struct node*)malloc(sizeof(struct node));

    if (temp == NULL) {
        printf("\n\t\t\t\t\t\t\t" RED "Memory allocation failed!" RESET "\n");
        return head;
    }
    temp->data = data;
    strcpy(temp->foodname, foodname);
    temp->price = price;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        struct node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
    char logMessage[100];
    snprintf(logMessage, sizeof(logMessage), "Created customer item: ID=%d, Name=%s, Price=%.2f", data, foodname, price);
    logActivity(logMessage, 0);

    return head;
}

struct node* deleteCustomer(struct node* head, int data);
struct node* deleteCustomer(struct node* head, int data) {
    if (head == NULL) {
        printf("\n\t\t\t\t\t\t\t" RED "No items found in order!" RESET "\n");
        return head;
    }

    struct node* prev = NULL;
    struct node* curr = head;

    while (curr != NULL && curr->data != data) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL) {
        printf("\n\t\t\t\t\t\t\t" YELLOW "Item found: %s (Price: Tk. %.2f)" RESET "\n", curr->foodname, curr->price);
        printf("\n\t\t\t\t\t\t\t" CYAN "Are you sure you want to delete this item? (1 = Yes, 0 = No): " RESET);

        int confirm;
        while (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
            while (getchar() != '\n');
            printf("\n\t\t\t\t\t\t\t" RED "Invalid input! Please enter 1 for Yes or 0 for No: " RESET);
        }

        if (confirm == 1) {
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            printf("\n\t\t\t\t\t\t\t" GREEN "Item removed from order!" RESET "\n");


            char logMessage[100];
            snprintf(logMessage, sizeof(logMessage), "Deleted customer order item: ID=%d, Name=%s, Price=%.2f", curr->data, curr->foodname, curr->price);
            logActivity(logMessage, 0);

            free(curr);
            curr = NULL;
        } else {
            printf("\n\t\t\t\t\t\t\t" CYAN "Item not removed. Returning to menu." RESET "\n");
        }
    } else {
        printf("\n\t\t\t\t\t\t\t" RED "Item not found in order!" RESET "\n");
    }

    return head;
}

float calculateTotalBill() {
    struct node* ptr = headc;
    float total = 0.0;
    while (ptr != NULL) {
        total += ptr->price;
        ptr = ptr->next;
    }
    return total;
}
void paymentMethod(float bill) {
    int paymentChoice;
    printf("\n\t\t\t\t\t\t\t" CYAN "Select Payment Method:" RESET "\n");
    printf("\t\t\t\t\t\t\t1. Cash\n");
    printf("\t\t\t\t\t\t\t2. Credit/Debit Card\n");
    printf("\t\t\t\t\t\t\t3. Mobile Banking (Bkash, Rocket, Nagad, etc.)\n");
    printf("\t\t\t\t\t\t\t4. Exit\n");
    printf("\t\t\t\t\t\t\tEnter choice (1-4): ");

    while (scanf("%d", &paymentChoice) != 1 || paymentChoice < 1 || paymentChoice > 4) {
        while (getchar() != '\n');
        printf("\n\t\t\t\t\t\t\t" RED "Invalid input! Please enter a valid option (1-4): " RESET);
    }

    switch (paymentChoice) {
        case 1:
            printf("\n\t\t\t\t\t\t\t" GREEN "Payment of Tk. %.2f accepted via Cash!" RESET "\n", bill);
            logActivity("Payment completed via Cash", 0);
            break;
        case 2:
            printf("\n\t\t\t\t\t\t\t" GREEN "Payment of Tk. %.2f accepted via Credit/Debit Card!" RESET "\n", bill);
            logActivity("Payment completed via Credit/Debit Card", 0);
            break;
        case 3:
            printf("\n\t\t\t\t\t\t\t" GREEN "Payment of Tk. %.2f accepted via Mobile Banking!" RESET "\n", bill);
            logActivity("Payment completed via Mobile Banking", 0);
            break;
        case 4:
            printf("\n\t\t\t\t\t\t\t" YELLOW "Payment process canceled. Returning to the menu." RESET "\n");
            return;
        default:
            printf("\n\t\t\t\t\t\t\t" RED "Unexpected error occurred!" RESET "\n");
            return;
    }
    totalSales += bill;
    freeMenu(headc);
    headc = NULL;
    printf("\n\t\t\t\t\t\t\t" YELLOW "Thank you for your payment!" RESET "\n");
}
void orderMenu() {
    printf("\n\t\t\t\t\t\t\t" BLUE "***** MENU *****" RESET "\n\n");
    printf("\t\t\t\t\t\t\tID\tFood Name\t\tPrice\n");

    struct node* ptr = heada;
    while (ptr != NULL) {
        printf("\n\t\t\t\t\t\t\t%-3d\t%-15s\t\tTk.%.2f\n", ptr->data, ptr->foodname, ptr->price);
        ptr = ptr->next;
    }
    printf("\n\t\t\t\t\t\t\tEnter food ID to add to order (0 to exit): ");

    int id;
    while (1) {
        while (scanf("\n\t\t\t\t\t\t\t%d", &id) != 1) {
            while (getchar() != '\n');
            printf("\n\t\t\t\t\t\t\t" RED "Invalid input! Please enter a valid food ID (0 to exit): " RESET);
        }

        if (id == 0) {
            printf("\n\t\t\t\t\t\t\t" CYAN "Thank you for your order! Have a great day!" RESET "\n");
            break;
        }

        struct node* foodPtr = heada;
        while (foodPtr != NULL && foodPtr->data != id) {
            foodPtr = foodPtr->next;
        }

        if (foodPtr != NULL) {
            headc = createCustomer(headc, foodPtr->data, foodPtr->foodname, foodPtr->price);
            printf("\t\t\t\t\t\t\t" GREEN "Added %s to your order!" RESET "\n", foodPtr->foodname);
        } else {
            printf("\t\t\t\t\t\t\t" RED "Invalid ID! Please try again: " RESET);
        }
    }
}
void view(struct node* head) {
    if (head == NULL) {
        printf("\n\t\t\t\t\t\t\t" RED "No items found!" RESET "\n");
    } else {
        printf("\n\t\t\t\t\t\t\t" YELLOW "***** Menu *****" RESET "\n\n");
        struct node* temp = head;
        while (temp != NULL) {
            printf("\n\t\t\t\t\t\t\tID: %d | Name: %s | Price: %.2f\n", temp->data, temp->foodname, temp->price);
            temp = temp->next;
        }
        char logMessage[100];
        snprintf(logMessage, sizeof(logMessage), "Viewed items in the menu");
        logActivity(logMessage, 0);
    }
}
void freeMenu(struct node* head) {
    while (head != NULL) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }
}
void viewActivities() {
    FILE* file = fopen("activities.log", "r");
    if (file == NULL) {
        printf("\n\t\t\t\t\t\t\t" RED "No activity log found!" RESET "\n");
        return;
    }
    printf("\n\t\t\t\t\t\t\t" YELLOW "***** Activity Log *****" RESET "\n\n");

    char line[256];
    int lineCount = 0;

    while (fgets(line, sizeof(line), file)) {
        lineCount++;
        printf("\t\t\t\t\t\t\t%s", line);
    }
    if (lineCount == 0) {
        printf("\n\t\t\t\t\t\t\t" RED "No activities recorded yet." RESET "\n");
    }

    fclose(file);
}
void mainMenu() {
    clear();
    int choice;
    printf("\n\n");
    printf("\t\t\t\t\t\t\t   _______________\n");
    printf("\t\t\t\t\t\t\t  |               |\n");
    printf("\t\t\t\t\t\t\t  |     DEOWAN    |\n");
    printf("\t\t\t\t\t\t\t  | HOTEL & RESTRO|\n");
    printf("\t\t\t\t\t\t\t  |_______________|\n");
    printf("\t\t\t\t\t\t\t   /      _      \\\n");
    printf("\t\t\t\t\t\t\t  /  _.-\"   \"-._  \\\n");
    printf("\t\t\t\t\t\t\t /.-\"           \"-.\\\n");
    printf("\t\t\t\t\t\t\t |                 |\n");
    printf("\t\t\t\t\t\t\t |   []       []   |\n");
    printf("\t\t\t\t\t\t\t |       ___       |\n");
    printf("\t\t\t\t\t\t\t |_________________|\n\n");

    while (1) {
    printf("\n\t\t\t\t\t\t\t" MAGENTA "***** Deowan Hotel & Restaurant *****" RESET "\n\n");
    printf("\t\t\t\t\t\t\t1. Admin\n");
    printf("\t\t\t\t\t\t\t2. Customer\n");
    printf("\t\t\t\t\t\t\t3. About\n");
    printf("\t\t\t\t\t\t\t4. Exit\n\n");
    printf("\t\t\t\t\t\t\tEnter your choice: ");
    scanf("%d", &choice);

        if (choice == 1) {
            char username[20];
            int password;
            printf("\n\t\t\t\t\t\t\tEnter username: ");
            scanf("%s", username);
            printf("\t\t\t\t\t\t\tEnter password: ");
            scanf("%d", &password);

            if (strcmp(username, "sabit") == 0 && password == 386) {
                adminMenu();
            } else {
                printf("\n\t\t\t\t\t\t\t" RED "Invalid username or password!" RESET "\n");
            }
        } else if (choice == 2) {
            customerMenu();
        }
        else if (choice == 3) {
            developerInfo();
        }

        else if (choice == 4) {
            clear();
            freeMenu(heada);
            freeMenu(headc);
            printf("\n\t\t\t\t\t\t\t" GREEN "Thank you! Exiting..." RESET "\n");
            exit(0);
        } else {
            printf("\n\t\t\t\t\t\t\t" RED "Invalid choice! Please try again." RESET "\n");
        }
    }
}
void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
int main() {
    struct node* head = NULL;

    heada = createAdmin(heada, 1, "Vaat plate", 10);
    heada = createAdmin(heada, 2, "Chicken half", 40);
    heada = createAdmin(heada, 3, "Chicken full", 70);
    heada = createAdmin(heada, 4, "Chingri Mach", 60);
    heada = createAdmin(heada, 5, "Pabda Mach", 60);
    heada = createAdmin(heada, 6, "Dim Vorta", 10);
    heada = createAdmin(heada, 7, "Alu Vorta", 10);
    heada = createAdmin(heada, 8, "Mach Vorta", 10);
    heada = createAdmin(heada, 9, "Chicken Chap", 120);
    heada = createAdmin(heada, 10, "Nun Roti", 20);
    heada = createAdmin(heada, 11, "Chicken Grill", 90);
    heada = createAdmin(heada, 12, "Coca-Cola 250ml", 25);
    heada = createAdmin(heada, 13, "Pepsi 250ml", 25);
    heada = createAdmin(heada, 14, "Speed 250ml", 30);

    logActivity("Clearing log...", 1);

    mainMenu();
    return 0;
}
