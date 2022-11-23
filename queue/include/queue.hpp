
namespace my_containers 
{

template <typename T>
struct q_node
{
    T data_; 
    q_node<T>* next_ = nullptr;
};

template <typename T> 
class queue_list final
{   
public:


private:
    q_node<T>* rear = nullptr;
    q_node<T>* front = nullptr;
};

}
