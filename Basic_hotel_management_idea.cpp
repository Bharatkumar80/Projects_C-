#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct HotelRoom {
    string roomID;
    int level;
    int currentGuests;
    int maxCapacity;
};

// Function to check the validity of room information
int verifyRoomInfo(const HotelRoom& room) {
    if (room.level <= 0) {
        cout << "Invalid level number " << room.level << " for room " << room.roomID << endl;
        return 0;
    }
    if (room.maxCapacity <= 0) {
        cout << "Invalid capacity " << room.maxCapacity << " for room " << room.roomID << endl;
        return 0;
    }
    if (room.currentGuests < 0) {
        cout << "Invalid guest count " << room.currentGuests << " for room " << room.roomID << endl;
        return 0;
    }
    if (room.currentGuests > room.maxCapacity) {
        cout << "Exceeding capacity: " << room.currentGuests << " guests in room " << room.roomID << ". Max capacity is " << room.maxCapacity << endl;
        return 0;
    }
    return 1;
}

// Function to compute the guest occupancy rate
double computeOccupancyPercentage(int occupiedRooms, int totalRooms) {
    return totalRooms == 0 ? 0.0 : (static_cast<double>(occupiedRooms) / totalRooms) * 100;
}

// Function to calculate the required number of housekeepers
int determineHousekeepersRequired(const vector<HotelRoom>& rooms) {
    int totalGuests = 0;
    for (const auto& room : rooms) {
        totalGuests += room.currentGuests;
    }
    return (totalGuests + 7) / 8; // 1 housekeeper per 8 guests
}

// Function to handle and process hotel transactions
int handleTransactions(const string& transactionFileName, vector<HotelRoom>& rooms) {
    ifstream transactionFile(transactionFileName);
    if (!transactionFile) {
        cout << "Error: Unable to open transaction file." << endl;
        return 0;
    }

    string transactionType, roomID;
    int guestCount;

    // Process each transaction
    while (transactionFile >> transactionType >> roomID >> guestCount) {
        bool validRoom = false;
        for (auto& room : rooms) {
            if (room.roomID == roomID) {
                validRoom = true;
                if (transactionType == "CI") { // Check-in
                    if (room.currentGuests + guestCount <= room.maxCapacity) {
                        room.currentGuests += guestCount;
                    } else {
                        cout << "Error: Cannot check in " << guestCount << " guests to room " << roomID << ". Max capacity is " << room.maxCapacity << "." << endl;
                    }
                } else if (transactionType == "CO") { // Check-out
                    if (room.currentGuests - guestCount >= 0) {
                        room.currentGuests -= guestCount;
                    } else {
                        cout << "Error: Cannot check out " << guestCount << " guests from room " << roomID << ". Current guests: " << room.currentGuests << "." << endl;
                    }
                } else {
                    cout << "Invalid transaction type: " << transactionType << " in record." << endl;
                }
                break;
            }
        }
        if (!validRoom) {
            cout << "Error: Room ID " << roomID << " not found." << endl;
        }
    }
    return 1;
}

int main() {
    string hotelDataFile, guestTransactionFile;

    // Request hotel data file from user
    cout << "Enter the file path for the hotel data: ";
    cin >> hotelDataFile;

    ifstream hotelFileStream(hotelDataFile);
    if (!hotelFileStream) {
        cout << "Error: Unable to open hotel data file." << endl;
        return 1;
    }

    string hotelName;
    double breakEvenOccupancyRate;
    hotelFileStream >> hotelName >> breakEvenOccupancyRate;

    vector<HotelRoom> rooms;
    HotelRoom tempRoom;
    while (hotelFileStream >> tempRoom.roomID >> tempRoom.level >> tempRoom.currentGuests >> tempRoom.maxCapacity) {
        if (verifyRoomInfo(tempRoom)) {
            rooms.push_back(tempRoom);
        }
    }

    int totalRooms = rooms.size();
    int occupiedRooms = 0;
    for (const auto& room : rooms) {
        if (room.currentGuests > 0) {
            occupiedRooms++;
        }
    }

    double occupancyRate = computeOccupancyPercentage(occupiedRooms, totalRooms);

    cout << fixed << setprecision(2);
    cout << "The hotel has " << totalRooms << " rooms; break-even occupancy rate is " << (breakEvenOccupancyRate * 100) << "%." << endl;
    cout << "Currently, " << occupiedRooms << " rooms are occupied, resulting in an occupancy rate of " << occupancyRate << "%." << endl;

    if (occupancyRate >= breakEvenOccupancyRate * 100) {
        cout << "The hotel is profitable." << endl;
    } else {
        cout << "The hotel is not profitable." << endl;
    }

    // Request guest transaction data file
    cout << "Enter the file path for the guest transactions: ";
    cin >> guestTransactionFile;

    if (handleTransactions(guestTransactionFile, rooms)) {
        int totalGuests = 0;
        for (const auto& room : rooms) {
            totalGuests += room.currentGuests;
        }
        int requiredHousekeepers = determineHousekeepersRequired(rooms);

        cout << "With " << totalGuests << " guests, the hotel requires " << requiredHousekeepers << " housekeepers." << endl;
        occupancyRate = computeOccupancyPercentage(totalGuests, totalRooms);

        cout << "The updated occupancy rate is " << occupancyRate << "%." << endl;
        if (occupancyRate >= breakEvenOccupancyRate * 100) {
            cout << "The hotel is profitable." << endl;
        } else {
            cout << "The hotel is not profitable." << endl;
        }
    }

    return 0;
}
