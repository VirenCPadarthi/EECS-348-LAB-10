#include "calculator.hpp"
#include <cctype>
#include <algorithm>

using namespace std;

// Checks if a string is a valid double (manually, no cheating with stod)
bool isValidDouble(const string& s) {
    int i = 0;
    int len = s.size();
    if (len == 0) return false;

    // optional + or - at the start
    if (s[i] == '+' || s[i] == '-') i++;

    bool hasDigits = false;
    bool hasDot = false;
    bool digitsAfterDot = false;

    // go through each character
    for (; i < len; ++i) {
        if (isdigit(s[i])) {
            hasDigits = true;
            if (hasDot) digitsAfterDot = true;
        } else if (s[i] == '.') {
            // already has a dot? invalid
            if (hasDot) return false;
            hasDot = true;
        } else {
            // found something weird like a letter? invalid
            return false;
        }
    }

    // must have digits, and if dot is there, needs digits after it
    if (!hasDigits) return false;
    if (hasDot && !digitsAfterDot) return false;

    return true;
}

// Pads the strings so both have the same number of digits before and after the decimal
void normalizeStrings(string& a, string& b) {
    size_t dotA = a.find('.');
    size_t dotB = b.find('.');

    // if no dot, pretend it's at the end and add it
    if (dotA == string::npos) {
        dotA = a.size();
        a += '.';
    }
    if (dotB == string::npos) {
        dotB = b.size();
        b += '.';
    }

    size_t intA = dotA, intB = dotB;
    size_t fracA = a.size() - dotA - 1;
    size_t fracB = b.size() - dotB - 1;

    // pad front (integer part)
    if (intA < intB) a.insert(0, intB - intA, '0');
    if (intB < intA) b.insert(0, intA - intB, '0');

    // pad back (fraction part)
    if (fracA < fracB) a.append(fracB - fracA, '0');
    if (fracB < fracA) b.append(fracA - fracB, '0');
}

// Adds two valid double strings together (same sign only), returns result as a string
string addStrings(const string& s1, const string& s2) {
    string a = s1, b = s2;
    bool negA = false, negB = false;

    // clean the signs and keep track
    if (a[0] == '-') {
        negA = true;
        a = a.substr(1);
    } else if (a[0] == '+') {
        a = a.substr(1);
    }

    if (b[0] == '-') {
        negB = true;
        b = b.substr(1);
    } else if (b[0] == '+') {
        b = b.substr(1);
    }

    // make sure both strings have same length before and after dot
    normalizeStrings(a, b);
    string result;
    int carry = 0;

    // loop from right to left like manual math
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] == '.') {
            result += '.';
        } else {
            int sum = (a[i] - '0') + (b[i] - '0') + carry;
            carry = sum / 10;
            result += (sum % 10) + '0';
        }
    }

    // leftover carry? add it
    if (carry) result += (carry + '0');
    reverse(result.begin(), result.end());

    // clean trailing 0s and dot if needed
    while (result.back() == '0') result.pop_back();
    if (result.back() == '.') result.pop_back();

    // if both were negative, keep the negative sign
    if (negA && negB) result.insert(result.begin(), '-');
    return result;
}
