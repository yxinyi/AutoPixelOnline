#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <string.h>

using namespace std;
//muduo
class CBuffer
{
public:
    //预设前置8个字节来插入消息大小
    static const size_t g_cheap_prepend = 8;
    //预分配缓存大小
    static const size_t g_initial_size = 1024;

    explicit Buffer(size_t initialSize = g_initial_size)
        : m_buffer(g_cheap_prepend + initialSize),
        m_reader_index(g_cheap_prepend),
        m_writer_index(g_cheap_prepend)
    {
        assert(readableBytes() == 0);
        assert(writableBytes() == initialSize);
        assert(prependableBytes() == g_cheap_prepend);
    }

    // implicit copy-ctor, move-ctor, dtor and assignment are fine
    // NOTE: implicit move-ctor is added in g++ 4.6

    void swap(Buffer& rhs)
    {
        m_buffer.swap(rhs.m_buffer);
        std::swap(m_reader_index, rhs.m_reader_index);
        std::swap(m_writer_index, rhs.m_writer_index);
    }

    size_t readableBytes() const
    {
        return m_writer_index - m_reader_index;
    }

    size_t writableBytes() const
    {
        return m_buffer.size() - m_writer_index;
    }

    size_t prependableBytes() const
    {
        return m_reader_index;
    }

    const char* peek() const
    {
        return begin() + m_reader_index;
    }

    // retrieve returns void, to prevent
    // string str(retrieve(readableBytes()), readableBytes());
    // the evaluation of two functions are unspecified
    void retrieve(size_t len)
    {
        assert(len <= readableBytes());
        if (len < readableBytes())
        {
            m_reader_index += len;
        }
        else
        {
            retrieveAll();
        }
    }

    void retrieveUntil(const char* end)
    {
        assert(peek() <= end);
        assert(end <= beginWrite());
        retrieve(end - peek());
    }

    void retrieveInt64()
    {
        retrieve(sizeof(int64_t));
    }

    void retrieveInt32()
    {
        retrieve(sizeof(int32_t));
    }

    void retrieveInt16()
    {
        retrieve(sizeof(int16_t));
    }

    void retrieveInt8()
    {
        retrieve(sizeof(int8_t));
    }

    void retrieveAll()
    {
        m_reader_index = g_cheap_prepend;
        m_writer_index = g_cheap_prepend;
    }

    string retrieveAllAsString()
    {
        return retrieveAsString(readableBytes());
    }

    string retrieveAsString(size_t len)
    {
        assert(len <= readableBytes());
        string result(peek(), len);
        retrieve(len);
        return result;
    }

    string toStringPiece() const
    {
        return string(peek(), static_cast<int>(readableBytes()));
    }

    void append(const string& str)
    {
        append(str.data(), str.size());
    }

    void append(const char* /*restrict*/ data, size_t len)
    {
        ensureWritableBytes(len);
        std::copy(data, data + len, beginWrite());
        hasWritten(len);
    }

    void append(const void* /*restrict*/ data, size_t len)
    {
        append(static_cast<const char*>(data), len);
    }

    void ensureWritableBytes(size_t len)
    {
        if (writableBytes() < len)
        {
            makeSpace(len);
        }
        assert(writableBytes() >= len);
    }

    char* beginWrite()
    {
        return begin() + m_writer_index;
    }

    const char* beginWrite() const
    {
        return begin() + m_writer_index;
    }

    void hasWritten(size_t len)
    {
        assert(len <= writableBytes());
        m_writer_index += len;
    }

    void unwrite(size_t len)
    {
        assert(len <= readableBytes());
        m_writer_index -= len;
    }

    ///
    /// Append int64_t using network endian
    ///
    void appendInt64(int64_t x)
    {
        int64_t be64 = x;
        append(&be64, sizeof be64);
    }

    ///
    /// Append int32_t using network endian
    ///
    void appendInt32(int32_t x)
    {
        //int32_t be32 = sockets::hostToNetwork32(x);
        //append(&be32, sizeof be32);
        append(&x, sizeof x);
    }

    void appendInt16(int16_t x)
    {
        //int16_t be16 = sockets::hostToNetwork16(x);
        //append(&be16, sizeof be16);
        append(&x, sizeof x);
    }

