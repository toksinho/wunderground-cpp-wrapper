
#ifndef CURL_DATA_H
#define CURL_DATA_H

#include <cstdio>
#include <iostream>
#include <string>
#include <curl/curl.h>

class MyCurl
{
public:
    static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
    static void get_file(std::string,std::string,std::string,char*,char*);
};

#endif // CURL_DATA_H
