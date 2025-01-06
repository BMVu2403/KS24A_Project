#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>


#define MAX_USER_ID_LENGTH 10
#define MAX_USERNAME_LENGTH 20
#define MAX_PHONE_LENGTH 10
#define MAX_EMAIL_LENGTH 20
#define MAX_NAME_LENGTH 20
#define MAX_TRANSACTION_HISTORY 100


struct Date
{
    int month, day, year;
};

struct Transaction
{
    char transferId[10];
    char receivingId[10];
    double amount;
    char type[10];
    char message[50];
    struct Date transactionDate;
};

typedef struct
{
    char userId[10];
    char username[20];
    char password[20];
    float balance;
    bool status;
    struct Transaction transactionHistory[];
} AccountInfo;


typedef struct
{
    char userId[10];
    char name[20];
    struct Date dateOfBirth;
    bool gender;
    char phone[11];
    char email[20];
    AccountInfo account;
} User;


bool checkDuplicate(User users[], int n, char key[], char value[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(key, "userId") == 0 && strcmp(users[i].userId, value) == 0)
        {
            return true;
        }
        else if (strcmp(key, "phone") == 0 && strcmp(users[i].phone, value) == 0)
        {
            return true;
        }
        else if (strcmp(key, "email") == 0 && strcmp(users[i].email, value) == 0)
        {
            return true;
        }
        else if(strcmp(key, "username") == 0 && strcmp(users[i].account.username, value) == 0)
        {
            return true;
        }
    }
    return false;
}

bool checkDuplicate_Update(User users[], int n, char key[], char value[], char userId[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(key, "phone") == 0 && strcmp(users[i].phone, value) == 0 && strcmp(users[i].userId, userId) != 0)
        {
            return true;
        }
        else if (strcmp(key, "email") == 0 && strcmp(users[i].email, value) == 0 && strcmp(users[i].userId, userId) != 0)
        {
            return true;
        }
        else if(strcmp(key, "username") == 0 && strcmp(users[i].account.username, value) == 0 && strcmp(users[i].userId, userId) != 0)
        {
            return true;
        }
    }
    return false;
}

AccountInfo inputAccount(User users[], int n, User u)
{
    AccountInfo acc;
    getchar();
    do
    {
        printf("\nEnter Username: ");
        fgets(acc.username, sizeof(acc.username), stdin);
        acc.username[strcspn(acc.username, "\n")] = 0;
        if(strlen(acc.username) == 0 || strlen(acc.username) >= sizeof(acc.username))
        {
            printf("\nError: Invalid Username length");
        }
        else if(checkDuplicate(users, n, "username", acc.username))
        {
            printf("\nError: Username already exists");
        }
        else
        {
            break;
        }
    }
    while(1);

    printf("\nEnter balance: ");
    scanf("%f", &acc.balance);
    strcpy(acc.userId, u.userId);
    strcpy(acc.password, u.phone);
    acc.status = true;
    return acc;
}


int isValidChar(char c)
{
    return isalnum(c) || c == '.' || c == '_' || c == '%' || c == '+' || c == '-';
}

int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    const char *dot;

    if (!at || at == email)
    {
        return 0;
    }
    for (const char *p = email; p < at; p++)
    {
        if (!isValidChar(*p))
        {
            return 0;
        }
    }
    dot = strchr(at + 1, '.');
    if (!dot || dot == at + 1)
    {
        return 0;
    }
    for (const char *p = at + 1; p < dot; p++)
    {
        if (!isalnum(*p) && *p != '-')
        {
            return 0;
        }
    }

    if (strlen(dot + 1) < 2)
    {
        return 0;
    }
    for (const char *p = dot + 1; *p; p++)
    {
        if (!isalpha(*p))
        {
            return 0;
        }
    }

    return 1;
}

