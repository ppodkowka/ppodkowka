/* Design and implement classes for a currency calculator */
/*
Kalkulator opiera sie na pobieraniu waluty wejsciowej oraz tej, na ktora chcemy zmienic nasza kwote pieniedzy. W przypadku wpisania niewlasciwych parametrow, nastapi poproszenie o ponowne ich wprowadzenie.
Kursy walut ujete sa w kontenerze, z ktorych wylacznie pobieramy wartosc przy pozniejszym obliczaniu.
Metoda klasy na obliczanie pieniedzy opiera sie na funkcji isdigit, do ochrony programu przed niepoprawnym wpisaniem liter w miejscu cyfr.

//Autorzy Piotr Podkówka i Kacper Czepiec
*/
#include <iostream> 
#include <string>
#include <map> //Kontener przechowujacy wartosci przelicznikow walut
#include <cctype> //Do metody isdigit
#include <fstream> //Wpisywanie do pliku
#include <ctime> //Markery czasu
#pragma warning(disable:4996) //Usuniecie warningu _CRT_SECURE_NO_WARNINGS, ktory uniemozliwial uzycie metody time
using namespace std;

float kursy(string a) { //Kontener z przelicznikami
    map<string, float> kursy_walut;
    kursy_walut["PLN_TO_EUR"] = 0.22; //EURO
    kursy_walut["PLN_TO_USD"] = 0.24; //DOLAR AMERYKANSKI
    kursy_walut["PLN_TO_GBP"] = 0.18; //FUNT BRYTYJSKI
    kursy_walut["PLN_TO_RUB"] = 18.00; //RUBEL ROSYJSKI
    kursy_walut["PLN_TO_KUN"] = 1.62; //KUNA CHORWACKA
    kursy_walut["PLN_TO_CHF"] = 0.22; //FRANK SZWAJCARSKI

    kursy_walut["EUR_TO_PLN"] = 4.63;
    kursy_walut["EUR_TO_USD"] = 1.12;
    kursy_walut["EUR_TO_GBP"] = 0.85;
    kursy_walut["EUR_TO_RUB"] = 83.37;
    kursy_walut["EUR_TO_KUN"] = 7.52;
    kursy_walut["EUR_TO_CHF"] = 1.04;

    kursy_walut["USD_TO_PLN"] = 4.12;
    kursy_walut["USD_TO_EUR"] = 0.89;
    kursy_walut["USD_TO_GBP"] = 0.75;
    kursy_walut["USD_TO_RUB"] = 74.17;
    kursy_walut["USD_TO_KUN"] = 6.69;
    kursy_walut["USD_TO_CHF"] = 0.92;

    kursy_walut["GBP_TO_PLN"] = 5.46;
    kursy_walut["GBP_TO_EUR"] = 1.18;
    kursy_walut["GBP_TO_USD"] = 1.32;
    kursy_walut["GBP_TO_RUB"] = 98.25;
    kursy_walut["GBP_TO_KUN"] = 8.86;
    kursy_walut["GBP_TO_CHF"] = 1.22;

    kursy_walut["RUB_TO_PLN"] = 0.056;
    kursy_walut["RUB_TO_EUR"] = 0.012;
    kursy_walut["RUB_TO_USD"] = 0.013;
    kursy_walut["RUB_TO_GBP"] = 0.010;
    kursy_walut["RUB_TO_KUN"] = 0.090;
    kursy_walut["RUB_TO_CHF"] = 0.012;

    kursy_walut["KUN_TO_PLN"] = 0.62;
    kursy_walut["KUN_TO_EUR"] = 0.13;
    kursy_walut["KUN_TO_USD"] = 0.15;
    kursy_walut["KUN_TO_GBP"] = 0.11;
    kursy_walut["KUN_TO_RUB"] = 11.09;
    kursy_walut["KUN_TO_CHF"] = 0.14;

    kursy_walut["CHF_TO_PLN"] = 4.46;
    kursy_walut["CHF_TO_EUR"] = 0.96;
    kursy_walut["CHF_TO_USD"] = 1.08;
    kursy_walut["CHF_TO_GBP"] = 0.82;
    kursy_walut["CHF_TO_RUB"] = 80.32;
    kursy_walut["CHF_TO_KUN"] = 7.24;

    return kursy_walut[a];
}

class Kantor //Glowna klasa zawierajaca metody do ustawiania walut oraz kwoty pienieznej.
{
private:
    char m_waluta_pocz;
    char m_waluta_konc;
    float m_kwota;

public:
    Kantor(char waluta = ' ', float kwota = 0) : m_waluta_pocz{ waluta }, m_waluta_konc{ waluta }, m_kwota{ kwota }
    {}

