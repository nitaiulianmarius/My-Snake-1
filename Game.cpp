#include "Game.h"

void Game::handleEvent()
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window->close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        std::ifstream f("config.mySnake");
        int bestScore, lastScore;
        lastScore = score;
        f >> bestScore;
        f.close();
        if(lastScore > bestScore)
            bestScore = lastScore;
        std::ofstream g("config.mySnake");
        g << bestScore << ' ' << lastScore;
        g.close();
        window->close();
    }
}

void Game::update()
{

    // coliziunea la deplasarea stanga
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getPosition().x > player.getGlobalBounds().width*0.5)
    {
        bool getCollision = false;
        for(int i=0; i<box.size(); i++)
            if(box[i].getPosition().x + box[i].getImage().getGlobalBounds().width >= player.getPosition().x - player.getGlobalBounds().width*0.5 - width*0.02 &&
               box[i].getPosition().y <= player.getPosition().y - player.getGlobalBounds().height*0.5 && box[i].getPosition().y + box[i].getImage().getGlobalBounds().height >= player.getPosition().y + player.getGlobalBounds().height*0.5)
            {
                getCollision = true;
                break;
            }
        if(!getCollision)
            player.move(-width*0.02, 0);
    }

    // coliziunea la deplasarea dreapta
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getPosition().x < width - player.getGlobalBounds().width*0.5)
    {
        bool getCollision = false;
        for(int i=0; i<box.size(); i++)
            if(box[i].getPosition().x <= player.getPosition().x + player.getGlobalBounds().width*0.5 + width*0.02 &&
               box[i].getPosition().y <= player.getPosition().y - player.getGlobalBounds().height*0.5 && box[i].getPosition().y + box[i].getImage().getGlobalBounds().height >= player.getPosition().y + player.getGlobalBounds().height*0.5)
            {
                getCollision = true;
                break;
            }
        if(!getCollision)
            player.move(width*0.02, 0);
    }


    // 50/100/secunda sansa sa adaug banut in fereastra
    if(rand()%100 < 50 && clock()-lastGoldTime > 1000)
    {
        lastGoldTime = clock();
        Gold goldTemp = Gold(sf::Vector2f(rand()%((int)(width-width*0.025)) + width*0.025, 0), rand()%10+1, width);
        gold.push_back(goldTemp);
    }

    //verific daca jucatorul ia banut
    for(int i=0; i<gold.size(); i++)
    {
        if(player.getPosition().x - player.getGlobalBounds().width*0.5 < gold[i].getPosition().x +  gold[i].getImage().getGlobalBounds().width*0.5 &&
           player.getPosition().x + player.getGlobalBounds().width*0.5 > gold[i].getPosition().x - gold[i].getImage().getGlobalBounds().width*0.5 &&
           abs(player.getPosition().y - gold[i].getPosition().y) < 2*player.getRadius() + 2*gold[i].getImage().getRadius())
        {
            lenght += gold[i].getValue();
            gold.erase(gold.begin()+i, gold.begin()+i+1);
            i--;
        }
    }


    // adauga patrate in fereastra
    if((box.size() && box[box.size()-1].getPosition().y > 0.7*height)||
       !box.size())
    {
        if((rand()%2)%2)
        {
            Box boxTemp = Box(width);
            boxTemp.setResist(rand()%50+1);
            boxTemp.setPosition(rand()%5*width*0.2, -width*0.2);
            box.push_back(boxTemp);
        }
        else
        {
            Box boxTemp = Box(width);
            boxTemp.setResist(rand()%50+1);
            boxTemp.setPosition(0, -width*0.2);
            box.push_back(boxTemp);
            boxTemp.setResist(rand()%50+1);
            boxTemp.setPosition(width*0.2, -width*0.2);
            box.push_back(boxTemp);
            boxTemp.setResist(rand()%50+1);
            boxTemp.setPosition(2*width*0.2, -width*0.2);
            box.push_back(boxTemp);
            boxTemp.setResist(rand()%50+1);
            boxTemp.setPosition(3*width*0.2, -width*0.2);
            box.push_back(boxTemp);
            boxTemp.setResist(rand()%50+1);
            boxTemp.setPosition(4*width*0.2, -width*0.2);
            box.push_back(boxTemp);
        }
    }

    // verifica daca jucatorul este sub patrat (scade lungimea, rezistenta, creste scorul)
    bool getCollision = false;
    for(int i=0; i<box.size(); i++)
    {
        if(abs(player.getPosition().y - player.getGlobalBounds().height*0.5 - box[i].getPosition().y - box[i].getImage().getGlobalBounds().height) < width*0.01 &&
           player.getPosition().x >= box[i].getPosition().x && player.getPosition().x <= box[i].getPosition().x + box[i].getImage().getGlobalBounds().width)
        {
            playerBoxCollision = true;
            getCollision = true;
            box[i].setResist(box[i].getResist()-0.25);
            lenght-=0.25;
            score+=0.25;

            if(lenght < 0)
            {
                std::ifstream f("config.mySnake");
                int bestScore, lastScore;
                lastScore = score;
                f >> bestScore;
                f.close();
                if(lastScore > bestScore)
                    bestScore = lastScore;
                std::ofstream g("config.mySnake");
                g << bestScore << ' ' << lastScore;
                g.close();
                window->close();
            }
        }

        if(box[i].getResist() < 1)
        {
            box.erase(box.begin()+i, box.begin()+i+1);
            i--;
        }
    }
    if(getCollision == false)
        playerBoxCollision = false;


    // update la patrate si banuti
    if(!playerBoxCollision)
    {
        for(int i=0; i<box.size(); i++)
        {
            box[i].update(height);
            if(box[i].getPosition().y > height)
            {
                box.erase(box.begin()+i, box.begin()+i+1);
                i--;
            }
        }

        for(int i=0; i<gold.size(); i++)
        {
            gold[i].update(height);
            if(gold[i].getPosition().y + gold[i].getImage().getRadius() > height)
            {
                gold.erase(gold.begin()+i, gold.begin()+i+1);
                i--;
            }
        }
    }

    // la fiecare 10 secunde creste fps cu 5 (viteza jocului)
    if(clock() - globalTime > 10000)
    {
        globalTime = clock();
        currentFPS += 5;
        window->setFramerateLimit(currentFPS);
    }
}

