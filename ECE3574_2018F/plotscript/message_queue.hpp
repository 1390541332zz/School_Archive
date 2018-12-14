#ifndef PLOTSCRIPT_MESSAGE_QUEUE_H
#define PLOTSCRIPT_MESSAGE_QUEUE_H 

#include <deque>
#include <mutex>
#include <algorithm>

template <typename T>
struct message {
    std::uint64_t id;
    T item;
};

template <typename T>
class message_queue {
private:
    std::deque<message<T>> d;
    std::vector<std::uint64_t> ids;
    std::mutex m;
public:
    message_queue() = default;
    ~message_queue() = default;

    void push(message<T> m);
    bool pop(std::uint64_t id, message<T> & m_out);
};

#include "message_queue.tpp"

#endif /* PLOTSCRIPT_MESSAGE_QUEUE_H */
