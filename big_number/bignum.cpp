#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "bignum.h"

#define BASE_MAX_LEN 4 //for base 10000 max is 9999 length 4
void List::add_node_back(MAX_INT_REP val){
    Node *temp = new Node(val);
    if(_head == nullptr){//empty
        _head = _tail = temp;
    }
    else{
        _head->prev = temp;
        temp->next = _head;
        _head = temp;
    }
    _length++;
    //Back insertion
}

void List::add_node_front(MAX_INT_REP val){
    Node *temp = new Node(val);
    if(_head == nullptr){//empty
        _head = _tail = temp;
    }
    else{
        _tail->next = temp;
        temp->prev = _tail;
        _tail = temp;
    }
    _length++;
    //Front insertion
}

void List::traverse_node(){
    Node *current = _tail;
    while(current != nullptr){
        std::cout << current->value << " ";
        current = current->next;
    }
}

big_num::big_num(const std::string& num_as_strn){
    //Create a big number from a string
    //Begin by splitting the decimal & whole parts
    auto pos = num_as_strn.find_first_of('.');

    //Build the decimal part first
    if(pos != std::string::npos){
        std::string build_dec = num_as_strn.substr(pos+1, num_as_strn.size());

        //trim trailing zeros
        auto ix = build_dec.find_last_not_of("0");
        build_dec.resize(ix + 1);
        
        //build nodes for decimal part
        for(S_LONG_TYP i = 0; i < build_dec.size(); i++){
            _num_dec.add_node_front((int)build_dec[i] - 48);
        }
    }
    else {pos = num_as_strn.size();}

    //Build the whole number part
    std::string build_whole = num_as_strn.substr(0, pos);
    if(build_whole.size() == 0){
        _num_whole.add_node_front(0);
    }
    else{
        //Check for sign
        if(build_whole[0] == '-') { sign = 1; }

        //Trim preceding zeros and negative sign
        auto ix = build_whole.find_first_not_of("0-");
        build_whole.erase(0, ix);

        //build nodes for the whole part
        for(S_LONG_TYP i = 0; i < build_whole.size(); i++){
            _num_whole.add_node_front((int)build_whole[i] - 48);
        }
    }
}

big_num& big_num::operator+=( big_num& to_add){
    //Adding the second node to the current node
    
    //Ensure the decimal nodes are equal
    while(this->_num_dec.num_length() > to_add._num_dec.num_length()){  to_add._num_dec.add_node_front(0); }
    while(this->_num_dec.num_length() < to_add._num_dec.num_length()){  this->_num_dec.add_node_front(0); }

    Node* gen_rsult = to_add._num_dec.get_tail_node();
    Node* this_cpy = this->_num_dec.get_tail_node();
    big_num result;
    int carry{};

    //start with decimal
    while(gen_rsult){ //equal size
        result._num_dec.add_node_back((this_cpy->value + gen_rsult->value + carry)%10);
        carry = (this_cpy->value + gen_rsult->value + carry)/10;
        gen_rsult = gen_rsult->prev;
        this_cpy = this_cpy->prev;
    }

    //finish with whole
    gen_rsult = to_add._num_whole.get_tail_node();
    this_cpy = this->_num_whole.get_tail_node();
    while(gen_rsult && this_cpy){
        result._num_whole.add_node_back((this_cpy->value + gen_rsult->value + carry)%10);
        carry = (this_cpy->value + gen_rsult->value + carry)/10;
        gen_rsult = gen_rsult->prev;
        this_cpy = this_cpy->prev;
    }

    while(gen_rsult){
        result._num_whole.add_node_back((gen_rsult->value + carry)%10);
        carry = (gen_rsult->value + carry)/10;
        gen_rsult = gen_rsult->prev;
    }
    
    while(this_cpy){
        result._num_whole.add_node_back((this_cpy->value + carry)%10);
        carry = (this_cpy->value + carry)/10;
        this_cpy = this_cpy->prev;
    }

    if(carry == 1)
        result._num_whole.add_node_back(1);

    *this = result;
    return *this;
}

