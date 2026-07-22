#include <stdio.h>
#include <string.h>

#define SIZE 6

int main(void) {
  int farmerNumbers[SIZE] = {101, 102, 103, 104, 105, 106};

  char farmerNames[SIZE][50] = {"Mwangi Kamau",   "Wanjiku Njeri",
                                "Peter Maina",    "Akinyi Otieno",
                                "Mutiso Musyoka", "Chebet Kiptoo"};

  char produceTypes[SIZE][20] = {"Milk",  "Coffee", "Potatoes",
                                 "Maize", "Milk",   "Vegetables"};

  int quantities[SIZE] = {120, 85, 300, 250, 150, 95};

  double pricesPerUnit[SIZE] = {55, 120, 40, 65, 55, 80};

  char paymentStatus[SIZE][10] = {"Pending", "Paid", "Pending",
                                  "Pending", "Paid", "Pending"};

  // Question 1: Display Farmer Records //

  int i;

  for (i = 0; i < SIZE; i++) {
    printf("Farmer Number : %d\n", farmerNumbers[i]);
    printf("Farmer Name   : %s\n", farmerNames[i]);
    printf("Produce Type  : %s\n", produceTypes[i]);
    printf("Quantity      : %d\n", quantities[i]);
    printf("Price Per Unit: %.2f\n", pricesPerUnit[i]);
    printf("Payment Status: %s\n", paymentStatus[i]);
    printf("\n");
  }

  // Question 2: Calculate Farmer Payments //

  double payments[SIZE];

  printf("\n Farmer Payments \n");

  for (i = 0; i < SIZE; i++) {
    payments[i] = quantities[i] * pricesPerUnit[i];
    printf("%s: KES %.2f\n", farmerNames[i], payments[i]);
  }

  return 0;
}
