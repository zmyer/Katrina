//
// Created by StevensChew on 17/1/11.
//

#ifndef KATRINA_HTTPCONTEXT_H
#define KATRINA_HTTPCONTEXT_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

namespace donet {
    typedef std::vector<std::string> StdStringList;

    class HttpContext {
    public:
    public:
        virtual ~HttpContext() { }

        const std::string &GetHeader(const std::string &name) const {
            return _headers.at(name);
        }

        void SetHeader(const std::string &name, const std::string &value) {
            _headers[name] = value;
        }

        bool HasHeader(const std::string name) const {
            return _headers.find(name) != _headers.end();
        }

        StdStringList GetHeaderNames() const;

        const std::string &GetContent() const {
            return _content;
        }

        const std::string &GetVersion() const {
            return _version;
        }

        void SetVersion(const std::string &version) {
            _version = version;
        }

        virtual void ParseStdStringList(const StdStringList &stringList);

        virtual std::string ToStdString() const;

        static HttpContext FromStdStringList(const StdStringList &stringList);

    private:
        std::string _version;
        std::map<std::string, std::string> _headers;
        std::string _content;
    };
}
#endif //KATRINA_HTTPCONTEXT_H
