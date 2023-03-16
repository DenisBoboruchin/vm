#include <cstring>

#include "work_with_bytes.hpp"

namespace work_with_bytes {

reader::reader(const std::string &text_path)
{
    FILE *text_stream = fopen(text_path.c_str(), "rb");
    if (!text_stream) {
        std::cout << "error reading, text path incorrect (" << text_path << ")" << std::endl;
        return;
    }

    fseek(text_stream, 0, SEEK_END);
    size_ = ftell(text_stream);
    rewind(text_stream);

    data_ = new char[size_];
    int num_readed_elem = fread(data_, sizeof(char), size_, text_stream);
    fclose(text_stream);

    if (num_readed_elem != size_) {
        std::cout << "error reading, readed " << num_readed_elem << " elems" << std::endl;
        return;
    }
    pointer_ = data_;
}

reader::~reader()
{
    delete[] data_;
}

int reader::get_int()
{
    if (empty()) {
        return {};
    }

    int number = 0;
    memcpy(&number, pointer_, sizeof(int));
    pointer_ += sizeof(int);

    return number;
}

char reader::get_char()
{
    if (empty()) {
        return {};
    }

    char number = *pointer_;
    pointer_ += sizeof(char);

    return number;
}

std::string reader::get_word()
{
    if (empty()) {
        return {};
    }

    char *temp_ptr = pointer_;
    char symb = tolower(*pointer_);
    while (('a' <= symb) && (symb <= 'z')) {
        *pointer_ = symb;
        if (!increase_pointer_()) {
            break;
        }
        symb = tolower(*pointer_);
    }
    *pointer_ = '\0';

    size_t len_word = pointer_ - temp_ptr;
    std::string word = {temp_ptr, len_word};

    if (symb == '\0') {
        if (!increase_pointer_()) {
            return word;
        }
    } else {
        *pointer_ = symb;
    }

    return word;
}

std::string reader::get_punct()
{
    if (empty()) {
        return {};
    }

    std::string punkt_str {};
    char symb = tolower(*pointer_);
    while (!(('a' <= symb) && (symb <= 'z'))) {
        punkt_str.append(1, symb);
        if (!increase_pointer_()) {
            return punkt_str;
        }

        symb = tolower(*pointer_);
    }

    return punkt_str;
}

bool reader::increase_pointer_()
{
    if (empty()) {
        return 0;
    }

    pointer_++;
    return 1;
}

bool reader::can_get_int() const
{
    return (static_cast<int>(pointer_ - data_ + sizeof(int)) >= size_ - 1) || !data_;
}

size_t reader::size() const
{
    return size_;
}

bool reader::empty() const
{
    return (static_cast<int>(pointer_ - data_) >= size_ - 1) || !data_;
}

}  // namespace work_with_bytes
