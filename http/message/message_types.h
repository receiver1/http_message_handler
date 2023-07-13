#ifndef HTTP_MESSAGE_HANDLER_MESSAGE_TYPES_H
#define HTTP_MESSAGE_HANDLER_MESSAGE_TYPES_H

#include <string>
#include <unordered_map>
#include <vector>

namespace net {
namespace http {
using headers_t = std::unordered_map<std::string, std::string>;
using headers_pair_t = std::pair<std::string, std::string>;
using body_t = std::vector<char>;

enum class type { REQUEST, RESPONSE, BOTH };
enum class method { DELETE = 0, GET, HEAD, POST, PUT };
enum class status {
  CONTINUE = 100,
  SWITCHING_PROTOCOLS,
  PROCESSING,
  OK = 200,
  CREATED,
  ACCEPTED,
  NON_AUTHORITATIVE_INFORMATION,
  NO_CONTENT,
  RESET_CONTENT,
  PARTIAL_CONTENT,
  MULTI_STATUS,
  ALREADY_REPORTED,
  IM_USED = 226,
  MULTIPLE_CHOICES = 300,
};
} // namespace http
} // namespace net

#endif HTTP_MESSAGE_HANDLER_MESSAGE_TYPES_H // HTTP_MESSAGE_HANDLER_H
