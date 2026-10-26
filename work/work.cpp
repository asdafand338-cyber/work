17.10.26 самостійна
#include <iostream>
#include <string>
#include <stack>


bool isValid(const std::string& expression) {
    std::stack<char> st;

    for (char c : expression) {

        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        }

        else if (c == ')' || c == ']' || c == '}') {

            if (st.empty()) {
                return false;
            }

            char top = st.top();
            st.pop();

            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }

    return st.empty();
}

int main() {

    std::setlocale(LC_ALL, "Ukrainian");

    std::cout << "=== Програма перевірки дужок у виразі ===\n";
    std::cout << "Введіть рядок для перевірки (для виходу введіть 'exit'):\n\n";

    std::string input;
    while (true) {
        std::cout << "Введіть вираз: ";
        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input == "exit" || input == "вихід") {
            break;
        }

        if (isValid(input)) {
            std::cout << "Результат: Коректно\n\n";
        }
        else {
            std::cout << "Результат: Помилка\n\n";
        }
    }

    return 0;
}
17.10.26 практика
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>

std::string cleanAndLowerWord(const std::string & str) {
    std::string result = "";
    for (char c : str) {
       
        if (std::isalpha(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

int main() {

    std::setlocale(LC_ALL, "Ukrainian");

    std::cout << "=== Простий текстовий аналізатор ===\n";
    std::cout << "Введіть рядок тексту:\n> ";

    std::string text;
    if (!std::getline(std::cin, text)) {
        return 0;
    }

    std::stringstream ss(text);
    std::string rawWord;
    std::map<std::string, int> wordCounts;

    while (ss >> rawWord) {
        std::string word = cleanAndLowerWord(rawWord);
        if (!word.empty()) {
            wordCounts[word]++;
        }
    }

    if (wordCounts.empty()) {
        std::cout << "\nУ введеному тексті не знайдено слів.\n";
        return 0;
    }

    std::cout << "\n--- Частота слів (за алфавітом) ---\n";

    std::string mostFrequentWord = "";
    int maxFrequency = 0;

    for (const auto& pair : wordCounts) {
        std::cout << pair.first << " -> " << pair.second << "\n";


        if (pair.second > maxFrequency) {
            maxFrequency = pair.second;
            mostFrequentWord = pair.first;
        }
    }

    std::cout << "\n--- Найчастіше слово ---\n";
    std::cout << "Слово: \"" << mostFrequentWord << "\" (зустрічається " << maxFrequency << " раз(и))\n";

    return 0;
}
18.10.26 самостійна 
#include <iostream>
#include <string>

class Character {
protected:
    std::string name;
    int health;
    int shield;

public:
    Character(std::string charName, int charHealth = 100, int charShield = 50)
        : name(charName), health(charHealth), shield(charShield) {
    }

    virtual ~Character() = default;

    void takeDamage(int amount) {
        std::cout << name << " отримує " << amount << " одиниць шкоди.\n";

        if (shield >= amount) {
            shield -= amount;
        }
        else {
            amount -= shield; 
            shield = 0;       
            health -= amount; 

            if (health < 0) {
                health = 0;
            }
        }

        std::cout << "Статус -> Здоров'я: " << health << ", Броня: " << shield << "\n\n";
    }
};


class Recon : public Character {
public:
    Recon(std::string charName) : Character(charName) {}

    void scanArea() const {
        std::cout << name << " сканує місцевість: виявлено 2 ворогів!\n";
    }
};


class Support : public Character {
public:
    Support(std::string charName) : Character(charName) {}

    void dropHeal() const {
        std::cout << name << " скидає аптечку: здоров'я союзників успішно відновлено!\n";
    }
};


int main() {

    std::setlocale(LC_ALL, "Ukrainian");


    Recon scout("Рейвен");
    Support medic("Бейкер");

    std::cout << "=== Тестування отримання шкоди ==-\n";

    scout.takeDamage(30);

    medic.takeDamage(70);

    std::cout << "=== Виклик унікальних здібностей ==-\n";

 
    scout.scanArea();
    medic.dropHeal();

    return 0;
}

18.10.26 практика 
#include <iostream>
#include <string>


class Notification {
protected:
    std::string message;
    std::string timestamp;

public:

    Notification(std::string msg, std::string time)
        : message(msg), timestamp(time) {
    }


    virtual ~Notification() = default;


    virtual void send() const = 0;
};


class EmailNotification : public Notification {
private:
    std::string emailAddress;

public:
    EmailNotification(std::string msg, std::string time, std::string email)
        : Notification(msg, time), emailAddress(email) {
    }


    void send() const override {
        std::cout << "Відправка email на " << emailAddress << ": " << message
            << " [Час: " << timestamp << "]\n";
    }
};


class PushNotification : public Notification {
private:
    std::string deviceId;

public:
    PushNotification(std::string msg, std::string time, std::string device)
        : Notification(msg, time), deviceId(device) {
    }


    void send() const override {
        std::cout << "Відправка пуша на пристрій " << deviceId << ": " << message
            << " [Час: " << timestamp << "]\n";
    }
};


int main() {
    std::setlocale(LC_ALL, "Ukrainian");


    EmailNotification emailNotif("Зустріч перенесено на 15:00", "10:30", "yaroslav@example.com");
    PushNotification pushNotif("У вас нове повідомлення", "10:31", "device_id_777");


    emailNotif.send();
    pushNotif.send();

    return 0;
}

24.10.26 самостійна
#include <iostream>
#include <string>

class Audio {
public:
    virtual void Play() const = 0;

    virtual ~Audio() = default;
};

class Song : public Audio {
private:
    std::string title;
    std::string artist;

public:
    Song(std::string t, std::string a) : title(t), artist(a) {}

    void Play() const override {
        std::cout << "Playing song: " << title << " by " << artist << "\n";
    }
};

class Podcast : public Audio {
private:
    std::string host;
    std::string topic;

public:
    Podcast(std::string h, std::string top) : host(h), topic(top) {}

    void Play() const override {
        std::cout << "Podcast on " << topic << " hosted by " << host << "\n";
    }
};

class Audiobook : public Audio {
private:
    std::string bookTitle;
    std::string author;
    std::string voice;

public:
    Audiobook(std::string bt, std::string aut, std::string v)
        : bookTitle(bt), author(aut), voice(v) {
    }

    void Play() const override {
        std::cout << "Listening to audiobook: " << bookTitle << " by " << author << ". Read by " << voice << ".\n";
    }
};

int main() {
    std::setlocale(LC_ALL, "Ukrainian");

    int choice;
    std::cout << "Оберіть тип аудіо:\n";
    std::cout << "1. Пісня (Song)\n";
    std::cout << "2. Подкаст (Podcast)\n";
    std::cout << "3. Аудіокнига (Audiobook)\n";
    std::cout << "Ваш вибір (1-3): ";
    std::cin >> choice;

    std::cin.ignore();

    Audio* audioObj = nullptr;

    switch (choice) {
    case 1: {
        std::string title, artist;
        std::cout << "Введіть назву пісні: ";
        std::getline(std::cin, title);
        std::cout << "Введіть виконавця: ";
        std::getline(std::cin, artist);

        audioObj = new Song(title, artist);
        break;
    }
    case 2: {
        std::string topic, host;
        std::cout << "Введіть тему подкасту: ";
        std::getline(std::cin, topic);
        std::cout << "Введіть ведучого: ";
        std::getline(std::cin, host);

        audioObj = new Podcast(host, topic);
        break;
    }
    case 3: {
        std::string bookTitle, author, voice;
        std::cout << "Введіть назву книги: ";
        std::getline(std::cin, bookTitle);
        std::cout << "Введіть автора: ";
        std::getline(std::cin, author);
        std::cout << "Введіть читця (голос): ";
        std::getline(std::cin, voice);

        audioObj = new Audiobook(bookTitle, author, voice);
        break;
    }
    default:
        std::cout << "Невірний вибір!\n";
        return 1;
    }

    std::cout << "\n--- Результат ---\n";
    if (audioObj != nullptr) {
        audioObj->Play();

        delete audioObj;
    }

    return 0;
}

24.10.26 практика 
#include <iostream>
#include <cmath>

class Figure {
public:
    virtual double GetArea() const = 0;

    virtual ~Figure() = default;
};

class Rectangle : public Figure {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double GetArea() const override {
        return width * height;
    }
};

class Circle : public Figure {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double GetArea() const override {
        return 3.14159265358979323846 * radius * radius;
    }
};

class Triangle : public Figure {
private:
    double base;
    double height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    double GetArea() const override {
        return 0.5 * base * height;
    }
};

int main() {
    std::setlocale(LC_ALL, "Ukrainian");

    int choice;
    std::cout << "Оберіть фігуру для розрахунку площі:\n";
    std::cout << "1. Прямокутник (Rectangle)\n";
    std::cout << "2. Коло (Circle)\n";
    std::cout << "3. Трикутник (Triangle)\n";
    std::cout << "Ваш вибір (1-3): ";
    std::cin >> choice;

    Figure* figure = nullptr;

    switch (choice) {
    case 1: {
        double width, height;
        std::cout << "Введіть ширину прямокутника: ";
        std::cin >> width;
        std::cout << "Введіть висоту прямокутника: ";
        std::cin >> height;

        figure = new Rectangle(width, height);
        break;
    }
    case 2: {
        double radius;
        std::cout << "Введіть радіус кола: ";
        std::cin >> radius;

        figure = new Circle(radius);
        break;
    }
    case 3: {
        double base, height;
        std::cout << "Введіть основу трикутника: ";
        std::cin >> base;
        std::cout << "Введіть висоту трикутника: ";
        std::cin >> height;

        figure = new Triangle(base, height);
        break;
    }
    default:
        std::cout << "Невірний вибір!\n";
        return 1;
    }

    std::cout << "\n--- Результат ---\n";
    if (figure != nullptr) {
        std::cout << "Площа фігури: " << figure->GetArea() << "\n";

    }

    return 0;
}

25.10.26 практика 
#include <iostream>
#include <string>
#include <vector>

// Базовий клас Домашня тварина
class Pet {
protected:
    std::string name;
    std::string characteristics;

public:
    Pet(std::string animalName, std::string characts)
        : name(animalName), characteristics(characts) {
    }

    virtual ~Pet() = default;

    // Чисто віртуальні або віртуальні функції за вимогами
    virtual void Sound() const = 0;

    virtual void Show() const {
        std::cout << "Ім'я тварини: " << name << " | Характеристики: " << characteristics << "\n";
    }

    virtual void Type() const = 0;
};

// Клас Собака
class Dog : public Pet {
public:
    Dog(std::string name, std::string characteristics) : Pet(name, characteristics) {}

    void Sound() const override {
        std::cout << "Звук: Гав-гав!\n";
    }

    void Type() const override {
        std::cout << "Підвид: Собака\n";
    }
};

// Клас Кішка
class Cat : public Pet {
public:
    Cat(std::string name, std::string characteristics) : Pet(name, characteristics) {}

    void Sound() const override {
        std::cout << "Звук: Мяу-мяу!\n";
    }

    void Type() const override {
        std::cout << "Підвид: Кішка\n";
    }
};

// Клас Папуга
class Parrot : public Pet {
public:
    Parrot(std::string name, std::string characteristics) : Pet(name, characteristics) {}

    void Sound() const override {
        std::cout << "Звук: Чирік-чирік!\n";
    }

    void Type() const override {
        std::cout << "Підвид: Папуга\n";
    }
};

// Клас Хом’як
class Hamster : public Pet {
public:
    Hamster(std::string name, std::string characteristics) : Pet(name, characteristics) {}

    void Sound() const override {
        std::cout << "Звук: Пі-пі-пі (хрусь-хрусь!)\n";
    }

    void Type() const override {
        std::cout << "Підвид: Хом’як\n";
    }
};

25.10.26 самостійна
#include <iostream>
#include <string>
#include <vector>

// 1. Інтерфейс IHackable (Контракт взаємодії)
class IHackable {
public:
    virtual void applyHack(int techLevel) = 0;
    virtual bool isHacked() const = 0;
    virtual ~IHackable() = default;
};

// 2. Клас VendingMachine (Автомат з газованкою)
class VendingMachine : public IHackable {
private:
    bool hacked;

public:
    VendingMachine() : hacked(false) {}

    void applyHack(int techLevel) override {
        if (techLevel >= 2) {
            hacked = true;
            std::cout << "[VendingMachine] Злам успішний! Автомат закорочує схему і викидає всі напої назовні!\n";
        }
        else {
            hacked = false;
            std::cout << "[VendingMachine] Помилка зламу! Рівень навички занизький (потрібно >= 2), автомат б'є хакера струмом!\n";
        }
    }

    bool isHacked() const override {
        return hacked;
    }
};

class SmartDoor : public IHackable {
private:
    bool hacked;
    bool isOpen;

public:
    SmartDoor() : hacked(false), isOpen(false) {}

    void applyHack(int techLevel) override {
        if (techLevel >= 5) {
            hacked = true;
            isOpen = true;
            std::cout << "[SmartDoor] Доступ зламано! Електронні двері відчинилися.\n";
        }
        else {
            hacked = false;
            std::cout << "[SmartDoor] Не вдалося зламати систему безпеки. Потрібен рівень навички >= 5.\n";
        }
    }

    bool isHacked() const override {
        return hacked;
    }

    bool getIsOpen() const {
        return isOpen;
    }
};

int main() {
    std::setlocale(LC_ALL, "Ukrainian");

    std::cout << "=== СИСТЕМА КІБЕР-ЗЛАМУ ===\n\n";

    std::vector<IHackable*> environmentObjects = {
        new VendingMachine(),
        new SmartDoor()
    };

    int hackerLevel = 3;
    std::cout << "Хакер намагається зламати об'єкти з рівнем навички: " << hackerLevel << "\n\n";

    for (size_t i = 0; i < environmentObjects.size(); ++i) {
        std::cout << "--- Об'єкт " << (i + 1) << " ---\n";
        environmentObjects[i]->applyHack(hackerLevel);
        std::cout << "Статус зламу (isHacked): " << (environmentObjects[i]->isHacked() ? "Так" : "Ні") << "\n\n";
    }

    for (auto obj : environmentObjects) {
        delete obj;
    }

    return 0;
}