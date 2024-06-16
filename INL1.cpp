#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ctime>
#include <tuple>
#include <utility>
using namespace std;

int input(int StartKapital);
tuple<string, int, int> bet();
int spin();
vector<int> sortera(string Farg, int Siffra, int Identifierare);
int matcha(vector<int> ValdaVarden, int hjulet);
int resultat(vector<int> ValdaVarden, int Vinst, int Insats, int StartKapital, int hjulet);
bool nyomgang(int StartKapital, bool SpelSlut);

int main() 
{
    //Ingångsvariabler
    int StartKapital = 1000;
    cout << "Pengar på kontot: " << StartKapital << endl;
    bool SpelSlut;
    SpelSlut = false;

    while (SpelSlut == false) {
        int Insats = input(StartKapital);
        tuple<string, int, int> SpelarVal = bet(); //Första returnerade värde är färg, andra är siffra, tredje är identifierare
        int hjulet = spin();
        vector<int> ValdaVarden = sortera(get<0>(SpelarVal), get<1>(SpelarVal), get<2>(SpelarVal));
        int Vinst = matcha(ValdaVarden, hjulet);
        StartKapital = resultat(ValdaVarden, Vinst, Insats, StartKapital, hjulet);
        SpelSlut = nyomgang(StartKapital, SpelSlut);
    }
    
    return 0;
}

int input(int StartKapital)
{
    //Tar emot spelarens insats
    int Insats;
    while (true) {
        //Loopar igenom tills en tillfredställande input fås
        cout << "Välj insats: 100kr, 300kr, 500kr ";
        std::cin >> Insats;

        if (std::cin.fail()) {
            //Ser till så att inputten är en siffra
            std::cout << "Vänligen välj en siffra." << endl;
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            if (Insats == 100 || Insats== 300 || Insats == 500) {
                if (Insats > StartKapital)
                    std::cout << "Du har inte råd med den insatsen." << endl;
                else 
                    break;
            } else
                std::cout << "Vänligen välj 100, 300, eller 500kr." << endl;
        }
    }
    return Insats;
}

tuple<string, int, int> bet()
{
    //Tar emot spelarens färg/nummer
    string FargElSiffra;
    string Farg;
    int Siffra;
    int Identifierare = 0; //1 betyder att spelaren valt färg, 2 betyder siffra
    while (true) {
        cout << "Vill du välja farg eller siffra? ";
        cin >> FargElSiffra;

        if (FargElSiffra == "farg") {
            //Om spelaren vill betta på färg
            cout << "svart eller rod?";
            cin >> Farg;
            if (Farg == "svart"||Farg == "rod") {
                Identifierare = 1;
                break;
            } else
                cout << "Vänligen välj svart eller rod." << endl;
        } else if (FargElSiffra == "siffra") {
            //Om spelaren vill betta på siffra
            cout << "Välj siffra 1-36: ";
            cin >> Siffra;
            //Ser till så att inputten är en siffra
            if (cin.fail()) {
                cout << "Vänligen välj en siffra." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                if (Siffra >= 1 && Siffra <= 36) {
                    Identifierare = 2;
                    break;
                } else
                    cout << "Vänligen välj en siffra mellan 1-36." << endl;
            }
        } else
            cout << "Var god skriv in farg eller siffra." << endl;
    }
    return make_tuple(Farg, Siffra, Identifierare);
}

int spin()
{
    //Spinner roulettehjulet
    srand(time(0));
    int hjulet = rand() % 36 + 1;
    return hjulet;
}

vector<int> sortera(string Farg, int Siffra, int Identifierare)
{
    //Sorterar inputen så att den kan matchas mot roulettehjulet
    vector<int> ValdaVarden;
    if (Identifierare == 1) {
        //Färg har valts
        if (Farg == "svart") { //Svart representerar jämna nummer
            for (int i = 1; i <= 36; ++i) {
                if (i % 2 == 0)
                    ValdaVarden.push_back(i);
            }
        } else { //Rött representerar udda nummer
            for (int i = 1; i <= 36; ++i) {
                if (i % 2 != 0)
                    ValdaVarden.push_back(i);
            }
        }
    } else //Siffra har valts
        ValdaVarden.push_back(Siffra);
    return ValdaVarden;
}

int matcha(vector<int> ValdaVarden, int hjulet)
{
    //Matchar valda siffror mot hjulets värde
    int Vinst = 3; //1 är färgvinst, 2 är nummervinst, 3 är förlust
    if (ValdaVarden.size() > 1) {
        //Färgvinst eller förlust
        for (int i = 0; i < ValdaVarden.size(); ++i) {
            if (ValdaVarden[i] == hjulet) {
                Vinst = 1;
                break;
            }
        }
    } else {
        //Nummervinst eller förlust
        if (ValdaVarden[0] == hjulet)
            Vinst = 2;
    }
    return Vinst;
}

int resultat(vector<int> ValdaVarden, int Vinst, int Insats, int StartKapital, int hjulet)
{
    //Meddelar resultatet av omgången
    cout << "Valda siffror: ";
    for (int i = 0; i < ValdaVarden.size(); ++i)
        cout << ValdaVarden[i] << " ";
    cout << endl;
    cout << "Hjulets resultat: " << hjulet << endl;

    //Meddelar utfall och justerar kapitalet
    if (Vinst == 1) {
        StartKapital += 2 * Insats;
        cout << "Du vann på färg! " << endl;
        cout << "Vinst: " << 2 * Insats << "kr" <<endl;
    } else if (Vinst == 2) {
        StartKapital += 10 * Insats;
        cout << "Du vann på siffra! " << endl;
        cout << "Vinst: " << 10 * Insats << "kr" << endl;
    } else if (Vinst == 3) {
        StartKapital -= Insats;
        cout << "Du förlorade! " << endl;
        cout << "Förlust: " << Insats << "kr" << endl;
    }
    cout << "Nytt saldo: " << StartKapital << "kr" << endl;
    return StartKapital;
}

bool nyomgang(int StartKapital, bool SpelSlut)
{
    //Förbereder nästa omgång
    string NyOmgang;
    while (true) {
        cout << "Vill du köra en ny omgång? ja eller nej";
        cin >> NyOmgang;
        if (NyOmgang == "ja") {
            SpelSlut = false;
            break;
        } else if (NyOmgang == "nej") {
            SpelSlut = true;
            cout << "Tack för att du spelade! Du slutade spelet med " << StartKapital << "kr i saldot!" << endl;
            break;
        } else
            cout << "Skriv in ja eller nej." << endl;
    }
    
    //Kollar så att spelaren har råd med en till omgång
    if (StartKapital < 100) {
        SpelSlut = true;
        cout << "Du har ej råd att spela mer!" << endl;
    }
    return SpelSlut;
}