User inputUser(User users[], int n)
{
    User u;
    getchar();
    do
    {
        printf("\nEnter user id: ");
        fgets(u.userId, sizeof(u.userId), stdin);
        u.userId[strcspn(u.userId, "\n")] = 0;
        if(strlen(u.userId) == 0 || strlen(u.userId) >= sizeof(u.userId))
        {
            printf("\nError: Invalid ID length");
        }
        else if(checkDuplicate(users, n, "userId", u.userId))
        {
            printf("\nError: User ID already exists");
        }
        else
        {
            break;
        }
    }
    while(1);

    do
    {
        printf("\nEnter name: ");
        fgets(u.name, sizeof(u.name), stdin);
        u.name[strcspn(u.name, "\n")] = 0;
        if(strlen(u.name) == 0)
        {
            printf("\nError: Invalid name length");
        }
        else
        {
            break;
        }
    }
    while(1);

    bool isContinue = true;
    while(1)
    {
        isContinue = true;
        printf("\nEnter birthday(dd/MM/yyyy): ");
        int result = scanf("%d/%d/%d", &u.dateOfBirth.day, &u.dateOfBirth.month, &u.dateOfBirth.year);
        if(result != 3)
        {
            printf("\nError: Invalid input format. Please enter in dd/MM/yyyy format.");
            isContinue = false;
        }
        if((u.dateOfBirth.day < 1 || u.dateOfBirth.day > 31) || (u.dateOfBirth.month < 1 || u.dateOfBirth.month > 12))
        {
            printf("\nError: Invalid date. Please enter again");
            isContinue = false;
        }
        if(isContinue)
            break;
    }
    int gender;
    while(1)
    {
        printf("\nEnter gender(1 - Male; 0 - Female): ");
        scanf("%d", &gender);
        if(gender != 0 && gender != 1)
        {
            printf("\nError: Invalid input. Please choose 1 or 0");
        }
        else
        {
            u.gender = gender == 1;
            break;
        }
    }

    do
    {
        printf("\nEnter phone: ");
        scanf("%10s", u.phone);
        if(strlen(u.phone) == 0 || strlen(u.phone) >= sizeof(u.phone))
        {
            printf("\nError: Invalid phone length");
        }
        else if(strlen(u.phone) != 10)
        {
            printf("\nError: phone number is 10 digits");
        }
        else if(checkDuplicate(users, n, "phone", u.phone))
        {
            printf("\nError: Phone already exists");
        }
        else
        {
            break;
        }
    }
    while(1);

    do
    {
        printf("\nEnter email: ");
        scanf("%19s", u.email);
        if(strlen(u.email) == 0 || strlen(u.email) >= sizeof(u.email))
        {
            printf("\nError: Invalid email length");
        }
        else if (!isValidEmail(u.email))
        {
            printf("\nError: Invalid email format");
        }
        else if(checkDuplicate(users, n, "email", u.email))
        {
            printf("\nError: Email already exists");
        }
        else
        {
            break;
        }
    }
    while(1);


    u.account = inputAccount(users, n, u);
    return u;
}


void printUser(User u)
{
    printf("\nUser Information:");
    printf("\nID: %s", u.userId);
    printf("\nName: %s", u.name);
    printf("\nDate of Birth: %02d/%02d/%04d", u.dateOfBirth.day, u.dateOfBirth.month, u.dateOfBirth.year);
    printf("\nGender: %s", u.gender == 1 ? "Male" : "Female");
    printf("\nPhone: %s", u.phone);
    printf("\nEmail: %s", u.email);
    printf("\nUsername: %s", u.account.username);
    printf("\nBalance: %f", u.account.balance);
}

void printUserList(User users[], int n)
{
    printf("| ID         | Name               | Email              | Phone      | Date Of Birth | Gender  | Status |\n");
    printf("|------------|--------------------|--------------------|------------|---------------|---------|--------|\n");
    for(int i = 0; i < n; i++)
    {
        printf("| %-10s | %-18s | %-18s | %-10s | %02d/%02d/%04d    | %-7s | %-6s |\n",
               users[i].userId,
               users[i].name,
               users[i].email,
               users[i].phone,
               users[i].dateOfBirth.day,
               users[i].dateOfBirth.month,
               users[i].dateOfBirth.year,
               users[i].gender ? "Male" : "Female",
               users[i].account.status ? "Open" : "Lock");
    }
}

void toLowerCase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

