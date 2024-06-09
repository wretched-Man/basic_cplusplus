#include <iostream>
#include "polynomial.h"
#include <string>
#include <regex>
#include <algorithm>

void List::add_node(int coef, int deg){
    Node *temp = new Node(coef, deg);
    if(head == nullptr){//empty
        head = tail = temp;
    }
    else{
        tail->next = temp;
        tail = temp;
    }
}

void List::traverse_node(){
    Node *current = head;
    while(current != nullptr){
        std::cout << current->coefficient << " " << current->degree <<"\n";
        current = current->next;
    }
}

Polynomial::Polynomial(const std::string& my_string){
    //Create a Polynomial
    std::string str = my_string;
    size_t pos = 0;
    while((pos = str.find("x^")) != std::string::npos){ str.replace(pos, 2, " "); }
    std::regex regexz(" ");
    std::vector<std::string> tokens(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
                                  std::sregex_token_iterator());
    std::vector<std::vector<int>> pairs;
    std::vector<int> temp;

    //Insert the first elements
    temp.push_back(std::stoi(tokens[0]));
    temp.push_back(std::stoi(tokens[1]));
    pairs.push_back(temp);

    for(int i = 3; i<tokens.size(); i++){
        //Insert the remaining elements
        temp.clear();
        if((int)tokens[i-1][0] < 46){ //'+' or '-'
            tokens[i-1].append(tokens[i]);
            temp.push_back(std::stoi(tokens[i-1]));
            temp.push_back(std::stoi(tokens[++i]));
            pairs.push_back(temp);
            ++i;
        }
        else{ ++i; }
    }

    //sort pairs
    std::sort(pairs.begin(), pairs.end(),
              [](std::vector<int>& a, std::vector<int>& b){ return a[1] > b[1]; } );
    //now build list
    for(auto k:pairs){ _single_link.add_node(k[0], k[1]); }
}

Polynomial add(const Polynomial& a, const Polynomial& b){
    Polynomial result;
    Node *first = a._single_link.head;
    Node *second = b._single_link.head;

    while(first && second){
        //Only add coefficients if the degrees are equal
        //Otherwise, add the larger one in directly
        if(first->degree > second->degree){
            result._single_link.add_node(first->coefficient, first->degree);
            first = first->next;
        }
        else if(first->degree < second->degree){
            result._single_link.add_node(second->coefficient, second->degree);
            second = second->next;
        }
        else{ //equal
            result._single_link.add_node((first->coefficient + second->coefficient), first->degree);
            first = first->next;
            second = second->next;
        }
    }

    //In-case one of them is shorter than the other
    while(first){
        result._single_link.add_node(first->coefficient, first->degree);
        first = first->next;
    }

    while(second){
        result._single_link.add_node(second->coefficient, second->degree);
        second = second->next;
    }
    return result;
}

Polynomial sub(const Polynomial& aa, const Polynomial& bb){
    //This we do simply by negating the coefficients of the second polynomial
    //then adding the polynomials
    Polynomial cc;
    Node *neg = bb._single_link.head;
    while(neg){
        cc._single_link.add_node((-1*neg->coefficient), neg->degree); //negate coefficient
        neg = neg->next;
    }
    return add(aa, cc);
}

std::ostream& operator<< (std::ostream& out_s, const Polynomial& a){
    Node *current = a._single_link.head;
    //In order to output, we copy the polynomial into a string
    //and add the coefficients and degrees i.e. (coeff)x^(deg)
    //We then push the string to the output
    std::string final_poly;
    while(current->next){
        if(current->coefficient != 0){ //no need of 0x^n
            final_poly.append(std::to_string(current->coefficient)).append("x^").append(std::to_string(current->degree));
            final_poly.append(" + ");
        }
        current = current->next;
    }
    final_poly.append(std::to_string(current->coefficient));
    if(current->degree != 0){
        final_poly.append("x^").append(std::to_string(current->degree));  //no need to append x^0
    }
    out_s << final_poly;
    return out_s;
}

Polynomial mul_util(int coeff, int deg, Node* m_dend){
    //A utiltiy function for the mul function
    //Node *second = m_dend._single_link.head;
    Polynomial m_util_result;
    while(m_dend){
        m_util_result._single_link.add_node(coeff * m_dend->coefficient, deg + m_dend->degree);
        m_dend = m_dend->next;
    }

    return m_util_result;
}

Polynomial mul(const Polynomial& pFirst, const Polynomial& pScnd){
    Polynomial m_result;
    Node *first = pFirst._single_link.head;
    Node *second = pScnd._single_link.head;
    while(first){
        int f_deg = first->degree;
        int f_coeff = first->coefficient;
        m_result = add(m_result, mul_util(f_coeff, f_deg, second));
        first = first->next;
    }

    return m_result;
}

int main(){
    //In a separate main file, add functionality for user input & output
    //Add functionality for division
    //Overload arithmetic operators
    //in future projects reduce the number of friends & repetitions
    Polynomial aa("455x^4 + 123x^3 + 831x^2 + 275x^1 + 469x^0");
    Polynomial ba("897x^2 + 512x^1 + 436x^0");

    std::cout << "The given polynomials are, A: " << aa << "  and B: " << ba << std::endl << std::endl;
    //std::cout << "A + B: " << add(aa, ba) << std::endl;
    //std::cout << "A - B: " << sub(aa, ba) << std::endl;
    std::cout << "A * B: " << add(aa, ba);
}
