#include "utils.h"
#include "button.h"
#include "pokedex.h"
#include "Background.h"

using namespace std;

int main(){

    //load all variables and objects

    bool menu = true;
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Poke Clicker YOYOOYOOOO OOOOOH so gut at dis geim");
    Background background("Resources/Images/background.png");    
    vector<Button*> buttons;

    Button pokeball("Resources/Images/pokeball.png");
    pokeball.setPosition(425,509);
    buttons.push_back(&pokeball);

    Button buyEgg("Resources/Images/buyEgg.png");
    buyEgg.setPosition(643,509);
    buttons.push_back(&buyEgg);


    Button toPokedex("Resources/Images/pokedexbutton.png");
    toPokedex.setPosition(111,509);
    buttons.push_back(&toPokedex);

    Background pokedexBkg("Resources/Images/pokedexbackground.png");
    Pokedex pokedex("Resources/Images/icons.png",14,11);

    //just to test
    pokedex.addPokemon(1);
    pokedex.addPokemon(3);
    pokedex.addPokemon(16);
    pokedex.addPokemon(35);
    pokedex.addPokemon(63);
    pokedex.addPokemon(64);
    pokedex.addPokemon(100);
    pokedex.addPokemon(151);


    Button back("Resources/Images/backButton.png");
    back.setPosition(881,618);

    //game loop
    while(window.isOpen()){

        //handle events
        while(window.pollEvent(event)){
            switch (event.type) {

                //pressed buttons
                case (sf::Event::MouseButtonPressed) :
                case (sf::Event::MouseButtonReleased) :
                    if(menu)
                        for (int i = 0; i < buttons.size(); ++i){
                            buttons[i]->handleMouseEvent(event);
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

            for(int i = 0; i < buttons.size(); ++i){
                buttons[i]->update(sf::Mouse::getPosition(window));
            }

            if(toPokedex.getClicks() != 0) menu = false;


            //draw all the stuff
            window.clear();
            background.draw(window);
            for (int i = 0; i < buttons.size(); ++i) window.draw(*buttons[i]);
        }


        //handle pokedex scene
        else{

            back.update(sf::Mouse::getPosition(window));
            if(back.getClicks() != 0) menu = true;

            //draw all the stuff
            window.clear();
            pokedexBkg.draw(window);
            pokedex.draw(window);
            window.draw(back);


        }


        window.display();

    }
}
