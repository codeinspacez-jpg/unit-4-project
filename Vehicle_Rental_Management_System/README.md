# Vehicle Rental Management System

A menu-driven C mini project based on the supplied Unit 4 assignment. It demonstrates **structures, unions, enumerations, arrays, and functions**.

## Features

1. Add a car or bike
2. Display all registered vehicles
3. Search for a vehicle by its ID
4. Rent an available vehicle
5. Return a rented vehicle
6. Display only available vehicles
7. Exit

## Data design

- `struct Vehicle` stores the common vehicle information.
- `union VehicleDetail` stores either a car's seating capacity or a bike's engine capacity.
- `enum VehicleType` identifies `CAR` or `BIKE`.
- `enum RentalStatus` identifies `AVAILABLE` or `RENTED`.
- An array stores up to 100 vehicle records.

The program prevents duplicate vehicle IDs, renting a vehicle that is already rented, and returning a vehicle that is already available. It also reports missing IDs and a full vehicle list.

## Requirements

- Visual Studio Code
- GCC C compiler
- VS Code C/C++ extension (recommended)

## Compile and run

Open this folder in VS Code, then select **Terminal → New Terminal**.

Compile:

```bash
gcc main.c -o vehicle_rental
```

Run on Windows PowerShell:

```powershell
.\vehicle_rental.exe
```

Run on Linux/macOS:

```bash
./vehicle_rental
```

## Example workflow

1. Choose `1` to add a vehicle.
2. Enter its ID, name, brand, and type.
3. Enter the seating capacity for a car, or engine capacity for a bike.
4. Choose `2` to view all vehicles or `3` to search by ID.
5. Choose `4` to rent an available vehicle.
6. Choose `5` to return a rented vehicle.
7. Choose `6` to view vehicles currently available.
8. Choose `7` to exit.

## Sample output

See [`sample_output.txt`](sample_output.txt) for a sample session.

## Note

Records are stored in memory while the program runs. They are cleared when the application exits. Permanent file storage is not part of the supplied assignment.
