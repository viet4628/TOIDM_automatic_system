#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Hàm chuyển chuỗi về chữ thường và loại bỏ khoảng trắng thừa
string normalize(const string& s) {
    string result;
    for (char c : s) {
        if (!isspace(c)) result += tolower(c);
    }
    return result;
}

// Đọc file đáp án vào map: <số câu, đáp án>
map<int, string> read_answers(const string& filename) {
    ifstream fin(filename);
    map<int, string> answers;
    string line;
    while (getline(fin, line)) {
        // Loại bỏ enter thừa
        if (line.empty()) continue;
        // Tìm số câu và đáp án
        size_t pos = line.find('.');
        if (pos != string::npos) {
            int qnum = stoi(line.substr(0, pos));
            string ans = normalize(line.substr(pos + 1));
            answers[qnum] = ans;
        }
    }
    return answers;
}

int main() {
    map<int, string> correct = read_answers("DA_1.txt");
    map<int, string> test = read_answers("DA_test.txt");

    int total = 0, correct_count = 0, score = 0;
    for (const auto& [qnum, ans] : correct) {
        total++;
        auto it = test.find(qnum);
        if (it != test.end() && ans == it->second) {
            correct_count++;
            score += 5;
            cout << "Câu " << qnum << ": Đúng (+5 điểm)\n";
        } else {
            cout << "Câu " << qnum << ": Sai (+0 điểm)\n";
        }
    }
    cout << "Tổng số câu: " << total << "\n";
    cout << "Số câu đúng: " << correct_count << "\n";
    cout << "Tổng điểm: " << score << "\n";
    return 0;
}