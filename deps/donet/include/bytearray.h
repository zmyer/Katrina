//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_BYTEARRAY_H
#define KATRINA_BYTEARRAY_H

#include <iostream>
#include <vector>
#include "Exendian.h"

using namespace std;
namespace donet {
    class ByteArray : std::vector<char> {
    public:
        ByteArray() = default;

        ByteArray(int32_t size) : std::vector<char>(size) {

        }

        ByteArray(const char *buffer, int32_t size) : std::vector<char>(buffer, buffer + size) {

        }

        ByteArray(const std::string &str) :
                std::vector<char>(str.size()) {
            memcpy(data(), str.c_str(), str.size());
        }

        std::string ToStdString() const {
            std::string result(this->cbegin(), this->cend());
            return result;
        }

        ByteArray &Concat(const ByteArray &buffer) {
            size_t oldSize = size();
            size_t newSize = oldSize + buffer.size();
            resize(newSize);
            memcpy(this->data() + oldSize, buffer.data(), buffer.size());
            return *this;
        }

        ByteArray operator+(const ByteArray &buffer) const {
            ByteArray dstBuffer(this->size() + buffer.size());
            memcpy(dstBuffer.data(), this->data(), this->size());
            memcpy(dstBuffer.data() + this->size(), buffer.data(), buffer.size());
            return dstBuffer;
        }
    };

    class IODevice {
    public:
        enum class SeekMode {
            SET,
            FORWARD,
            BACKEND
        };

        ~IODevice() { }
    };

    class ByteArrayReader : public IODevice {
    public:
        ByteArrayReader(const ByteArray &buffer) : _buffer(buffer), _pos(0) {

        }

        template<class T>
        int32_t Read(T *buffer, int32_t count) {
            if (_pos >= _buffer.size())
                return 0;
            int32_t sizeToRead = sizeof(T) * count;
            if (_pos + sizeToRead > _buffer.size()) {
                sizeToRead = _buffer.size() - _pos;
            }
            memcpy(buffer, _pos + _buffer.data(), sizeToRead);
            _pos += sizeToRead;
            return sizeToRead;
        }

        template<class T>
        T Read() {
            T t;
            int32_t size = Read(&t, 1);
            return t;
        }

        int16_t readInt16BE() {
            int16_t value = Read<int16_t>();
            return ConvertNetworkToHostShort(value);
        }

        int32_t readInt32BE() {
            int32_t value = Read<int32_t>();
            return ConvertNetworkToHostLong(value);
        }

        int64_t readInt64BE() {
            int64_t value = Read<int64_t>();
            return ConvertNetworkToHostLongLong(value);
        }

        ByteArray ReadData(int32_t size) {
            if (_pos >= _buffer.size())
                return 0;
            int32_t sizeToRead = size;
            if (_pos + sizeToRead >= _buffer.size()) {
                sizeToRead = _buffer.size() - _pos;
            }
            ByteArray result(sizeToRead);
            memcpy(result.data(), _buffer.data(), sizeToRead);
            _pos += sizeToRead;
            return result;
        }

        int32_t Tell() const {
            return _pos;
        }

        void seek(SeekMode mode, int32_t size) {
            int32_t dest = _pos;
            if (mode == SeekMode::SET) {
                dest = size;
            } else if (mode == SeekMode::FORWARD) {
                dest += size;
            } else if (mode == SeekMode::BACKEND) {
                dest -= size;
            }
        }

    private:
        ByteArray _buffer;
        int32_t _pos;
    };

    class ByteArrayWriter {
    public:
        ByteArrayWriter() {

        }

        template<class T>
        int32_t Write(const T *buffer, int32_t count) {
            int32_t size = sizeof(T) * count;
            ByteArray result(buffer, size);
            _buffer.Concat(result);
            return size;
        }

        template<class T>
        int32_t Write(const T &value) {
            return Write(&value, 1);
        }

        int32_t Write(const ByteArray &buffer) {
            _buffer.Concat(buffer);
            return buffer.size();
        }

        int32_t WriteInt16BE(int value) {
            int16_t beValue = ConvertHostToNetworkShort(value);
            return Write(beValue);
        }

        int32_t WriteInt32BE(int value) {
            int32_t beValue = ConvertHostToNetworkLong(value);
            return Write(beValue);
        }

        int64_t WriteInt64BE(int value) {
            int64_t beValue = ConvertHostToNetworkLongLong(value);
            return Write(beValue);
        }

        const ByteArray &GetByteArray() const {
            return _buffer;
        }

    private:
        ByteArray _buffer;
    };

}
#endif //KATRINA_BYTEARRAY_H
