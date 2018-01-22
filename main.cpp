 /*
 * Copyright 2018, Carlos Aniorte Llanes <carlos.aniortellanes@gmail.com>
 *
 * This file is part of snailScape
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>


using namespace std;



#define kVel 0.2f



string toString(int integer){
    char numstr[10]; // enough to hold all numbers up to 32-bits
    sprintf(numstr, "%i", integer);
    return numstr;
}


int main()
{
    std::cout<<std::endl;
    std::cout<< "Practica 0 - Fundamentos de los Videojuegos - Ingenieria Multimedia" << std::endl;
    std::cout<<std::endl;
    std::cout<< "Realizada por: Carlos Aniorte Llanes" << std::endl;


    //Creamos una ventana
    sf::RenderWindow window(sf::VideoMode(640, 480), "SnailScape - Carlos Aniorte Llanes");

    //Asignamos icono a la ventana
    sf::Image icon;
    icon.loadFromFile("resources/icon.png");
    window.setIcon(16,16,icon.getPixelsPtr());

     // Texto
    sf::Font font;
    if (!font.loadFromFile("resources/fonts/calibri.ttf"))
        return EXIT_FAILURE;

    sf::Font fontpixelated;
    if (!fontpixelated.loadFromFile("resources/fonts/pixelated.ttf"))
        return EXIT_FAILURE;

    sf::Text vida("VIDA:", fontpixelated, 30);
    vida.setPosition(450,-2);
    vida.setCharacterSize(30);
    vida.setFillColor(sf::Color::Black);

    sf::Text puntos("PUNTOS:", fontpixelated, 30);
    puntos.setPosition(450,35);
    puntos.setCharacterSize(30);
    puntos.setFillColor(sf::Color::Black);

    sf::Text pData("0", fontpixelated, 30);
    pData.setPosition(565,35);
    pData.setCharacterSize(30);
    pData.setFillColor(sf::Color::Black);

    sf::Text nivel("NIVEL:", fontpixelated, 30);
    nivel.setPosition(450,72);
    nivel.setCharacterSize(30);
    nivel.setFillColor(sf::Color::Black);

    sf::Text pLevel("0", fontpixelated, 30);
    pLevel.setPosition(565,72);
    pLevel.setCharacterSize(30);
    pLevel.setFillColor(sf::Color::Black);



    sf::Text sign("Carlos Aniorte Llanes", font, 10);
    sign.setPosition(545,465);
    sign.setCharacterSize(10);
    sign.setFillColor(sf::Color::Black);

    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/caracol.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }



    sf::Texture lettuce;
    if (!lettuce.loadFromFile("resources/vida.png"))
    {
        std::cerr << "Error cargando la imagen vida.png";
        exit(0);
    }


    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(tex);
    sf::Sprite life1(lettuce);
    sf::Sprite life2(lettuce);
    sf::Sprite life3(lettuce);


    //Le pongo el centroide donde corresponde
    sprite.setOrigin(64/2,32/2);
    life1.setOrigin(32/2, 32/2);
    life2.setOrigin(32/2, 32/2);
    life3.setOrigin(32/2, 32/2);

    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0*64, 0*32, 64, 32));
    //sprite.setColor(sf::Color(255,0,0));

    life1.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
    life2.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
    life3.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));

    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(320, 390);
    life1.setPosition(540, 20);
    life2.setPosition(580, 20);
    life3.setPosition(620, 20);

    //BABA

    sf::CircleShape baba[200];




    //CARTEL DE GAME OVER
    sf::RectangleShape gameoverblock;
    gameoverblock.setSize(sf::Vector2f(580, 420));
    gameoverblock.setOutlineColor(sf::Color::Black);
    gameoverblock.setOutlineThickness(2);
    gameoverblock.setPosition(32, 32);

    sf::Text gameovertext("Has perdido las 3 vidas", font, 50);
    sf::Text gameovertext2(L"Pulsa cualquier tecla de dirección \n         para volver a intentarlo", font, 40);
    gameovertext.setPosition(175,100);
    gameovertext.setCharacterSize(30);
    gameovertext.setStyle(sf::Text::Bold);
    gameovertext.setFillColor(sf::Color::Red);
    gameovertext2.setPosition(125,240);
    gameovertext2.setCharacterSize(25);
    gameovertext2.setStyle(sf::Text::Bold);
    gameovertext2.setFillColor(sf::Color::Black);


    //DEFINICION DE LOS MUROS
    sf::RectangleShape wall;
    wall.setSize(sf::Vector2f(150, 15));
    wall.setOutlineColor(sf::Color::Black);
    wall.setOutlineThickness(2);

    //CONSTRUCCION DE LOS MUROS
    sf::RectangleShape walls[6];
    for(int i=0;i<6;i++) walls[i] = wall;

    //POSICIONAMIENTO DE LOS MUROS
    walls[0].setPosition(2, 320); //ABAJO IZQ
    walls[1].setPosition(240, 320); //ABAJO CENTRO
    walls[2].setPosition(488, 320); //ABAJO DCHA
    walls[3].setPosition(240, 220); //CENTRO CENTRO
    walls[4].setPosition(2, 120); //ARRIBA IZQ
    walls[5].setPosition(488, 120); //ARRIBA DCHA


    //DEFINICION DE LAS PUERTAS
    sf::RectangleShape door;
    door.setSize(sf::Vector2f(250, 2));
    door.setOutlineColor(sf::Color::Red);
    door.setFillColor(sf::Color::Red);
    door.setOutlineThickness(2);



     //CONSTRUCCION DE LAS PUERTAS
    sf::RectangleShape doors[5];
    for(int i=0;i<5;i++) doors[i] = door;

    //POSICIONAMIENTO DE LAS PUERTAS
    doors[0].setPosition(158, 326); //ABAJO
    doors[1].setPosition(140, 226); //MITAD_L
    doors[2].setPosition(240, 226); //MITAD_R
    doors[3].setPosition(140, 126); //ARRIBA_L
    doors[4].setPosition(240, 126); //ARRIBA_R


    bool door0_state = false;
    bool door1_state = false;
    bool door2_state = false;

    //DEFINICION DE LAS METAS
    sf::RectangleShape goal;
    goal.setSize(sf::Vector2f(100, 30));
    goal.setOutlineColor(sf::Color::Black);
    goal.setFillColor(sf::Color(193,255,192));
    goal.setOutlineThickness(5);

     //CONSTRUCCION DE LAS METAS
    sf::RectangleShape goals[3];
    for(int i=0;i<3;i++) goals[i] = goal;

    //POSICIONAMIENTO DE LAS METAS
    goals[0].setPosition(90, 10); //IZQUIERDA
    goals[0].setFillColor(sf::Color(203,183,158));

    goals[1].setPosition(210, 10); //CENTRO
    goals[1].setFillColor(sf::Color(238,238,238));

    goals[2].setPosition(330, 10); //DERECHA
    goals[2].setFillColor(sf::Color(255,201,129));

    //DEFINICION DE LAS PUNTUACIONES DE LAS METAS
    sf::Text meta1("50p.", fontpixelated, 30);
    meta1.setCharacterSize(30);
    meta1.setFillColor(sf::Color::Black);
    meta1.setPosition(goals[0].getPosition().x+30, goals[0].getPosition().y-5);

    sf::Text meta2("100p.", fontpixelated, 30);
    meta2.setCharacterSize(30);
    meta2.setFillColor(sf::Color::Black);
    meta2.setPosition(goals[1].getPosition().x+25, goals[1].getPosition().y-5);

    sf::Text meta3("200p.", fontpixelated, 30);
    meta3.setCharacterSize(30);
    meta3.setFillColor(sf::Color::Black);
    meta3.setPosition(goals[2].getPosition().x+25, goals[2].getPosition().y-5);


    //sf::Clock reloj;
    //BABA
    sf::Clock babas;
    //clock.restart();

    //RETRASO POR DAÑO
    sf::Clock hurtDelay;
    //RETRASO POR DAÑO
    sf::Clock goalDelay;
    //hurtDelay
    //RELOJ POR META
    sf::Clock win;
     //RELOJ POR META
    sf::Clock goalsClock;


    bool lock = false;  //variable de bloqueo de controles por colisión
    int  last_x = 0,  last_y = 0;  //almacenan posición anterior a la colisión
    int difficulty = 3;
    int level = 1;
    int life = 3;
    int hurt = -1;
    int babaCounter = 0;
    bool gameover = false;
    //int state = 0; //controla el estado de la animacion de elementos
    int score = 0;
    int scoreScreen = 0;

    //Bucle del juego
   //std::cout << difficulty << std::endl;


    //14999

    while (window.isOpen())
    {

        if(goalsClock.getElapsedTime().asMilliseconds()>16000)
                goalsClock.restart();

        if(goalsClock.getElapsedTime().asMilliseconds() > 3000 && goalsClock.getElapsedTime().asMilliseconds() < 12999){

            goals[0].setPosition(goals[0].getPosition().x, 10);
            meta1.setPosition(meta1.getPosition().x, goals[0].getPosition().y-5);
        }
        else {
            goals[0].setPosition(goals[0].getPosition().x, goals[0].getPosition().y-100);
            meta1.setPosition(meta1.getPosition().x, goals[0].getPosition().y-100);

        }

        if(goalsClock.getElapsedTime().asMilliseconds() > 13000 && goalsClock.getElapsedTime().asMilliseconds() < 15999){

            goals[1].setPosition(goals[1].getPosition().x, 10);
            meta2.setPosition(meta2.getPosition().x, goals[1].getPosition().y-5);

        }
        else {
            goals[1].setPosition(goals[1].getPosition().x, goals[1].getPosition().y-100);
            meta2.setPosition(meta2.getPosition().x, goals[1].getPosition().y-100);
        }

        if(goalsClock.getElapsedTime().asMilliseconds() > 0 && goalsClock.getElapsedTime().asMilliseconds() < 2999){

            goals[2].setPosition(goals[2].getPosition().x, 10);
            meta3.setPosition(meta3.getPosition().x, goals[2].getPosition().y-5);

        }
        else {
            goals[2].setPosition(goals[2].getPosition().x, goals[2].getPosition().y-100);
            meta3.setPosition(meta3.getPosition().x, goals[2].getPosition().y-100);
        }

        pLevel.setString(toString(level));

        if(scoreScreen<score){
            scoreScreen++;
            pData.setString(toString(scoreScreen));
        }


        if(level>1 && win.getElapsedTime().asMilliseconds()<1000){
            if(win.getElapsedTime().asMilliseconds()%2==0){
                pLevel.setFillColor(sf::Color::Yellow); //COLOR DE FONDO BLANCO

            }
            else
                pLevel.setFillColor(sf::Color::Black); //COLOR DE FONDO BLANCO
        }
        else
             pLevel.setFillColor(sf::Color::Black);


        //CONTROLADOR DE VIDAS
        switch(life){

            case 3: life1.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                    life2.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                    life3.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                    break;

            case 2: life1.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                    life2.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                    life3.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                    break;

            case 1: life1.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                    life2.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                    life3.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                    break;

            case 0: life1.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                    life2.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                    life3.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                    break;

            case -1:
                    gameover = true;

        }


                //std::cout << tiempo.asMilliseconds() << std::endl;
                //std::cout << state << std::endl;

            /*
             if(state==0)
                compuerta1.move(0.01,0);
             else
                 compuerta1.move(-0.01,0);
            */

        if(babas.getElapsedTime().asMilliseconds() > 10){
            baba[babaCounter].setRadius(10.0);
            baba[babaCounter].setOutlineColor(sf::Color::Red);
            wall.setOutlineThickness(10);
            if(life==3)baba[babaCounter].setFillColor(sf::Color(193,255,192));
            if(life==2)baba[babaCounter].setFillColor(sf::Color(228,255,192));
            if(life==1)baba[babaCounter].setFillColor(sf::Color(255,241,192));
            if(life==0)baba[babaCounter].setFillColor(sf::Color(255,187,187));
            baba[babaCounter].setPosition(sprite.getPosition().x-17+(rand()%(15-0 + 1) + 0), sprite.getPosition().y+(rand()%(15-0 + 1) + 0));
            //window.draw(baba);
            babaCounter++;
            if(babaCounter>75)babaCounter = 0;
            //std::cout << babas.getElapsedTime().asMilliseconds() << " babaCounter: " << babaCounter << std::endl;
            babas.restart();
        }

            //CONTORLADOR DE PUERTA 1
            if(!door0_state){
                doors[0].move((babas.getElapsedTime().asMilliseconds()%2*0.02)*difficulty,0);
                if(doors[0].getPosition().x < 240) door0_state = false;
                else door0_state = true;
            }
            if(door0_state){
                doors[0].move((babas.getElapsedTime().asMilliseconds()%2*-0.02)*difficulty,0);
                if(doors[0].getPosition().x > 140) door0_state = true;
                else door0_state = false;
            }

        //CONTORLADOR DE PUERTA 2
            if(!door1_state){
                doors[1].move((babas.getElapsedTime().asMilliseconds()%2*0.02)*difficulty,0);
                doors[2].move((babas.getElapsedTime().asMilliseconds()%2*-0.02)*difficulty,0);
                if(doors[1].getPosition().x < 150) door1_state = false;
                else door1_state = true;

            }
            if(door1_state){
                doors[1].move((babas.getElapsedTime().asMilliseconds()%2*-0.02)*difficulty,0);
                doors[2].move((babas.getElapsedTime().asMilliseconds()%2*+0.02)*difficulty,0);
                if(doors[1].getPosition().x > 30) door1_state = true;
                else door1_state = false;

            }

            //CONTORLADOR DE PUERTA 3
            if(!door2_state){
                doors[3].move((babas.getElapsedTime().asMilliseconds()%2*0.03)*difficulty,0);
                doors[4].move((babas.getElapsedTime().asMilliseconds()%2*-0.03)*difficulty,0);
                if(doors[3].getPosition().x < 65) door2_state = false;
                else door2_state = true;

            }
            if(door2_state){
                doors[3].move((babas.getElapsedTime().asMilliseconds()%2*-0.03)*difficulty,0);
                doors[4].move((babas.getElapsedTime().asMilliseconds()%2*+0.03)*difficulty,0);
                if(doors[3].getPosition().x > -80) door2_state = true;
                else door2_state = false;

            }

            for(sf::RectangleShape ddr : doors){
                //std::cout << "Checking.. " << std::endl;
                if(life>=0 && sprite.getGlobalBounds().intersects(ddr.getGlobalBounds())){
                    //std::cout << "Hurt: " << hurt << std::endl;
                    //std::cout << "Life: " << life << std::endl;
                    lock = true;
                    //std::cout << "Colision!!" << std::endl;
                    //std::cout << "diff: (" << last_x-sprite.getPosition().x << "," <<  last_y-sprite.getPosition().y << ")" << std::endl;
                    if(life>=0)sprite.move((last_x-sprite.getPosition().x)*4,  (last_y-sprite.getPosition().y)*4);
                    else sprite.setPosition(320, 390);
                    hurt++;
                    life--;
                    hurtDelay.restart();
                    break;
                }
                else
                    lock = false;   //Desbloqueo

            }
        //COLISIONES CON LAS METAS
            int j=0;
            for(sf::RectangleShape gls : goals){

                if(sprite.getGlobalBounds().intersects(gls.getGlobalBounds())){

                    if(j==0){
                        score+=50;
                        pData.setString(toString(score));

                    }
                    if(j==1){
                        score+=100;
                        pData.setString(toString(score));
                    }
                    if(j==2){
                        score+=200;
                        pData.setString(toString(score));

                    }

                    win.restart();

                    //0pData.setString("score");
                    //life = 3;
                    //hurt = -1;
                    difficulty+=2;
                    level++;
                    //pLevel.setString(toString(level));

                    //score = 0;
                    sprite.setPosition(320, 390);
                    gameover = false;
                    goalDelay.restart();
                    goalsClock.restart();

                    break;
                }
                j++;
            }





            //RESET DEL JUEGO
            if(hurtDelay.getElapsedTime().asMilliseconds()>1000)
            if(gameover && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))){

                life = 3;
                hurt = -1;
                difficulty = 3;
                score = 0;
                scoreScreen = 0;
                pData.setString(toString(scoreScreen));
                sprite.setPosition(320, 390);
                gameover = false;

            }


             //COLISIONES CON LOS MUROS
            for(sf::RectangleShape spr : walls){

                if(sprite.getGlobalBounds().intersects(spr.getGlobalBounds())){
                    lock = true;

                    sprite.move((last_x-sprite.getPosition().x)*2,  (last_y-sprite.getPosition().y)*2);

                    break;
                }
                else
                    lock = false;   //Desbloqueo

            }

            if(sprite.getPosition().x<30 || sprite.getPosition().y<30 || sprite.getPosition().x>610 || sprite.getPosition().y>450){
                    lock = true;

                    sprite.move((last_x-sprite.getPosition().x)*2,  (last_y-sprite.getPosition().y)*2);

                  //  break;
                }


            //Nos quedamos con la posición anterior a la de bloqueo
            if(!lock){
                    last_x = sprite.getPosition().x;
                    last_y = sprite.getPosition().y;
            }

            //sf::Time contador = sf::milliseconds(500);
            //std::cout << contador.asMilliseconds() << std::endl;


            if(sprite.getGlobalBounds().intersects(doors[0].getGlobalBounds())){
                life--;
                if(life==0)
                    window.clear();
            }


                    if(hurtDelay.getElapsedTime().asMilliseconds()>1000 && goalDelay.getElapsedTime().asMilliseconds()>1000){


                         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                            sprite.setTextureRect(sf::IntRect(0*64, 0*32, 64, 32));
                            //Reflejo vertical
                            sprite.setScale(1,1);
                            sprite.setRotation(0);
                            sprite.move(-kVel,0);
                        }

                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                            sprite.setTextureRect(sf::IntRect(0*64, 0*32, 64, 32));
                            //Escala por defecto
                            sprite.setScale(1,-1);
                            sprite.setRotation(180);
                            sprite.move(kVel,0);
                        }

                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                            sprite.setScale(1,1);
                            sprite.setTextureRect(sf::IntRect(1*64, 0*32, 64, 32));
                            sprite.setRotation(90);
                            sprite.move(0,-kVel);
                        }

                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                            sprite.setTextureRect(sf::IntRect(1*64, 0*32, 64, 32));
                            sprite.setScale(1,-1);
                            sprite.setRotation(-90);
                            sprite.move(0,kVel);
                        }

            }


        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            //std::cout << "Now:" << sprite.getPosition().x << "," << sprite.getPosition().y << std::endl;
            //std::cout << "Last:" <<  last_x << "," <<  last_y << std::endl;
            switch(event.type){

                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;

            }

        }
        //std::cout << life << std::endl;

        //CONTROLADOR DE ANIMACION POR DAÑO
        if(life<3 && hurtDelay.getElapsedTime().asMilliseconds()<500){
            //hurt++;
            if(hurtDelay.getElapsedTime().asMilliseconds()%2==0)
                window.clear(sf::Color::Red); //COLOR DE FONDO BLANCO
            else
                window.clear(sf::Color::White); //COLOR DE FONDO BLANCO
        }
        else {
            window.clear(sf::Color(220,220,220)); //COLOR DE FONDO BLANCO
            //hurt=-1;
        }

        window.draw(sign);
        for(sf::CircleShape i : baba)window.draw(i); //BABAS
        for(sf::RectangleShape i : doors)window.draw(i); //PUERTAS
        for(sf::RectangleShape i : walls)window.draw(i); //MUROS
        for(sf::RectangleShape i : goals)window.draw(i); //METAS
        window.draw(meta1);
        window.draw(meta2);
        window.draw(meta3);

        window.draw(sprite);
        window.draw(life1);
        window.draw(life2);
        window.draw(life3);
        window.draw(vida);
        window.draw(puntos);
        window.draw(pData);
        window.draw(nivel);
        window.draw(pLevel);

        if(gameover){

            window.clear(sf::Color::Red); //COLOR DE FONDO BLANCO
            window.draw(gameoverblock);
            window.draw(gameovertext);
            window.draw(gameovertext2);

        }

        window.display();


    }

    return 0;
}
