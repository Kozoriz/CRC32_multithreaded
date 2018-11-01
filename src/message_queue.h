#pragma once

#include <mutex>
#include <queue>

template<class MessageType>
class MessageQueue
{
public:
  void AddMessage(MessageType&& message)
  {
    std::lock_guard<std::mutex> lock(m_storage_mutex);
    m_storage.push(message);
  }

  void AddMessage(MessageType& message)
  {
    std::lock_guard<std::mutex> lock(m_storage_mutex);
    m_storage.push(message);
  }

  MessageType GetMessage()
  {
    std::lock_guard<std::mutex> lock(m_storage_mutex); // TODO no need to copy block here
    MessageType b = m_storage.front();
    m_storage.pop();
    return b;
  }

  const MessageType& Front() const
  {
    std::lock_guard<std::mutex> lock(m_storage_mutex);
    return m_storage.front();
  }

  void Pop()
  {
    std::lock_guard<std::mutex> lock(m_storage_mutex);
    m_storage.pop();
  }

  bool IsEmpty() const {
    std::lock_guard<std::mutex> lock(m_storage_mutex);
    return m_storage.empty();
  }

private:
  std::queue<MessageType> m_storage;
  mutable std::mutex m_storage_mutex;
};
