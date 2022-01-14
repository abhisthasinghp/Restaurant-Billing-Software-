#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ITEMS{
    char item[20];
    float price;
    int qty;
};

struct ORDERS{
    char CUSTOMER[50];
    char date[50];
    int numberofitems;
    struct ITEMS itm[50];
};

//funtions to generate bills
void GenerateBILLHEADER(char name[50], char date[30]) {
	printf("\n\n");
		printf("\t   HAM Restaurant");
		printf("\n\t ----------------------");
		printf("\nDate: %s", date);
		printf("\nInvoice To: %s", name);
		printf("\n");
		printf("---------------------------------------------------\n");
		printf("Items\t\t");
		printf("Quantity\t\t");
		printf("TOTAL\t\t");
		printf("\n---------------------------------------------------");
		printf("\n\n");
}

void GenerateBILLBODY(char item[30], int qty, float price) {
	printf("%s\t\t", item);
		printf("%d\t\t", qty);
		printf("%.2f\t\t", qty * price);
		printf("\n");
}

void BillFooter(float TOTAL) {
	printf("\n");
	float discount = 0.1 * TOTAL;
	float nETTOTAL = TOTAL - discount;
	float GST = 0.09 * nETTOTAL;
	float GRAnDTOTAL = nETTOTAL + GST;
	printf("----------------------------------------------------\n");
	printf("Sub TOTAL\t\t\t%.2f", TOTAL);
	printf("\nDiscount @10%s\t\t\t%.2f", "%", discount);
	printf("\n\t\t\t\t--------------------");
	printf("\nnet TOTAL\t\t\t%.2f", nETTOTAL);
	printf("\nGST @9%s\t\t\t\t%.2f", "%", GST);
	printf("\n----------------------------------------------------");
	printf("\nGrand TOTAL\t\t\t%.2f", GRAnDTOTAL);
	printf("\n----------------------------------------------------");
}

int main(){
    int option,n;
    struct ORDERS ord;
    struct ORDERS order;
    char saveBill ='y', contFlag = 'y';
    char name[50];
    FILE *fp;
	//dashboard
    while(contFlag == 'y') {
        system("cls");
        float TOTAL;
        int InvoiceFound = 0;
        printf("\t**********HAM Restaurant**********");
        printf("\n\n---------CHOICES---------");
        printf("\n\n1. New Invoice");
        printf("\n2. Display all Invoices");
        printf("\n3. Search Invoice");
        printf("\n4. Exit");

        printf("\n\nEnter your option:\t");
        scanf("%d", &option);
        fgetc(stdin);

        switch (option) {
            case 1:
                system("cls");
                printf("\nEnter customer's name:\t");
                fgets(ord.CUSTOMER, 50, stdin);
                ord.CUSTOMER[strlen(ord.CUSTOMER) - 1] = 0;
                strcpy(ord.date, __DATE__);
                printf("\nEnter total number of items ordered:\t");
                scanf("%d", &n);
                ord.numberofitems = n;

                for (int i = 0; i < n; i++) {
                    fgetc(stdin);
                    printf("\n\n");
                    printf("Please enter the item %d:", i + 1);
                    fgets(ord.itm[i].item, 20, stdin);
                    ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                    printf("\nPlease enter the quantity:");
                    scanf("%d", &ord.itm[i].qty);
                    printf("\nPlease enter the unit price:");
                    scanf("%f", &ord.itm[i].price);
                    TOTAL += ord.itm[i].qty * ord.itm[i].price;
                }

                GenerateBILLHEADER(ord.CUSTOMER, ord.date);
                for (int i = 0; i < ord.numberofitems; i++) {
                    GenerateBILLBODY(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                }
                BillFooter(TOTAL);

                printf("\nDo you want to save the invoice? [y/n]\t");
                scanf("%s", &saveBill);
                if (saveBill == 'y') {
                    fp = fopen("RestaurantReciept.dat", "a+");
                    fwrite(&ord, sizeof(struct ORDERS), 1, fp);
                    if (fwrite != 0)
                        printf("\nSuccessfully saved");
                    else
                        printf("\nError, Not Saved");
                    fclose(fp);
                }
                break;

            case 2:
                system("cls");
                fp = fopen("RestaurantReciept.dat", "r");
                printf("\n *****Your Previous Invoices*****\n");
                while (fread(&order, sizeof(struct ORDERS), 1, fp)) {
                    float tot = 0;
                    GenerateBILLHEADER(order.CUSTOMER, order.date);
                    for (int i = 0; i < order.numberofitems; i++) {
                        GenerateBILLBODY(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    BillFooter(tot);
                }
                break;

            case 3:
                printf("\nEnter the name of the CUSTOMER:\t");
                //fgetc(stdin);
                fgets(name, 50, stdin);
                name[strlen(name) - 1] = 0;
                system("cls");
                fp = fopen("RestaurantRecieptBill.dat", "r");
                while (fread(&order, sizeof(struct ORDERS), 1, fp)) {
                    float tot = 0;
                    if (!strcmp(order.CUSTOMER,name)) {
                        printf("\n *****Invoice of %s*****\n", name);
                        GenerateBILLHEADER(order.CUSTOMER, order.date);
                        for (int i = 0; i < order.numberofitems; i++) {
                            GenerateBILLBODY(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                            tot += order.itm[i].qty * order.itm[i].price;
                        }
                        BillFooter(tot);
                        InvoiceFound = 1;
                    }
                }
                if (!InvoiceFound) {
                    printf("Sorry, the invoice for %s doesn't exist", name);
                }
                fclose(fp);
                break;

            case 4:
                printf("\n\t\t HAVE A GOOD DAY\n\n");
                exit(0);
                break;

            default:
                printf("Sorry Invalid choice");
                break;

        }
        printf("\nDo you want to continue?[y/n]\t");
        scanf("%s", &contFlag);
    }
    printf("\n\t\t HAVE A GOOD DAY\n\n");
	printf("\n\n");
	return 0;
}
