#ifndef WORK_WITH_BYTES_HPP
#define WORK_WITH_BYTES_HPP
#include <iostream>

namespace work_with_bytes {

class reader final {
public:
    explicit reader(const std::string &text_path);
    reader(const reader &other) = delete;
    reader(reader &&other) = delete;

    reader &operator=(const reader &other) = delete;
    reader &operator=(reader &&other) = delete;

    ~reader();

    std::string get_word();
    std::string get_punct();

    size_t size() const;
    bool empty() const;

private:
    bool increase_pointer_();

    char *data_ = nullptr;
    char *pointer_ = nullptr;
    int size_ = 0;
};

}  // namespace work_with_bytes

#endif