void Game::render()
{
    window->clear();
    window->draw(player);

    for(int i=0; i<box.size(); i++)
    {
        window->draw(box[i].getImage());
        outtextxy(box[i].getPosition().x+width*0.1, box[i].getPosition().y+width*0.1, box[i].getResist(), width*0.05, 0);
    }

    for(int i=0; i<gold.size(); i++)
    {
        window->draw(gold[i].getImage());
        outtextxy(gold[i].getPosition().x, gold[i].getPosition().y - gold[i].getImage().getGlobalBounds().height, gold[i].getValue(), gold[i].getImage().getGlobalBounds().width*0.7, 0);
    }

    outtextxy(player.getPosition().x, player.getPosition().y-player.getGlobalBounds().height, lenght, player.getGlobalBounds().width*0.7, 0);

    outtextxy(0.99*width, 0.01*height, score, width*0.07, 1);

    window->display();
}

bool Game::isOpen()
{
    return window->isOpen();
}

bool Game::onFocus()
{
    return window->hasFocus();
}

void Game::outtextxy(int x, int y, int t, int size, int align)
{
    std::ostringstream streamTemp;
    streamTemp << t;
    text.setString(streamTemp.str());
    text.setCharacterSize(size);
    text.setOrigin(text.getGlobalBounds().width*0.5, text.getGlobalBounds().height); // aliniere mijloc-jos
    if(align == 1)
        text.setOrigin(text.getGlobalBounds().width, 0); // aliniere dreapta-sus
    text.setPosition(x, y);
    window->draw(text);
}

void Game::outtextxy(int x, int y, char *t, int size, int align)
{
    text.setString(t);
    text.setCharacterSize(size);
    text.setOrigin(text.getGlobalBounds().width*0.5, text.getGlobalBounds().height); // aliniere mijloc-jos
    if(align == 1)
        text.setOrigin(text.getGlobalBounds().width, 0); // aliniere dreapta-sus
    text.setPosition(x, y);
    window->draw(text);
}
