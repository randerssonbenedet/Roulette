#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ctime>

int main() {
    //Ingångsvariabler
    int StartKapital = 1000;
    std::cout << "Pengar på kontot: " << StartKapital << std::endl;

    //Tar emot spelarens insats
    int Insats;
    while (true) {
        //Loopar igenom tills en tillfredställande input fås
        std::cout << "Välj insats: 100kr, 300kr, 500kr ";
        std::cin >> Insats;
        if (std::cin.fail()) {
            //Ser till så att inputten är en siffra
            std::cout << "Vänligen välj en siffra." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if (Insats == 100 || Insats== 300 || Insats == 500) {
                break;
            } else {
                std::cout << "Vänligen välj 100, 300, eller 500kr." << std::endl;
            }
        }
    }

    //Tar emot spelarens färg/nummer
    std::string FargElSiffra;
    std::string Farg;
    int Siffra;
    int Identifierare = 0; //1 betyder att spelaren valt färg, 2 betyder siffra
    while (true) {
        std::cout << "Vill du välja farg eller siffra? ";
        std::cin >> FargElSiffra;

        if (FargElSiffra == "farg") {
            //Om spelaren vill betta på färg
            std::cout << "svart eller rod?";
            std::cin >> Farg;
            if (Farg == "svart"||Farg == "rod") {
                Identifierare = 1;
                break;
            } else {
                std::cout << "Vänligen välj svart eller rod." << std::endl;
            }
        } else if (FargElSiffra == "siffra") {
            //Om spelaren vill betta på siffra
            std::cout << "Välj siffra 1-36: ";
            std::cin >> Siffra;
            //Ser till så att inputten är en siffra
            if (std::cin.fail()) {
                std::cout << "Vänligen välj en siffra." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                if (Siffra >= 1 && Siffra <= 36) {
                    Identifierare = 2;
                    break;
                } else {
                    std::cout << "Vänligen välj en siffra mellan 1-36." << std::endl;
                }
            }
        } else {    
            std::cout << "Var god skriv in farg eller siffra." << std::endl;
        }

    }
    
    //Spinner roulettehjulet
    srand(time(0));
    int hjulet = rand() % 36 + 1;

    //Sorterar inputen så att den kan matchas mot roulettehjulet
    std::vector<int> ValdaVarden;
    if (Identifierare == 1) {
        //Färg har valts
        if (Farg == "svart") {
            //Svart representerar jämna nummer
            for (int i = 1; i <= 36; ++i) {
                if (i % 2 == 0) {
                    ValdaVarden.push_back(i);
                }
            }
        } else {
            //Rött representerar udda nummer
            for (int i = 1; i <= 36; ++i) {
                if (i % 2 != 0) {
                    ValdaVarden.push_back(i);
                }
            }
        }
    } else {
        //Siffra har valts
        ValdaVarden.push_back(Siffra);
    }

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
        if (ValdaVarden[0] == hjulet) {
            Vinst = 2;
        }
    }

    //Ändrar pengar på kontot utefter vinstsort


    std::cout << "VALDAVARDEN: ";
    for (int i = 0; i < ValdaVarden.size(); ++i) {
        std::cout << ValdaVarden[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "HJULET: " << hjulet << std::endl;

    std::cout << "VINSTSORT: " << Vinst << std::endl;

    std::cout << "GAGABBABAOOOGOGOOOOOOO" << std::endl;
    return 0;
}