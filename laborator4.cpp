#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <vector>



using namespace std;

bool compareFunction(string a, string b) { return a < b; }

void linear(string text, string substring)
{
    bool is_substring;
    for (int i = 0; i < text.length() - substring.length() + 1; i++)
    {
        if (substring.length() == 0)
        {
            cout << "������ ���������\n";
            return;
        }
        is_substring = true;
        for (int j = 0; j < substring.length(); j++) {
            if (text[i + j] != substring[j]) {
                is_substring = false;
                break;
            }
        }
        if (is_substring) {
            cout << "��������� ������� �� �������: " << i << endl;
        }
    }

}

void KMP(string text, string substring)
{
    int m = text.length();
    int n = substring.length();

    // ���� ������ ��� ������ ������
    if (n == 0)
    {
        cout << "������ ���������\n";
        return;
    }

    // ���� ����� ������ ������ ����� �������
    if (m < n)
    {
        return;
    }

    // next[i] ��������� ������ ���������� ������� ���������� ����������
    int* next = new int[n + 1];

    for (int i = 0; i < n + 1; i++) {
        next[i] = 0;
    }

    for (int i = 1; i < n; i++)
    {
        int j = next[i];

        while (j > 0 && substring[j] != substring[i]) {
            j = next[j];
        }

        if (j > 0 || substring[j] == substring[i]) {
            next[i + 1] = j + 1;
        }
    }

    for (int i = 0, j = 0; i < m; i++)
    {
        if (text[i] == substring[j])
        {
            if (++j == n) {
                cout << "��������� ������� �� �������: " << i - j + 1 << endl;
            }
        }
        else if (j > 0)
        {
            j = next[j];
            i--;    // ��� ��� `i` ����� �������� �� ��������� ��������
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    string s;
    int input_choose = 0;
    int task_choose = 0;
    while (true)
    {
        int task_choose;
        while (true)
        {
            cout << "\n\n\n�������� �������, ������� ������ ���������:\n"
                "1.� ���������� �������� ������������������, ���������� �� 1 �� 50 ����, � ������ �� ������� �� 1 �� 10 �������� ��������� ���� � ����. ����� ������� ������������ ���������� ��������. �� ��������� �������� ����� �����\n"
                "2.�������������� �������� ������\n"
                "3.������� �� ����� ����� ������������������ � ���������� �������\n"
                "4.������� �� �����  ��� ����� ������������������ � ��� ��� ��� ������� (� ����������� �� ���������� ����) � ������������� ���� �� ������ ������� �������\n"
                "5.���������� ����� ��� ���������, ������� ����� ������������ � ��������� ������. ���������� �������� �������� ����� � ���\n";
            cin >> task_choose;
            if (task_choose == -1)
            {
                break;
            }
            if (task_choose != 1 && task_choose != 2 && task_choose != 3 && task_choose != 4 && task_choose != 5)
            {
                cout << "������� ���������� ��������! \n";
                continue;
            }
            switch (task_choose)
            {
            case 1:
            {
                cout << "\n\n\n�������� ������ �����: \n"
                    "1.������ ����\n"
                    "2.���� ����������� text.txt\n";
                cin >> input_choose;
                cout << "\n";
                if (input_choose == -1)
                {
                    return 0;
                }
                if (input_choose != 1 && input_choose != 2)
                {
                    cout << "������� ���������� ��������! \n";
                    continue;
                }
                else {
                    s = "";
                    switch (input_choose)
                    {
                    case 1:
                    {
                        cout << "������� ������ ����:\n";
                        getline(cin, s);
                        getline(cin, s);
                        cout << "\n";
                        break;
                    }
                    case 2:
                    {
                        ifstream in("text.txt");
                        string line;
                        if (in.is_open())
                        {
                            while (getline(in, line))
                            {
                                s += line;
                            }
                        }
                        in.close();
                        break;
                    }
                    }
                    vector <string> words;

                    string cur_word = "";
                    bool extra_space = false;
                    for (int i = 0; i < (s.length() - 1); i++) {
                        if (s.at(i) == ' ') {
                            if (!extra_space) {
                                words.push_back(cur_word);
                                cur_word = "";
                            }
                            extra_space = true;
                            continue;
                        }
                        cur_word += s.at(i);
                        extra_space = false;
                    }
                    words.push_back(cur_word);
                    cout << "��������� ������ ����:\n\n";
                    for (int i = 0; i < words.size(); i++) {
                        cout << i + 1 << ": " << words[i] << "\n";
                    }
                    break;
                }
            case 2:
            {
                cout << "������� �����: ";
                getline(cin, s);
                getline(cin, s);
                //�������� ������ ��������
                bool previousIsSpace = false;
                for (auto it = s.begin(); it != s.end();) {
                    if (std::isspace(*it)) {
                        if (previousIsSpace) {
                            it = s.erase(it);
                        }
                        else {
                            previousIsSpace = true;
                            ++it;
                        }
                    }
                    else {
                        previousIsSpace = false;
                        ++it;
                    }
                }
                // �������� ������ ������ ����������
                for (auto it = s.begin(); it != s.end();) {
                    if (std::ispunct(*it)) {
                        auto next = std::next(it);
                        while (next != s.end() && std::ispunct(*next)) {
                            next = s.erase(next);
                        }
                        ++it;
                    }
                    else {
                        ++it;
                    }
                }
                // ����������� �������� ����
                for (auto& ch : s) {
                    if (std::isalpha(ch)) {
                        if (std::islower(ch)) {
                            ch = std::tolower(ch);
                        }
                        else {
                            ch = std::tolower(ch);
                        }
                    }
                }
                std::cout << "����������������� �����: " << s;
                break;
            }
            case 3:
            {
                cout << "\n\n\n�������� ������ �����: \n"
                    "1.������ ����\n"
                    "2.���� ����������� text.txt\n";
                cin >> input_choose;
                cout << "\n";
                if (input_choose == -1)
                {
                    return 0;
                }
                if (input_choose != 1 && input_choose != 2)
                {
                    cout << "������� ���������� ��������! \n";
                    continue;
                }
                else
                    switch (input_choose)
                    {
                    case 1:
                    {
                        cout << "������� ������ ����:\n";
                        getline(cin, s);
                        getline(cin, s);
                        cout << "\n";
                        break;
                    }
                    case 2:
                    {
                        ifstream in("text.txt");
                        string line;
                        if (in.is_open())
                        {
                            while (getline(in, line))
                            {
                                s += line;
                            }
                        }
                        in.close();
                        break;
                    }
                    }
                vector <string> words;
                string cur_word = "";
                bool extra_space = false;
                for (int i = 0; i < (s.length() - 1); i++) {
                    if (s.at(i) == ' ') {
                        if (!extra_space) {
                            words.push_back(cur_word);
                            cur_word = "";
                        }
                        extra_space = true;
                        continue;
                    }
                    cur_word += s.at(i);
                    extra_space = false;
                }
                words.push_back(cur_word);
                cout << "��������� ������ ����:\n\n";
                for (int i = 0; i < words.size(); i++) {
                    cout << i + 1 << ": " << words[i] << "\n";
                }
                sort(words.begin(), words.end(), compareFunction);
                cout << "\n��������������� ������ ����:\n\n";
                for (int i = 0; i < words.size(); i++) {
                    cout << i + 1 << ": " << words[i] << "\n";
                }
                break;
            }
            case 4:
            {
                cout << "\n\n\n�������� ������ �����: \n"
                    "1.������ ����\n"
                    "2.���� ����������� text.txt\n";
                cin >> input_choose;
                cout << "\n";
                if (input_choose == -1)
                {
                    return 0;
                }
                if (input_choose != 1 && input_choose != 2)
                {
                    cout << "������� ���������� ��������! \n";
                    continue;
                }
                else
                    switch (input_choose)
                    {
                    case 1:
                    {
                        cout << "������� ������ ����:\n";
                        getline(cin, s);
                        getline(cin, s);
                        cout << "\n";
                        break;
                    }
                    case 2:
                    {
                        ifstream in("text.txt");
                        string line;
                        if (in.is_open())
                        {
                            while (getline(in, line))
                            {
                                s += line;
                            }
                        }
                        in.close();
                        break;
                    }
                    }
                vector <string> words;
                string cur_word = "";
                bool extra_space = false;
                for (int i = 0; i < (s.length() - 1); i++) {
                    if (s.at(i) == ' ') {
                        if (!extra_space) {
                            words.push_back(cur_word);
                            cur_word = "";
                        }
                        extra_space = true;
                        continue;
                    }
                    cur_word += s.at(i);
                    extra_space = false;
                }
                words.push_back(cur_word);
                int n_columns = words.size() > 12 ? 3 : 2;
                string temp;
                cout << "��������� ������ ���� � ���� �������:\n\n";
                for (int i = 0; i < words.size(); i++) {
                    temp = string((20 - words[i].length()), ' ') + words[i];
                    cout << temp;
                    if ((i + 1) % n_columns == 0) { cout << "\n"; }
                }
                break;
            }
            case 5:
            {
                cout << "������� ������:\n";
                getline(cin, s);
                getline(cin, s);
                cout << endl;
                string substring;
                cout << "������� ���������:\n";
                getline(cin, substring);
                cout << endl;
                cout << "�������� �����\n";
                linear(s, substring);
                cout << "���\n";
                KMP(s, substring);
                break;
            }
            }
            }
        }
        break;
    }
    return 0;
}