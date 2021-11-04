#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class  Config{
    private:
        Config();
        std::string _read_request_ip;
        std::string _write_request_ip;
    public:
        static Config& get();

        std::string& read_request_ip();
        std::string& write_request_ip();

        const std::string& get_read_request_ip();
        const std::string& get_write_request_ip();
};

#endif