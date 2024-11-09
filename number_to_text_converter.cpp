#include <iostream>
#include <map>
#include <stdexcept>

using namespace std;

map<int, string> FOURTH_BIT_DEPTH_MAP = {
  { 1, "одна" },
  { 2, "две" },
  { 3, "три" },
  { 4, "четыре" },
  { 5, "пять" },
  { 6, "шесть" },
  { 7, "семь" },
  { 8, "восемь" },
  { 9, "девять" },
};

map<int, string> THIRD_BIT_DEPTH_MAP = {
  { 1, "сто" },
  { 2, "двести" },
  { 3, "триста" },
  { 4, "четыреста" },
  { 5, "пятьсот" },
  { 6, "шестьсот" },
  { 7, "семьсот" },
  { 8, "восемьсот" },
  { 9, "девятьсот" },
};

map<int, string> SECOND_BIT_DEPTH_MAP = {
  { 1, "десять" },
  { 2, "двадцать" },
  { 3, "тридцать" },
  { 4, "сорок" },
  { 5, "пятьдесят" },
  { 6, "шестьдесят" },
  { 7, "семьдесят" },
  { 8, "восемьдесят" },
  { 9, "девяносто" },
};

map<int, string> FROM_11_TO_19_MAP = {
  { 1, "одиннадцать" },
  { 2, "двенадцать" },
  { 3, "тринадцать" },
  { 4, "четырнадцать" },
  { 5, "пятнадцать" },
  { 6, "шестнадцать" },
  { 7, "семнадцать" },
  { 8, "восемнадцать" },
  { 9, "девятнадцать" },
};

map<int, string> FIRST_BIT_DEPTH_MAP = {
  { 1, "один" },
  { 2, "два" },
  { 3, "три" },
  { 4, "четыре" },
  { 5, "пять" },
  { 6, "шесть" },
  { 7, "семь" },
  { 8, "восемь" },
  { 9, "девять" },
};

array<string, 3> THOUSANDS_TITLES = {"тысяча", "тысячи", "тысяч"};
array<string, 3> RUB_TITLES = {"рубль", "рубля", "рублей"};
array<string, 3> USD_TITLES = {"доллар", "доллара", "долларов"};

enum class BitDepth {
  First = 1,
  Second,
  Third,
  Fourth,
};

enum class Currency {
  Rub = 1,
  Usd,
  First = Rub,
  Last = Usd
};

map<Currency, array<string, 3>> CURRENCY_TITLES_MAP = {
    { Currency::Rub, RUB_TITLES },
    { Currency::Usd, USD_TITLES }
};

string count_format(int n, array<string, 3> titles) {
  int index =
    n % 10 == 1 && n % 100 != 11 ? 0 : n % 10 >= 2 && n % 10 <= 4 && (n % 100 < 10 || n % 100 >= 20) ? 1 : 2;

  return titles[index];
}

bool in_range(int num, int from, int to) {
  return num >= from && num <= to;
}

string convert_number_to_text(int count) {
  string count_str = to_string(count);
  int length = count_str.length();
  string result = "";

  for (int i = 0; i < length; i++) {
    BitDepth bit_depth = static_cast<BitDepth>(length - i);
    int number = count_str[i] - '0';
    int prev_number = count_str[i - 1] - '0';
    int next_number = count_str[i + 1] - '0';

    if (number == 0) {
      continue;
    }

    switch (bit_depth) {
      case BitDepth::Fourth:
        result += FOURTH_BIT_DEPTH_MAP[number] + " " + count_format(number, THOUSANDS_TITLES);
        break;
      case BitDepth::Third:
        result += THIRD_BIT_DEPTH_MAP[number];
        break;
      case BitDepth::Second:
        if (number > 1 || (number == 1 && next_number == 0)) {
          result += SECOND_BIT_DEPTH_MAP[number];
        }
        break;
      case BitDepth::First:
        if (prev_number == 1) {
          result += FROM_11_TO_19_MAP[number];
        } else {
          result += FIRST_BIT_DEPTH_MAP[number];
        }

        break;
      default:
        throw invalid_argument("Unknown bit depth of number: " + to_string(static_cast<int>(bit_depth)));
    }

    if (bit_depth != BitDepth::First) {
      result += " ";
    }
  }

  return result;
}

int ask_range(int from, int to) {
  int count = 0;

  while (!in_range(count, from, to)) {
    cout << "Введите целое число от " << from << " до " << to << ":" << endl;
    cin >> count;
  }

  return count;
}

Currency ask_currency() {
  int option = 0;

  while (!in_range(option, static_cast<int>(Currency::First), static_cast<int>(Currency::Last))) {
    cout << "Выберите валюту (введите номер опции):" << endl;
    cout << "1. Рубль" << endl;
    cout << "2. Доллар" << endl;
    cin >> option;
  }

  return static_cast<Currency>(option);
}

void init_app() {
  setlocale(LC_ALL, "Rus");
}

int main() {
  init_app();

  int count = ask_range(1, 9999);
  Currency currency = ask_currency();

  string count_display = convert_number_to_text(count);
  string currency_display = count_format(count, CURRENCY_TITLES_MAP[currency]);

  cout << count_display + " " + currency_display << endl;
  
  return 0;
}