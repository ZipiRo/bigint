// BigNumber
// Made by Perdun Ionut (ZipiRo)_
// Started 2024.01.14

#include <iostream>
#include <cstring>

struct bint{
    int numberLength = 0;
    int digits[5000];
    bool isNegative = false;

    bool operator < (bint t) const;
    bool operator > (bint t) const;
    
    bint operator + (bint t) const;
    bint operator - (bint t) const;
    bint operator * (bint t) const;
    bint operator / (bint t) const;

    friend std::ostream & operator << (std::ostream &out, const bint &c);
    friend std::istream & operator >> (std::istream &in, const bint &c);
};

bool bint::operator < (bint t) const{
    if(this->numberLength < t.numberLength) return true;

    if(this->digits[this->numberLength] < t.digits[t.numberLength]) return true;
    
    if(this->numberLength == t.numberLength)
        for (int i = t.numberLength - 1; i >= 0; i--)
            if(this->digits[i] < t.digits[i]) return true;

    return false;
}
bool bint::operator > (bint t) const{
    if(this->numberLength > t.numberLength) return true;

    if(this->digits[this->numberLength] > t.digits[t.numberLength]) return true;
    
    if(this->numberLength == t.numberLength)
        for (int i = t.numberLength - 1; i >= 0; i--)
            if(this->digits[i] > t.digits[i]) return true;

    return false;
}

bint bint::operator - (bint t) const{
    bint r;
    memset(&r, 0, sizeof(r));

    if(this->numberLength < t.numberLength) r.numberLength = t.numberLength;
        r.numberLength = this->numberLength;
    int i = 0, aux = this->digits[0];

    while (i <= r.numberLength){
        if(t.digits[i] > aux){
            r.digits[i] = (aux + 10) - t.digits[i];
            aux = this->digits[i + 1] - 1;
        }else{
            r.digits[i] = aux - t.digits[i];
            aux = this->digits[i + 1];
        }

        i++;
    }

    while(r.numberLength > 1 && r.digits[r.numberLength-1] == 0){
        r.numberLength--;
    }

    return r;
}
bint bint::operator + (bint t) const{
    bint r;
    memset(&r, 0, sizeof(r));

    if(this->numberLength < t.numberLength) r.numberLength = t.numberLength;
        r.numberLength = this->numberLength;
    int i = 0, j = 0;

    while (i <= r.numberLength){
        r.digits[i] += this->digits[i] + t.digits[i];

        r.digits[i + 1] += r.digits[i] / 10;
        r.digits[i] %= 10; 

        i++;
    }

    while(r.numberLength > 1 && r.digits[r.numberLength-1] == 0){
        r.numberLength--;
    }

    return r;
}
bint bint::operator * (bint t) const{
    bint r;
    memset(&r, 0, sizeof(r));

    r.numberLength = this->numberLength + t.numberLength;

    for (int i = 0; i < (int)this->numberLength; i++)
        for(int j = 0; j < t.numberLength; j++)
            r.digits[i + j] += this->digits[i] * t.digits[j];
    
    for (int i = 0; i < r.numberLength; i++){
        r.digits[i + 1] += r.digits[i] / 10;
        r.digits[i] %= 10; 
    }
    
    while(r.numberLength > 1 && r.digits[r.numberLength-1] == 0){
        r.numberLength--;
    }

    return r;
}

bint bint::operator / (bint t) const{
    bint r;
    memset(&r, 0, sizeof(r));

    if(this->numberLength == 1 || t.numberLength == 1){
        if(this->digits[0] == 0 || t.digits[0] == 0) { r = {1, {0}}; }
            else if(this->digits[0] == 1) { r = {1, {0}}; }
                else if(t.digits[0] == 1){
                    r.numberLength = this->numberLength;
                    for (int i = 0; i < this->numberLength; i++)
                        r.digits[i] = this->digits[i];
                }
    }

    //TO DO: figure this out
    
    return r;
}

std::ostream & operator << (std::ostream &out, const bint &c){
    if(c.isNegative) out << '-';
    for(int i = c.numberLength - 1; i >= 0; i--)
        out << c.digits[i];
    
    return out;
}
std::istream & operator >> (std::istream &in, bint &c){
    char num[5000]; in >> num;
    
    if(num[0] == '-'){ 
        c.isNegative = true; 
        strcpy(num, num + 1); 
    }

    c.numberLength = strlen(num);

    for(int i = 0; num[i]; i++){
        char n[3];
        n[0] = num[i];
        n[1] = '\0';

        if(!isdigit(n[0]) && !c.isNegative)
            throw std::invalid_argument("NAN");

        c.digits[c.numberLength - i - 1] = atoi(n);
    }

    return in;
}