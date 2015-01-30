#include "curl_data.h"
using std::string;


// Write all expected data in here
static string buffer;
size_t MyCurl::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void MyCurl::get_file(string city, string state,string key,char* forecast,char* filename)
{
    CURL* easyhandle = curl_easy_init();
    FILE* file = fopen(filename, "w");
    std::string s("http://api.wunderground.com/api/"+ key +"//"+forecast+"/q/"+state+"//"+city+".xml");
    curl_easy_setopt( easyhandle, CURLOPT_URL,s.c_str()  );

    curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, write_data);

    curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;
    curl_easy_perform(easyhandle);
    curl_easy_cleanup( easyhandle );





    fclose(file);
}

