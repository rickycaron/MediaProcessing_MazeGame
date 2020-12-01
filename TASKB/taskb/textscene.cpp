#include "textscene.h"
#include <QDebug>

//TextScene::TextScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
//                     const std::vector<std::shared_ptr<Enemy> > &enemies, const std::vector<std::shared_ptr<Tile> > &healthpacks): QGraphicsScene(parent)
//{
//    printTiles(tiles);
//    printProtagonist(protagonist);
//    printEnemies(enemies);
//    printHealthpacks(healthpacks);
//    parent->connect(protagonist.get(),&Protagonist::posChanged,this,&TextScene::redrawProtagonist);
//    for (unsigned int i=0; i<enemies.size(); i++) {
//        parent->connect(enemies[i].get(),&Enemy::dead,enemyQlist[i],&TEnemy::indicateDead);
//    }
//}

TextScene::TextScene(QObject *parent, const std::vector<std::shared_ptr<Tile> > &tiles, const std::shared_ptr<Protagonist> &protagonist, const std::vector<std::shared_ptr<Enemy> > &normalEnemies, const std::vector<std::shared_ptr<PEnemy> > &pEnemies, const std::vector<std::shared_ptr<Tile> > &healthpacks)
    :QGraphicsScene(parent)
{
    printTiles(tiles);
    printProtagonist(protagonist);
    printEnemies(normalEnemies,pEnemies);
    printHealthpacks(healthpacks);
    connect(protagonist.get(),&Protagonist::posChanged,this,&TextScene::redrawProtagonist);

    for(int i=0; i<normalEnemyQlist.size(); i++){
        connect(normalEnemies[i].get(),&Enemy::dead,normalEnemyQlist[i],&TEnemy::indicateDead);
        connect(protagonist.get(),&Protagonist::posChanged,normalEnemyQlist[i],&TEnemy::checkCollide);
        connect(normalEnemyQlist[i],&TEnemy::collide,this,&TextScene::collideEnemy);
    }
    for (int i=0; i<pEnemyQlist.size(); i++) {
        connect(pEnemies[i].get(),&Enemy::dead,pEnemyQlist[i],&TEnemy::indicateDead);
        connect(protagonist.get(),&Protagonist::posChanged,pEnemyQlist[i],&TEnemy::checkCollide);
        connect(pEnemyQlist[i],&TEnemy::collide,this,&TextScene::collideEnemy);
    }
}

void TextScene::printTiles(const std::vector<std::shared_ptr<Tile>> &tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        TTile *tile;
        if(tiles[i]->getValue()>100){
            tile = new TTile(tiles[i]->getXPos(),tiles[i]->getYPos(),false);
        }else{
            tile = new TTile(tiles[i]->getXPos(),tiles[i]->getYPos(),true);
        }
        tileQlist.append(tile);
        this->addItem(tile);
    }
}

void TextScene::printProtagonist(const std::shared_ptr<Protagonist> &protagonist)
{
    protagonistView = new TProtagonist(protagonist->getXPos(),protagonist->getYPos());
    this->addItem(protagonistView);
}

void TextScene::printEnemies(const std::vector<std::shared_ptr<Enemy> > &normalEnemies, const std::vector<std::shared_ptr<PEnemy>> &pEnemies)
{
    for(unsigned int i=0;i<normalEnemies.size();i++){
        TEnemy * enemy = new TEnemy(normalEnemies[i]->getXPos(),normalEnemies[i]->getYPos(),i,false);
        normalEnemyQlist.append(enemy);
        this->addItem(enemy);
    }
    for(unsigned int i=0;i<pEnemies.size();i++){
        TEnemy * enemy = new TEnemy(pEnemies[i]->getXPos(),pEnemies[i]->getYPos(),i,true);
        pEnemyQlist.append(enemy);
        this->addItem(enemy);
    }
}

void TextScene::printHealthpacks(const std::vector<std::shared_ptr<Tile> > &healthpacks)
{
    for(unsigned int i=0;i<healthpacks.size();i++){
        THealthpack * healthpack = new THealthpack(healthpacks[i]->getXPos(),healthpacks[i]->getYPos());
        healthpackQlist.append(healthpack);
        this->addItem(healthpack);
    }
}

int TextScene::detectHealthpack()
{
    int index = -1;
    for (int i=0; i<healthpackQlist.size(); i++) {
        if(protagonistView->collidesWithItem(healthpackQlist[i],Qt::IntersectsItemShape)&&!healthpackQlist[i]->getIsEmpty()){
            index = i;
            break;
        }
    }
    return index;
}

void TextScene::redrawHealthpack(int index)
{
    healthpackQlist[index]->emptyContent();
}

void TextScene::redrawProtagonist(int xPos, int yPos)
{
    protagonistView->setPos(20*xPos,20*yPos);
}

void TextScene::collideEnemy(int i, bool isP)
{
    enemyIndex = i;
    isPEnemy = isP;
}

bool TextScene::getIsPEnemy() const
{
    return isPEnemy;
}

void TextScene::setIsPEnemy(bool value)
{
    isPEnemy = value;
}

int TextScene::getEnemyIndex() const
{
    return enemyIndex;
}

void TextScene::setEnemyIndex(int value)
{
    enemyIndex = value;
}
