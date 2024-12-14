#include <iostream>
#include <string>
#include <curl/curl.h>

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    ((std::string*)userdata)->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

void sendMessage(std::string token, std::string chat_id, std::string text) {
    CURL* curl = curl_easy_init();
    if(curl) {
        std::string url = "https://api.telegram.org/bot" + token + "/sendMessage";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        std::string post_fields = "chat_id=" + chat_id + "&text=" + text;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
        
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        
        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "Ошибка: " << curl_easy_strerror(res) << std::endl;
        }
        
        curl_easy_cleanup(curl);
    }

int main(int argc, char* argv[]) {
    curl_global_init(CURL_GLOBAL_ALL);
    
    // Замените на ваш токен и ID чата
    std::string token = "token";
    std::string chat_id = "t.me/ptosamples_Bot";
    
    sendMessage(token, chat_id, "Привет! Это тестовое сообщение.");
    
    curl_global_cleanup();
    return 0;
}
