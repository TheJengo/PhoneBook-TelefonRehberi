#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
typedef struct{
    char isim[100]; //name
    long int kod;   // Area/Regional Code
    long long int numara; // phone number
}Telephone;
/* Prototypes */
char* readFile(char*);
int countContacts(char*);
int checkContact(Telephone*);
void addContact(char*,Telephone,int);
void updateContact(char*,Telephone[],int);
int findWithName(char*,char[],int);
int deleteContact(char*,long int);
int findWithNumber(char*,long long int);

int MAX = 100; // Capacity of Phone book, you can change it on here
int countContact;
int main()
{
    setlocale(LC_ALL,"English");
    Telephone Telephone,*pArr;
    pArr = &Telephone;

    printf("   PHONE BOOK v1.0\n************************\n");

    /* Contact Number Controls*/
    int restriction = 0;
    countContact = countContacts("Contact.txt");
    if(countContact >= MAX)
    {
        printf("Your Telephone Book Full! Your activities restricted.\n");
        restriction = 1;
    }

    /* Menu */
    char forMenu;
    char name[100];
    int countTry = 0, menuChoice, update = 0, result;

    do{
        printf("\n1. Add Contact\n2. List Contacts\n3. Update Contact\n4. Find Contact with Number\n5. Find Contact with Name\n6. Delete Contact\n0. Exit\n");
        printf("Choice : "); scanf("%d",&menuChoice);
        switch(menuChoice){
            /* Exit */
            case 0:
                exit(1);
                break;
            /* Add Contact */
            case 1:
                if(restriction == 0) //  Restriction Control
                {
                    system("CLS");
                    char name[100];
                    printf("Welcome to the Add Contact!\n");
                    printf("Name:"); scanf(" %s",name);
                    strcpy(pArr->isim,name);
                    printf("Area Code:"); scanf("%d",&pArr->kod);
                    printf("Phone:"); scanf("%lld",&pArr->numara);
                    /* Verification of Values and Adding Contact */
                    if(checkContact(pArr))
                    {
                        update = 0;
                        addContact("Contact.txt",*pArr,update);
                    }
                    else{
                        printf("Adding Contact, Failed!\n");
                    }
                }
                else{
                    system("CLS");
                    printf("\nYour access is restricted on this area because your Phone Book is full!\n");
                    countTry = 0;
                }
                break;
                /* List All Contacts */
            case 2:
                system("CLS");
                printf("All Contacts:\n\n");
                char *list;
                list = readFile("Contact.txt");
                printf("%s",list);
                countTry = 0;
                break;
                /* Update Contact */
            case 3:
                system("CLS");
                update = 1;
                do{
                    printf("Welcome to the Update Section!\n");
                    printf("Name of Contact: "); scanf("%s",name);
                    result = findWithName("Contact.txt",name, update);
                    if(!result)
                    {
                        printf("Do you want to search again? ( Y / N )\n");
                        scanf(" %c",&forMenu);
                    }
                }while(forMenu == 'Y');
                break;
                /* Find Contact with Number */
            case 4:
                system("CLS");
                long long int phoneNumber;
                do{
                    printf("Welcome to the Find Contact with Number Section!\n");
                    printf("Number :"); scanf("%lld",&phoneNumber);
                    result = findWithNumber("Contact.txt",phoneNumber);
                    if(!result)
                    {
                        printf("Do you want to search again? ( Y / N )\n");
                        scanf(" %c",&forMenu);
                    }
                }while(forMenu == 'Y');
                break;
                /* Find Contact With Name*/
            case 5:
                system("CLS");
                //int sonuc;
                update = 0;
                do{
                    printf("Welcome to the Find Contact with Name Section!\n");
                    printf("Name: "); scanf("%s",name);
                    result = findWithName("Contact.txt",name,update);
                    if(!result)
                    {
                        printf("Do you want to search again? ( Y / N )\n");
                        scanf(" %c",&forMenu);
                    }
                }while(forMenu == 'Y');
                break;
                /* Delete Contact */
            case 6:
                system("CLS");
                long int areaCode;
                do{
                    printf("Welcome to the Delete Contact!\n");
                    printf("Area Code:"); scanf("%ld",&areaCode);
                    result = deleteContact("Contact.txt",areaCode);
                if(!result)
                {
                    printf("Do you want to search again? ( Y / N )\n");
                    scanf(" %c",&forMenu);
                }

                }while(forMenu == 'Y');
                break;
            default:
                printf("Invalid selection process please try again!\n");
                countTry++;
                break;
        }
    }while(countTry != 3);
}
char* readFile(char *DosyaAdi)
{
    char *text = NULL;
    int i,text_size;
    FILE *fp = fopen(DosyaAdi,"r");
    if(fp != NULL)
    {
        /* imleci en sona götür. */
        fseek(fp,0,SEEK_END);

        /* imlecin bulundugu byte degerini al */
        text_size = ftell(fp);
        /* imleci en basa geri gönder */
        rewind(fp);

        /* imlecin bulundugu noktaya kadar boyut yarat */
        text = (char *) malloc(sizeof(char) * (text_size + 1));

        // For döngüsüyle ayni islemi döngü kullanmadan stdio.h kutuphanesinin kendi fonksiyonu ile yapar.
        fread(text,sizeof(char),text_size,fp);
    /* En Sevdigimiz "Actigin dosyayi kapat!" */
    fclose(fp);
    }
    else{
        printf("File process failed!");
        exit(1);
    }
    return text;
}
/* Add Contact */
void addContact(char *fileName,Telephone Telefon,int update)
{
    /*
        Contacts adding with this function, parameters respectively, file name, phone struct, update.
    */
    FILE *fp;
    Telephone *pArr;
    pArr = &Telefon;
    fp = fopen(fileName,"a"); // we open our file with "a" mode it means "append".
    if(fp != NULL)
    {
        fprintf(fp,"Name: %s\n",pArr->isim);
        fprintf(fp,"Code: %d\n",pArr->kod);
        fprintf(fp,"Phone: %lld\n",pArr->numara);
        fclose(fp);
        if(update == 0)
        {
            printf("Adding Contact, Successful!\n\n");
        }
    }
    else{
        printf("Writing process failed!\n");
        exit(1);
    }
    fclose(fp);
}
int findWithName(char *fileName,char name[],int update)
{
    /*
       Update parameter used for understand what to do in this function.
       Update and Find Contact with Name sections are the same so we used "update" variable as a boolean.
       if update equals "1" that means update else don't update the contact.
    */
    FILE *fp;
    Telephone *pArr,Contact[MAX];
    pArr = &Contact;
    char nameTag[20],kodTag[20],noTag[20];
    fp = fopen(fileName,"r+");  // Opened file with "r+" in reading mode.
    int contactFound[MAX];
    int isEqual = 0,FlagOne = 0,i = 0,c = 0,contactNo;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s %s ",nameTag,&(pArr+i)->isim);
            fscanf(fp," %s %ld ",kodTag,&(pArr+i)->kod);
            fscanf(fp," %s %lld ",noTag,&(pArr+i)->numara);
            isEqual = strncmp((pArr+i)->isim,name,sizeof(name));
            if(!isEqual)
             {
                 printf("\n%d. Contact:\n%s %s\n%s %d\n%s %lld\n",i+1,nameTag,(pArr+i)->isim,kodTag,(pArr+i)->kod,noTag,(pArr+i)->numara);
                 contactFound[c]=i;
                 c++;
                 FlagOne++;
             }
            i++;
        }
        if(FlagOne != 0)
        {
            fclose(fp);
            printf("\n%d Contact found.\n",FlagOne);
            if(update) // If FindContact function called in Update Section this if block will work.
            {
            int FlagTwo = 0;
            do{
                printf("Contact Number you want to update:");
                scanf("%d",&contactNo);
                for(c=0;c<i;c++)
                {
                    // If entered contact number is valid with contactFound, update the Contact
                    if(contactFound[c] == (contactNo-1))
                    {
                        updateContact("Contact.txt",(pArr+contactNo-1),contactNo-1);
                        FlagTwo = 1;
                        break;
                    }
                }
                if(c==i)
                {
                    printf("\nInvalid Contact Number!\n");
                }
            }while(FlagTwo == 0);

                return 1; // If this function returns 1, our program will work the code for Contact found in Main Function.
            }
        }
        else{
            fclose(fp);
            printf("\nContact Not Found.\n");
            return 0; // If this function returns 0, our program will work the code for Contact not found in Main Function.
        }
    }
    else{
        printf("Reading process failed!\n");
        exit(1);
    }
}
void updateContact(char *fileName,Telephone Phone[],int contactNo) //  contactNo parameter sent from FindContact function
{
    /*
        To update a Contact with file process get the all contacts in a new file except updated one, add a new contact to this file and delete old file rename new file with old file's name.
    */
    Telephone *pArr,updated;
    pArr = &Phone[0];
    char name[100];
    char nameTag[20],kodTag[20],noTag[20];
    int i=0,update = 1;

    printf("Name:"); scanf(" %s",name);
    strcpy(updated.isim,name);
    printf("Area Code:"); scanf("%ld",&updated.kod);
    printf("Phone:"); scanf("%lld",&updated.numara);

    if(checkContact(pArr))  // Checking for invalid values
    {
        FILE *fp_new;
        FILE *fp_old;
        if((fp_old = fopen(fileName,"r+")) == NULL)
        {
            printf("File couldn't open ! \n");
            exit(1);
        }
        if((fp_new = fopen("New_File.txt","wt")) == NULL)
        {
            printf("File couldn't open ! \n");
            exit(1);
        }
        while(!feof(fp_old)) // Getting whole contacts in a Telephone Struct Array.
        {
                fscanf(fp_old," %s %s ",nameTag,&(pArr+i)->isim);
                fscanf(fp_old," %s %ld ",kodTag,&(pArr+i)->kod);
                fscanf(fp_old," %s %lld ",noTag,&(pArr+i)->numara);
                i++;
        }
        int c;
        for(c=0;c<i;c++) // All contacts printing in new file except updated one.
        {
            if(c==contactNo)
                continue;
            else{
                fprintf(fp_new,"Name: %s\n",(pArr+c)->isim);
                fprintf(fp_new,"Code: %d\n",(pArr+c)->kod);
                fprintf(fp_new,"Phone: %lld\n",(pArr+c)->numara);
            }
        }
        fclose(fp_new);
        fclose(fp_old);
        addContact("New_File.txt",updated,update); // Updated Contact adding in New_File as a new contact
        remove(fileName);                   // Delete old file
        rename("New_File.txt",fileName); // ReName new file
        printf("Contact Updated!!\n");
    }
    else{
        printf("Update Failed!\n");
    }
}
int checkContact(Telephone *pArr) // Entry control function
{
        int FlagOne = 0,FlagTwo = 0,FlagThree = 0;
        if(pArr->kod <= 200 || pArr->kod >= 500)
        {
            if(pArr->kod == 90)
            {
                FlagThree = 1;
                FlagOne = 0;
            }
            else{
                printf("Invalid Area/Regional Code!\n");
                FlagOne = 1;
            }
        }
        if(FlagThree)   // In Turkey we have 11 digits mobile phone numbers you cant set those values for your country standarts.
        {
            if(pArr->numara <= 5000000000 || pArr->numara >= 6000000000)
            {
                printf("Invalid Phone Number!\n");
                FlagTwo = 1;
            }
        }
        if(!FlagOne && !FlagTwo && FlagThree == 0) // In Turkey we have 7 digits stable phone numbers you cant set those values for your country standarts.
        {
            if((pArr->numara <= 1000000 || pArr->numara >= 9999999) )
            {
                printf("Invalid Phone Number!\n");
                FlagTwo = 1;
            }
        }
        if(!FlagOne && !FlagTwo)
        {
            return 1;
        }
        else{
            return 0;
        }
}
int findWithNumber(char *fileName,long long number) // Find Contact with Number Function
{
    FILE *fp;
    Telephone *pArr,Contact[MAX];
    pArr = &Contact;
    char nameTag[20],kodTag[20],noTag[20];
    fp = fopen(fileName,"r+");
    int FlagOne = 0,i = 0;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s %s ",nameTag,&(pArr+i)->isim);
            fscanf(fp," %s %ld ",kodTag,&(pArr+i)->kod);
            fscanf(fp," %s %lld ",noTag,&(pArr+i)->numara);
            if((pArr+i)->numara == number)
            {
                printf("\n%d. Contact:\n%s %s\n%s %d\n%s %lld\n",i+1,nameTag,(pArr+i)->isim,kodTag,(pArr+i)->kod,noTag,(pArr+i)->numara);
                FlagOne++;
            }
            i++;
            if(FlagOne != 0)
            {
                fclose(fp);
                printf("\n%d Contact Found.\n",FlagOne);
                return 1;
            }
            else{
                fclose(fp);
                printf("\nContact Not Found.\n");
                return 0;
            }
        }
    }
    else{
        printf("Reading process failed!\n");
        exit(1);
    }
}
/* Delete Contact Function */
int deleteContact(char *fileName,long int code)
{
    /*
        To delete a Contact with file process get the all contacts in a new file except deleted one and delete old file rename new file with old file's name.
    */
    FILE *fp_old;
    FILE *fp_new;
    Telephone *pArr,Contact[MAX];
    pArr = &Contact[0];
    char nameTag[20],kodTag[20],noTag[20];
    int i=0, FlagOne = 0,contactNo,c=0;
    int contactFound[MAX];
    if((fp_old = fopen(fileName,"r")) == NULL)
    {
        printf("File couldn't open ! \n");
    }
    if((fp_new = fopen("New_File.txt","wt")) == NULL)
    {
        printf("File couldn't open ! \n");
    }
    while(!feof(fp_old)) // All Contacts assigned to a Struct array in old file.
    {
            fscanf(fp_old," %s %s ",nameTag,&(pArr+i)->isim);
            fscanf(fp_old," %s %ld ",kodTag,&(pArr+i)->kod);
            fscanf(fp_old," %s %lld ",noTag,&(pArr+i)->numara);
            if((pArr+i)->kod == code)
            {
                printf("\n%d. Contact:\n%s %s\n%s %ld\n%s %lld\n",i+1,nameTag,(pArr+i)->isim,kodTag,(pArr+i)->kod,noTag,(pArr+i)->numara);
                contactFound[c]=i;
                FlagOne++;
                c++;
            }
            i++;
   }
   if(FlagOne != 0)
   {    int c;
        printf("\n%d Contact found.\n",FlagOne);
        int FlagTwo = 0;
        do{
            printf("Contact Number want to delete:");
            scanf("%d",&contactNo);
            for(c=0;c<i;c++)
            {
                if(contactFound[c] == (contactNo-1))
                {
                    FlagTwo = 1;
                    break;
                }
            }
            if(c==i)
            {
                printf("\nInvalid contact number!\n");
            }
        }while(FlagTwo == 0);
        for(c=0;c<i;c++) //  All contacts printing in new file except deleted one.
        {
            if(c != (contactNo-1))
            {
                fprintf(fp_new,"Name: %s\n",(pArr+c)->isim);
                fprintf(fp_new,"Code: %ld\n",(pArr+c)->kod);
                fprintf(fp_new,"Phone: %lld\n",(pArr+c)->numara);
            }else{
                continue;
            }
        }
        printf("Contact Deleted!\n");
        fclose(fp_new);
        fclose(fp_old);
        /* File Switch processes */
        remove(fileName);
        rename("New_File.txt",fileName);
        return 1;
   }
   else{
        fclose(fp_new);
        fclose(fp_old);

        remove(fileName);
        rename("New_File.txt",fileName);
        printf("\nContact not found.\n");
        return 0;
   }
}
int countContacts(char *fileName)// Counts all contacts in the file and returns their quanity.
{
    FILE *fp;
    fp = fopen(fileName,"r+");
    Telephone *pArr,Telephone;
    pArr = &Telephone;
    char nameTag[20],kodTag[20],noTag[20];
    int i=0;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp," %s %s ",nameTag,&pArr->isim);
            fscanf(fp," %s %ld ",kodTag,&pArr->kod);
            fscanf(fp," %s %lld ",noTag,&pArr->numara);
            i++;
        }
        fclose(fp);
        return i;
    }
    else{
        printf("Not found file!\n");
        exit(1);
    }
}
