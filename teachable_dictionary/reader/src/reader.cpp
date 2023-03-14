#include "reader.hpp"

namespace my_containers {

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

std::string reader::get_word()
{
    char *temp_ptr = pointer_;
    char symb = tolower(*pointer_);
    while (('a' <= symb) && (symb <= 'z')) {
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

std::string reader::check_punct()
{
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
    if (static_cast<int>(pointer_ - data_ + 1) == size_) {
        return 0;
    }

    pointer_++;
    return 1;
}

}  // namespace my_containers
