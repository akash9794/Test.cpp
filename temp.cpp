#include <iostream>
#include <fstream>
#include <cmath>
#include <json/json.h>
#include <vector>
#include <string>

long long convertToBase10(const std::string& num, int base) {
    long long result = 0;
    for (char digit : num) {
        int val;
        if ('0' <= digit && digit <= '9') val = digit - '0';
        else if ('a' <= digit && digit <= 'f') val = 10 + (digit - 'a');
        result = result * base + val;
    }
    return result;
}

double computeConstant(const std::vector<std::pair<int, long long>>& data) {
    double constant = 0;
    int size = data.size();

    for (int i = 0; i < size; i++) {
        double term = data[i].second;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                term *= (0 - data[j].first) / static_cast<double>(data[i].first - data[j].first);
            }
        }
        constant += term;
    }
    return constant;
}

int main() {
    std::ifstream file("testcase.json");
    Json::Value jsonData;
    file >> jsonData;

    int numKeys = jsonData["keys"]["n"].asInt();
    int kValue = jsonData["keys"]["k"].asInt();

    std::vector<std::pair<int, long long>> dataPoints;
    for (const auto& key : jsonData.getMemberNames()) {
        if (key == "keys") continue;

        int xValue = std::stoi(key);
        int baseValue = jsonData[key]["base"].asInt();
        std::string valueString = jsonData[key]["value"].asString();

        long long decodedNum = convertToBase10(valueString, baseValue);
        dataPoints.push_back({xValue, decodedNum});
    }

    double constant = computeConstant(dataPoints);
    std::cout << "The constant term 'c' for the polynomial is: " << static_cast<long long>(round(constant)) << std::endl;

    return 0;
}










						




























