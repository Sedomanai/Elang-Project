/*****************************************************************//**
 * @file   stream.h
 * @brief  For bitstreaming i.e. serializing. 
 *         Mostly replaced by cereal, used only in specific conditions 
 *         (Exporting serialized data to other languages like C# for exmaple)
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_STREAM_H
#define  EL_STREAM_H

#include <fstream>
#include <vector>
#include "define.h"

namespace el 
{
    /** @see el::vector<T> */
    template <typename T>
    using vector = std::vector<T>;
#ifndef __EL_ARRAY_
    /** @see el::array<T> */
    template<typename Ty_>
    struct array { Ty_* data; size_t size; };
#define __EL_ARRAY_
#endif

    /**
     * @brief Binary stream.
     * 
     * Wrapper for std::fstream, used only for in-and-output binary data. 
     * Semantics are a little different: save means out, load means in.
     */
    struct stream {
        //stream() {} //why was this here?..

        /**
         * @brief Set fstream for output mode.
         * 
         * Must be called before saving.
         * @param path File path name of the output file.
         * @see save(void*, sizet)
         */
        bool toSave(const char* filepath) {
            f.open(filepath, std::ios::out | std::ios::binary);
            return f.good();
        }
        /**
         * @brief Set fstream for input mode.
         *
         * Must be called before loading.
         * @param filename File path name of the input file.
         */
        bool toLoad(const char* filepath) {
            f.open(filepath, std::ios::in | std::ios::binary);
            return f.good();
        }
        /**
         * @brief Flush and close stream.
         *
         * Must be called after saving.
         * @see save(void*, sizet)
         */
        void close() {
            f.flush();
            f.close();
        }

        /**
         * @brief Output binary data.
         * 
         * Used to output a binary file. 
         * @ref toSave(const char*) must be called before saving.
         * There's no check to guarantee that behavior. 
         * 
         */
        void save(void* ptr, sizet size) {
            f.write(reinterpret_cast<const char*>(ptr), size);
        }

        /**
         * @brief Input binary data.
         * 
         * Used to input a binary file.
         * @ref toLoad(const char*) must be called before loading.
         * @warning el::stream does not guarantee matching data types nor debug the read stream.
         *              You will have to maintain and check for it yourself.
         */
        void load(void* ptr, sizet size) {
            f.read(reinterpret_cast<char*>(ptr), size);
        }

        void skip(sizet size) { f.seekp(f.tellp() + std::streampos(size)); }
        bool invalid() { return f.tellg() == -1; }
        sizet curr() { return (sizet)f.tellp(); }

        /**
         * @brief Write data.
         * Write pod struct data that is not a pointer.
         * @param t Data to write.
         * @tparam T Data type. T must be pod type and not a pointer.
         */
        template<typename T>
        std::enable_if_t<!std::is_pointer_v<T >&& std::is_pod_v<T>, el::stream&>
            operator<<(T t) {
            f.write(reinterpret_cast<const char*>(&t), sizeof(T));
            return (*this);
        }

        /**
         * @brief Write array.
         * Write custom @ref el::array<T> type.
         * @param t Data to write.
         * @tparam T Data type of the template param of @ref el::array<T>. T must be pod type and not a pointer.
         * @see el::array<T>
         */
        template<typename T>
        std::enable_if_t<!std::is_pointer_v<T >&& std::is_pod_v<T>, el::stream&>
            operator<<(array<T> a) {
            f.write(reinterpret_cast<const char*>(a.data), sizeof(T) * a.size);
            return *this;
        }

        /**
         * @brief Write a string.
         * Write a @ref el::string type, which is just an alias for @c std::string.
         * @param str String to write.
         * @see el::string
         */
        stream& operator<<(const std::string& str) {
            int32 size = (int32)str.size();
            f.write(reinterpret_cast<const char*>(&size), sizeof(int32));
            f.write(str.c_str(), size);
            return *this;
        }

        /**
         * @brief Write vector.
         * Write a @ref el::vector<T> type, which is just an alias for @c std::vector<T>.
         * @tparam T Data type of the template param of @ref el::vector<T>. T must be pod type and not a pointer.
         * @param t Vector to write.
         * @see el::vector<T>
         */
        template<typename T>
        std::enable_if_t<!std::is_pointer_v<T >&& std::is_pod_v<T>, el::stream&>
        operator<<(const vector<T>& t) {
            int32 size = (int32)t.size();
            f.write(reinterpret_cast<const char*>(&size), sizeof(int32));
            f.write(reinterpret_cast<const char*>(&t[0]), sizeof(T) * size);
            return *this;
        }

        /**
         * @brief Write recursive data for of vector.
         * Write a @ref el::vector<T> type, and all its custom data.
         * @tparam T Data type of the template param of @ref el::vector<T>. 
         *          T must be be stream writeable with its own << operator overload.
         * @param t Vector to write.
         * @see el::vector<T>
         */
        template<typename T>
        el::stream& operator<<(const vector<T>& t) {
            int32 size = (int32)t.size();
            f.write(reinterpret_cast<const char*>(&size), sizeof(int32));
            for (sizet i = 0; i < size; i++) {
                operator<<(t[i]);
            }
            return *this;
        }

        /**
         * @brief Read a string.
         * Read a @ref el::string type, which is just an alias for @c std::string.
         * @param str String to read and contain streamed data.
         * @see el::string
         */
        stream& operator>>(std::string& str) {
            int32 size;
            f.read(reinterpret_cast<char*>(&size), sizeof(int32));
            str.resize((sizet)size);
            f.read(&str[0], (std::streamsize)size);
            return *this;
        }

        /**
         * @brief Read data.
         * Read a pod struct data that is not a pointer.
         * @param t Data to read and contain streamed data.
         * @tparam T Data type. T must be pod type and not a pointer.
         */
        template<typename T>
        std::enable_if_t<!std::is_pointer_v<T >&& std::is_pod_v<T>, el::stream&>
        operator>>(T& t) {
            f.read(reinterpret_cast<char*>(&t), sizeof(T));
            return *this;
        }

        /**
         * @brief Read array.
         * Read custom @ref el::array<T> type.
         * @param t Data to read.
         * @tparam T Data type of the template param of @ref el::array<T>. T must be pod type and not a pointer.
         * @see el::array<T>
         */
        template<typename T>
        std::enable_if_t<!std::is_pointer_v<T >&& std::is_pod_v<T>, el::stream&>
        operator>>(array<T> a) {
            f.read(reinterpret_cast<char*>(a.data), sizeof(T) * a.size);
            return *this;
        }

        /**
         * @brief Read vector.
         * Read a @ref el::vector<T> type, which is just an alias for @c std::vector<T>.
         * @tparam T Data type of the template param of @ref el::vector<T>. T must be pod type and not a pointer.
         * @param t Vector to read and save streamed data.
         * @see el::vector<T>
         */
        template<typename T>
        std::enable_if_t<!std::is_pointer_v<T >&& std::is_pod_v<T>, el::stream&>
        operator>>(vector<T>& t) {
            int32 size;
            f.read(reinterpret_cast<char*>(&size), sizeof(int32));
            t.reserve((sizet)size);
            f.read(reinterpret_cast<char*>(&t[0]), sizeof(T) * (std::streamsize)size);
            t.erase(t.begin() + (std::streamsize)size, t.end());
            return *this;
        }

        /**
         * @brief Read recursive data for of vector.
         * Read a @ref el::vector<T> type, and all its custom data.
         * @tparam T Data type of the template param of @ref el::vector<T>.
         *          T must be be stream readable with its own >> operator overload.
         * @param t Vector to read and save streamed data.
         * @see el::vector<T>
         */
        template<typename T>
        el::stream& operator>>(vector<T>& t) {
            int32 size;
            f.read(reinterpret_cast<char*>(&size), sizeof(int32));
            t.reserve((sizet)size);
            for (sizet i = 0; i < size; i++) {
                auto& data = t.emplace_back();
                operator>>(data);
            }
            return *this;
        }

    private:
        std::fstream f;
    };
}
#endif