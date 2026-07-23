#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <mysql.h>
#include "db_config.h"

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

  // Question 3: Calculate total pay //

  double totalPayment = 0;

  for (i = 0; i < SIZE; i++) {
    totalPayment = totalPayment + payments[i];
  }

  printf("\nTotal amount payable: KES %.2f\n", totalPayment);

  // Question 4: Identify Pending Payments //

  printf("\n Pending Payments \n");

  for (i = 0; i < SIZE; i++) {
    if (strcmp(paymentStatus[i], "Pending") == 0) {
      printf("Farmer Number : %d\n", farmerNumbers[i]);
      printf("Farmer Name   : %s\n", farmerNames[i]);
      printf("Amount Payable: KES %.2f\n", payments[i]);
      printf("Payment Status: %s\n", paymentStatus[i]);
      printf("\n");
    }
  }

      // Question 5: Update Payment Status //

    for (i = 0; i< SIZE; i++) {
      if (payments[i] < 10000 && strcmp(paymentStatus[i], "Pending") == 0) {
        strcpy(paymentStatus[i], "Paid");
      }
    }

    printf("\n Updated Payment Statuses \n");

    for (i = 0; i < SIZE; i++) {
      printf("%s: %s\n", farmerNames[i], paymentStatus[i]);
    }

    // Question 6: Finding the highest delivery //

  int highestPosition = 0;

    for (i = 1; i < SIZE; i++) {
        if (quantities[i] > quantities[highestPosition]) {
            highestPosition = i;
        }
    }

    printf("\n Highest Delivery \n");
    printf("Farmer Name: %s\n", farmerNames[highestPosition]);
    printf("Produce Type: %s\n", produceTypes[highestPosition]);
    printf("Quantity: %d\n", quantities[highestPosition]);

    // Question 7: Find the Lowest Payment //

  int lowestIndex = 0;

  for (i = 1; i < SIZE; i++) {
    if (payments[i] < payments[lowestIndex]) {
      lowestIndex = i;
    }
  }

  printf("\n Lowest Payment \n");
  printf("Farmer Name   : %s\n", farmerNames[lowestIndex]);
  printf("Amount Payable: KES %.2f\n", payments[lowestIndex]);

  // Connecting to the MySQL database //

  MYSQL *conn;

  conn = mysql_init(NULL);

  if (conn == NULL) {
    printf("mysql_init() failed\n");
    return 1;
  }

  conn = mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);

  if (conn == NULL) {
    printf("Connection failed!\n");
    return 1;
  } else {
    printf("Connected to the database successfully!\n");
  }

const char *pendingQuery =
      "SELECT FarmerNumber, FarmerName, Quantity, PricePerUnit, PaymentStatus "
      "FROM ProduceDeliveries WHERE PaymentStatus = 'Pending'";

  if (mysql_query(conn, pendingQuery)) {
    printf("Query failed: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  MYSQL_ROW row;

  printf("\n Pending Payments (from database) \n");

  while ((row = mysql_fetch_row(result)) != NULL) {
    double amountPayable = atof(row[2]) * atof(row[3]);
    printf("Farmer Number : %s\n", row[0]);
    printf("Farmer Name   : %s\n", row[1]);
    printf("Amount Payable: KES %.2f\n", amountPayable);
    printf("Payment Status: %s\n", row[4]);
    printf("\n");
  }

  mysql_free_result(result);


    // Question 5: Update Payment Status (SQL) //

  const char *updateQuery =
      "UPDATE ProduceDeliveries SET PaymentStatus = 'Paid' "
      "WHERE (Quantity * PricePerUnit) < 10000 AND PaymentStatus = 'Pending' ";

  if (mysql_query(conn, updateQuery)) {
    printf("Update failed: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  printf("\nRows updated: %llu\n", (unsigned long long)mysql_affected_rows(conn));

// Question 6: Find the Highest Delivery (SQL) //

  const char *highestQuery =
      "SELECT FarmerName, ProduceType, Quantity FROM ProduceDeliveries "
      "ORDER BY Quantity DESC LIMIT 1";

  if (mysql_query(conn, highestQuery)) {
    printf("Query failed: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  MYSQL_RES *highestResult = mysql_store_result(conn);
  MYSQL_ROW highestRow = mysql_fetch_row(highestResult);

  printf("\n Highest Delivery (from database) \n");
  printf("Farmer Name : %s\n", highestRow[0]);
  printf("Produce Type: %s\n", highestRow[1]);
  printf("Quantity    : %s\n", highestRow[2]);

  mysql_free_result(highestResult);

  // Question 7: Find the Lowest Payment (SQL) //

  const char *lowestQuery =
      "SELECT FarmerName, (Quantity * PricePerUnit) AS AmountPayable "
      "FROM ProduceDeliveries ORDER BY AmountPayable ASC LIMIT 1";

  if (mysql_query(conn, lowestQuery)) {
    printf("Query failed: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  MYSQL_RES *lowestResult = mysql_store_result(conn);
  MYSQL_ROW lowestRow = mysql_fetch_row(lowestResult);

  printf("\n--- Lowest Payment (from database) ---\n");
  printf("Farmer Name   : %s\n", lowestRow[0]);
  printf("Amount Payable: KES %s\n", lowestRow[1]);

  mysql_free_result(lowestResult);

  mysql_close(conn);
  return 0;
}
