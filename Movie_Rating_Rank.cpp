#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Function prototypes
int sortRatings(vector<double> &ratings);
double calculateAverage(const vector<double> &ratings);
double calculateMedian(const vector<double> &ratings);

int main() {
    // Get the filename from the user
    string filename;
    cout << "Enter the filename containing the movie ratings: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Declare variables
    string movieTitle;
    vector<double> ratings(9);
    double highestAverage = 0.0;
    double highestMedian = 0.0;
    string winningMovie;
    int movieCount = 0;
    bool wasTieBreaker = false;

    cin.ignore();

    // Read the file and process the data
    while (getline(inputFile, movieTitle) && movieCount < 10) {
        for (int i = 0; i < 9; i++) {
            if (!(inputFile >> ratings[i])) {
                cout << "Error reading ratings." << endl;
                return 1;
            }

            // Ensuring ratings are within a valid range
            if (ratings[i] < 0) {
                ratings[i] = abs(ratings[i]);
            }
            if (ratings[i] > 100) {
                ratings[i] -= 100;
            }
        }
        inputFile.ignore(numeric_limits<streamsize>::max(), '\n');

        sortRatings(ratings);

        cout << "Movie Title: " << movieTitle << endl;
        cout << "Ratings (sorted): ";
        for (double r : ratings) {
            cout << fixed << setprecision(1) << r << " ";
        }
        cout << endl;

        // Calculate average and median
        double average = calculateAverage(ratings);
        double median = calculateMedian(ratings);
        cout << "Average (excluding highest and lowest): " << fixed << setprecision(2) << average << endl;
        cout << "Median of qualifying ratings: " << median << endl;

        // Update highest average and median
        if (average > highestAverage) {
            highestAverage = average;
            highestMedian = median;
            winningMovie = movieTitle;
            wasTieBreaker = false;
        } else if (average == highestAverage) {
            if (median > highestMedian) {
                highestMedian = median;
                winningMovie = movieTitle;
                wasTieBreaker = true;
            }
        }

        movieCount++;
    }

    // Output the results
    cout << "Total number of participating movies: " << movieCount << endl;
    cout << "Winner of the Golden Award: " << winningMovie << endl;
    cout << "Winning average rating: " << fixed << setprecision(2) << highestAverage << endl;
    if (wasTieBreaker) {
        cout << "Won by tie-breaker with median rating of: " << highestMedian << endl;
    }

    inputFile.close();
    return 0;
}

// Function to sort the ratings in ascending order
int sortRatings(vector<double> &ratings) {
    int n = ratings.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ratings[j] > ratings[j + 1]) {
                double temp = ratings[j];
                ratings[j] = ratings[j + 1];
                ratings[j + 1] = temp;
            }
        }
    }
    return 0;
}

// Function to calculate the average of ratings excluding the lowest and highest
double calculateAverage(const vector<double> &ratings) {
    double sum = 0.0;
    for (int i = 1; i < ratings.size() - 1; i++) {
        sum += ratings[i];
    }
    return sum / 7.0; 
}

// Function to calculate the median of ratings excluding the lowest and highest
double calculateMedian(const vector<double> &ratings) {
    return ratings[4]; // Median is the middle value after sorting
}
