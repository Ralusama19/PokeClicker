#include "utils.h"
#include "button.h"
#include "slot.h"
#include "pokedex.h"
#include "levelbar.h"
#include "Background.h"


using namespace std;

int main(){

   //load all variables and objects
    srand (time(NULL));
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Poke Clicker YOYOOYOOOO OOOOOH so gut at dis geim");
    Background background("Resources/Images/background.png");
    Background pokedexBkg("Resources/Images/pokedexbackground.png");
    Pokedex pokedex("Resources/Images/icons.png",14,11);
    vector<Slot> sslots;
    vector<Button*> buttons;
    vector<Button*> feeders(3);
    Button pokeball("Resources/Images/pokeball.png");
    Button buyEgg("Resources/Images/buyEgg.png");
    Button toPokedex("Resources/Images/pokedexbutton.png");
    Button back("Resources/Images/backButton.png");
    LevelBar eggBar("Resources/Images/eggBarE.png", "Resources/Images/eggBarF.png", 894, 509);
   // LevelBar _healthBar ("Resources/Images/lvlbarE.png","Resources/Images/lvlbarF.png", 23 + 253, 23);
   // LevelBar _berryBar("Resources/Images/berrybarE.png","Resources/Images/berrybarF.png", 23 + 253, 23 + 253);
    sf::Texture pokemonTexture, eggTexture;



//Main environment
    int newClicks;
    bool menu = true;
    bool canBuy = false;
    int eggClicks = 0;
    int eggPrice = 4;
    int freeSlot;

    //makin buttons, making bacon buttons, taking buttons and then put them in a button, BACON BUTTOOOONS....

    pokeball.setPosition(425,509);
    buttons.push_back(&pokeball);
    pokeball.turnOn();

    buyEgg.setPosition(643,509);
    buttons.push_back(&buyEgg);

    toPokedex.setPosition(111,509);
    buttons.push_back(&toPokedex);
    toPokedex.turnOn();

    if(!pokemonTexture.loadFromFile("Resources/Images/pokemons.png"))cout << "couldnt load pokemon sprite texture!" << endl;
    if(!eggTexture.loadFromFile("Resources/Images/egg.png")) cout << "couldnt load egg texture!" << endl;

    //SLOTS
    int offset = 333;
    for(uint i = 0; i<3; ++i){
        sslots.push_back(Slot(pokemonTexture, eggTexture, 24 + i*offset, 24));
    }

    //FEEDEEEERS

    for(uint i = 0; i < feeders.size(); ++i){
        feeders[i] = new Button("Resources/Images/feedButton.png");
        feeders[i]->setPosition(24 + i*offset,275);
        //feeders[i]->turnOn();
    }


//Pokedex environment

    back.setPosition(881,618);
    back.turnOn();
/*
    LevelBar bar("Resources/Images/lvlbarE.png", "Resources/Images/lvlbarF.png", 941, 24);
*/




//game loop
    while(window.isOpen()){
        //cout << "ekisku te cierras" << endl;

        //handle events
        while(window.pollEvent(event)){
            switch (event.type) {

                //pressed buttons
                case (sf::Event::MouseButtonPressed) :
                case (sf::Event::MouseButtonReleased) :
                    if(menu){
                        for (uint i = 0; i < buttons.size(); ++i){
                            buttons[i]->handleMouseEvent(event);
                        }
                        for (uint i = 0; i < feeders.size(); ++i){
                            feeders[i]->handleMouseEvent(event);
                        }
                    }

                    else back.handleMouseEvent(event);

                    break;

                //closed window
                case (sf::Event::Closed):
                        window.close();
                    break;

            default:
                    break;
            }
        }

    //handle menu scene
        if(menu){

            //update inputs
            for(uint i = 0; i < buttons.size(); ++i){
                buttons[i]->update(sf::Mouse::getPosition(window));
            }

            for(uint i = 0; i < feeders.size(); ++i){
                feeders[i]->update(sf::Mouse::getPosition(window));
            }

            //pokeball button
            newClicks = pokeball.getClicks();
            eggClicks += newClicks;
            //cout << eggClicks << endl;

            //feed buttons
            for(uint i = 0; i < feeders.size(); ++i){
                if(sslots[i].canFeed()) feeders[i]->turnOn();
            }
            for(uint i = 0; i < feeders.size(); ++i){
                if(feeders[i]->getClicks() > 0){
                    feeders[i]->turnOff();
                    sslots[i].buyBerry();
                }
            }

            //cout << "test1" << endl;
            //slots
            for (uint i =  0; i < sslots.size(); ++i){
                sslots[i].update(newClicks);
            }
            //cout << "test2" << endl;
            //buy egg button
            if(!buyEgg.isOn() && canBuy) buyEgg.turnOn();

            if(buyEgg.getClicks() > 0){
                buyEgg.turnOff();
                canBuy = false;
                eggClicks = eggClicks - eggPrice;
                eggPrice *= 2;
                eggBar.update((eggClicks*100)/eggPrice);
                sslots[freeSlot].addPokemon(rand()%15,15);
                //cout << "new egg Price" << eggPrice << endl;

            }

            //switch to pokedex
            if(toPokedex.getClicks() != 0) menu = false;

            //update stuff
            eggBar.update((eggClicks*100)/eggPrice);/*
            _healthBar.update((eggClicks*100)/eggPrice);
            _berryBar.update((eggClicks*100)/eggPrice);*/
            //cout << "bar status" << (eggClicks*100)/eggPrice << endl;
            if(!canBuy){
                freeSlot = -1;
                for (uint i =  0; i < sslots.size(); ++i){
                    if(sslots[i].isFree()) freeSlot = i;
                }
                if(eggClicks >= eggPrice && freeSlot != -1) canBuy = true;
            }

        //draw all the stuff
            window.clear();
            background.draw(window);
            for (uint i = 0; i < buttons.size(); ++i) window.draw(*buttons[i]);
            for (uint i = 0; i < feeders.size(); ++i) window.draw(*feeders[i]);
            for (uint i = 0; i < sslots.size(); ++i) sslots[i].draw(window);
            eggBar.draw(window);/*
            _healthBar.draw(window);
            _berryBar.draw(window);*/
        }


    //handle pokedex scene
        else{

            //update inputs
            back.update(sf::Mouse::getPosition(window));

            //switch to main
            if(back.getClicks() != 0) menu = true;

            //draw all the stuff
            window.clear();
            pokedexBkg.draw(window);
            pokedex.draw(window);
            window.draw(back);


        }

        window.display();
    }

    for(uint i = 0; i < feeders.size(); ++i){
        delete feeders[i];
    }
}
