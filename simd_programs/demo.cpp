#include <iostream>
#include <vector>
using namespace std;

// Function to convert RGB to Grayscale
void rgbToGrayscale(const vector<vector<int>> &rgb, vector<int> &grayscale) {
    float rconst = 0.29891f;
    float gconst = 0.58661f;
    float bconst = 0.11448f;

    for (const auto &pixel : rgb) {
        int r = pixel[0];
        int g = pixel[1];
        int b = pixel[2];

        // Calculate grayscale value
        int gray = static_cast<int>(r * rconst + g * gconst + b * bconst);

        // Ensure the value is within the valid range [0, 255]
        if (gray > 255) gray = 255;
        if (gray < 0) gray = 0;

        grayscale.push_back(gray);
    }
}

int main() {
    // Example input: RGB values for 4 pixels
    vector<vector<int>> rgb = {
        {200, 32, 22},  // Pixel 1
        {32, 43, 53},   // Pixel 2
        {53, 22, 44},   // Pixel 3
        {42, 24, 22}    // Pixel 4
    };

    // Vector to store grayscale output
    vector<int> grayscale;

    // Convert RGB to Grayscale
    rgbToGrayscale(rgb, grayscale);

    // Output the grayscale values
    cout << "Grayscale values: ";
    for (int gray : grayscale) {
        cout << gray << " ";
    }
    cout << endl;

    return 0;
}
