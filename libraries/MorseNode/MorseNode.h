//
// Created by schlegel11 on 17.02.17.
// Class which represents a Morsecode tree.
//

#ifndef ARDUINO_MORSENODE_H
#define ARDUINO_MORSENODE_H

enum Action {
    DIT, DAH, GAP
};

class MorseNode {

public:
    static MorseNode &getInstance() {

        static MorseNode root;
        static MorseNode *t = new MorseNode("T", DAH);
        static MorseNode *e = new MorseNode("E", DIT);

        static MorseNode *m = new MorseNode("M", DAH);
        static MorseNode *n = new MorseNode("N", DIT);
        static MorseNode *a = new MorseNode("A", DAH);
        static MorseNode *i = new MorseNode("I", DIT);

        static MorseNode *o = new MorseNode("O", DAH);
        static MorseNode *g = new MorseNode("G", DIT);
        static MorseNode *k = new MorseNode("K", DAH);
        static MorseNode *d = new MorseNode("D", DIT);
        static MorseNode *w = new MorseNode("W", DAH);
        static MorseNode *r = new MorseNode("R", DIT);
        static MorseNode *u = new MorseNode("U", DAH);
        static MorseNode *s = new MorseNode("S", DIT);

        static MorseNode *ch = new MorseNode("CH", DAH);
        static MorseNode *oe = new MorseNode("OE", DIT);
        static MorseNode *q = new MorseNode("Q", DAH);
        static MorseNode *z = new MorseNode("Z", DIT);
        static MorseNode *y = new MorseNode("Y", DAH);
        static MorseNode *c = new MorseNode("C", DIT);
        static MorseNode *x = new MorseNode("X", DAH);
        static MorseNode *b = new MorseNode("B", DIT);
        static MorseNode *j = new MorseNode("J", DAH);
        static MorseNode *p = new MorseNode("P", DIT);
        static MorseNode *ae = new MorseNode("AE", DAH);
        static MorseNode *l = new MorseNode("L", DIT);
        static MorseNode *ue = new MorseNode("UE", DAH);
        static MorseNode *f = new MorseNode("F", DIT);
        static MorseNode *v = new MorseNode("V", DAH);
        static MorseNode *h = new MorseNode("H", DIT);

        static MorseNode *one = new MorseNode("1", DAH);
        static MorseNode *two = new MorseNode("2", DAH);
        static MorseNode *three = new MorseNode("3", DAH);
        static MorseNode *four = new MorseNode("4", DAH);
        static MorseNode *five = new MorseNode("5", DIT);
        static MorseNode *six = new MorseNode("6", DIT);
        static MorseNode *seven = new MorseNode("7", DIT);
        static MorseNode *eight = new MorseNode("8", DIT);
        static MorseNode *nine = new MorseNode("9", DIT);
        static MorseNode *zero = new MorseNode("0", DAH);

        root.setRight(t);
        root.setLeft(e);

        t->setRight(m);
        t->setLeft(n);
        e->setRight(a);
        e->setLeft(i);

        m->setRight(o);
        m->setLeft(g);
        n->setRight(k);
        n->setLeft(d);
        a->setRight(w);
        a->setLeft(r);
        i->setRight(u);
        i->setLeft(s);

        o->setRight(ch);
        o->setLeft(oe);
        g->setRight(q);
        g->setLeft(z);
        k->setRight(y);
        k->setLeft(c);
        d->setRight(x);
        d->setLeft(b);
        w->setRight(j);
        w->setLeft(p);
        r->setRight(ae);
        r->setLeft(l);
        u->setRight(ue);
        u->setLeft(f);
        s->setRight(v);
        s->setLeft(h);

        j->setRight(one);
        ue->setRight(two);
        v->setRight(three);
        h->setRight(four);
        h->setLeft(five);
        b->setLeft(six);
        z->setLeft(seven);
        oe->setLeft(eight);
        ch->setLeft(nine);
        ch->setRight(zero);

        // Instantiated on first use.
        return root;
    }

    MorseNode *getLeft();

    MorseNode *getRight();

    char *getCharacter();

    Action getAction();

private:
    char *character;
    Action action;
    MorseNode *left;
    MorseNode *right;

    MorseNode() : MorseNode(0, GAP) {}

    MorseNode(char *character, Action action);

    MorseNode(MorseNode const &);

    void operator=(MorseNode const &);

    void setLeft(MorseNode *left);

    void setRight(MorseNode *right);

    void setCharacter(char *character);

    void setAction(Action action);


};


#endif //ARDUINO_MORSENODE_H