big_num& big_num::operator-=( big_num& to_sub){
    //Ensure the nodes are equal
    while(this->_num_dec.num_length() > to_sub._num_dec.num_length()){ to_sub._num_dec.add_node_front(0); }
    while(this->_num_dec.num_length() < to_sub._num_dec.num_length()){  this->_num_dec.add_node_front(0); }

    Node* gen_rsult = to_sub._num_whole.get_start_node();
    Node* this_cpy = this->_num_whole.get_start_node();
    big_num result;

    //This sentinel value is changed only if
    //the whole parts of both numbers are equal
    int sentinel{};

    //Swap, so that '*this' is the larger value
    if(to_sub._num_whole.num_length() > this->_num_whole.num_length()){
        swap(to_sub, *this);
        result.sign = 1;
    }
    else if(to_sub._num_whole.num_length() == this->_num_whole.num_length()){
        //If they are equal, find the larger value
        while(gen_rsult && this_cpy){
            if(gen_rsult->value != this_cpy->value){
                if(gen_rsult->value > this_cpy->value){
                    swap(to_sub, *this);
                    result.sign = 1;
                }
                sentinel = 1; //only changes when != is true
                break;
            }
            gen_rsult = gen_rsult->next;
            this_cpy = this_cpy->next;
        }

        //Both whole parts are equal,
        //look at the decimal portions
        if(sentinel == 0){
            gen_rsult = to_sub._num_dec.get_start_node();
            this_cpy = this->_num_dec.get_start_node();

            while(gen_rsult && this_cpy){
                if(gen_rsult->value != this_cpy->value){
                    if(gen_rsult->value > this_cpy->value){
                        swap(to_sub, *this);
                        result.sign = 1;
                    }
                    break;
                }
                gen_rsult = gen_rsult->next;
                this_cpy = this_cpy->next;
            }
            sentinel = 2; //to mean wholes are equal
        }
    }

    gen_rsult = to_sub._num_dec.get_tail_node();
    this_cpy = this->_num_dec.get_tail_node();
    int borrow{};

    //Subtract the decimal parts
    while(this_cpy){
        this_cpy->value-=borrow; borrow = 0;
        if(this_cpy->value < gen_rsult->value) { borrow = 1; this_cpy->value+=10; }
        result._num_dec.add_node_back(abs(this_cpy->value - gen_rsult->value));
        gen_rsult = gen_rsult->prev;
        this_cpy = this_cpy->prev;
    }

    //Subtract the whole parts
    if(sentinel == 2){
        //wholes are equal, return 0
        result._num_whole.add_node_back(0);
        *this = result;
        return *this;
    }
    else{
        gen_rsult = to_sub._num_whole.get_tail_node();
        this_cpy = this->_num_whole.get_tail_node();
        while(this_cpy && gen_rsult){
            this_cpy->value-=borrow; borrow = 0;
            if(this_cpy->value < gen_rsult->value) { borrow = 1; this_cpy->value+=10; }
            result._num_whole.add_node_back(abs(this_cpy->value - gen_rsult->value));
            gen_rsult = gen_rsult->prev;
            this_cpy = this_cpy->prev;
        }

        while(this_cpy){
            this_cpy->value-=borrow; borrow = 0;
            if(this_cpy->value < 0) { borrow = 1; this_cpy->value+=10; }
            result._num_whole.add_node_back(abs(this_cpy->value));
            this_cpy = this_cpy->prev;
        }

        *this = result;
        return *this;
    }
}

big_num& big_num::operator*=( big_num& to_mul){
    //One value must be less than 18, since one of the
    //operands is to be an unsigned long.
    //If all are greater than 18 digits, use the toom_cook algorithm
    if( (this->length() < to_mul.length()) && (to_mul.length() <= 18)){
        swap(*this, to_mul);
    }
    else if(this->length() > 18){
        if(to_mul.length() > 18){
            //forward to toom_cook
            //result = toom_cook(*this, to_mul);
            //*this = result;

            //These two lines remain, until toom_cook is implemented
            std::cout << "Overflow fear. Returning this!\n";
            return *this;
        }
            swap(*this, to_mul);
    }

    //copy 'this' to unsigned long
    //hold size of new decimal
    unsigned long size_of_dec = this->_num_dec.num_length() + to_mul._num_dec.num_length();
    std::string temp;

    auto node_to_strn = [&temp](Node* tmp){
        while(tmp){
            temp.append(std::to_string(tmp->value));
            tmp = tmp->next;
        }
    };

    //both portions of 'this' are copied to the temp string
    Node* temp_node = this->_num_whole.get_start_node();
    node_to_strn(temp_node);
    temp_node = this->_num_dec.get_start_node();
    node_to_strn(temp_node);

    unsigned long long rem = 0; //hold this & reminder
    const unsigned long long hold_this = std::stoull(temp); //hold this & reminder

    temp.clear();

    //Where the multiplication happens
    //'temp' is reused to hold the final string
    auto mul_node = [&](Node* tmp){ //multiplication lambda
        while(tmp){
            temp.insert(0, std::to_string(((hold_this*tmp->value) + rem)%10));
            //((hold_this*tmp->value) + rem) may overflow
            rem = ((hold_this*tmp->value) + rem)/10;
            tmp = tmp->prev;
        }
    };

    //Decimal multiplication
    if(to_mul._num_dec.num_length() > 0){
        temp_node = to_mul._num_dec.get_tail_node();
        mul_node(temp_node);
    }

    //whole multiplication
    if(to_mul._num_whole.num_length() > 0){
        temp_node = to_mul._num_whole.get_tail_node();
        mul_node(temp_node);
        if(rem){ temp.insert(0, std::to_string(rem)); }
    }

    //if there is a decimal part, add a decimal point
    if(size_of_dec > 0){
        temp.insert(temp.size() - size_of_dec, ".");
    }

    //build the final polynomial from the 'temp' string
    big_num result(temp);
    result.sign = this->sign ^ to_mul.sign;
    *this = result;
    return *this;
}

std::ostream& operator<<(std::ostream& out_s, big_num& to_out){
    //whole
    //output take start
    Node *temp = to_out._num_whole.get_start_node();
    if(to_out.sign == 1) { out_s << "-"; }
    while(temp){
        out_s << temp->value;
        temp = temp->next;
    }

    //decimal
    temp = to_out._num_dec.get_start_node();
    if(temp) {out_s << ".";}
    while(temp){
        out_s << temp->value;
        temp = temp->next;
    }

    return out_s;
}

int main(){
    //Example usage
    big_num pi("4923397535"); // 1/31101
    big_num e("4923397535");
    std::cout << pi << "\n";
    pi*=e;
    std::cout << pi << "\n";
    return 0;
}