    char get_waluta_pocz(void) const {
        return m_waluta_pocz;
    }

    char get_waluta_konc(void) const {
        return m_waluta_konc;
    }
    float get_kwota(void) const {
        return  m_kwota;
    }
    void set_kwota(double kwota) {
        m_kwota = kwota;
    }

    void waluta_we();
    void waluta_wy();
    void pieniadze();
    void wymiana();

};


void Kantor::waluta_we() //Pobieranie od uzytkownika waluty, z ktorej wymienia pieniadze
{
    cout << "Program zamiany walut. Kurs z dnia 16 grudnia 2021 roku.  \nOznaczenia -\n";
    cout << "(P) Zloty, (E) Euro, (U) Dolar amerykanski \n";
    cout << "(G) Funt Brytyjski, (R) Rubel rosyjski \n";
    cout << "(K) Kuna Chorwacka, (C) Frank Szwajcarski \n";
    cout << "Aby wyjsc z programu wcisnij (Q)\n\n";
    cout << "Wybierz walute, ktora posiadasz: ";


    string m_waluta;
start:
    cin >> m_waluta;

    //Ochrona przed wpisaniem 2 i wiecej znakow
    if (m_waluta[1] != '\0') {
        cout << "Podaj wylacznie jedna litere.\nWybierz walute: ";
        goto start;
    }
    else m_waluta_pocz = m_waluta[0];

    //Konwersja malych liter na duze
    m_waluta_pocz = static_cast<char>(toupper(m_waluta_pocz));
    switch (m_waluta_pocz)
    {
    case 'P':
        m_waluta_pocz = 'P';
        break;
    case 'E':
        m_waluta_pocz = 'E';
        break;
    case 'U':
        m_waluta_pocz = 'U';
        break;
    case 'G':
        m_waluta_pocz = 'G';
        break;
    case 'R':
        m_waluta_pocz = 'R';
        break;
    case 'K':
        m_waluta_pocz = 'K';
        break;
    case 'C':
        m_waluta_pocz = 'C';
        break;
    case 'Q':
        cout << "Uzyto kodu wyjscia. Dziekujemy za skorzystanie z konwertera.";
        exit(0);
    default:
        cout << "Wybierz poprawna walute (litere): ";
        goto start;
    }

    get_waluta_pocz(); //Uzyskanie waluty od uzytkownika
}

void Kantor::waluta_wy() //Pobieranie od uzytkownika waluty na ktora wymienia pieniadze
{
    cout << "Wybierz walute, ktora chcesz zakupic: ";
    string m_walut;
start:
    cin >> m_walut;

    if (m_walut[1] != '\0') {
        cout << "Podaj wylacznie jedna litere.\nWybierz walute: ";
        goto start;
    }
    else {
        m_waluta_konc = m_walut[0];
    }

    m_waluta_konc = static_cast<char>(toupper(m_waluta_konc));
    get_waluta_pocz(); //Do sprawdzenia, czy nie wpisano jednakowych walut, porownamy wyjsciowa wraz z poczatkowa.
    switch (m_waluta_konc)
    {
    case 'P':
        if (m_waluta_pocz == 'P') {
            cout << "Wybrales Zlotowki jako obie waluty. Wprowadz ponownie walute, ktora chcesz zakupic: ";
            goto start;
        }
        m_waluta_konc = 'P';
        break;
    case 'E':
        if (m_waluta_pocz == 'E') {
            cout << "Wybrales Euro jako obie waluty. Wprowadz ponownie walute, ktora chcesz zakupic: ";
            goto start;
        }
        m_waluta_konc = 'E';
        break;
    case 'U':
        if (m_waluta_pocz == 'U') {
            cout << "Wybrales Dolary jako obie waluty. Wprowadz ponownie walute, ktora chcesz zakupic: ";
            goto start;
        }
        m_waluta_konc = 'U';
        break;
    case 'G':
        if (m_waluta_pocz == 'G') {
            cout << "Wybrales Funty jako obie waluty. Wprowadz ponownie walute, ktora chcesz zakupic: ";
            goto start;
        }
        m_waluta_konc = 'G';
        break;
    case 'R':
        if (m_waluta_pocz == 'R') {
            cout << "Wybrales Ruble jako obie waluty. Wprowadz ponownie walute, ktora chcesz zakupic: ";
            goto start;
        }
        m_waluta_konc = 'R';
        break;
    case 'K':
        if (m_waluta_pocz == 'K') {
            cout << "Wybrales Kuny jako obie waluty. Wprowadz ponownie walute, ktora chcesz zakupic: ";
            goto start;
        }
        m_waluta_konc = 'K';
        break;
    case 'C':
        if (m_waluta_pocz == 'C') {
            cout << "Wybrales Franki jako obie waluty. Wprowadz ponownie walute, ktora chcesz zakupic: ";
            goto start;
        }
        m_waluta_konc = 'C';
        break;
    case 'Q':
        cout << "Uzyto kodu wyjscia. Dziekujemy za skorzystanie z konwertera.\n";
        exit(0);
    default:
        cout << "Wybierz poprawna walute (litere): ";
        goto start;
    }
    get_waluta_konc();
}

