# http_message_handler

It is a parser and HTTP message builder.
This project uses https://github.com/nodejs/http-parser for message parsing. I use vcpkg to connect it.

Parsing message:
```cpp
std::string request_str{R"(GET /path HTTP/1.1
Content-Length: 16
Content-Type: application/json
User-Agent: test-user-agent

{"key": "value"})"};

net::http::request request{request_str};
std::cout << request.str() << std::endl;
```

Building message from scratch:
```cpp
std::string body{R"({"key": "value"})"};

net::http::request request{};
request.version("1.1");
request.method(net::http::method::GET);
request.target("/path");
request.headers(
    net::http::headers_t{{"Content-Length", std::to_string(body.size())},
                         {"Content-Type", "applicaton/json"},
                         {"User-Agent", "test-user-agent"}});
request.body({body.begin(), body.end()});
std::cout << request.str() << std::endl;
```

You can do the same with response.
