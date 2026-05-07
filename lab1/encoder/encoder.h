#ifndef ENCODER
#define ENCODER

class encoder {
private:
    unsigned char* key_;
    size_t key_len_;
public:
    //конструктор
    encoder(unsigned char const* key, size_t length);

    //конструктор копирования
    encoder(encoder const& other);

    //оператор присваивания(копирующий)
    encoder& operator=(encoder const& other) noexcept;
    void swap(encoder& other) noexcept;

    //деструктор
    ~encoder();

    //изменение ключа
    bool mutator(unsigned char const* newKey, size_t newLen);

    //основной метод кодирования
    bool encode(char const* inPath, char const* outPath, bool encrypt);

};


//конструктор
encoder::encoder(unsigned char const* key, size_t length) {

    if (key == nullptr || length == 0 || length > 256) {
        key_ = nullptr;
        key_len_ = 0;
        return;
    }

    key_ = new unsigned char[length];

    for (size_t i = 0; i < length; i++) {
        key_[i] = key[i];
    }

    key_len_ = length;

}



bool encoder::encode( char const* inPath, char const* outPath, bool encrypt) {

    //тест на эволюцию
    if (!key_) return false;
    if (inPath == nullptr || outPath == nullptr) return false;

    //файл для кодирования
    FILE* file_input = fopen(inPath, "rb");
    //закодированный файл
    FILE* file_output = fopen(outPath, "wb");

    // S: array[256] of unsigned char
    // for i from 0 to 255:
    //      S[i] = i
    // j = 0
    // for i from 0 to 255:
    //     j = (j + S[i] + key[i % key_len]) % 256
    //     swap(S[i], S[j])


    //инициализация S(реализуем KSA(Key Scheduling Alg))
    unsigned char S[256];
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key_[i % key_len_]) % 256;

        unsigned char tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
    }

    // i = 0
    // j = 0
    // while (байт p ещё есть во входном потоке):
    //     i = (i + 1) % 256
    //     j = (j + S[i]) % 256
    //     swap(S[i], S[j])
    //     K = S[ (S[i] + S[j]) % 256 ]
    //     c = p XOR K
    //     записать c в out

    //шифрование/дешифрования (реализуем PRGA(Pseudo-Random Generation Algorithm))
    const size_t BUF_SIZE = 4096;
    unsigned char buffer[BUF_SIZE];
    int i = 0;
    int j = 0;
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUF_SIZE, file_input)) > 0) {
        for (size_t k = 0; k < bytesRead; k++) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            unsigned char tmp = S[i];
            S[i] = S[j];    
            S[j] = tmp;
            unsigned char K = S[(S[i] + S[j]) % 256];
            buffer[k] ^= K;
        }

        if (fwrite(buffer, 1, bytesRead, file_output) != bytesRead) {
            fclose(file_input);
            fclose(file_output);
            return false;
        }
    }

    fclose(file_input);
    fclose(file_output);

    return true;
}

bool encoder::mutator(unsigned char const* newKey, size_t newLen) {

    if (newKey == nullptr || newLen == 0 || newLen > 256) return false;

    //буфер. При ошибке выделения памяти сваливаемся в nullptr
    unsigned char* temp = new (std::nothrow) unsigned char[newLen];
    //тест на крысу в new(возвращаем false при ошибке выделения памяти)
    if (!temp) return false;

    //копируем ключ в temp
    for (size_t i = 0; i < newLen; i++) {
        temp[i] = newKey[i];
    }

    delete[] key_;
    key_ = temp;
    key_len_ = newLen;
    return true;

}


/* ПРАВИЛО ТРЕХ */

//деструктор
encoder::~encoder() {
    delete[] key_;
}

//конструктор копирования
encoder::encoder(encoder const& other) {
    if (other.key_) {
        key_ = new unsigned char[other.key_len_];
        for (size_t i = 0; i < other.key_len_; ++i) key_[i] = other.key_[i];
        key_len_ = other.key_len_;
    }
}

//оператор присваивания
encoder& encoder::operator=(encoder const& other) noexcept {
    if (this != &other) {
        encoder tmp(other);
        swap(tmp);
    }
    return *this;
}

// метод swap
void encoder::swap(encoder& other) noexcept {
    unsigned char* tmpKey = key_; key_ = other.key_; other.key_ = tmpKey;
    size_t tmpLen = key_len_; key_len_ = other.key_len_; other.key_len_ = tmpLen;
}


#endif
