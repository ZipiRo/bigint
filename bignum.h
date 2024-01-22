#include <iostream>
#include <cstring>

struct bint{
    int numberLength = 1;
    int digits[5005] = {0};
    bool negative = false;

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
    if(this->negative && t.negative){
        if(this->numberLength > t.numberLength) return true;

        if(this->digits[this->numberLength] > t.digits[t.numberLength]) return true;
    
        if(this->numberLength == t.numberLength)
            for (int i = t.numberLength - 1; i >= 0; i--)
                if(this->digits[i] > t.digits[i]) return true;
    }
    else if(this->negative) return true;
    else if(t.negative) return false;
    else{
        if(this->numberLength < t.numberLength) return true;

        if(this->digits[this->numberLength] < t.digits[t.numberLength]) return true;
    
        if(this->numberLength == t.numberLength)
            for (int i = t.numberLength - 1; i >= 0; i--)
                if(this->digits[i] < t.digits[i]) return true;
    }

    return false;
}
bool bint::operator > (bint t) const{
    if(this->negative && t.negative){
        if(this->numberLength < t.numberLength) return true;

        if(this->digits[this->numberLength] < t.digits[t.numberLength]) return true;
    
        if(this->numberLength == t.numberLength)
            for (int i = t.numberLength - 1; i >= 0; i--)
                if(this->digits[i] < t.digits[i]) return true;
    }
    else if(this->negative) return false;
    else if(t.negative) return true;
    else{
        if(this->numberLength > t.numberLength) return true;

        if(this->digits[this->numberLength] > t.digits[t.numberLength]) return true;
        
        if(this->numberLength == t.numberLength)
            for (int i = t.numberLength - 1; i >= 0; i--)
                if(this->digits[i] > t.digits[i]) return true;
    }

    return false;
}

bint bint::operator - (bint t) const{
    bint r;
    memset(&r, 0, sizeof(r));

    if(this->numberLength < t.numberLength) r.numberLength = t.numberLength;
        r.numberLength = this->numberLength;

    bint a;
    
    a.numberLength = this->numberLength;
    for (int i = 0; i < this->numberLength; i++)
        a.digits[i] = this->digits[i];
    a.negative = this->negative;

    if(a < t){
        int i = 0, aux = t.digits[0];
        while (i <= r.numberLength){
            if(this->digits[i] > aux){
                r.digits[i] = (aux + 10) - this->digits[i];
                aux = t.digits[i + 1] - 1;
            }else{
                r.digits[i] = aux - this->digits[i];
                aux = t.digits[i + 1];
            }

            i++;
        }

        r.negative = true;
    }else if(a > t){
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
    
    if(this->negative && t.negative) r.negative = true;

    if(this->negative && !r.negative){
        bint a;
        
        a.numberLength = this->numberLength;
        for (int i = 0; i < this->numberLength; i++)
            a.digits[i] = this->digits[i];

        t.negative = false;
        if(a < t) r = t - a;
        else if(a > t) { r = a - t; r.negative = true; }
    }else if(t.negative && !r.negative){
        bint a;
        
        a.numberLength = this->numberLength;
        for (int i = 0; i < this->numberLength; i++)
            a.digits[i] = this->digits[i];
            
        t.negative = false;
        if(a < t) { r = t - a; r.negative = true; }
        else if(a > t) r = a - t;
    }else{
        while (i <= r.numberLength){
            r.digits[i] += this->digits[i] + t.digits[i];

            r.digits[i + 1] += r.digits[i] / 10;
            r.digits[i] %= 10; 

            i++;
        }
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

    if(this->negative && t.negative) r.negative = false;
    else if(this->negative || t.negative) r.negative = true;

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

    if(this->negative || t.negative) r.negative = true;
        r.negative = false;

    if(this->numberLength == 1 || t.numberLength == 1){
        if(this->digits[0] == 0 || t.digits[0] == 0) { return r; }
            else if(this->digits[0] == 1) { return r; }
                else if(t.digits[0] == 1){
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
    char num[5005]; in >> num;
    
    if(num[0] == '-'){ 
        c.negative = true; 
        strncpy(num, num + 1, 5000); 
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