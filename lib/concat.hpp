#ifndef lib__concat_hpp
#define lib__concat_hpp

#include <cinttypes>
#include <ostream>
#include <string_view>

namespace lib {
    template<typename, typename> class concat;
    // template<typename> class substr;

    template<typename T, template<typename...> typename U>
    struct is_template_of : std::false_type {};
    template<typename ...Args, template<typename...> typename U>
    struct is_template_of<U<Args...>, U> : std::true_type {};

    template<typename T>
    struct is_string_view_type : std::false_type {};
    template<>
    struct is_string_view_type<std::string_view> : std::true_type {};
    template<typename LHS, typename RHS>
    struct is_string_view_type<concat<LHS, RHS>> : std::true_type {};
    /*
    template<typename STR>
    struct is_string_view_type<substr<STR>> : std::true_type {};
    */
    template<typename T>
    constexpr bool is_string_view_type_v = is_string_view_type<T>::value;
    template<typename LHS, typename RHS>
    class concat {
        static_assert(is_string_view_type_v<LHS>, "LHS is not of type string_view nor template type concat.");
        static_assert(is_string_view_type_v<RHS>, "RHS is not of type string_view nor template type concat.");

        using size_type = uint64_t;
        LHS const &lhs;
        RHS const &rhs;

    public:
        constexpr concat(LHS const &l, RHS const &r) : lhs(l), rhs(r) {}
        constexpr LHS const &left() const { return lhs; }
        constexpr RHS const &right() const { return rhs; }
        
        static constexpr size_type npos = (size_type)(-1);

        constexpr size_type size() const noexcept { return lhs.size() + rhs.size(); }
        constexpr size_type length() const noexcept { return lhs.length() + rhs.length(); }
        constexpr bool empty() const noexcept { return lhs.empty() && rhs.empty(); }

        constexpr char const &operator[](size_type idx) const {
            if (lhs.size() > idx) {
                return lhs[idx];
            }
            else {
                return rhs[idx - lhs.size()];
            }
        }
        constexpr char const &at(size_type idx) const {
            if (lhs.size() > idx) {
                return lhs[idx];
            }
            else {
                return rhs.at(idx - lhs.size());
            }
        }
        constexpr char const &front() const {
            if (lhs.empty()) {
                return rhs.front();
            }
            else {
                return lhs.front();
            }
        }
        constexpr char const &back() const {
            if (rhs.empty()) {
                return lhs.back();
            }
            else {
                return rhs.back();
            }
        }

        friend std::ostream &operator<<(std::ostream &os, concat<LHS, RHS> const &cc) {
            os << cc.lhs << cc.rhs;
            return os;
        }
    };
}

#endif