void Kantor::pieniadze() //Funkcja do pobrania od uzytkownika ilosci pieniedzy do wymiany
{
    //Zaczynamy od string, zeby moc przekonwertowac to dopiero na int. Pozwoli to uniknac bledow przy wpisywaniu liter zamiast cyfr.
    string kasa_na_kwote;
    int kwota;
start:
    cout << "Wpisz kwote jaka posiadasz: ";
    cin >> kasa_na_kwote;
    if (kasa_na_kwote == "Q" || kasa_na_kwote == "q") {
        cout << "Uzyto kodu wyjscia. Dziekujemy za skorzystanie z konwertera.\n";
        exit(0);
    }
    else if (kasa_na_kwote == "0") {
        cout << "Kwota musi byc wieksza od 0.\n";
        goto start;
    }
    for (int i = 0; i < kasa_na_kwote.size(); i++) {
        if (isdigit(kasa_na_kwote[i])) {
            //isdigit sprawdza, czy wartość jest cyfrą
            //atoi - konwertuje string na int
            kwota = atoi(&kasa_na_kwote[i]);
            return set_kwota(kwota);
        }
        else {
            cout << "Wpisales litere, wiele liter lub niepoprawna kwote.\n";
            goto start;
        }
    }
}

void Kantor::wymiana() //Glowna funkcja, w ktorej odbywa sie konwersja walut
{
    char wal_pocz = get_waluta_pocz();
    char wal_konc = get_waluta_konc();
    float pieniadze = get_kwota();
    float przelicznik = 0;

    if (wal_pocz == 'P') {

        switch (wal_konc)
        {
        case 'E':
            przelicznik = kursy("PLN_TO_EUR");
            break;
        case 'U':
            przelicznik = kursy("PLN_TO_USD");
            break;
        case 'G':
            przelicznik = kursy("PLN_TO_GBP");
            break;
        case 'R':
            przelicznik = kursy("PLN_TO_RUB");
            break;
        case 'K':
            przelicznik = kursy("PLN_TO_KUN");
            break;
        case 'C':
            przelicznik = kursy("PLN_TO_CHF");
            break;
        default:
            cout << "Zle wybrales.\n" << endl;
        }
    }

    if (wal_pocz == 'E') {

        switch (wal_konc)
        {
        case 'P':
            przelicznik = kursy("EUR_TO_PLN");
            break;
        case 'U':
            przelicznik = kursy("EUR_TO_USD");
            break;
        case 'G':
            przelicznik = kursy("EUR_TO_GBP");
            break;
        case 'R':
            przelicznik = kursy("EUR_TO_RUB");
            break;
        case 'K':
            przelicznik = kursy("EUR_TO_KUN");
            break;
        case 'C':
            przelicznik = kursy("EUR_TO_CHF");
            break;
        default:
            cout << "Zle wybrales.\n" << endl;
        }
    }

    if (wal_pocz == 'U') {

        switch (wal_konc)
        {
        case 'P':
            przelicznik = kursy("USD_TO_PLN");
            break;
        case 'E':
            przelicznik = kursy("USD_TO_EUR");
            break;
        case 'G':
            przelicznik = kursy("USD_TO_GBP");
            break;
        case 'R':
            przelicznik = kursy("USD_TO_RUB");
            break;
        case 'K':
            przelicznik = kursy("USD_TO_KUN");
            break;
        case 'C':
            przelicznik = kursy("USD_TO_CHF");
            break;
        default:
            cout << "Zle wybrales.\n" << endl;
        }
    }

    if (wal_pocz == 'G') {

        switch (wal_konc)
        {
        case 'P':
            przelicznik = kursy("GBP_TO_PLN");
            break;
        case 'E':
            przelicznik = kursy("GBP_TO_EUR");
            break;
        case 'U':
            przelicznik = kursy("GBP_TO_USD");
            break;
        case 'R':
            przelicznik = kursy("GBP_TO_RUB");
            break;
        case 'K':
            przelicznik = kursy("GBP_TO_KUN");
            break;
        case 'C':
            przelicznik = kursy("GBP_TO_CHF");
            break;
        default:
            cout << "Zle wybrales.\n" << endl;
        }
    }

    if (wal_pocz == 'R') {

        switch (wal_konc)
        {
        case 'P':
            przelicznik = kursy("RUB_TO_PLN");
            break;
        case 'E':
            przelicznik = kursy("RUB_TO_EUR");
            break;
        case 'U':
            przelicznik = kursy("RUB_TO_USD");
            break;
        case 'G':
            przelicznik = kursy("RUB_TO_GBP");
            break;
        case 'K':
            przelicznik = kursy("RUB_TO_KUN");
            break;
        case 'C':
            przelicznik = kursy("RUB_TO_CHF");
            break;
        default:
            cout << "Zle wybrales.\n" << endl;
        }
    }

    if (wal_pocz == 'K') {

        switch (wal_konc)
        {
        case 'P':
            przelicznik = kursy("KUN_TO_PLN");
            break;
        case 'E':
            przelicznik = kursy("KUN_TO_EUR");
            break;
        case 'U':
            przelicznik = kursy("KUN_TO_USD");
            break;
        case 'G':
            przelicznik = kursy("KUN_TO_GBP");
            break;
        case 'R':
            przelicznik = kursy("KUN_TO_RUB");
            break;
        case 'C':
            przelicznik = kursy("KUN_TO_CHF");
            break;
        default:
            cout << "Zle wybrales.\n" << endl;
        }
    }

    if (wal_pocz == 'C') {

        switch (wal_konc)
        {
        case 'P':
            przelicznik = kursy("CHF_TO_PLN");
            break;
        case 'E':
            przelicznik = kursy("CHF_TO_EUR");
            break;
        case 'U':
            przelicznik = kursy("CHF_TO_USD");
            break;
        case 'G':
            przelicznik = kursy("CHF_TO_GBP");
            break;
        case 'R':
            przelicznik = kursy("CHF_TO_RUB");
            break;
        case 'K':
            przelicznik = kursy("CHF_TO_KUN");
            break;
        default:
            cout << "Zle wybrales.\n" << endl;
        }
    }

    string wypisz_waluta2;
    switch (wal_konc) {
    case'P':
        wypisz_waluta2 = "Zlotych\n";
        break;
    case'E':
        wypisz_waluta2 = "Euro\n";
        break;
    case'U':
        wypisz_waluta2 = "Dolarow amerykanskich\n";
        break;
    case'G':
        wypisz_waluta2 = "Funtow brytyjskich\n";
        break;
    case'R':
        wypisz_waluta2 = "Rubli rosyjskich\n";
        break;
    case'K':
        wypisz_waluta2 = "Kun chorwackich\n";
        break;
    case'C':
        wypisz_waluta2 = "Frankow szwajcarskich\n";
        break;
    }

    string wypisz_waluta1;
    switch (wal_pocz) {
    case'P':
        wypisz_waluta1 = "Zlotych\n";
        break;
    case'E':
        wypisz_waluta1 = "Euro\n";
        break;
    case'U':
        wypisz_waluta1 = "Dolarow amerykanskich\n";
        break;
    case'G':
        wypisz_waluta1 = "Funtow brytyjskich\n";
        break;
    case'R':
        wypisz_waluta1 = "Rubli rosyjskich\n";
        break;
    case'K':
        wypisz_waluta1 = "Kun chorwackich\n";
        break;
    case'C':
        wypisz_waluta1 = "Frankow szwajcarskich\n";
        break;
    }

    cout << "Otrzymasz: " << przelicznik * pieniadze << " " << wypisz_waluta2 << "za " << pieniadze << " " << wypisz_waluta1 << "\n\n\n";


    //Dodano markery czasu, aby bylo wiadomo z kiedy konwersja byla dokonywana.
    ofstream file("Logi.txt", std::ofstream::app);
    if (file.is_open()) {
        time_t t = time(0);   // get time czas
        tm* czas = localtime(&t);
        file << (czas->tm_year + 1900) << '-'
            << (czas->tm_mon + 1) << '-'
            << czas->tm_mday << " "
            << (czas->tm_hour + 1) << ":"
            << czas->tm_min << ":"
            << czas->tm_sec
            << "\n";
        file << "Wymieniono" << " " << pieniadze << " " << wypisz_waluta1 << "na" << " " << przelicznik * pieniadze << " " << wypisz_waluta2 << " \n";
        file.close();
    }
}

int main() {
    Kantor klient;
    //Petla nieskonczona, ktora ciagle wymaga od uzytkownika podawania danych. W przypadku checi zakonczenia, nalezy w dowolnym z trzech okienek wyboru (2 walut oraz pieniedzy) wpisac Q lub q.
    for (;;) {
        klient.waluta_we();
        klient.waluta_wy();
        klient.pieniadze();
        klient.wymiana();
    }
}
