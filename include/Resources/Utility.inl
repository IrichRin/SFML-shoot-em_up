template <typename T>
inline std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}
