#pragma once
class big_num;

typedef signed long long MAX_INT_REP;
typedef signed long S_LONG_TYP;

struct Node{ //doubly-linked node
    MAX_INT_REP value{};
    Node *next, *prev;
    Node(MAX_INT_REP vl = 0) : next{nullptr}, prev{nullptr}, value{vl} {}
};

class List{ //singly-linked list
public:
    List(): _head{nullptr}, _tail{nullptr} {}
    void add_node_back(MAX_INT_REP);
    void add_node_front(MAX_INT_REP);
    void traverse_node();
    Node* get_start_node(){
        Node *temp = _head;
        return temp;
    }
    Node* get_tail_node(){
        Node *temp = _tail;
        return temp;
    }
    size_t num_length(){ return _length;}
    //friend
    friend void swap(big_num&, big_num&);
private:
    Node *_head, *_tail;
    size_t _length{};
};

class big_num{
public:
    big_num(const std::string&); //build list in this manner
    big_num() = default;
    //operators
    big_num& operator+=(big_num&);
    big_num& operator-=(big_num&);
    big_num& operator*=(big_num&);
    friend std::ostream& operator<<(std::ostream&, big_num&);
    friend void swap(big_num& a, big_num& b){
        //swap whole
        //head
        Node* temp_head = a._num_whole.get_start_node();
        a._num_whole._head = b._num_whole._head;
        b._num_whole._head = temp_head;
        //tail
        Node* temp_tail = a._num_whole.get_tail_node();
        a._num_whole._tail = b._num_whole._tail;
        b._num_whole._tail = temp_tail;
        //swap dec
        //head
        temp_head = a._num_dec.get_start_node();
        a._num_dec._head = b._num_dec._head;
        b._num_dec._head = temp_head;
        //tail
        temp_tail = a._num_dec.get_tail_node();
        a._num_dec._tail = b._num_dec._tail;
        b._num_dec._tail = temp_tail;
        //sign n len
        std::swap(a.sign, b.sign);
        //length
        std::swap(a._num_whole._length, b._num_whole._length);
        std::swap(a._num_dec._length, b._num_dec._length);
    }
    unsigned long length(){ return _num_whole.num_length() + _num_dec.num_length(); }
    size_t sign = 0; //1 means negative
private:
    List _num_whole, _num_dec;
};
