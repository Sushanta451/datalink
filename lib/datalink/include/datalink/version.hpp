#ifndef DATALINK_VERSION_HPP_
#define DATALINK_VERSION_HPP_

namespace datalink {

// Returns a pointer to a static string literal rather than a std::string or
// std::string_view: the freestanding C++20 library subset does not guarantee
// <string_view>, and the core must remain buildable for bare-metal targets.
[[nodiscard]] const char* version() noexcept;

}  // namespace datalink

#endif  // DATALINK_VERSION_HPP_