void filterUserByName(User users[], int n)
{
    bool hasUser = false;
    char key[20];
    printf("\nEnter the name: ");
    getchar();
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;
    toLowerCase(key);

    for (int i = 0; i < n; i++)
    {
        char nameLower[sizeof(users[i].name)];
        strcpy(nameLower, users[i].name);
        toLowerCase(nameLower);

        if (strstr(nameLower, key) != NULL)
        {
            hasUser = true;
        }
    }

    if (hasUser)
    {
        printf("| ID         | Name               | Email              | Phone      | Date Of Birth | Gender  | Status |\n");
        printf("|------------|--------------------|--------------------|------------|---------------|---------|--------|\n");
        for (int i = 0; i < n; i++)
        {
            char nameLower[sizeof(users[i].name)];
            strcpy(nameLower, users[i].name);
            toLowerCase(nameLower);

            if (strstr(nameLower, key) != NULL)
            {
                printf("| %-10s | %-18s | %-18s | %-10s | %02d/%02d/%04d    | %-7s | %-6s |\n",
                       users[i].userId,
                       users[i].name,
                       users[i].email,
                       users[i].phone,
                       users[i].dateOfBirth.day,
                       users[i].dateOfBirth.month,
                       users[i].dateOfBirth.year,
                       users[i].gender ? "Male" : "Female",
                       users[i].account.status ? "Open" : "Lock");
            }
        }
    }
    else
    {
        printf("\nNot found user");
    }
}

bool equalsCharArray(char arr1[], char arr2[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (arr1[i] != arr2[i])
        {
            return false;
        }
    }

    return true;
}

void searchUserById(User users[], int n)
{
    char id[10];

    printf("\nEnter id: ");
    scanf("%9s", &id);
    bool hasUser = false;
    for(int i = 0; i < n; i++)
    {
        if(strcmp(users[i].userId, id) == 0)
        {
            User u = users[i];
            printf("\nUser Information:");
            printf("\nID: %s", u.userId);
            printf("\nName: %s", u.name);
            printf("\nDate of Birth: %02d/%02d/%04d", u.dateOfBirth.day, u.dateOfBirth.month, u.dateOfBirth.year);
            printf("\nGender: %s", u.gender == 1 ? "Male" : "Female");
            printf("\nEmail: %s", u.email);
            printf("\nUsername: %s", u.account.username);
            printf("\nBalance: %f", u.account.balance);
            hasUser = true;
            break;
        }
    }

    if(!hasUser)
    {
        printf("\nNo User has id: %s", id);
    }
}

void changeStatusAccount(User users[], int n)
{
    char id[10];
    int i;
    printf("\nEnter id: ");
    scanf("%9s", &id);
    bool hasUser = false;
    for(i = 0; i < n; i++)
    {
        if(strcmp(users[i].userId, id) == 0)
        {
            hasUser = true;
            break;
        }
    }

    if(!hasUser)
    {
        printf("\nNo user was found for id: %s", id);
    }
    else
    {
        User user = users[i];
        char opt;
        printf("\nOne user was found for id: %s", id);
        getchar();
        if(!user.account.status)
        {
            printf("\nUser's status was lock, unlock user?\nYes(y)? or No(n)?: ");
            opt = getchar();
            if(opt == 'y')
            {
                users[i].account.status = true;
                printf("\nUnlock user successfully");
            }

        }
        else
        {
            printf("\nUser's status was unlock, lock user?\nYes(y)? or No(n)?: ");
            opt = getchar();
            if(opt == 'y')
            {
                users[i].account.status = false;
                printf("\nLock user successfully");
            }

        }
    }
}

void sortUsers(User users[], int n)
{
    printf("\t    CHOOSE TYPE SORT USER NAME\n");
    printf("\t======================\n");
    printf("\t[1] Sort A-Z.\n");
    printf("\t[2] Sort Z-A.\n");
    printf("\t[0] Exit.\n");
    printf("\t======================\n");
    printf("\tEnter The Choice: ");
    int choice;
    scanf("%d", &choice);
    if(choice == 0)
    {
        return;
    }
    if(choice != 1 && choice != 2)
    {
        printf("\nChoice is invalid");
        return;
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            int compareName = strcmp(users[j].name, users[j+1].name);
            if((choice == 1 && compareName > 0) || (choice == 2 && compareName < 0))
            {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }

    printf("\nSorting completed");
}

void saveFile(User users[], int n)
{
    FILE *f = fopen("users.dat", "wb");
    if (f == NULL)
    {
        perror("Error opening file for writing");
        return;
    }

    fwrite(&n, sizeof(int), 1, f);
    for (int i = 0; i < n; i++)
    {
        fwrite(&users[i], sizeof(User), 1, f);
    }

    fclose(f);
    printf("\nSaved file successfully\n");
}

void readFile(User users[], int *n)
{
    FILE *f = fopen("users.dat", "rb");
    if (f == NULL)
    {
        perror("Error opening file for reading");
        return;
    }

    fread(n, sizeof(int), 1, f);
    for (int i = 0; i < *n; i++)
    {
        fread(&users[i], sizeof(User), 1, f);
    }

    fclose(f);
}







//users


void inputPassword(char *password, int maxLength)
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == '\r')
        {
            password[i] = '\0';
            break;
        }
        else if (ch == '\b' && i > 0)
        {
            i--;
            printf("\b \b");
        }
        else if (i < maxLength - 1 && ch != '\b')
        {
            password[i++] = ch;
            printf("*");
        }
    }
}


