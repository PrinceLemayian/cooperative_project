#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <mysql.h>
#include "db_config.h"

#define MAX_RECORDS 100

int main(void) {

  int farmerNumbers[MAX_RECORDS];
  char farmerNames[MAX_RECORDS][50];
  char produceTypes[MAX_RECORDS][20];
  int quantities[MAX_RECORDS];
  double pricesPerUnit[MAX_RECORDS];
  char paymentStatus[MAX_RECORDS][10];
  double payments[MAX_RECORDS];

  int recordCount = 0;
  int i;

  // Connect to the database

  MYSQL *conn = mysql_init(NULL);
  if (conn == NULL) {
    printf("mysql_init() failed\n");
    return 1;
  }

  conn = mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0);
  if (conn == NULL) {
    printf("Connection failed!\n");
    return 1;
  }
  printf("Connected to the database successfully!\n");

  // Retrieve records into arrays

  const char *loadQuery =
      "SELECT FarmerNumber, FarmerName, ProduceType, Quantity, PricePerUnit, PaymentStatus "
      "FROM ProduceDeliveries";

  if (mysql_query(conn, loadQuery)) {
    printf("Failed to load records: %s\n", mysql_error(conn));
    mysql_close(conn);
    return 1;
  }

  MYSQL_RES *loadResult = mysql_store_result(conn);
  MYSQL_ROW loadRow;

  while ((loadRow = mysql_fetch_row(loadResult)) != NULL && recordCount < MAX_RECORDS) {
    farmerNumbers[recordCount] = atoi(loadRow[0]);
    strcpy(farmerNames[recordCount], loadRow[1]);
    strcpy(produceTypes[recordCount], loadRow[2]);
    quantities[recordCount] = atoi(loadRow[3]);
    pricesPerUnit[recordCount] = atof(loadRow[4]);
    strcpy(paymentStatus[recordCount], loadRow[5]);
    payments[recordCount] = quantities[recordCount] * pricesPerUnit[recordCount];
    recordCount++;
  }

  mysql_free_result(loadResult);

  printf("Loaded %d farmer records from the database.\n", recordCount);

  // Menu loop

  int choice;
  int running = 1;

  while (running) {

    printf("\n===== Nyeri Green Farmers Cooperative =====\n");
    printf("1. Display all farmer deliveries\n");
    printf("2. Search for a farmer\n");
    printf("3. Calculate farmer payments\n");
    printf("4. Display pending payments\n");
    printf("5. Update payment status\n");
    printf("6. Display large deliveries\n");
    printf("7. Generate daily report\n");
    printf("8. Save updated records to the database\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
      while (getchar() != '\n');   // clear bad input from the buffer
      printf("Invalid input. Please enter a number from the menu.\n");
      continue;
    }

    switch (choice) {

      case 1: {
        printf("\n--- All Farmer Deliveries ---\n");
        for (i = 0; i < recordCount; i++) {
          printf("Farmer Number : %d\n", farmerNumbers[i]);
          printf("Farmer Name   : %s\n", farmerNames[i]);
          printf("Produce Type  : %s\n", produceTypes[i]);
          printf("Quantity      : %d\n", quantities[i]);
          printf("Price Per Unit: KES %.2f\n", pricesPerUnit[i]);
          printf("Payment Status: %s\n", paymentStatus[i]);
          printf("\n");
        }
        break;
      }

      case 2: {
        int searchNumber;
        int foundIndex = -1;

        printf("Enter farmer number to search: ");
        if (scanf("%d", &searchNumber) != 1) {
          while (getchar() != '\n');
          printf("Invalid farmer number.\n");
          break;
        }

        for (i = 0; i < recordCount; i++) {
          if (farmerNumbers[i] == searchNumber) {
            foundIndex = i;
          }
        }

        if (foundIndex != -1) {
          printf("\nFarmer Number : %d\n", farmerNumbers[foundIndex]);
          printf("Farmer Name   : %s\n", farmerNames[foundIndex]);
          printf("Produce Type  : %s\n", produceTypes[foundIndex]);
          printf("Quantity      : %d\n", quantities[foundIndex]);
          printf("Amount Payable: KES %.2f\n", payments[foundIndex]);
          printf("Payment Status: %s\n", paymentStatus[foundIndex]);
        } else {
          printf("Farmer record not found.\n");
        }
        break;
      }

      case 3: {
        printf("\n--- Farmer Payments ---\n");
        for (i = 0; i < recordCount; i++) {
          payments[i] = quantities[i] * pricesPerUnit[i];
          printf("%s: KES %.2f\n", farmerNames[i], payments[i]);
        }
        break;
      }

      case 4: {
        printf("\n--- Pending Payments ---\n");
        for (i = 0; i < recordCount; i++) {
          if (strcmp(paymentStatus[i], "Pending") == 0) {
            printf("Farmer Number : %d\n", farmerNumbers[i]);
            printf("Farmer Name   : %s\n", farmerNames[i]);
            printf("Amount Payable: KES %.2f\n", payments[i]);
            printf("\n");
          }
        }
        break;
      }

      case 5: {
        int updatedCount = 0;
        for (i = 0; i < recordCount; i++) {
          if (payments[i] < 10000 && strcmp(paymentStatus[i], "Pending") == 0) {
            strcpy(paymentStatus[i], "Paid");
            updatedCount++;
          }
        }
        printf("%d payment status(es) updated to Paid in memory.\n", updatedCount);
        printf("Use option 8 to save these changes to the database.\n");
        break;
      }

      case 6: {
        printf("\n--- Large Deliveries (over 200 units) ---\n");
        for (i = 0; i < recordCount; i++) {
          if (quantities[i] > 200) {
            printf("Farmer Number: %d, Farmer Name: %s, Quantity: %d\n",
                   farmerNumbers[i], farmerNames[i], quantities[i]);
          }
        }
        break;
      }

      case 7: {
        int totalQuantity = 0;
        double totalGross = 0;
        int paidCount = 0;
        int pendingCount = 0;
        int highestDeliveryIndex = 0;
        int highestPaymentIndex = 0;

        for (i = 0; i < recordCount; i++) {
          totalQuantity += quantities[i];
          totalGross += payments[i];

          if (strcmp(paymentStatus[i], "Paid") == 0) {
            paidCount++;
          } else {
            pendingCount++;
          }

          if (quantities[i] > quantities[highestDeliveryIndex]) {
            highestDeliveryIndex = i;
          }
          if (payments[i] > payments[highestPaymentIndex]) {
            highestPaymentIndex = i;
          }
        }

        printf("\n--- Daily Cooperative Report ---\n");
        printf("Total Farmers          : %d\n", recordCount);
        printf("Total Quantity         : %d\n", totalQuantity);
        printf("Total Gross Payment    : KES %.2f\n", totalGross);
        printf("Farmers Paid            : %d\n", paidCount);
        printf("Farmers Pending         : %d\n", pendingCount);
        printf("Highest Delivery        : %s (%d units)\n",
               farmerNames[highestDeliveryIndex], quantities[highestDeliveryIndex]);
        printf("Highest Payment         : %s (KES %.2f)\n",
               farmerNames[highestPaymentIndex], payments[highestPaymentIndex]);
        break;
      }

      case 8: {
        char confirm;
        printf("Save all updated payment statuses to the database? (Y/N): ");
        scanf(" %c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {

          MYSQL_STMT *stmt = mysql_stmt_init(conn);
          const char *updateSql =
              "UPDATE ProduceDeliveries SET PaymentStatus = ? WHERE FarmerNumber = ?";

          if (mysql_stmt_prepare(stmt, updateSql, strlen(updateSql))) {
            printf("Prepare failed: %s\n", mysql_stmt_error(stmt));
            mysql_stmt_close(stmt);
            break;
          }

          int savedCount = 0;
          int skippedCount = 0;

          for (i = 0; i < recordCount; i++) {

            // Skip invalid records
            if (quantities[i] <= 0 || pricesPerUnit[i] <= 0 || farmerNumbers[i] <= 0) {
              printf("Skipped farmer %d: invalid record.\n", farmerNumbers[i]);
              skippedCount++;
              continue;
            }

            // Skip duplicate farmer numbers (keep only the first occurrence)
            int isDuplicate = 0;
            int j;
            for (j = 0; j < i; j++) {
              if (farmerNumbers[j] == farmerNumbers[i]) {
                isDuplicate = 1;
                break;
              }
            }
            if (isDuplicate) {
              printf("Skipped farmer %d: duplicate record.\n", farmerNumbers[i]);
              skippedCount++;
              continue;
            }

            MYSQL_BIND bind[2];
            memset(bind, 0, sizeof(bind));

            unsigned long statusLen = strlen(paymentStatus[i]);

            bind[0].buffer_type = MYSQL_TYPE_STRING;
            bind[0].buffer = paymentStatus[i];
            bind[0].buffer_length = sizeof(paymentStatus[i]);
            bind[0].length = &statusLen;

            bind[1].buffer_type = MYSQL_TYPE_LONG;
            bind[1].buffer = &farmerNumbers[i];

            if (mysql_stmt_bind_param(stmt, bind)) {
              printf("Bind failed for farmer %d: %s\n", farmerNumbers[i], mysql_stmt_error(stmt));
              continue;
            }

            if (mysql_stmt_execute(stmt)) {
              printf("Update failed for farmer %d: %s\n", farmerNumbers[i], mysql_stmt_error(stmt));
              continue;
            }

            savedCount++;
          }

          mysql_stmt_close(stmt);
          printf("%d record(s) saved to the database. %d record(s) skipped.\n", savedCount, skippedCount);

        } else {
          printf("Save cancelled.\n");
        }
        break;
      }

      case 9: {
        printf("Exiting program. Goodbye!\n");
        running = 0;
        break;
      }

      default: {
        printf("Invalid choice. Please select an option between 1 and 9.\n");
        break;
      }
    }
  }

  mysql_close(conn);
  return 0;
}