//
// Created by schlegel11 on 17.02.17.
//

#include <stddef.h>
#include "MorseNode.h"

MorseNode::MorseNode(char *character, Action action) {
    left = NULL;
    right = NULL;
    setCharacter(character);
    setAction(action);
}

MorseNode *MorseNode::getLeft() {
    return left;
}

MorseNode *MorseNode::getRight() {
    return right;
}

char *MorseNode::getCharacter() {
    return character;
}

Action MorseNode::getAction() {
    return action;
}

void MorseNode::setLeft(MorseNode *left) {
    this->left = left;
}

void MorseNode::setRight(MorseNode *right) {
    this->right = right;
}

void MorseNode::setAction(Action action) {
    this->action = action;
}

void MorseNode::setCharacter(char *character) {
    this->character = character;
}