User* login(User users[], int n)
{
    char username[20];
    char password[20];
    printf(" ***Bank Management System Using C***\n");
    printf("\n\t   LOGIN\n");
    printf("\t====================================\n");
    printf("\tUsername: ");
    scanf("%19s", username);
    printf("\tPassword: ");
    inputPassword(password, sizeof(password));
    printf("\n\t====================================\n");

    for(int i = 0; i < n; i++)
    {
        if(((strcmp(users[i].account.username, username) == 0) || (strcmp(users[i].userId, username) == 0))
                && strcmp(users[i].account.password, password) == 0)
        {
            if(users[i].account.status)
                return &users[i];
            else
            {
                printf("\nUser's status was lock.\n");
                return NULL;
            }
        }
    }
    printf("\nInvalid username or password.\n");
    return NULL;
}


void changeUserInfo(User *user, User users[], int n)
{

    int choice;
    do
    {
        printf("\nCurrent User Information:");
        printf("\n1. Name: %s", user->name);
        printf("\n2. Birthday: %02d/%02d/%04d", user->dateOfBirth.day, user->dateOfBirth.month, user->dateOfBirth.year);
        printf("\n3. Gender: %s", user->gender ? "Male" : "Female");
        printf("\n4. Phone: %s", user->phone);
        printf("\n5. Email: %s", user->email);
        printf("\n0. Exit");

        printf("\n\nEnter the field number you want to change (1-5): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            while(1)
            {
                printf("\nEnter new Name: ");
                getchar();
                char newName[20];
                fgets(newName, sizeof(newName), stdin);
                newName[strcspn(newName, "\n")] = 0;

                if (strlen(newName) == 0)
                {
                    printf("\nError: Invalid name length");
                }
                else
                {
                    strcpy(user->name, newName);
                    printf("\nName updated successfully.");
                    break;
                }
            }


            break;
        }
        case 2:
        {
            while(1)
            {
                printf("\nEnter new Birthday (dd/MM/yyyy): ");
                int day, month, year;
                int result = scanf("%d/%d/%d", &day, &month, &year);
                if(result != 3)
                {
                    printf("\nError: Invalid input format. Please enter in dd/MM/yyyy format.");
                }
                else if((day < 1 || day > 31) || (month < 1 || month > 12))
                {
                    printf("\nError: Invalid date. Please enter again");
                }
                else
                {
                    user->dateOfBirth.day = day;
                    user->dateOfBirth.month = month;
                    user->dateOfBirth.year = year;
                    printf("\nBirthday updated successfully.");
                    break;
                }
            }
            break;
        }
        case 3:
        {
            while(1)
            {
                printf("\nEnter new Gender (1 - Male; 0 - Female): ");
                int gender;
                scanf("%d", &gender);

                if (gender != 0 && gender != 1)
                {
                    printf("\nError: Invalid gender.");
                }
                else
                {
                    user->gender = gender == 1;
                    printf("\nGender updated successfully.");
                    break;
                }
            }
            break;
        }
        case 4:
        {
            while(1)
            {
                printf("\nEnter new Phone: ");
                char newPhone[11];
                scanf("%10s", newPhone);

                if (strlen(newPhone) != 10)
                {
                    printf("\nError: Phone number must be 10 digits.");
                }
                else if (checkDuplicate_Update(users, n, "phone", newPhone, user->userId))
                {
                    printf("\nError: Phone number already exists.");
                }
                else
                {
                    strcpy(user->phone, newPhone);
                    printf("\nPhone updated successfully.");
                    break;
                }
            }
            break;
        }
        case 5:
        {
            while(1)
            {
                printf("\nEnter new Email: ");
                char newEmail[20];
                scanf("%19s", newEmail);

                if (!isValidEmail(newEmail))
                {
                    printf("\nError: Invalid email format.");
                }
                else if (checkDuplicate_Update(users, n, "email", newEmail, user->userId))
                {
                    printf("\nError: Email already exists.");
                }
                else
                {
                    strcpy(user->email, newEmail);
                    printf("\nEmail updated successfully.");
                    break;
                }
            }
            break;
        }
        case 0:
            printf("\nExiting update process.");
            for(int i = 0; i < n; i++)
            {
                if(strcmp(users[i].userId, user->userId) == 0)
                {
                    strcpy(users[i].name, user->name);
                    users[i].dateOfBirth = user->dateOfBirth;
                    users[i].gender = user->gender;
                    strcpy(users[i].phone, user->phone);
                    strcpy(users[i].email, user->email);
                    break;
                }
            }
            break;
        default:
            printf("\nError: Invalid choice. Please try again.");
        }
    }
    while(choice != 0);
}

