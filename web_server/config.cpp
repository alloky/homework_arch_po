#include "config.h"



Config::Config(){
    _read_request_ip = "localhost";
    _write_request_ip = "localhost";
}

Config & Config::get(){
    static Config _instance;
    return _instance;
}

const std::string& Config::get_read_request_ip(){
    return _read_request_ip;
}

const std::string& Config::get_write_request_ip(){
    return _write_request_ip;
}

std::string& Config::read_request_ip(){
    return _read_request_ip;
}

std::string& Config::write_request_ip(){
    return _write_request_ip;
}