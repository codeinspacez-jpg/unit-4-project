#include <stdio.h>
#include <string.h>

#define MAX_VEHICLES 100

enum VehicleType {
    CAR = 1,
    BIKE = 2
};

enum RentalStatus {
    AVAILABLE = 1,
    RENTED = 2
};

union VehicleDetail {
    int seatingCapacity;   /* Used when the vehicle is a car */
    int engineCapacity;    /* Used when the vehicle is a bike */
};

struct Vehicle {
    int vehicleID;
    char name[50];
    char brand[50];
    enum VehicleType type;
    enum RentalStatus status;
    union VehicleDetail detail;
};

struct Vehicle vehicles[MAX_VEHICLES];
int vehicleCount = 0;

/* Read a complete line, including spaces. */
void readLine(const char *prompt, char *buffer, int size) {
    int ch;

    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        /* Discard extra characters if the input was longer than the buffer. */
        if (strchr(buffer, '\0') != NULL) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* discard */
            }
        }
    }
}

/* Read an integer safely. */
int readInt(const char *prompt) {
    char line[100];
    int value;
    char extra;

    while (1) {
        readLine(prompt, line, sizeof(line));
        if (sscanf(line, "%d %c", &value, &extra) == 1) {
            return value;
        }
        printf("Invalid input. Please enter a whole number.\n");
    }
}

int findVehicleIndex(int id) {
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i].vehicleID == id) {
            return i;
        }
    }
    return -1;
}

void addVehicle(void) {
    struct Vehicle v;

    if (vehicleCount >= MAX_VEHICLES) {
        printf("\nVehicle limit reached. Cannot add more vehicles.\n");
        return;
    }

    printf("\n--- Add Vehicle ---\n");
    v.vehicleID = readInt("Enter Vehicle ID: ");

    if (findVehicleIndex(v.vehicleID) != -1) {
        printf("A vehicle with this ID already exists. Vehicle not added.\n");
        return;
    }

    readLine("Enter Vehicle Name: ", v.name, sizeof(v.name));
    readLine("Enter Brand: ", v.brand, sizeof(v.brand));

    printf("Select Vehicle Type:\n");
    printf("1. Car\n");
    printf("2. Bike\n");

    int choice;
    do {
        choice = readInt("Enter choice: ");
        if (choice != CAR && choice != BIKE) {
            printf("Please select 1 for Car or 2 for Bike.\n");
        }
    } while (choice != CAR && choice != BIKE);

    v.type = (enum VehicleType)choice;

    if (v.type == CAR) {
        do {
            v.detail.seatingCapacity = readInt("Enter Number of Seats: ");
            if (v.detail.seatingCapacity <= 0) {
                printf("Seating capacity must be positive.\n");
            }
        } while (v.detail.seatingCapacity <= 0);
    } else {
        do {
            v.detail.engineCapacity = readInt("Enter Engine Capacity (cc): ");
            if (v.detail.engineCapacity <= 0) {
                printf("Engine capacity must be positive.\n");
            }
        } while (v.detail.engineCapacity <= 0);
    }

    v.status = AVAILABLE;
    vehicles[vehicleCount] = v;
    vehicleCount++;

    printf("\nVehicle Added Successfully!\n");
}

void printVehicle(const struct Vehicle *v) {
    printf("\nVehicle ID : %d\n", v->vehicleID);
    printf("Name       : %s\n", v->name);
    printf("Brand      : %s\n", v->brand);

    if (v->type == CAR) {
        printf("Type       : Car\n");
        printf("Seats      : %d\n", v->detail.seatingCapacity);
    } else {
        printf("Type       : Bike\n");
        printf("Engine     : %d cc\n", v->detail.engineCapacity);
    }

    printf("Status     : %s\n",
           v->status == AVAILABLE ? "Available" : "Rented");
}

void displayAllVehicles(void) {
    printf("\n--- All Registered Vehicles ---\n");

    if (vehicleCount == 0) {
        printf("No vehicles have been registered yet.\n");
        return;
    }

    for (int i = 0; i < vehicleCount; i++) {
        printf("\nVehicle %d\n", i + 1);
        printf("------------------------------\n");
        printVehicle(&vehicles[i]);
    }
}

void searchVehicle(void) {
    int id = readInt("\nEnter Vehicle ID to search: ");
    int index = findVehicleIndex(id);

    if (index == -1) {
        printf("Vehicle ID %d was not found.\n", id);
        return;
    }

    printf("\nVehicle Found:\n");
    printVehicle(&vehicles[index]);
}

void rentVehicle(void) {
    int id = readInt("\nEnter Vehicle ID to rent: ");
    int index = findVehicleIndex(id);

    if (index == -1) {
        printf("Vehicle ID %d was not found.\n", id);
    } else if (vehicles[index].status == RENTED) {
        printf("This vehicle is already rented.\n");
    } else {
        vehicles[index].status = RENTED;
        printf("Vehicle rented successfully!\n");
    }
}

void returnVehicle(void) {
    int id = readInt("\nEnter Vehicle ID to return: ");
    int index = findVehicleIndex(id);

    if (index == -1) {
        printf("Vehicle ID %d was not found.\n", id);
    } else if (vehicles[index].status == AVAILABLE) {
        printf("This vehicle is already available. It cannot be returned again.\n");
    } else {
        vehicles[index].status = AVAILABLE;
        printf("Vehicle returned successfully!\n");
    }
}

void displayAvailableVehicles(void) {
    int found = 0;

    printf("\n--- Available Vehicles ---\n");

    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i].status == AVAILABLE) {
            found = 1;
            printVehicle(&vehicles[i]);
            printf("------------------------------\n");
        }
    }

    if (!found) {
        printf("No vehicles are currently available.\n");
    }
}

void displayMenu(void) {
    printf("\n===== VEHICLE RENTAL MANAGEMENT SYSTEM =====\n");
    printf("1. Add Vehicle\n");
    printf("2. Display All Vehicles\n");
    printf("3. Search Vehicle\n");
    printf("4. Rent Vehicle\n");
    printf("5. Return Vehicle\n");
    printf("6. Display Available Vehicles\n");
    printf("7. Exit\n");
}

int main(void) {
    int choice;

    do {
        displayMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addVehicle();
                break;
            case 2:
                displayAllVehicles();
                break;
            case 3:
                searchVehicle();
                break;
            case 4:
                rentVehicle();
                break;
            case 5:
                returnVehicle();
                break;
            case 6:
                displayAvailableVehicles();
                break;
            case 7:
                printf("\nThank you for using the Vehicle Rental Management System!\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a number from 1 to 7.\n");
        }
    } while (choice != 7);

    return 0;
}