void changePassword(User *user, User users[], int n)
{
    char passwordOld[20], passwordNew[20], passwordEnter[20];
    while(1)
    {
        printf("\nEnter password old: ");
        inputPassword(passwordOld, sizeof(passwordOld));
        if(strcmp(user->account.password, passwordOld) == 0) {
            break;
        } else {
            printf("\nInvalid password old");
        }
    }

    while(1)
    {
        printf("\nEnter password new: ");
        inputPassword(passwordNew, sizeof(passwordNew));
        printf("\nEnter confirm password new: ");
        inputPassword(passwordEnter, sizeof(passwordEnter));
        if(strcmp(passwordNew, passwordEnter) != 0) {
            printf("\nError: The new passoword and confirmation password do not match.");
        } else {
            break;
        }
    }

    printf("\nChange password successfully");
    strcpy(user->account.password, passwordNew);
    for(int i = 0; i < n; i++)
    {
        if(strcmp(users[i].userId, user->userId) == 0)
        {
            strcpy(users[i].account.password, passwordNew);
            break;
        }
    }
}
void menuUserManagement()
{
    printf("*** Bank Management System Using C ***\n");
    printf("\t    CHOOSE YOUR ROLE\n");
    printf("\t======================\n");
    printf("\t[1] Admin.\n");
    printf("\t[2] User.\n");
    printf("\t[0] Exit the Program.\n");
    printf("\t======================\n");
    printf("\tEnter The Choice: ");
}

void menuAdmin()
{
    printf("*** Bank Management System Using C ***\n");
    printf("\t\tMENU ADMIN\n");
    printf("\t======================\n");
    printf("\t[1] Add A New user.\n");
    printf("\t[2] Show All users.\n");
    printf("\t[3] Filter user by name.\n");
    printf("\t[4] Show detail an user.\n");
    printf("\t[5] Lock (Unlock) an user.\n");
    printf("\t[6] Sort Users by name.\n");
    printf("\t[7] About Us.\n");
    printf("\t[8] User Guideline.\n");
    printf("\t[9] Save users in file.\n");
    printf("\t[10] Read users from file.\n");
    printf("\t[0] Exit the Program.\n");
    printf("\t======================\n");
    printf("\tEnter The Choice: ");
}

void menuUser()
{
    printf("\n*** Bank Management System Using C ***\n");
    printf("\t\tMENU USER\n");
    printf("\t======================\n");
    printf("\t[1] Account management.\n");
    printf("\t[0] Exit the Program.\n");
    printf("\t======================\n");
    printf("\tEnter The Choice: ");
}

void menuAccountManagement()
{
    printf("*** Bank Management System Using C ***\n");
    printf("\t   MENU ACCOUNT MANAGEMENT\n");
    printf("\t======================\n");
    printf("\t[1] Display detail user.\n");
    printf("\t[2] Update user info.\n");
    printf("\t[3] Change password.\n");
    printf("\t[4] Save account in file.\n");
    printf("\t[5] Read account from file.\n");
    printf("\t[0] Exit the Program.\n");
    printf("\t======================\n");
    printf("\tEnter The Choice: ");
}

