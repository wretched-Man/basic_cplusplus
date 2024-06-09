#pragma once
class Polynomial;
class List;
struct Node{ //singly-linked node
    int coefficient{}, degree{};
    Node *next;
    Node(int cf = 0, int dg = 0):next{nullptr}, coefficient{cf}, degree{dg}{}
    //copy constructor
    //destructor
};

class List{ //singly-linked list
public:
    List():head{nullptr}, tail{nullptr} {}
    void add_node(int, int); //adds node at the end
    void traverse_node();
    friend Polynomial add(const Polynomial&, const Polynomial&);
    friend Polynomial sub(const Polynomial&, const Polynomial&);
    friend Polynomial mul(const Polynomial&, const Polynomial&);
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);
private:
    Node *head, *tail;
};

class Polynomial{
public:
    Polynomial(const std::string&); //build list in this manner
    Polynomial() = default; //define
    friend Polynomial add(const Polynomial&, const Polynomial&);
    friend Polynomial sub(const Polynomial&, const Polynomial&);
    friend Polynomial mul(const Polynomial&, const Polynomial&);
    friend Polynomial mul_util(int, int, Node*);

//operators
    friend std::ostream& operator<<(std::ostream&, const Polynomial&); //define
private:
    List _single_link;
};
