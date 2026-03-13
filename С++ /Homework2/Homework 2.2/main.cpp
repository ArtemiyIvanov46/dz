#include <iostream>
#include <sstream>
#include <string>

class numfilterbuf : public std::streambuf {
private:
    std::istream *in;
    std::ostream *out;
    
    int cur; 
    
protected:
    virtual int overflow(int c) override {
            //честно говоря, не до конца понял, когда нам не надо возвращать EOF
            char ch = static_cast<char>(c);
                
            // запрещенные символы -> успех
            if (!isdigit(ch) && ch != ' ') {
            return static_cast<unsigned char>(ch);
            }
                
            if (!out) {
            return EOF;
            }
                
            if (out->put(ch)) {
                return static_cast<unsigned char>(ch);
            }
        
            return EOF;
        }
        virtual int uflow() override {
            if (in){
                while(true) {
                    int beb=in->get();
                    if (beb==EOF){
                        return EOF;
                    } else if ( isdigit(beb) || beb==' ') {
                        return beb;
                    }
                }
            } else {
                return EOF;
            }
        }
        
        virtual int underflow() override {
            if (in){
                int beb=in->peek();
                if (beb==EOF){
                    return EOF;
                }
                return beb;
            } else {
                return EOF;
            }
        }
    
public:
    numfilterbuf(std::istream &_in, std::ostream &_out)
        : in(&_in), out(&_out), cur(traits_type::eof())
    {}
};

int main(int argc, char **argv){
    const char str1[] = "In 4 bytes contains 32 bits";
    const char str2[] = "Unix time starts from Jan 1 1970";
    std::istringstream str(str1);
    
    numfilterbuf buf(str, std::cout); // читать из stringstream, выводить в консоль
    std::iostream numfilter(&buf); // таким образом обходимся без реализации своего наследника iostream
    
    std::string val;
    std::getline(numfilter, val);
    numfilter.clear(); // сбросить невалидное состояние после EOF в процессе чтения из stringstream
    
    std::cout << "Original: '" << str1 << "'" << std::endl;
    std::cout << "Read from numfilter: '" << val << "'" << std::endl;
    
    std::cout << "Original: '" << str2 << "'" << std::endl;
    std::cout << "Written to numfilter: '";
    numfilter << str2;
    numfilter.flush();
    std::cout << "'" << std::endl;
    
    return 0;
}