int main()
{
    int chooseRole;
    int chooseAdmin;
    int chooseUser;
    int chooseAccount;
    User users[100];
    User *userCurrent;
    int n = 0;
    char nav;
    do
    {
        menuUserManagement();
        scanf("%d", &chooseRole);
        switch(chooseRole)
        {
        case 1:
            do
            {
                menuAdmin();
                scanf("%d", &chooseAdmin);
                switch(chooseAdmin)
                {
                case 1:
                    do
                    {
                        if(n < 100)
                        {
                            users[n] = inputUser(users, n);
                            printf("\nUser added successfully");
                            printUser(users[n]);
                            n++;
                        }
                        getchar();
                        printf("\nGo back(b)? or Exit(0)?: ");
                        nav = getchar();

                    }
                    while(nav == 'b');
                    break;
                case 2:
                    do
                    {
                        if(n > 0)
                        {
                            printUserList(users, n);
                        }
                        else
                        {
                            printf("\nNo data");
                        }
                        getchar();
                        printf("\nGo back(b)? or Exit(0)?: ");
                        nav = getchar();

                    }
                    while(nav == 'b');
                    break;
                case 3:
                    do
                    {
                        filterUserByName(users, n);
                        getchar();
                        printf("\nGo back(b)? or Exit(0)?: ");
                        nav = getchar();

                    }
                    while(nav == 'b');
                    break;

                case 4:
                    do
                    {
                        searchUserById(users, n);
                        getchar();
                        printf("\nGo back(b)? or Exit(0)?: ");
                        nav = getchar();

                    }
                    while(nav == 'b');
                    break;
                case 5:
                    do
                    {
                        changeStatusAccount(users, n);
                        getchar();
                        printf("\nGo back(b)? or Exit(0)?: ");
                        nav = getchar();

                    }
                    while(nav == 'b');
                    break;
                case 6:
                    do
                    {
                        sortUsers(users, n);
                        getchar();
                        printf("\nGo back(b)? or Exit(0)?: ");
                        nav = getchar();

                    }
                    while(nav == 'b');
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    do
                    {
                        saveFile(users, n);
                        getchar();
                        printf("\nGo back(b)? or Exit(0)?: ");
                        nav = getchar();

                    }
                    while(nav == 'b');
                    break;
                case 10:
                    do
                    {
                        readFile(users, &n);
                        printf("\nRead file successfully\n");
                        getchar();
                        printf("\nGo back(b)? or Exit(0)?: ");
                        nav = getchar();

                    }
                    while(nav == 'b');
                    break;
                case 0:
                    break;
                default:
                    printf("Invalid selection\n");
                    break;
                }
            }
            while(chooseAdmin != 0);

            break;
        case 2:

            readFile(users, &n);
            userCurrent = login(users, n);
            if(userCurrent == NULL)
            {
                break;
            }
            printf("\nLogin successfully\n");
            do
            {

                menuUser();
                scanf("%d", &chooseUser);
                switch(chooseUser)
                {
                case 1:
                    do
                    {
                        menuAccountManagement();
                        scanf("%d", &chooseAccount);
                        switch(chooseAccount)
                        {
                            case 1:
                                do
                                {
                                    printUser(*userCurrent);
                                    getchar();
                                    printf("\nGo back(b)? or Exit(0)?: ");
                                    nav = getchar();

                                }
                                while(nav == 'b');
                                printf("\n");
                                break;
                            case 2:
                                do
                                {
                                    changeUserInfo(userCurrent, users, n);
                                    getchar();
                                    printf("\nGo back(b)? or Exit(0)?: ");
                                    nav = getchar();

                                }
                                while(nav == 'b');
                                break;
                            case 3:
                                do
                                {
                                    changePassword(userCurrent, users, n);
                                    getchar();
                                    printf("\nGo back(b)? or Exit(0)?: ");
                                    nav = getchar();

                                }
                                while(nav == 'b');
                                break;
                            case 4:
                                do
                                {
                                    saveFile(users, n);
                                    getchar();
                                    printf("\nGo back(b)? or Exit(0)?: ");
                                    nav = getchar();

                                }
                                while(nav == 'b');
                                break;
                            case 5:
                                do
                                {
                                    readFile(users, &n);
                                    printf("\nRead file successfully\n");
                                    getchar();
                                    printf("\nGo back(b)? or Exit(0)?: ");
                                    nav = getchar();
                                }
                                while(nav == 'b');
                                break;
                            case 0:
                                break;
                        }
                    }
                    while(chooseAccount != 0);
                    break;
                case 0:
                    break;
                }
            }
            while(chooseUser != 0);
            break;
        case 0:
            break;
        default:
            printf("Invalid selection\n");
            break;
        }
    }
    while(chooseRole != 0);

    return 0;
}
