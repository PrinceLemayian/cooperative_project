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

  // Question 8: Search for a Farmer //

  int searchNumber;
  int foundIndex = -1;

  printf("\nEnter farmer number to search: ");
  scanf("%d", &searchNumber);

  for (i = 0; i < SIZE; i++) {
    if (farmerNumbers[i] == searchNumber) {
      foundIndex = i;
    }
  }

  printf("\n Farmer Search \n");

  if (foundIndex != -1) {
    printf("Farmer Number : %d\n", farmerNumbers[foundIndex]);
    printf("Farmer Name   : %s\n", farmerNames[foundIndex]);
    printf("Produce Type  : %s\n", produceTypes[foundIndex]);
    printf("Quantity      : %d\n", quantities[foundIndex]);
  } else {
    printf("Farmer not found.\n");
  }

  // Question 9: Counting Produce Categories //

  char produceCategories[5][20] = {"Milk", "Coffee", "Maize", "Potatoes", "Vegetables"};
  int produceCounts[5] = {0, 0, 0, 0, 0};

  int categoryIndex;

  for (categoryIndex = 0; categoryIndex < 5; categoryIndex++) {
    for (i = 0; i < SIZE; i++) {
      if (strcmp(produceTypes[i], produceCategories[categoryIndex]) == 0) {
        produceCounts[categoryIndex]++;
      }
    }
  }

  printf("\n Produce Category Counts \n");

  for (categoryIndex = 0; categoryIndex < 5; categoryIndex++) {
    printf("%s: %d\n", produceCategories[categoryIndex], produceCounts[categoryIndex]);
  }

  // Question 10: Calculate Payments by Produce Type //

  double producePayments[5] = {0, 0, 0, 0, 0};

  for (categoryIndex = 0; categoryIndex < 5; categoryIndex++) {
    for (i = 0; i < SIZE; i++) {
      if (strcmp(produceTypes[i], produceCategories[categoryIndex]) == 0) {
        producePayments[categoryIndex] += payments[i];
      }
    }
  }

  printf("\n Payments by Produce Type \n");

  for (categoryIndex = 0; categoryIndex < 5; categoryIndex++) {
    printf("%s: KES %.2f\n", produceCategories[categoryIndex], producePayments[categoryIndex]);
  }

  // Question 11: Identify Large Deliveries //

  int largeDeliveryFarmers[SIZE];
  int largeDeliveryCount = 0;

  for (i = 0; i < SIZE; i++) {
    if (quantities[i] > 200) {
      largeDeliveryFarmers[largeDeliveryCount] = farmerNumbers[i];
      largeDeliveryCount++;
    }
  }

  printf("\n Large Deliveries (over 200 units) \n");

  for (i = 0; i < largeDeliveryCount; i++) {
    printf("Farmer Number: %d\n", largeDeliveryFarmers[i]);
  }

  // Question 12: Apply Cooperative Levy //

  double levies[SIZE];
  double netPayments[SIZE];

  printf("\n Net Payments After Levy \n");

  for (i = 0; i < SIZE; i++) {
    levies[i] = payments[i] * 0.02;
    netPayments[i] = payments[i] - levies[i];
    printf("%s: Gross KES %.2f, Levy KES %.2f, Net KES %.2f\n",
           farmerNames[i], payments[i], levies[i], netPayments[i]);
  }

  // Question 14: Identify Invalid Records //

  printf("\n Invalid Records \n");

  int foundInvalid = 0;

  for (i = 0; i < SIZE; i++) {
    if (quantities[i] <= 0 || pricesPerUnit[i] <= 0 || farmerNumbers[i] <= 0) {
      printf("Farmer Number : %d\n", farmerNumbers[i]);
      printf("Farmer Name   : %s\n", farmerNames[i]);
      printf("Quantity      : %d\n", quantities[i]);
      printf("Price Per Unit: %.2f\n", pricesPerUnit[i]);
      printf("Reason        : Invalid record\n");
      printf("\n");
      foundInvalid = 1;
    }
  }

  if (foundInvalid == 0) {
    printf("No invalid records found.\n");
  }

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

  printf("\n Lowest Payment (from database) \n");
  printf("Farmer Name   : %s\n", lowestRow[0]);
  printf("Amount Payable: KES %s\n", lowestRow[1]);

  mysql_free_result(lowestResult);

  // Question 8: Search for a Farmer (SQL) //

  // Empty buffer big enough to hold finished SQL text
  char searchQuery[200];

  // Build the query text using the number the user typed in
  sprintf(searchQuery,
          "SELECT FarmerNumber, FarmerName, ProduceType, Quantity "
          "FROM ProduceDeliveries WHERE FarmerNumber = %d",
          searchNumber);

  if (mysql_query(conn, searchQuery)) {
    printf("Query failed: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  MYSQL_RES *searchResult = mysql_store_result(conn);
  MYSQL_ROW searchRow = mysql_fetch_row(searchResult);

  printf("\n Farmer Search (from database) \n");

  if (searchRow != NULL) { 
    printf("Farmer Number : %s\n", searchRow[0]);
    printf("Farmer Name   : %s\n", searchRow[1]);
    printf("Produce Type  : %s\n", searchRow[2]);
    printf("Quantity      : %s\n", searchRow[3]);
  } else {
    printf("Farmer not found.\n");
  }

  mysql_free_result(searchResult);

// Question 11: Large Deliveries (SQL) //

  const char *largeDeliveryQuery =
      "SELECT FarmerNumber, FarmerName, Quantity FROM ProduceDeliveries "
      "WHERE Quantity > 200";

  if (mysql_query(conn, largeDeliveryQuery)) {
    printf("Query failed: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  MYSQL_RES *largeResult = mysql_store_result(conn);
  MYSQL_ROW largeRow;

  printf("\n Large Deliveries (from database) \n");

  while ((largeRow = mysql_fetch_row(largeResult)) != NULL) {
    printf("Farmer Number: %s, Farmer Name: %s, Quantity: %s\n",
           largeRow[0], largeRow[1], largeRow[2]);
  }

  mysql_free_result(largeResult);

  // Question 14: Identify Invalid Records (SQL) //

  const char *invalidQuery =
      "SELECT FarmerNumber, FarmerName, Quantity, PricePerUnit "
      "FROM ProduceDeliveries "
      "WHERE Quantity <= 0 OR PricePerUnit <= 0 OR FarmerNumber <= 0";

  if (mysql_query(conn, invalidQuery)) {
    printf("Query failed: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  MYSQL_RES *invalidResult = mysql_store_result(conn);
  MYSQL_ROW invalidRow;

  printf("\n Invalid Records (from database) \n");

  int foundInvalidDb = 0;

  while ((invalidRow = mysql_fetch_row(invalidResult)) != NULL) {
    printf("Farmer Number : %s\n", invalidRow[0]);
    printf("Farmer Name   : %s\n", invalidRow[1]);
    printf("Quantity      : %s\n", invalidRow[2]);
    printf("Price Per Unit: %s\n", invalidRow[3]);
    printf("\n");
    foundInvalidDb = 1;
  }

  if (foundInvalidDb == 0) {
    printf("No invalid records found.\n");
  }

  mysql_free_result(invalidResult);

 // Question 14: Remove Invalid Records (SQL) //

  if (foundInvalidDb == 1) {
    char confirm;
    printf("Delete all invalid records shown above? (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
      const char *deleteQuery =
          "DELETE FROM ProduceDeliveries "
          "WHERE Quantity <= 0 OR PricePerUnit <= 0 OR FarmerNumber <= 0";

      if (mysql_query(conn, deleteQuery)) {
        printf("Delete failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
      }

      printf("\nInvalid records removed: %llu\n", (unsigned long long)mysql_affected_rows(conn));
    } else {
      printf("Deletion cancelled.\n");
    }
  }

  mysql_close(conn);
  return 0;
}