    void appendInt8(int8_t x)
    {
        append(&x, sizeof x);
    }

    ///
    /// Read int64_t from network endian
    ///
    /// Require: buf->readableBytes() >= sizeof(int32_t)
    int64_t readInt64()
    {
        int64_t result = peekInt64();
        retrieveInt64();
        return result;
    }

    ///
    /// Read int32_t from network endian
    ///
    /// Require: buf->readableBytes() >= sizeof(int32_t)
    int32_t readInt32()
    {
        int32_t result = peekInt32();
        retrieveInt32();
        return result;
    }

    int16_t readInt16()
    {
        int16_t result = peekInt16();
        retrieveInt16();
        return result;
    }

    int8_t readInt8()
    {
        int8_t result = peekInt8();
        retrieveInt8();
        return result;
    }

    ///
    /// Peek int64_t from network endian
    ///
    /// Require: buf->readableBytes() >= sizeof(int64_t)
    int64_t peekInt64() const
    {
        assert(readableBytes() >= sizeof(int64_t));
        int64_t be64 = 0;
        ::memcpy(&be64, peek(), sizeof be64);
        return (be64);
    }

    ///
    /// Peek int32_t from network endian
    ///
    /// Require: buf->readableBytes() >= sizeof(int32_t)
    int32_t peekInt32() const
    {
        assert(readableBytes() >= sizeof(int32_t));
        int32_t be32 = 0;
        ::memcpy(&be32, peek(), sizeof be32);
        //return sockets::networkToHost32(be32);
        return be32;
    }

    int16_t peekInt16() const
    {
        assert(readableBytes() >= sizeof(int16_t));
        int16_t be16 = 0;
        ::memcpy(&be16, peek(), sizeof be16);
        //return sockets::networkToHost16(be16);
        return be16;
    }

    int8_t peekInt8() const
    {
        assert(readableBytes() >= sizeof(int8_t));
        int8_t x = *peek();
        return x;
    }

    ///
    /// Prepend int64_t using network endian
    ///
    void prependInt64(int64_t x)
    {
        //int64_t be64 = sockets::hostToNetwork64(x);
        //prepend(&be64, sizeof be64);
        prepend(&x, sizeof x);

    }

    ///
    /// Prepend int32_t using network endian
    ///
    void prependInt32(int32_t x)
    {
        //int32_t be32 = sockets::hostToNetwork32(x);
        //prepend(&be32, sizeof be32);
        prepend(&x, sizeof x);
    }

    void prependInt16(int16_t x)
    {
        //int16_t be16 = sockets::hostToNetwork16(x);
        //prepend(&be16, sizeof be16);
        prepend(&x, sizeof x);
    }

    void prependInt8(int8_t x)
    {
        prepend(&x, sizeof x);
    }

    void prepend(const void* /*restrict*/ data, size_t len)
    {
        assert(len <= prependableBytes());
        m_reader_index -= len;
        const char* d = static_cast<const char*>(data);
        std::copy(d, d + len, begin() + m_reader_index);
    }

    void shrink(size_t reserve)
    {
        // FIXME: use vector::shrink_to_fit() in C++ 11 if possible.
        Buffer other;
        other.ensureWritableBytes(readableBytes() + reserve);
        other.append(toStringPiece());
        swap(other);
    }

    size_t internalCapacity() const
    {
        return m_buffer.capacity();
    }

private:

    char* begin()
    {
        return &*m_buffer.begin();
    }

    const char* begin() const
    {
        return &*m_buffer.begin();
    }

    void makeSpace(size_t len)
    {
        if (writableBytes() + prependableBytes() < len + g_cheap_prepend)
        {
            // FIXME: move readable data
            m_buffer.resize(m_writer_index + len);
        }
        else
        {
            // move readable data to the front, make space inside buffer
            assert(g_cheap_prepend < m_reader_index);
            size_t readable = readableBytes();
            std::copy(begin() + m_reader_index,
                begin() + m_writer_index,
                begin() + g_cheap_prepend);
            m_reader_index = g_cheap_prepend;
            m_writer_index = m_reader_index + readable;
            assert(readable == readableBytes());
        }
    }

private:
    std::vector<char> m_buffer;
    size_t m_reader_index;
    size_t m_writer_index;

};
