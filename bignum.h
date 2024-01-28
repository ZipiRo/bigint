#include <iostream>
#include <cstring>

class bint{
    public:
    int numberLength = 1;
    int digits[5005] = {0};
    bool negative = false;

    bool operator < (bint b) const;
    bool operator > (bint b) const;
    bool operator == (bint b) const;
    bool operator != (bint b) const;
    
    bint operator + (bint b) const;
    bint operator - (bint b) const;
    bint operator * (bint b) const;
    bint operator / (bint b) const;

    friend std::ostream & operator << (std::ostream &out, const bint &c);
    friend std::istream & operator >> (std::istream &in, const bint &c);
};
bint add(bint a, bint b);
bint subtract(bint a, bint b);
bint multiply(bint a, bint b);

bool bint::operator == (bint b) const{
    bool checker = false;
    
    if(this->numberLength != b.numberLength || b.negative || this->negative) return false;

    for(int i = 0; i < this->numberLength; i++){
        if(this->digits[i] == b.digits[i]) checker = true;
            else return false;
    }
        
    return checker;
}
bool bint::operator != (bint b) const{
    bool checker = false;
    
    if(this->numberLength != b.numberLength || b.negative || this->negative) return true;

    for(int i = 0; i < this->numberLength; i++)
        if(this->digits[i] != b.digits[i]) checker = true;
        
    return checker;
}
bool bint::operator < (bint b) const{
    if(this->negative && b.negative){
        if(this->numberLength > b.numberLength) return true;
    
        for (int i = b.numberLength - 1; i >= 0; i--)
            if(this->digits[i] > b.digits[i]) return true;
                else return false;
    }
    else if(this->negative) return true;
    else if(b.negative) return false;
    else{
        if(this->numberLength < b.numberLength) return true;
    
        for (int i = b.numberLength - 1; i >= 0; i--)
            if(this->digits[i] < b.digits[i]) return true;
                else return false;
    }

    return false;
}
bool bint::operator > (bint b) const{
    if(this->negative && b.negative){
        if(this->numberLength < b.numberLength) return true;

        for (int i = b.numberLength - 1; i >= 0; i--)
            if(this->digits[i] < b.digits[i]) return true;
                else return false;
    }
    else if(this->negative) return false;
    else if(b.negative) return true;
    else{
        if(this->numberLength > b.numberLength) return true;

        for (int i = b.numberLength - 1; i >= 0; i--)
            if(this->digits[i] > b.digits[i]) return true;
                else return false;
    }

    return false;
}

bint bint::operator - (bint b) const{
    bint a;  
    for (int i = 0; i < this->numberLength; i++) a.digits[i] = this->digits[i];
    a.numberLength = this->numberLength;
    a.negative = this->negative;

    bint r;
    if(b > a) { r = subtract(b, a); r.negative = true; }
    else if(a > b) { r = subtract(a, b); }
    
    return r;
}
bint bint::operator + (bint b) const{
    bint a;  
    for (int i = 0; i < this->numberLength; i++) a.digits[i] = this->digits[i];
    a.numberLength = this->numberLength;
    a.negative = this->negative;

    
    return add(a, b);
    
}
bint bint::operator * (bint b) const{   
    bint a; 

    a.numberLength = this->numberLength;
    for (int i = 0; i < this->numberLength; i++)
        a.digits[i] = this->digits[i];
    a.negative = this->negative;

    return multiply(a, b);
}

bint bint::operator / (bint b) const{
    bint r;
    memset(&r, 0, sizeof(r));

    if(this->negative || b.negative) r.negative = true;
        r.negative = false;

    if(this->numberLength == 1 || b.numberLength == 1){
        if(this->digits[0] == 0 || b.digits[0] == 0) { return r; }
            else if(this->digits[0] == 1) { return r; }
                else if(b.digits[0] == 1){
                    r.numberLength = this->numberLength;
                    for (int i = 0; i < this->numberLength; i++)
                        r.digits[i] = this->digits[i];
                }
    }
    
    return r;
}

std::ostream & operator << (std::ostream &out, const bint &c){
    if(c.negative) out << '-';
    for(int i = c.numberLength - 1; i >= 0; i--)
        out << c.digits[i];
    
    return out;
}
std::istream & operator >> (std::istream &in, bint &c){
    char num[5005]; in >> num; num[5001] = '\0';
    
    if(num[0] == '-'){ 
        c.negative = true; strcpy(num, num+1);
    }

    c.numberLength = strlen(num);

    for(int i = 0; num[i]; i++){
        char n[3];
        n[0] = num[i];
        n[1] = '\0';

        if(!isdigit(n[0]) && !c.negative)
            throw std::invalid_argument("NAN");

        c.digits[c.numberLength - i - 1] = atoi(n);
    }

    return in;
}

bint add(bint a, bint b){
    bint r;

    r.numberLength = a.numberLength + b.numberLength;
    int i = 0, j = 0;

    while (i <= r.numberLength){
        r.digits[i] += a.digits[i] + b.digits[i];

        r.digits[i + 1] += r.digits[i] / 10;
        r.digits[i] %= 10; 

        i++;
    }

    while(r.numberLength > 1 && r.digits[r.numberLength - 1] == 0) r.numberLength--;

    return r;
}
bint subtract(bint a, bint b){
    bint r;

    r.numberLength = a.numberLength + b.numberLength;

    int i = 0, aux = a.digits[0];
    while (i <= r.numberLength){
        if(b.digits[i] > aux){
            r.digits[i] = (aux + 10) - b.digits[i];
            aux = a.digits[i + 1] - 1;
        }else{
            r.digits[i] = aux - b.digits[i];
            aux = a.digits[i + 1];
        }

        i++;
    }

    while(r.numberLength > 1 && r.digits[r.numberLength - 1] == 0) r.numberLength--;
    return r;
}
bint multiply(bint a, bint b){
    bint r;
    memset(&r, 0, sizeof(r));

    r.numberLength = a.numberLength + b.numberLength;

    if(a.negative && b.negative) r.negative = false;
    else if(a.negative || b.negative) r.negative = true;

    for (int i = 0; i < a.numberLength; i++)
        for(int j = 0; j < b.numberLength; j++)
            r.digits[i + j] += a.digits[i] * b.digits[j];
    
    for (int i = 0; i < r.numberLength; i++){
        r.digits[i + 1] += r.digits[i] / 10;
        r.digits[i] %= 10; 
    }

    while(r.numberLength > 1 && r.digits[r.numberLength - 1] == 0) r.numberLength--;

    return r;
}