#ifndef PLOTSCRIPT_MESSAGE_QUEUE_T_H
#define PLOTSCRIPT_MESSAGE_QUEUE_T_H 

#include "message_queue.hpp"

template <typename T>
void message_queue<T>::push(message<T> m_in)
{
    std::lock_guard<std::mutex> lock(m);
    if (std::find(ids.cbegin(), ids.cend(), m_in.id) == ids.cend()) {
        ids.push_back(m_in.id);
    }
    d.push_back(m_in);
}

template <typename T>
bool message_queue<T>::pop(std::uint64_t id, message<T> & m_out)
{
    std::lock_guard<std::mutex> lock(m);
    auto p = [id](message<T> m_test){ return (m_test.id == id); };
    auto it = d.begin();
    if (  (std::find(ids.cbegin(), ids.cend(), id) == ids.cend())
       || (it = std::find_if(d.begin(), d.end(), p), it == d.end())
       ) {
        return false;
    }
    m_out = *it;
    d.erase(it);
    return true;
}

#endif /* PLOTSCRIPT_MESSAGE_QUEUE_T_H */
