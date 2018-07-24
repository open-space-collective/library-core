////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Types/String.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_Types_String__
#define __Library_Core_Types_String__

#include <Library/Core/Types/Index.hpp>
#include <Library/Core/Types/Size.hpp>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <regex>
#include <ostream>
#include <string>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace types
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Index ;
using library::core::types::Size ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      A sequence of characters
/// @note                       The current implementation (derived for std::string) is temporary, as this type of inheritance this is not recommended.

class String : public std::string
{

    public:

        using std::string::string ;

                                String                                      ( ) ;

                                String                                      (   const   std::string&                aString                                     ) ;

                                ~String                                     ( ) ;

        bool                    isEmpty                                     ( ) const ;

        bool                    isUppercase                                 ( ) const ;

        bool                    isLowercase                                 ( ) const ;

        /// @brief              Returns whether the string matches a regular expression
        ///
        /// @code
        ///                     String("abc").match(std::regex("^[a-z]{3}$")) ; // True
        /// @endcode
        ///
        /// @param              [in] aRegularExpression A regular expression
        /// @return             True if matches regular expression

        bool                    match                                       (   const   std::regex&                 aRegularExpression                          ) const ;

        Size                    getLength                                   ( ) const ;

        char                    getFirst                                    ( ) const ;

        char                    getLast                                     ( ) const ;

        String                  getHead                                     (   const   Size&                       aLength                                     ) const ;

        String                  getTail                                     (   const   Size&                       aLength                                     ) const ;

        String                  getSubstring                                (   const   Index&                      aStartPosition,
                                                                                const   Size&                       aLength                                     ) const ;

        /// @brief              Removes whitespace from both ends
        ///
        /// @return             Reference to string

        String&                 trim                                        ( ) ;

        static String           Empty                                       ( ) ;

        static String           Boolean                                     (           bool                        aBoolean                                    ) ;

        static String           Char                                        (           char                        aCharacter                                  ) ;

        static String           Replicate                                   (           char                        aCharacter,
                                                                                        Size                        aCount                                      ) ;

        static String           Replicate                                   (   const   String&                     aString,
                                                                                        Size                        aCount                                      ) ;

        /// @brief              Create formatted string
        ///
        /// @code
        ///                     String::Format("{0}, {1}!", "Hello", "World") ; // "Hello, World!"
        ///                     String::Format("Let's operate {0} {1}!", 123, "satellites") ; // "Let's operate 123 satellites!"
        /// @endcode
        ///
        /// @param              [in] aFormat A format
        /// @param              [in] anArgumentList A list of arguments
        /// @return             Formatted string

        template <typename ...Args>
        static String           Format                                      (   const   char*                       aFormat,
                                                                                        Args...                     anArgumentList                              )
        {
            return fmt::format(aFormat, anArgumentList...) ;
        }

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @ref                        https://gist.github.com/fenbf/d2cd670704b82e2ce7fd

template <typename T>
class HasToString
{

    private:

        typedef char YesType[1] ;
        typedef char NoType[2] ;

        template <typename C> static YesType& test( decltype(&C::toString) ) ;
        template <typename C> static NoType& test(...) ;

    public:

        enum { value = sizeof(test<T>(0)) == sizeof(YesType) } ;

} ;

template<typename T> 
typename std::enable_if<HasToString<T>::value, std::string>::type
CallToString (T * t)
{
    return t->toString() ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace std
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<>
struct hash<library::core::types::String>
{
    
    typedef library::core::types::String argument_type ;
    typedef std::size_t result_type ;
    
    result_type                 operator ()                                 (   const   argument_type&              aString                                     ) const
    {
        return std::hash<std::string>{}(aString) ;
    }

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////