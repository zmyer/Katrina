//
// Created by StevensChew on 17/1/12.
//

#ifndef KATRINA_HTTPREQUEST_H
#define KATRINA_HTTPREQUEST_H

#include <iostream>
#include "HttpContext.h"

using namespace std;
namespace donet {
    class HttpRequest {
    public:
        HttpRequest() { }

        void ParseStdString(const std::string &text);

        virtual void ParseStdStringList(const StdStringList &stdStringList);

        static HttpRequest FromStdString(const std::string &text);

        static HttpRequest FromStdStringList(const StdStringList &stdStringList);

        const std::string &GetMethod() const {
            return _method;
        }

        const std::string &GetPath() const {
            return _path;
        }

        void SetMethod(const std::string &method) {
            _method = method;
        }

        void SetPath(const std::string &path) {
            _path = path;
        }

    private:
        void ParseRequestLine(const std::string &requestLine);

    private:
        std::string _method;
        std::string _path;
    };
}

#endif //KATRINA_HTTPREQUEST_H
