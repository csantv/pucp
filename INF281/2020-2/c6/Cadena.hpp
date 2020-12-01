#ifndef INF281_CADENA_HPP
#define INF281_CADENA_HPP


class Cadena {
public:
    Cadena();
    explicit Cadena(const char *val);
    explicit Cadena(int num);
    Cadena(const Cadena& rhs);
    ~Cadena();

    unsigned long long length() const;
    void assign(const char *val);
    void assign(const Cadena& cad);
    void getStr(char *ptr) const;

    Cadena& operator=(const char *val);
    Cadena& operator=(const Cadena &cad);
    Cadena operator+(const Cadena &rhs) const;
    bool operator==(const Cadena &rhs) const;
    bool operator>(const Cadena &rhs) const;
    bool operator<(const Cadena &rhs) const;
    bool operator>=(const Cadena &rhs) const;
    bool operator<=(const Cadena &rhs) const;

    void append(const char *val);
    void append(const Cadena &cad);
    void swap(Cadena &cad);
    void print() const;
    int compare(const char *val);
    int compare(const Cadena &cad);

private:
    char *str;
    unsigned long long len;
    unsigned long long cap;
};


#endif //INF281_CADENA_HPP
